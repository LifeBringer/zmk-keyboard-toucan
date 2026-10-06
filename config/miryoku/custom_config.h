// Miryoku configuration for the beekeeb Toucan2.
// Engine: https://github.com/manna-harbour/miryoku_zmk
//
// In the Miryoku docs options are written as MIRYOKU_OPTION=VALUE.
// In this file that becomes:  #define MIRYOKU_OPTION_VALUE
// (see https://github.com/manna-harbour/miryoku/tree/master/docs/reference)

// Base alphas: QWERTY
#define MIRYOKU_ALPHAS_QWERTY

// Tap-layer alphas: QWERTY (explicit -- the default would be Colemak-DH)
#define MIRYOKU_TAP_QWERTY

// Extra-layer alphas: Colemak-DH (the engine default would be QWERTY,
// a duplicate of Base). The Extra layer is only reached via the "Extra"
// key on the Nav / Num / Sym / Fun layers.
#define MIRYOKU_EXTRA_COLEMAKDH

// Navigation: inverted-T arrows -- Up on the top row,
// Left / Down / Right on the home row.
#define MIRYOKU_NAV_INVERTEDT

// Flipped layers: the Nav / Media / Num / Sym / Fun content sits on the
// opposite hand from stock Miryoku (inverted-T arrows on the LEFT hand).
// NOTE: the thumb clusters below are deliberately NOT flipped -- the Base
// layer uses a custom thumb mapping (ESC->Fun, SPACE->Num, TAB->Sym,
// RET->MouseVir, BSPC->Nav, DEL->Media); Extra / Tap use the original
// Miryoku arrangement (left = hold MEDIA / NAV, right = hold SYM / NUM /
// FUN), via the MIRYOKU_LAYER_BASE / EXTRA / TAP overrides.
#define MIRYOKU_LAYERS_FLIP

// Clipboard shortcuts: default set (Undo=K_UNDO, Cut=Shift+Del,
// Copy=Ctrl+Ins, Paste=Shift+Ins, Redo=K_AGAIN).
// For macOS Cmd-based shortcuts:   #define MIRYOKU_CLIPBOARD_MAC
// For Windows Ctrl+Z/X/C/V:        #define MIRYOKU_CLIPBOARD_WIN

// ---------------------------------------------------------------------------
// Layer list: stock Miryoku minus its Mouse and Button layers.
//
// The Toucan2's trackpad activates the mouse functionality while touched
// (see config/toucan.keymap), so Miryoku's keyboard-driven mouse-movement
// layer is redundant. Miryoku's Button layer is likewise removed -- its
// content (mouse buttons + clipboard + mods) is merged into the
// Toucan2's touch-activated Mouse layer instead (config/toucan.keymap).
//
// This must be defined before miryoku.dtsi is included (it is -- see
// config/toucan.keymap). Defining MIRYOKU_LAYER_LIST skips the engine's
// default 10-layer list in miryoku_babel/miryoku_layer_list.h, so the U_*
// indices below replace the engine's.
// ---------------------------------------------------------------------------
#define MIRYOKU_LAYER_LIST \
MIRYOKU_X(BASE,   "Base") \
MIRYOKU_X(EXTRA,  "Extra") \
MIRYOKU_X(TAP,    "Tap") \
MIRYOKU_X(NAV,    "Nav") \
MIRYOKU_X(MEDIA,  "Media") \
MIRYOKU_X(NUM,    "Num") \
MIRYOKU_X(SYM,    "Sym") \
MIRYOKU_X(FUN,    "Fun") \
MIRYOKU_X(MOUSEVIR, "MouseVir")

#define U_BASE   0
#define U_EXTRA  1
#define U_TAP    2
#define U_NAV    3
#define U_MEDIA  4
#define U_NUM    5
#define U_SYM    6
#define U_FUN    7
#define U_MOUSEVIR 8

// The touch-activated Mouse layer is a plain ZMK layer (not a Miryoku
// layer), defined in config/toucan.keymap after miryoku.dtsi -- it lands at
// keymap index 9, right after the 9 Miryoku layers above.
#define U_MOUSE 9

