
#include "stages.h"
#include "gba.h"
#include "maths.h"
#include "rules_bin.h"
#include "vars.h"

#define MENU_DELAY_TIME     2

void menu2_update()
{
    if( stage_initialised == 0 )
    {
        frame_delay = MENU_DELAY_TIME;
        stage_initialised = 1;
    }

    if((keysHeld() & (KEY_A | KEY_START)) != 0)
    {
        mmStop();
        SetStage(setuparena_update);
        raninit(frame_time);
        return;
    }

    frame_delay--;
    if(frame_delay >= 0) 
    {
        return;
    }

    if( frame_time <= 50 )
    {
        int cury = 19;
        int curx = 29 - frame_time;
        while( cury >= 0 )
        {
            if( curx < 30 )
            {
                int fx = curx << 3;
                int fy = cury << 3;
                if( curx >= 0 ) { FillRect( fx, fy, 8, 8, 1 ); }
                if( curx < 29 ) { fx += 8; BitBlit4BPPSub( rules_bin, 240, 160, fx, fy, 8, 8, fx, fy ); }  // Replace with rules_bin portion
            }
            curx++;
            cury--;
        }
    }


    frame_time++;
    if( frame_time >= 0x100 )
    {
        SetStage(menu_update);
        return;
    }
    frame_delay = MENU_DELAY_TIME;
}
