#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

uint8_t text[DISPLAY_ROWS][DISPLAY_WIDTH];
const uint8_t const font[128][CHAR_WIDTH] = {
	{0, 0, 0, 0, 0, 0, 0}, // Null
	{0, 0, 0, 0, 0, 0, 0}, // SOH
	{0, 0, 0, 0, 0, 0, 0}, // STX
	{0, 0, 0, 0, 0, 0, 0}, // ETX
	{0, 0, 0, 0, 0, 0, 0}, // EOT
	{0, 0, 0, 0, 0, 0, 0}, // ENQ
	{0, 0, 0, 0, 0, 0, 0}, // ACK
	{0, 0, 0, 0, 0, 0, 0}, // BEL
	{0, 0, 0, 0, 0, 0, 0}, // BS
	{0, 0, 0, 0, 0, 0, 0}, // TAB
	{0, 0, 0, 0, 0, 0, 0}, // LF
	{0, 0, 0, 0, 0, 0, 0}, // VT
	{0, 0, 0, 0, 0, 0, 0}, // FF
	{0, 0, 0, 0, 0, 0, 0}, // CR
	{0, 0, 0, 0, 0, 0, 0}, // SO
	{0, 0, 0, 0, 0, 0, 0}, // SI
	{0, 0, 0, 0, 0, 0, 0}, // DLE
	{0, 0, 0, 0, 0, 0, 0}, // DC1
	{0, 0, 0, 0, 0, 0, 0}, // DC2
	{0, 0, 0, 0, 0, 0, 0}, // DC3
	{0, 0, 0, 0, 0, 0, 0}, // DC4
	{0, 0, 0, 0, 0, 0, 0}, // NAK
	{0, 0, 0, 0, 0, 0, 0}, // SYN
	{0, 0, 0, 0, 0, 0, 0}, // ETB
	{0, 0, 0, 0, 0, 0, 0}, // CAN
	{0, 0, 0, 0, 0, 0, 0}, // EM
	{0, 0, 0, 0, 0, 0, 0}, // SUB
	{0, 0, 0, 0, 0, 0, 0}, // ENC
	{0, 0, 0, 0, 0, 0, 0}, // FS
	{0, 0, 0, 0, 0, 0, 0}, // GS
	{0, 0, 0, 0, 0, 0, 0}, // RS
	{0, 0, 0, 0, 0, 0, 0}, // US
	{0, 0, 0, 0, 0, 0, 0}, // Space
	{94, 0, 0}, // !
	{4, 3, 4, 3, 0, 0}, // "
	{36, 126, 36, 36, 126, 36, 0}, // #
	{36, 74, 255, 82, 36, 0, 0}, // $
	{70, 38, 16, 8, 100, 98, 0}, // %
	{52, 74, 74, 52, 32, 80, 0}, // &
	{4, 3, 0, 0}, // '
	{126, 129, 0, 0}, // (
	{129, 126, 0, 0}, // )
	{42, 28, 62, 28, 42, 0, 0}, // *
	{8, 8, 62, 8, 8, 0, 0}, // +
	{128, 96, 0, 0}, // ,
	{8, 8, 8, 8, 8, 0, 0}, // -
	{96, 0, 0, }, // .
	{64, 32, 16, 8, 4, 2, 0}, // /
	{62, 65, 73, 65, 62, 0, 0}, // 0
	{66, 127, 64, 0, 0}, // 1
	{98, 81, 73, 70, 0}, // 2
	{34, 73, 73, 54, 0, 0}, // 3 
	{14, 8, 127, 8, 0, 0}, // 4
	{35, 69, 69, 57, 0, 0}, // 5
	{62, 73, 73, 50, 0}, // 6
	{1, 97, 25, 7, 0, 0}, // 7
	{54, 73, 73, 54, 0, 0}, // 8
	{6, 9, 9, 126, 0, 0}, // 9
	{102, 0, 0}, // :
	{128, 102, 0, 0}, // ;
	{8, 20, 34, 65, 0, 0}, // <
	{20, 20, 20, 20, 0}, // =
	{65, 34, 20, 8, 0, 0}, // >
	{2, 1, 81, 9, 6, 0, 0}, // ?
	{28, 34, 89, 89, 82, 12, 0}, // @
	{126, 9, 9, 126, 0, 0}, // A
	{127, 73, 73, 54, 0, 0}, // B
	{62, 65, 65, 34, 0, 0}, // C
	{127, 65, 65, 62, 0, 0}, // D
	{127, 73, 73, 65, 0, 0}, // E
	{127, 9, 9, 1, 0, 0}, // F
	{62, 65, 81, 50, 0}, // G
	{127, 8, 8, 127, 0, 0}, // H
	{65, 127, 65, 0, 0}, // I
	{32, 64, 64, 63, 0, 0}, // J
	{127, 8, 20, 99, 0, 0}, // K
	{127, 64, 64, 64, 0, 0}, // L
	{127, 2, 4, 2, 127, 0, 0}, // M
	{127, 6, 8, 48, 127, 0, 0}, // N
	{62, 65, 65, 62, 0, 0}, // O
	{127, 9, 9, 6, 0, 0}, // P
	{62, 65, 97, 126, 64, 0}, // Q
	{127, 9, 9, 118, 0, 0}, // R
	{38, 73, 73, 50, 0}, // S
	{1, 1, 127, 1, 1, 0, 0}, // T
	{63, 64, 64, 63, 0, 0}, // U 
	{31, 32, 64, 32, 31, 0, 0}, // V
	{63, 64, 48, 64, 63, 0, 0}, // W
	{119, 8, 8, 119, 0, 0}, // X
	{3, 4, 120, 4, 3, 0, 0}, // Y
	{113, 73, 73, 71, 0, 0}, // Z
	{127, 65, 65, 0, 0}, // [
	{2, 4, 8, 16, 32, 64, 0}, // backslash
	{65, 65, 127, 0, 0}, // ]
	{4, 2, 1, 2, 4, 0, 0}, // ^
	{64, 64, 64, 64, 64, 64, 0}, // _
	{1, 2, 4, 0, 0}, // `
	{48, 72, 40, 120, 0}, // a
	{127, 72, 72, 48, 0, 0}, // b 
	{48, 72, 72, 0, 0}, // c
	{48, 72, 72, 127, 0, 0}, // d
	{48, 88, 88, 16, 0, 0}, // e
	{126, 9, 1, 2, 0, 0}, // f
	{80, 152, 152, 112, 0, 0}, // g
	{127, 8, 8, 112, 0, 0}, // h 
	{122, 0, 0}, // i
	{64, 128, 128, 122, 0, 0}, // j
	{127, 16, 40, 72, 0, 0}, // k
	{127, 0, 0}, // l
	{120, 8, 16, 8, 112, 0, 0}, // m
	{120, 8, 8, 112, 0, 0}, // n
	{48, 72, 72, 48, 0, 0}, // o
	{248, 40, 40, 16, 0, 0}, // p
	{16, 40, 40, 248, 0, 0}, // q
	{112, 8, 8, 16, 0, 0}, // r
	{72, 84, 84, 36, 0, 0}, // s
	{8, 60, 72, 32, 0, 0}, // t
	{56, 64, 32, 120, 0}, // u
	{56, 64, 56, 0, 0}, // v
	{56, 64, 32, 64, 56, 0, 0}, // w
	{72, 48, 48, 72, 0, 0}, // x
	{24, 160, 160, 120, 0}, // y
	{100, 84, 84, 76, 0, 0}, // z
	{8, 28, 34, 65, 0, 0}, // {
	{255, 0, 0, 0, 0, 0}, // |
	{65, 34, 28, 8, 0, 0}, // }
	{4, 2, 4, 2, 0, 0}, // ~
	{120, 68, 66, 68, 120, 0} // Delete
};

// Image for lever_up
// Displayed for example in menu (indicating to initate play)
const uint8_t const lever_up[16][9] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Image for lever_down
// Shown for example when game begins
const uint8_t const lever_down[16][9] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1}
};

const uint8_t const apple_icon[3][3] = {
    {0, 1, 0},
    {1, 1, 1},
    {0, 1, 0},
};