
#include "vars.h"
#include "gba.h"
#include "maths.h"


int frame_delay = 0;
int frame_time = 0;
u8 stage_initialised = 0;

const u8 menu_palettes[] = {
      0,  11,  11,  11,  // 0 Dark Gray
      0,  12,  12,  12,  // 1 Mid Gray
      0,  15,  15,  15,  // 2 Light Gray
      0,   1,   1,   1,  // 3 White
      0,   9,   9,   9,  // 4 Brown
      0,   8,   8,   8,  // 5 Orange
      0,  10,  10,  10,  // 6 Pink
      0,   5,  13,   1,  // 7 Green/Yellow Ramp
    255,   1,   1,   1,  // 8 White Transparent
    255,  15,  15,  15,  // 9 Light Gray Transparent
    255,  12,  12,  12,  //10 Mid Gray Transparent
};

u8 player_dead = 0;
u8 player_x = 0;
u8 player_y = 0;
u8 player_a_cooldown = 0;
u8 player_a_cooldown_current = 0;
u16 player_b_cooldown;
u16 player_b_cooldown_current;
u16 player_score = 0;
u8 player_a_spread = 0;

ranctx randomsource = { 0x5E, 0x00, 0x00, 0x00 };

void UpdatePlayer()
{
    OAM[0].attr0 = OBJ_Y(player_y - 8) | ATTR0_COLOR_16 | ATTR0_SQUARE;
    OAM[0].attr1 = OBJ_X(player_x - 8) | ATTR1_SIZE_16;
}
