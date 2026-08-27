#include <zephyr/kernel.h>
#include <stdio.h>

#include "battery_peripheral.h"
#include "../assets/custom_fonts.h"

/*
 * Split-link heartbeat.
 *
 * draw_level_peripheral() below paints an icon for any level > 1 and paints
 * nothing otherwise -- so once the right half stopped reporting, the last
 * reading simply latched on screen forever. Nothing on this display ever
 * reflected split-link state, which is why "the display shows the right half
 * as connected" was never evidence of anything.
 *
 * These timestamps make it honest: they record when the central last heard
 * from the right half, and the age is rendered on screen.
 *
 * uint32_t ms rather than the int64_t k_uptime_get() returns: an aligned
 * 32-bit access is atomic on Cortex-M, so the event-manager context can write
 * this while the display work queue reads it without a lock. Unsigned
 * subtraction stays correct across the ~49-day wrap.
 */
static uint32_t last_heard_ms;
static uint32_t last_local_ms;
static bool ever_heard;

/*
 * Silence alone cannot condemn the right half. ZMK raises the battery event only
 * when the percentage actually changes (app/src/battery.c), so the "slow floor"
 * feed can legitimately go quiet for a very long time, and an idle keyboard is
 * silent on both halves by definition.
 *
 * So the icon is only suppressed on corroborated evidence: the left half was used
 * just now, and the right half still has not said anything for far longer than any
 * real typing gap. During normal use you cannot go 30 s of active typing without
 * touching a right-hand key -- H, J, K, L, N, M, the arrows, Backspace and Enter
 * all live over there.
 *
 * A false positive is cheap and self-correcting: the icon returns on the next
 * right-hand keypress, and the age counter below never lies either way.
 */
#define PERIPHERAL_STALE_AFTER_S 30
#define LOCAL_ACTIVE_WITHIN_S    10

void note_peripheral_heard(void) {
    last_heard_ms = (uint32_t)k_uptime_get();
    ever_heard = true;
}

void note_local_activity(void) { last_local_ms = (uint32_t)k_uptime_get(); }

static uint32_t peripheral_silent_seconds(void) {
    return ((uint32_t)k_uptime_get() - last_heard_ms) / 1000U;
}

static bool peripheral_looks_dead(void) {
    if (!ever_heard) {
        return true;
    }

    uint32_t local_age_s = ((uint32_t)k_uptime_get() - last_local_ms) / 1000U;

    return peripheral_silent_seconds() >= PERIPHERAL_STALE_AFTER_S &&
           local_age_s <= LOCAL_ACTIVE_WITHIN_S;
}

LV_IMG_DECLARE(bolt);
LV_IMG_DECLARE(r_battery_100);
LV_IMG_DECLARE(r_battery_90);
LV_IMG_DECLARE(r_battery_75);
LV_IMG_DECLARE(r_battery_50);
LV_IMG_DECLARE(r_battery_25);
LV_IMG_DECLARE(r_battery_10);


static void draw_level_peripheral(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_img_dsc_t img_dsc_r;
    lv_draw_img_dsc_init(&img_dsc_r);

    uint8_t level = state->battery_p;
    if (level > 90) {
        lv_canvas_draw_img(canvas, 80, 10, &r_battery_100, &img_dsc_r);
    } else if (level > 75) {
        lv_canvas_draw_img(canvas, 80, 10, &r_battery_90, &img_dsc_r);
    } else if (level > 50) {
        lv_canvas_draw_img(canvas, 80, 10, &r_battery_75, &img_dsc_r);
    } else if (level > 25) {
        lv_canvas_draw_img(canvas, 80, 10, &r_battery_50, &img_dsc_r);
    } else if (level > 10) {
        lv_canvas_draw_img(canvas, 80, 10, &r_battery_25, &img_dsc_r);
    } else if (level > 1) {
        lv_canvas_draw_img(canvas, 80, 10, &r_battery_10, &img_dsc_r);
    }
}

/*
 * Seconds since the right half last said anything, drawn in the free band
 * between the battery row (y 10..27) and the layer name (y 70).
 *
 * In normal use this sits at 0-2 s and resets on every right-hand keypress.
 * When the right half wedges it climbs and keeps climbing no matter what you
 * press -- that divergence is the whole diagnostic. It is also honest while
 * idle: the counter rises because the right half genuinely has not spoken.
 */
static void draw_peripheral_age(lv_obj_t *canvas) {
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &quinquefive_8, LV_TEXT_ALIGN_CENTER);

    char text[12];
    if (!ever_heard) {
        // Never heard from it since boot -- distinct from "heard, then lost".
        snprintf(text, sizeof(text), "R --");
    } else {
        uint32_t secs = peripheral_silent_seconds();
        if (secs < 100) {
            snprintf(text, sizeof(text), "R %uS", (unsigned int)secs);
        } else if (secs < 100 * 60) {
            snprintf(text, sizeof(text), "R %uM", (unsigned int)(secs / 60U));
        } else {
            snprintf(text, sizeof(text), "R 99M+");
        }
    }

    lv_canvas_draw_text(canvas, 0, 32, SCREEN_WIDTH, &label_dsc, text);
}

void draw_battery_peripheral_status(lv_obj_t *canvas, const struct status_state *state) {
    // Only claim the right half is present if the evidence says it still is.
    if (!peripheral_looks_dead()) {
        draw_level_peripheral(canvas, state);
    }

    draw_peripheral_age(canvas);
}
