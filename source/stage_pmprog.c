
#include "stages.h"
#include "gba.h"
#include "polymath_logo_bin.h"
#include "vars.h"

#define POLYMATH_DELAY_TIME     4

const u8 polymathpalette_1[] = { 0, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 0 };
const u8 polymathpalette_2[] = { 0, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11, 0 };
const u8 polymathpalette_3[] = { 0, 11, 12, 15,  1,  1,  1,  1,  1,  1,  1,  1,  1, 15, 12, 11, 0 };

void pmprog_update()
{
    if(stage_initialised == 0)
    {
        frame_delay = POLYMATH_DELAY_TIME;
        stage_initialised = 1;
    }

    frame_delay--;
    if(frame_delay > 0) 
    {
        return;
    }

    if( frame_time >= 17 )
    {
        SetStage( menu_update );
        return;
    }

    u8 palette[] = { 255, polymathpalette_1[frame_time], polymathpalette_2[frame_time], polymathpalette_3[frame_time] };
    BitBlit2BPP( polymath_logo_bin, 100, 60, 40, 40, palette );

    frame_time++;
    frame_delay = POLYMATH_DELAY_TIME;
}