// U_BUTTON aliases the Mouse layer: the Extra layer holds Z / / for the
// Button layer (U_LT(U_BUTTON, ...)), as stock Miryoku does. Both resolve
// to the touch Mouse layer, which carries the old Button layer's content.
// (Also keeps the MIRYOKU_KLUDGE_* combos, which reference U_MOUSE,
// compiling if ever enabled.)
#define U_BUTTON U_MOUSE

// Right-hand home-row mods use the u_mt_r behavior (balanced, opposite-
// hand hold trigger), defined in config/toucan.keymap. Left-hand mods
// use Miryoku's stock U_MT (which now points at our overridden u_mt).
#define U_MT_R(MOD, TAP) &u_mt_r MOD TAP

// Output toggle (USB <-> BLE) on the Media layer, in the slot where stock
// Miryoku has the external-power toggle (U_EP_TOG). The engine has no
// U_OUT_TOG of its own.
#define U_OUT_TOG &out OUT_TOG

// ---------------------------------------------------------------------------
// Base layer: stock FLIP alphas with a CUSTOM thumb arrangement.
//
// Taps stay ESC / SPACE / TAB | RET / BSPC / DEL, but the holds are
// reassigned:
//   ESC -> Fun,  SPACE -> Num,  TAB -> Sym,
//   RET -> MouseVir,  BSPC -> Nav,  DEL -> Media.
//
// (TAB is tap-only for the touch Mouse layer -- that layer belongs to the
// trackpad -- but TAB hold for Sym is fine.)
//
// Z and / are plain keys here: stock Miryoku holds them for the Button
// layer, but on Base the Mouse layer belongs to the trackpad alone.
// (Extra keeps the stock Z / / holds.)
//
// Outer column (per-layer, via the mapping macro): left = VolUp / VolDn /
// Mute top-to-bottom, right = BriUp / BriDn / AltGr top-to-bottom. All
// other layers leave the outer column blank (U_NA).
// ---------------------------------------------------------------------------
#define MIRYOKU_LAYER_BASE \
&kp Q,             &kp W,             &kp E,             &kp R,             &kp T,             &kp Y,             &kp U,             &kp I,             &kp O,             &kp P,             \
U_MT(LGUI, A),     U_MT(LALT, S),     U_MT(LCTRL, D),    U_MT(LSHFT, F),    &kp G,             &kp H,             U_MT_R(RSHFT, J),  U_MT_R(RCTRL, K),  U_MT_R(RALT, L),   U_MT_R(RGUI, SQT), \
&kp Z,             U_MT(RALT, X),    &kp C,             &kp V,             &kp B,             &kp N,             &kp M,             &kp COMMA,         &kp DOT,           &kp SLASH,         \
U_NP,              U_NP,              U_LT(U_FUN, ESC),  U_LT(U_NUM, SPACE),U_LT(U_SYM, TAB),  U_LT(U_MOUSEVIR, RET),U_LT(U_NAV, BSPC),U_LT(U_MEDIA, DEL),U_NP,             U_NP,              \
&kp C_VOL_UP,     &kp C_VOL_DN,     &kp C_MUTE,        &kp C_BRI_UP,      &kp C_BRI_DN,      &kp RALT

// ---------------------------------------------------------------------------
// Extra / Tap layers: stock FLIP alphas with the ORIGINAL Miryoku thumb
// arrangement (not the flipped one).
//
// Original thumbs: left = hold MEDIA (ESC) / hold NAV (SPACE) with TAB
// tap-only, right = hold SYM (RET) / hold NUM (BSPC) / hold FUN (DEL).
// (Only the Base thumb cluster uses the custom mapping above.)
// ---------------------------------------------------------------------------
#define MIRYOKU_LAYER_EXTRA \
&kp Q,             &kp W,             &kp F,             &kp P,             &kp B,             &kp J,             &kp L,             &kp U,             &kp Y,             &kp SQT,           \
U_MT(LGUI, A),     U_MT(LALT, R),     U_MT(LCTRL, S),    U_MT(LSHFT, T),    &kp G,             &kp M,             U_MT_R(RSHFT, N),  U_MT_R(RCTRL, E),  U_MT_R(RALT, I),   U_MT_R(RGUI, O),   \
U_LT(U_BUTTON, Z), U_MT(RALT, X),    &kp C,             &kp D,             &kp V,             &kp K,             &kp H,             &kp COMMA,         &kp DOT,           U_LT(U_BUTTON, SLASH),\
U_NP,              U_NP,              U_LT(U_MEDIA, ESC),U_LT(U_NAV, SPACE),&kp TAB,            U_LT(U_SYM, RET),  U_LT(U_NUM, BSPC), U_LT(U_FUN, DEL),  U_NP,              U_NP,              \
U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA

