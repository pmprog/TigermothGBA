
#include "drawing.h"
#include "stages.h"
#include "gba.h"
#include "maths.h"
#include "vars.h"


void BitBlit4BPP(const u8* Sprite, int X, int Y, int W, int H)
{
    const u8* sprptr = Sprite;
    for( int y = 0; y < H; y++ )
    {
        u16* vidptr = &vid_page[ ( ((Y + y) * M4_WIDTH) + X) / 2 ];
        for( int x = 0; x < W; x += 2 )
        {
            u8 temp;
            u8 col;
            u16 target = *vidptr;

            col = *sprptr++;
            temp = col >> 4;
            target = (target & 0xFF00) | temp;
            temp = col & 0x000F;
            target = (target & 0x00FF) | (temp << 8);
            *vidptr++ = target;
        }
    }
}

void BitBlit4BPPT(const u8* Sprite, int X, int Y, int W, int H, u8 TransparentColourIndex)
{
    const u8* sprptr = Sprite;
    u8 emptypixel = TransparentColourIndex | (TransparentColourIndex << 4);
    for( int y = 0; y < H; y++ )
    {
        u16* vidptr = &vid_page[ ( ((Y + y) * M4_WIDTH) + X) / 2 ];
        for( int x = 0; x < W; x += 2 )
        {
            u8 temp;
            u8 col;
            u16 target = *vidptr;

            col = *sprptr++;
            if(col != emptypixel)
            {
                temp = col >> 4;
                if( temp != TransparentColourIndex ) { target = (target & 0xFF00) | temp; }
                temp = col & 0x000F;
                if( temp != TransparentColourIndex ) { target = (target & 0x00FF) | (temp << 8); }
                *vidptr++ = target;
            }
            else
            {
                vidptr++;
            }
        }
    }
}
