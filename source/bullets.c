
#include "bullets.h"
#include "vars.h"
#include <stdio.h>
#include <string.h>

BulletInfo bullets[MAX_BULLETS];
int activebullets = 0;
int bulletbatch = 0;

void InitBullets()
{
    for(int i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i].x = 0;
        bullets[i].y = 0;
        bullets[i].velocity = 0;
        bullets[i].size = 1;
    }
    activebullets = 0;
    bulletbatch = 0;
}

void SpawnBullet(int X, int Y, int Direction, int Velocity, u8 Colour, u8 Size, BulletUpdate Controller)
{
    if(activebullets >= MAX_BULLETS || X < BULLET_MIN_X || X >= BULLET_MAX_X || Y < 0 || Y >= SCREEN_HEIGHT)
    {
        return;
    }

    bullets[activebullets].x = X << 8;
    bullets[activebullets].y = Y << 8;
    bullets[activebullets].direction = Direction;
    bullets[activebullets].velocity = Velocity;
    bullets[activebullets].colour = Colour;
    bullets[activebullets].size = Size;
    bullets[activebullets].updatefunction = Controller;

    //SetPixel(bullets[activebullets].x >> 8, bullets[activebullets].y >> 8, bullets[activebullets].colour);

    activebullets++;
}

void UpdateBullets()
{
    int curbullet = bulletbatch * BATCH_SIZE;
    int endbullet = (bulletbatch + 1) * BATCH_SIZE;
    if(activebullets < endbullet)
    {
        endbullet = activebullets;
    }

    while(curbullet < endbullet && curbullet < activebullets)
    {
        int actualx = bullets[curbullet].x >> 8;
        int actualy = bullets[curbullet].y >> 8;

        if(actualx >= BULLET_MIN_X && actualx < BULLET_MAX_X && actualy >= 0 && actualy < SCREEN_HEIGHT)
        {
            bool progressbullet = true;
            if(bullets[curbullet].size == 2)
            {
                SetPixel(actualx - 1, actualy, 0);
                SetPixel(actualx + 1, actualy, 0);
                SetPixel(actualx, actualy - 1, 0);
                SetPixel(actualx, actualy + 1, 0);
            }
            SetPixel(actualx, actualy, 0);
            if(bullets[curbullet].updatefunction != 0)
            {
                progressbullet = bullets[curbullet].updatefunction(curbullet);
            }
            if(progressbullet)
            {
                // Keep bullet moving
                bullets[curbullet].x += ( sini(bullets[curbullet].direction) * bullets[curbullet].velocity);
                bullets[curbullet].y += (-cosi(bullets[curbullet].direction) * bullets[curbullet].velocity);
                actualx = bullets[curbullet].x >> 8;
                actualy = bullets[curbullet].y >> 8;
            }
            else
            {
                // Bullet has "died"
                actualx = 0;
                actualy = 0;
            }
        }
        if(actualx >= BULLET_MIN_X && actualx < BULLET_MAX_X && actualy >= 0 && actualy < SCREEN_HEIGHT)
        {
            if(bullets[curbullet].size == 2)
            {
                SetPixel(actualx - 1, actualy, bullets[curbullet].colour);
                SetPixel(actualx + 1, actualy, bullets[curbullet].colour);
                SetPixel(actualx, actualy - 1, bullets[curbullet].colour);
                SetPixel(actualx, actualy + 1, bullets[curbullet].colour);
            }
            SetPixel(actualx, actualy, bullets[curbullet].colour);
        }
        else
        {
            // Bullet is finished, shrink the array
            if(curbullet < activebullets-1)
            {
                memcpy(&bullets[curbullet], &bullets[activebullets-1], sizeof(BulletInfo));
                curbullet--;
            }
            activebullets--;
        }

        curbullet++;
    }

    bulletbatch = (bulletbatch + 1) % BATCH_COUNT;

}
