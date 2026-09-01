#pragma once

#include <lvgl.h>
#include "util.h"

struct battery_peripheral_status_state {
    uint8_t level;
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
    bool usb_present;
#endif
};

void draw_battery_peripheral_status(lv_obj_t *canvas, const struct status_state *state);

/*
 * Split-link heartbeat. Call from the central whenever it hears from the
 * peripheral at the *application* layer -- a battery report, a key event.
 * The BLE link staying up is not evidence that the right half is alive, so
 * only application traffic counts.
 */
void note_peripheral_heard(void);

/*
 * Left-half (local) activity. Needed to tell "the right half is wedged" apart
 * from "nobody is typing" -- an idle keyboard is silent on both halves, so
 * peripheral silence only means something while the local half is in use.
 */
void note_local_activity(void);
