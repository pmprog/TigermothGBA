
#pragma once

#include "gba.h"

#define M4_WIDTH                            240     // Width in mode 4
#define FULLSCREEN_COLUMNS_COLUMNS          0
#define FULLSCREEN_COLUMNS_ROWS             1
#define FULLSCREEN_COLUMNS_ROWS_REVERSE     2

typedef struct FullscreenInfo
{
    const u8* TileSheet;    // 8x(n) 2bpp image
    int TileSheetW;
    int TileSheetH;
    u8* TileArray;          // 30x20 array with tile numbers
    u8* ColourArray;        // 30x20 array of palette start index
    u8* MergedPalettes;     // Combined Palettes; Index 0 is start of first palette, Index 3 is start of second palette etc.
} FullscreenInfo;

extern u16* vid_page;     // Point to current frame buffer

// Setup screen to use C64 palette
void InitC64Palette();

void SetBitmapMode(bool WithSpriteLayer);
void SetTileMode(int BackgroundPlanes, bool WithSpriteLayer);

// Set individual pixel
void SetPixel(int X, int Y, u8 Colour);

// X must be multiple of 2
// W must be multiple of 2
void BitBlit(const u8* Sprite, int X, int Y, int W, int H);

// X must be multiple of 2
// W must be multiple of 4
// ColourIndicies must be an array of three u8 values pointing to a palette index
// Bits 00 = Transparent, 01 = ColourIndicies[0], 10 = ColourIndicies[1], 11 = ColourIndicies[2]
void BitBlit2BPP(const u8* Sprite, int X, int Y, int W, int H, const u8 ColourIndicies[]);
void BitBlit2BPPSub(const u8* Sprite, int SpriteW, int SpriteH, int SourceX, int SourceY, int SourceW, int SourceH, int DestX, int DestY, const u8 ColourIndicies[]);

// Blits 4BPP, with transparent
void BitBlit4BPP(const u8* Sprite, int X, int Y, int W, int H);
void BitBlit4BPPT(const u8* Sprite, int X, int Y, int W, int H, u8 TransparentColourIndex);
void BitBlit4BPPSub(const u8* Sprite, int SpriteW, int SpriteH, int SourceX, int SourceY, int SourceW, int SourceH, int DestX, int DestY);

// Fix region
void FillRect(int X, int Y, int W, int H, u8 Colour);

// Render a "tilemap"
void BlitFullscreen(const FullscreenInfo* Info, int Transition);

