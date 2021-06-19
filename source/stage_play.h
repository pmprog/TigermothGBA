
#pragma once

#include "stages.h"
#include "gba.h"
#include "maths.h"
#include "bullets.h"
#include "explosions.h"
#include "vars.h"
#include <string.h>

#define TIGERMOTH_SEGMENT_DELAY 8

//typedef void(*BulletUpdate)(TigermothSegment* Segment);

typedef struct ShotSpread
{
    int StartAngle;
    int EndAngle;
    int Spread;
    u8 Colour;
    u8 Velocity;
    BulletUpdate BulletUpdate;
} ShotSpread;

typedef struct TigermothSegment
{
    int X;
    int Y;
    u16 SpriteID;
    u8 Health;
    u8 BulletPattern;
    //int MoveX[TIGERMOTH_SEGMENT_DELAY];
    //int MoveY[TIGERMOTH_SEGMENT_DELAY];
} TigermothSegment;


typedef struct TigermothDetail
{
    int Direction;
    s8 Velocity;
    TigermothSegment Head;
    TigermothSegment Row1Left;
    TigermothSegment Row1Centre;
    TigermothSegment Row1Right;
    TigermothSegment Row2Left;
    TigermothSegment Row2Centre;
    TigermothSegment Row2Right;
    TigermothSegment Row3Left;
    TigermothSegment Row3Centre;
    TigermothSegment Row3Right;
//    TigermothSegment Row4Left;
//    TigermothSegment Row4Centre;
//    TigermothSegment Row4Right;
//    TigermothSegment Row5Left;
//    TigermothSegment Row5Centre;
//    TigermothSegment Row5Right;
    TigermothSegment Row6Centre;

    int HeadMoveX[TIGERMOTH_SEGMENT_DELAY];
    int HeadMoveY[TIGERMOTH_SEGMENT_DELAY];
    int Row1MoveX[TIGERMOTH_SEGMENT_DELAY];
    int Row1MoveY[TIGERMOTH_SEGMENT_DELAY];
    int Row2MoveX[TIGERMOTH_SEGMENT_DELAY];
    int Row2MoveY[TIGERMOTH_SEGMENT_DELAY];
    int Row3MoveX[TIGERMOTH_SEGMENT_DELAY];
    int Row3MoveY[TIGERMOTH_SEGMENT_DELAY];
    int Row6MoveX[TIGERMOTH_SEGMENT_DELAY];
    int Row6MoveY[TIGERMOTH_SEGMENT_DELAY];

} TigermothDetail;

extern const TigermothDetail play_tigermoth_level1;
extern const TigermothDetail play_tigermoth_level2;
extern const TigermothDetail play_tigermoth_level3;
extern const TigermothDetail play_tigermoth_level4;
extern const TigermothDetail play_tigermoth_level5;
extern const TigermothDetail play_tigermoth_level6;
extern const TigermothDetail play_tigermoth_level7;
extern const TigermothDetail play_tigermoth_level8;
extern const TigermothDetail play_tigermoth_level9;
extern const TigermothDetail play_tigermoth_level10;
extern const TigermothDetail play_tigermoth_level11;

extern const ShotSpread play_tigermoth_shotspreads[];
extern const int play_tigermoth_patterns[];

void InitialisePlayer();
void InitialiseTigermoth(int Level);
void ControlPlayer();
void ControlTigermoth();
void UpdateTigermoth();
void ProcessSpread(int X, int Y, const ShotSpread* Spread);

bool Bullet_PlayerCurved(int BulletIndex);
bool Bullet_PlayerStandard(int BulletIndex);
bool Bullet_TigermothStandard(int BulletIndex);
