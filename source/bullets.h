
#pragma once

#include "maths.h"
#include "gba.h"
#include "drawing.h"

#define BATCH_SIZE      220
#define BATCH_COUNT     3
#define MAX_BULLETS     BATCH_SIZE * BATCH_COUNT

// Returns true if bullet is to continue on, false if it is removed for some reason (ie, hit player/tigermoth)
typedef bool(*BulletUpdate)(int BulletIndex);

typedef struct BulletInfo
{
    int x;
    int y;
    int direction;
    int velocity;
    u8 colour;
    u8 size;
    BulletUpdate updatefunction;    // Need to configure bullets on the fly?
} BulletInfo;

// Move to EWRAM_DATA ??
extern BulletInfo bullets[MAX_BULLETS];
extern int activebullets;
extern int bulletbatch;

void InitBullets();
void SpawnBullet(int X, int Y, int Direction, int Velocity, u8 Colour, u8 Size, BulletUpdate Controller);
void UpdateBullets();