#define MIRYOKU_LAYER_TAP \
&kp Q,             &kp W,             &kp E,             &kp R,             &kp T,             &kp Y,             &kp U,             &kp I,             &kp O,             &kp P,             \
&kp A,             &kp S,             &kp D,             &kp F,             &kp G,             &kp H,             &kp J,             &kp K,             &kp L,             &kp SQT,           \
&kp Z,             &kp X,             &kp C,             &kp V,             &kp B,             &kp N,             &kp M,             &kp COMMA,         &kp DOT,           &kp SLASH,         \
U_NP,              U_NP,              &kp ESC,           &kp SPACE,         &kp TAB,           &kp RET,           &kp BSPC,          &kp DEL,           U_NP,              U_NP,              \
U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA

// ---------------------------------------------------------------------------
// Nav / Media layers: stock FLIP content, but the thumb rows are overridden
// to mirror the custom Base thumb positions.
//
// Stock FLIP puts the thumb keys on the LEFT (K32-K34), matching the stock
// FLIP Base where the left thumbs are DEL/BSPC/RET. But the custom Base
// above has left = ESC/SPACE/TAB and right = RET/BSPC/DEL, so the stock
// thumb rows land on the wrong side. Here the left thumbs mirror the Base
// left (ESC/SPACE/TAB taps); the right thumbs carry the layer's dedicated
// keys (or the Base right taps for Nav).
//
// Identical to MIRYOKU_ALTERNATIVES_NAV_INVERTEDT_FLIP /
// MIRYOKU_ALTERNATIVES_MEDIA_INVERTEDT_FLIP at the pinned engine commit
// otherwise (the engine selects the INVERTEDT media variant whenever
// MIRYOKU_NAV_INVERTEDT is defined).
// ---------------------------------------------------------------------------
#define MIRYOKU_LAYER_NAV \
&kp PG_UP,         &kp HOME,          &kp UP,            &kp END,           &kp INS,           U_NA,              &u_to_U_BASE,      &u_to_U_EXTRA,     &u_to_U_TAP,       U_NA,            \
&kp PG_DN,         &kp LEFT,          &kp DOWN,          &kp RIGHT,         &u_caps_word,      U_NA,              &kp RSHFT,         &kp RCTRL,         &kp RALT,          &kp RGUI,          \
U_UND,             U_CUT,             U_CPY,             U_PST,             U_RDO,             U_NA,              &u_to_U_NAV,       &u_to_U_NUM,       U_NA,              U_NA,              \
U_NP,              U_NP,              &kp ESC,           &kp SPACE,         &kp TAB,           U_NA,              &kp BSPC,          U_NA,              U_NP,              U_NP,              \
U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA

#define MIRYOKU_LAYER_MEDIA \
U_RGB_HUI,         U_RGB_SAI,         &kp C_VOL_UP,      U_RGB_BRI,         U_RGB_TOG,         U_NA,              &u_to_U_BASE,      &u_to_U_EXTRA,     &u_to_U_TAP,       U_NA,            \
U_RGB_EFF,         &kp C_PREV,        &kp C_VOL_DN,      &kp C_NEXT,        U_OUT_TOG,         U_NA,              &kp RSHFT,         &kp RCTRL,         &kp RALT,          &kp RGUI,          \
&u_bt_sel_0,       &u_bt_sel_1,       &u_bt_sel_2,       &u_bt_sel_3,       &u_bt_sel_4,       U_NA,              &u_to_U_MEDIA,     &u_to_U_FUN,       U_NA,              U_NA,              \
U_NP,              U_NP,              &kp C_MUTE,        &kp C_PP,          &kp C_STOP,        U_NP,              U_NP,              U_LT(U_MEDIA, DEL),U_NP,              U_NP,              \
&studio_unlock,   U_NA,              &bt BT_CLR,        U_NA,              U_NA,              U_NA

