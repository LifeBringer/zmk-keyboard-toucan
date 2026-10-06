// Miryoku layout mapping for the beekeeb Toucan2 (42 keys).
// https://github.com/beekeeb/zmk-keyboard-toucan2
//
// The Toucan2 is 3 rows x 6 columns + 3 thumb keys per hand (42 keys).
// Miryoku's 36-key core uses the inner 5 columns and all 3 thumb keys.
// The outer column on each hand is parameterized per layer via the six
// trailing arguments (OL0-OL2 = left outer column, rows 0-2 top to
// bottom; OR0-OR2 = right outer column, rows 0-2 top to bottom), so each
// layer macro supplies 46 bindings: the stock 40 plus the 6 outer keys.
// Layers that leave them blank pass U_NA.

#if !defined (MIRYOKU_LAYOUTMAPPING_TOUCAN2)

#define MIRYOKU_LAYOUTMAPPING_TOUCAN2( \
     K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,      K35, K36, K37, N38, N39, \
     OL0, OL1, OL2,                OR0, OR1, OR2 \
) \
OL0  K00  K01  K02  K03  K04       K05  K06  K07  K08  K09  OR0 \
OL1  K10  K11  K12  K13  K14       K15  K16  K17  K18  K19  OR1 \
OL2  K20  K21  K22  K23  K24       K25  K26  K27  K28  K29  OR2 \
               K32  K33  K34       K35  K36  K37

#endif

#define MIRYOKU_MAPPING MIRYOKU_LAYOUTMAPPING_TOUCAN2
