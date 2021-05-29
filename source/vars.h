
#pragma once

#include "gba.h"

#define BULLET_MIN_X    48
#define BULLET_MAX_X    192

extern int frame_delay;
extern int frame_time;
extern unsigned char stage_initialised;
extern const u8 menu_palettes[];

extern u8 player_dead;
extern u8 player_x;
extern u8 player_y;
extern u8 player_a_cooldown;
extern u8 player_a_cooldown_current;
extern u16 player_b_cooldown;
extern u16 player_b_cooldown_current;
extern u16 player_score;
extern u8 player_a_spread;

typedef struct ranctx
{
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} ranctx;
extern ranctx randomsource;


void UpdatePlayer();
