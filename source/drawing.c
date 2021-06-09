
#include "drawing.h"

u16* vid_page = (u16*)VRAM;     // Point to current frame buffer

// C64 palette
const u16 c64palette[] = {
    RGB8(   0,   0,   0 ), //  0 : Black
    RGB8( 255, 255, 255 ), //  1 : White
    RGB8( 104,  55,  43 ), //  2 : Red
    RGB8( 112, 164, 178 ), //  3 : Cyan
    RGB8( 111,  61, 134 ), //  4 : Purple
    RGB8(  88, 141,  67 ), //  5 : Green
    RGB8(  53,  40, 121 ), //  6 : Blue
    RGB8( 184, 199, 111 ), //  7 : Yellow
    RGB8( 111,  79,  37 ), //  8 : Orange
    RGB8(  67,  57,   0 ), //  9 : Brown
    RGB8( 154, 103,  89 ), // 10 : Pink
    RGB8(  68,  68,  68 ), // 11 : Dark Grey
    RGB8( 108, 108, 108 ), // 12 : Mid Grey
    RGB8( 154, 210, 132 ), // 13 : Light Green
    RGB8( 108,  94, 181 ), // 14 : Light Blue
    RGB8( 149, 149, 149 ), // 15 : Light Grey
};

void InitC64Palette()
{
	u16* bptr = BG_COLORS;
    u16* cptr = OBJ_COLORS;
	for( int i = 0; i < 16; i++ )
	{
		*bptr++ = c64palette[i];
        *cptr++ = c64palette[i];
	}
}

void SetBitmapMode(bool WithSpriteLayer)
{
    REG_DISPCNT = MODE_4 | BG2_ON | (WithSpriteLayer ? OBJ_ON | OBJ_1D_MAP : 0);
}

void SetTileMode(int BackgroundPlanes, bool WithSpriteLayer)
{
    REG_DISPCNT = MODE_0
        | (BackgroundPlanes >= 1 ? BG0_ON : 0)
        | (BackgroundPlanes >= 2 ? BG1_ON : 0)
        | (BackgroundPlanes >= 3 ? BG2_ON : 0)
        | (BackgroundPlanes >= 4 ? BG3_ON : 0)
        | (WithSpriteLayer ? OBJ_ON | OBJ_1D_MAP : 0);
}

void SetPixel(int X, int Y, u8 Colour)
{
    u16* ptr = &vid_page[ ( (Y * M4_WIDTH) + X) / 2 ];  // Division by 2 due to u8/u16 pointer mismatch!
    if( X & 1 )
    {
        *ptr = (*ptr & 0x00FF) | (Colour<<8);    // odd pixel
    }
    else
    {
        *ptr = (*ptr & 0xFF00) | Colour;        // even pixel
    }
}

void BitBlit(const u8* Sprite, int X, int Y, int W, int H)
{
    for( int y = 0; y < H; y++ )
    {
        u16* vidptr = &vid_page[ ( ((Y + y) * M4_WIDTH) + X) / 2 ];
        //u16* sprptr = &Sprite[ (y * W) / 2 ];
        u16* sprptr = (u16*)&Sprite[ (y * W) ];
        for( int x = 0; x < W; x += 2 )
        {
            *vidptr++ = *sprptr++;
        }
    }
}

void FillRect(int X, int Y, int W, int H, u8 Colour)
{
    for( int y = 0; y < H; y++ )
    {
        u16* vidptr = &vid_page[ ( ((Y + y) * M4_WIDTH) + X) / 2 ];
        for( int x = 0; x < W; x += 2 )
        {
            *vidptr++ = (Colour << 8) | Colour;
        }
    }
}
