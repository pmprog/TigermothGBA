
#include "stages.h"
#include "gba.h"
#include "maths.h"
#include "tilefaces_bin.h"
#include "vars.h"

#define MENU_DELAY_TIME     2

const u8 arena_tilemap[] = {
    1,1,1,1,1,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,2,4,15,11,16,
    1,1,1,1,1,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,15,5,1,1,1,
    1,1,1,1,1,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,6,1,4,8,5,
    1,1,1,1,1,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,19,3,1,1,1,
    1,1,1,1,1,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,3,3,3,1,1,
    1,1,1,1,1,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,5,1,5,1,1,
    1,1,1,1,1,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,41,42,1,1,1,
    1,1,1,1,1,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,44,43,1,5,1,
    1,1,1,1,1,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,5,5,5,1,1,
    1,1,1,1,1,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,1,5,1,1,1,
    1,1,1,1,1,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,1,1,1,1,1,
    1,1,1,1,1,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,1,1,1,1,1,
    1,1,1,4,6,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,1,1,1,1,1,
    1,1,1,31,10,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,1,1,1,1,1,
    1,1,1,2,6,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,1,1,1,1,1,
    1,1,1,1,4,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,1,1,1,1,1,
    1,1,1,1,2,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,1,1,1,1,1,
    1,1,1,1,4,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,1,1,1,1,1,
    1,1,1,1,2,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,1,1,1,1,1,
    1,1,1,1,1,29,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,30,1,1,1,1,1
};

const u8 arena_colourmap[] = {
    0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,5,2,5,6,3,
    0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,4,5,0,0,0,
    0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,5,0,1,3,2,
    0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,6,6,0,0,0,
    0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,2,5,6,0,0,
    0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,1,0,5,0,0,
    0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,2,3,0,0,0,
    0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,1,0,1,0,
    0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,2,1,0,0,0,
    0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,
    0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,
    0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,
    0,0,0,1,2,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,
    0,0,0,1,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,
    0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,
    0,0,0,0,1,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,
    0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,
    0,0,0,0,1,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,
    0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,
    0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0
};

const FullscreenInfo arena_fsinfo = { tilefaces_bin, 8, 384, arena_tilemap, arena_colourmap, menu_palettes };

void setuparena_update()
{
    if( stage_initialised == 0 )
    {
       	//mmStart( MOD_LN26, MM_PLAY_LOOP );

        player_x = 120;
        player_y = 170;
        OAM[0].attr2 = OBJ_CHAR(512) | ATTR2_PRIORITY(1);
        UpdatePlayer();

        frame_delay = MENU_DELAY_TIME;
        stage_initialised = 1;
    }

    frame_delay--;
    if(frame_delay >= 0) 
    {
        return;
    }

    if(frame_time >= 21)
    {
        SetStage(play_update);
        return;
    }

    BlitFullscreen(&arena_fsinfo, FULLSCREEN_COLUMNS_ROWS_REVERSE); // FULLSCREEN_COLUMNS_ROWS);
    if(frame_time == 7)
    {
        BitBlit2BPPSub(arena_fsinfo.TileSheet, arena_fsinfo.TileSheetW, arena_fsinfo.TileSheetH, 0, 16, 8, 8, 5 * 8, 12 * 8, &menu_palettes[8 * 4]);
    } else if( frame_time > 7 )
    {
        BitBlit2BPPSub(arena_fsinfo.TileSheet, arena_fsinfo.TileSheetW, arena_fsinfo.TileSheetH, 0, 16, 8, 8, 5 * 8, 12 * 8, &menu_palettes[9 * 4]);
    }
    if(frame_time == 6)
    {
        BitBlit2BPPSub(arena_fsinfo.TileSheet, arena_fsinfo.TileSheetW, arena_fsinfo.TileSheetH, 0, 16, 8, 8, 6 * 8, 13 * 8, &menu_palettes[8 * 4]);
    } else if( frame_time > 6 )
    {
        BitBlit2BPPSub(arena_fsinfo.TileSheet, arena_fsinfo.TileSheetW, arena_fsinfo.TileSheetH, 0, 16, 8, 8, 6 * 8, 13 * 8, &menu_palettes[9 * 4]);
    }
    if(frame_time == 5)
    {
        BitBlit2BPPSub(arena_fsinfo.TileSheet, arena_fsinfo.TileSheetW, arena_fsinfo.TileSheetH, 0, 32, 8, 8, 5 * 8, 14 * 8, &menu_palettes[8 * 4]);
    } else if( frame_time > 5 )
    {
        BitBlit2BPPSub(arena_fsinfo.TileSheet, arena_fsinfo.TileSheetW, arena_fsinfo.TileSheetH, 0, 32, 8, 8, 5 * 8, 14 * 8, &menu_palettes[10 * 4]);
    }

    if(frame_time == 4)
    {
        BitBlit2BPPSub(arena_fsinfo.TileSheet, arena_fsinfo.TileSheetW, arena_fsinfo.TileSheetH, 0, 16, 8, 8, 5 * 8, 15 * 8, &menu_palettes[8 * 4]);
    } else if( frame_time > 4 )
    {
        BitBlit2BPPSub(arena_fsinfo.TileSheet, arena_fsinfo.TileSheetW, arena_fsinfo.TileSheetH, 0, 16, 8, 8, 5 * 8, 15 * 8, &menu_palettes[9 * 4]);
    }
    if(frame_time == 3)
    {
        BitBlit2BPPSub(arena_fsinfo.TileSheet, arena_fsinfo.TileSheetW, arena_fsinfo.TileSheetH, 0, 32, 8, 8, 5 * 8, 16 * 8, &menu_palettes[8 * 4]);
    } else if( frame_time > 3 )
    {
        BitBlit2BPPSub(arena_fsinfo.TileSheet, arena_fsinfo.TileSheetW, arena_fsinfo.TileSheetH, 0, 32, 8, 8, 5 * 8, 16 * 8, &menu_palettes[10 * 4]);
    }
    if(frame_time == 2)
    {
        BitBlit2BPPSub(arena_fsinfo.TileSheet, arena_fsinfo.TileSheetW, arena_fsinfo.TileSheetH, 0, 16, 8, 8, 5 * 8, 17 * 8, &menu_palettes[8 * 4]);
    } else if( frame_time > 2 )
    {
        BitBlit2BPPSub(arena_fsinfo.TileSheet, arena_fsinfo.TileSheetW, arena_fsinfo.TileSheetH, 0, 16, 8, 8, 5 * 8, 17 * 8, &menu_palettes[9 * 4]);
    }
    if(frame_time == 1)
    {
        BitBlit2BPPSub(arena_fsinfo.TileSheet, arena_fsinfo.TileSheetW, arena_fsinfo.TileSheetH, 0, 32, 8, 8, 5 * 8, 18 * 8, &menu_palettes[8 * 4]);
    } else if( frame_time > 1 )
    {
        BitBlit2BPPSub(arena_fsinfo.TileSheet, arena_fsinfo.TileSheetW, arena_fsinfo.TileSheetH, 0, 32, 8, 8, 5 * 8, 18 * 8, &menu_palettes[10 * 4]);
    }

    player_y -= (frame_time >= 18 ? 1 : 2);
    UpdatePlayer();

    frame_time++;
    frame_delay = MENU_DELAY_TIME;
}
