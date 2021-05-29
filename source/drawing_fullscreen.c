
#include "drawing.h"
#include "stages.h"
#include "gba.h"
#include "maths.h"
#include "vars.h"

void BlitFullscreen(const FullscreenInfo* Info, int Transition)
{
    const u8 bfs_palettes[] = { 0, 1, 1, 1 };

    switch(Transition)
    {
        case FULLSCREEN_COLUMNS_COLUMNS:
            {
                if( frame_time > 30 )
                {
                    return;
                }
                for(int y = 0; y < 20; y++)
                {
                    int srcy;
                    if(frame_time > 0)
                    {
                        srcy = (int)(Info->TileArray[(y * 30) + frame_time - 1] - 1) << 3;
                        u8 coly = Info->ColourArray[(y * 30) + frame_time - 1];
                        u8* pal = &Info->MergedPalettes[coly * 4];
                        BitBlit2BPPSub(Info->TileSheet, Info->TileSheetW, Info->TileSheetH, 0, srcy, 8, 8, (frame_time - 1) * 8, y * 8, pal);
                    }
                    if(frame_time < 30)
                    {
                        srcy = (int)(Info->TileArray[(y * 30) + frame_time] - 1) << 3;
                        BitBlit2BPPSub(Info->TileSheet, Info->TileSheetW, Info->TileSheetH, 0, srcy, 8, 8, frame_time * 8, y * 8, bfs_palettes);
                    }
                }
            }
            break;
        case FULLSCREEN_COLUMNS_ROWS:
            {
                if( frame_time > 20 )
                {
                    return;
                }
                for(int x = 0; x < 30; x++)
                {
                    int srcy;
                    if(frame_time > 0)
                    {
                        srcy = (int)(Info->TileArray[((frame_time-1) * 30) + x] - 1) << 3;
                        u8 coly = Info->ColourArray[((frame_time - 1) * 30) + x];
                        u8* pal = &Info->MergedPalettes[coly * 4];
                        BitBlit2BPPSub(Info->TileSheet, Info->TileSheetW, Info->TileSheetH, 0, srcy, 8, 8, x * 8, (frame_time - 1) * 8, pal);
                    }
                    if(frame_time < 20)
                    {
                        srcy = (int)(Info->TileArray[(frame_time * 30) + x] - 1) << 3;
                        BitBlit2BPPSub(Info->TileSheet, Info->TileSheetW, Info->TileSheetH, 0, srcy, 8, 8, x * 8, frame_time * 8, bfs_palettes);
                    }
                }
            }
            break;
        case FULLSCREEN_COLUMNS_ROWS_REVERSE:
            {
                if( frame_time > 20 )
                {
                    return;
                }
                int reverse_time = 19 - frame_time;
                for(int x = 0; x < 30; x++)
                {
                    int srcy;
                    if(reverse_time < 20)
                    {
                        srcy = (int)(Info->TileArray[((reverse_time + 1) * 30) + x] - 1) << 3;
                        u8 coly = Info->ColourArray[((reverse_time + 1) * 30) + x];
                        u8* pal = &Info->MergedPalettes[coly * 4];
                        BitBlit2BPPSub(Info->TileSheet, Info->TileSheetW, Info->TileSheetH, 0, srcy, 8, 8, x * 8, (reverse_time + 1) * 8, pal);
                    }
                    if(reverse_time > 0)
                    {
                        srcy = (int)(Info->TileArray[(reverse_time * 30) + x] - 1) << 3;
                        BitBlit2BPPSub(Info->TileSheet, Info->TileSheetW, Info->TileSheetH, 0, srcy, 8, 8, x * 8, reverse_time * 8, bfs_palettes);
                    }
                }
            }
            break;
    }

}