// ---------------------------------------------------------------------------
// MouseVir layer: Miryoku's virtual-mouse layer (mouse movement + scroll
// wheel + buttons), in the FLIP + INVERTEDT arrangement the engine would
// select for this config.
//
// Reached by holding RET on the Base layer (U_LT(U_MOUSEVIR, RET)). This
// is the keyboard-driven mouse; the touch-activated Mouse layer
// (U_MOUSE, keymap index 9) is separate -- buttons + clipboard + mods
// while the trackpad is touched.
//
// Identical to MIRYOKU_ALTERNATIVES_MOUSE_INVERTEDT_FLIP at the pinned
// engine commit, except the thumb row mirrors the custom Base layout:
// left = ESC/SPACE/TAB taps, right = mouse buttons (stock had the buttons
// on the left). The &u_to_U_MOUSE key is the double-tap guard defined in
// config/toucan.keymap, targeting the touch Mouse layer (U_MOUSE).
//
// MouseVir is not an engine layer, so miryoku_layer_selection.h never
// defines a board mapping for it -- point it at the Toucan2 mapping here.
// ---------------------------------------------------------------------------
#define MIRYOKU_LAYERMAPPING_MOUSEVIR MIRYOKU_MAPPING

#define MIRYOKU_LAYER_MOUSEVIR \
U_WH_U,            U_WH_L,            U_MS_U,            U_WH_R,            U_NU,              U_NA,              &u_to_U_BASE,      &u_to_U_EXTRA,     &u_to_U_TAP,       U_NA,            \
U_WH_D,            U_MS_L,            U_MS_D,            U_MS_R,            U_NU,              U_NA,              &kp RSHFT,         &kp RCTRL,         &kp RALT,          &kp RGUI,          \
U_UND,             U_CUT,             U_CPY,             U_PST,             U_RDO,             U_NA,              &u_to_U_MOUSE,     &u_to_U_SYM,       U_NA,              U_NA,              \
U_NP,              U_NP,              U_BTN3,            U_BTN1,            U_BTN2,            U_LT(U_MOUSEVIR, RET),U_NA,           U_NA,              U_NP,              U_NP,              \
U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA
// ---------------------------------------------------------------------------
// Fun layer: F10 and F12 swapped.
// Stock Miryoku (FLIP) puts F12 top-right and F10 bottom-right of the F-key
// block; here they are swapped so the F10/F11/F12 column reads
// top-to-bottom. Identical to MIRYOKU_ALTERNATIVES_FUN_FLIP at the pinned
// engine commit otherwise.
// ---------------------------------------------------------------------------
#define MIRYOKU_LAYER_FUN \
U_NA,            &u_to_U_TAP,       &u_to_U_EXTRA,     &u_to_U_BASE,      U_NA,              &kp PSCRN,         &kp F7,            &kp F8,            &kp F9,            &kp F10,           \
&kp LGUI,          &kp LALT,          &kp LCTRL,         &kp LSHFT,         U_NA,              &kp SLCK,          &kp F4,            &kp F5,            &kp F6,            &kp F11,           \
U_NA,              &kp RALT,          &u_to_U_MEDIA,     &u_to_U_FUN,       U_NA,              &kp PAUSE_BREAK,   &kp F1,            &kp F2,            &kp F3,            &kp F12,           \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              &kp TAB,           &kp SPACE,         &kp K_APP,         U_NP,              U_NP,              \
U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA

// ---------------------------------------------------------------------------
// Num / Sym layers: stock FLIP content, plus 6 blank outer-column slots.
//
// Every layer macro must expand to 46 bindings (the 40 stock slots plus
// the 6 per-layer outer keys the mapping macro now takes). The engine
// would otherwise define these from MIRYOKU_ALTERNATIVES_NUM_FLIP /
// MIRYOKU_ALTERNATIVES_SYM_FLIP; defining them here first takes
// precedence (miryoku_layer_selection.h guards with !defined).
// ---------------------------------------------------------------------------
#define MIRYOKU_LAYER_NUM MIRYOKU_ALTERNATIVES_NUM_FLIP, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA
#define MIRYOKU_LAYER_SYM MIRYOKU_ALTERNATIVES_SYM_FLIP, U_NA, U_NA, U_NA, U_NA, U_NA, U_NA
