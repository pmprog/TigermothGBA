
#include "drawing.h"
#include "stages.h"
#include "gba.h"
#include "maths.h"
#include "vars.h"


void BitBlit2BPP(const u8* Sprite, int X, int Y, int W, int H, const u8 ColourIndicies[])
{
    const u8* sprptr = Sprite;
    for( int y = 0; y < H; y++ )
    {
        u16* vidptr = &vid_page[ ( ((Y + y) * M4_WIDTH) + X) / 2 ];
        for( int x = 0; x < W; x += 4 )
        {
            u8 temp;
            u8 col;
            u16 target;

            col = *sprptr++;

            // Calculate first two colours
            target = *vidptr;
            temp = (col & 0xC0) >> 6;
            if( ColourIndicies[temp] < 255 ) { target = (target & 0xFF00) | ColourIndicies[temp]; }
            temp = (col & 0x30) >> 4;
            if( ColourIndicies[temp] < 255 ) { target = (target & 0x00FF) | (ColourIndicies[temp] << 8); }
            // Draw pixels
            *vidptr++ = target;

            // Calculate second two colours
            target = *vidptr;
            temp = (col & 0x0C) >> 2;
            if( ColourIndicies[temp] < 255 ) { target = (target & 0xFF00) | ColourIndicies[temp]; }
            temp = (col & 0x03);
            if( ColourIndicies[temp] < 255 ) { target = (target & 0x00FF) | (ColourIndicies[temp] << 8); }
            // Draw pixels
            *vidptr++ = target;
        }
    }
}

void BitBlit2BPPSub(const u8* Sprite, int SpriteW, int SpriteH, int SourceX, int SourceY, int SourceW, int SourceH, int DestX, int DestY, const u8 ColourIndicies[])
{
    for( int y = 0; y < SourceH; y++ )
    {
        const u8* sprptr = &Sprite[((SourceY + y) * (SpriteW >> 2)) + (SourceX >> 2)];
        u16* vidptr = &vid_page[ ( ((DestY + y) * M4_WIDTH) + DestX) / 2 ];
        for( int x = 0; x < SourceW; x += 4 )
        {
            u8 temp;
            u8 col;
            u16 target;

            col = *sprptr++;

            // Calculate first two colours
            target = *vidptr;
            temp = (col & 0xC0) >> 6;
            if( ColourIndicies[temp] < 255 ) { target = (target & 0xFF00) | ColourIndicies[temp]; }
            temp = (col & 0x30) >> 4;
            if( ColourIndicies[temp] < 255 ) { target = (target & 0x00FF) | (ColourIndicies[temp] << 8); }
            // Draw pixels
            *vidptr++ = target;

            // Calculate second two colours
            target = *vidptr;
            temp = (col & 0x0C) >> 2;
            if( ColourIndicies[temp] < 255 ) { target = (target & 0xFF00) | ColourIndicies[temp]; }
            temp = (col & 0x03);
            if( ColourIndicies[temp] < 255 ) { target = (target & 0x00FF) | (ColourIndicies[temp] << 8); }
            // Draw pixels
            *vidptr++ = target;
        }
    }
}
