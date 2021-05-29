
#include "stage_play.h"
#include "tilefaces_bin.h"

#define TIGER_BULLET_DELAY      4

u8 play_level = 1;
TigermothDetail play_tigermoth;
u8 play_tigerbulletdelay = TIGER_BULLET_DELAY;
u8 play_tigerbulletframe = 0;

void play_update()
{
    if( stage_initialised == 0 )
    {
        mmStart( MOD_TIGERMOTH_INGAME, MM_PLAY_LOOP );
        InitialisePlayer();
        play_level = 1;
        InitialiseTigermoth(play_level);

        FillRect(  8, 8, 22, 34, 1 );
        FillRect( 10, 9,  8, 32, 0 );
        FillRect( 20, 9,  8, 32, 0 );
        stage_initialised = 1;
    }

    FillRect( 10, 9,  8, player_a_cooldown_current, 0 );
    FillRect( 10, 9 + player_a_cooldown_current,  8, 32 - player_a_cooldown_current, 2 );
    FillRect( 12, 9 + player_a_cooldown_current,  1, 32 - player_a_cooldown_current, 10 );
    FillRect( 20, 9,  8, (player_b_cooldown_current / 10), 0 );
    FillRect( 20, 9 + (player_b_cooldown_current / 10),  8, 32 - (player_b_cooldown_current / 10), 5 );
    FillRect( 22, 9 + (player_b_cooldown_current / 10),  1, 32 - (player_b_cooldown_current / 10), 13 );

    UpdateBullets();

    if( player_dead != 0 )
    {
        mmStop();
        SetStage(gameover_update);
        return;
    }

    if( play_tigermoth.Head.Health == 0 )
    {
        play_level++;
        if(player_a_cooldown >   3) { player_a_cooldown--; }
        if(player_b_cooldown > 150) { player_b_cooldown -= 5; }
        InitialiseTigermoth(play_level);
    }

    ControlPlayer();
    UpdatePlayer();

    ControlTigermoth();
    UpdateTigermoth();

    BitBlit2BPPSub(tilefaces_bin, 8, 384, 0, 16, 8, 8, 6 * 8, 13 * 8, &menu_palettes[9 * 4]);

    frame_time++;
    frame_time &= 0x001F;
}

void InitialisePlayer()
{
    player_score = 0;
    player_dead = 0;
    player_a_cooldown = 16;
    player_b_cooldown = 320;
    player_a_cooldown_current = 0;
    player_b_cooldown_current = 0;
    player_a_spread = 0;
}

void InitialiseTigermoth(int Level)
{
    switch(Level)
    {
        case 1:
            memcpy((void*)&play_tigermoth, (void*)&play_tigermoth_level1, sizeof(TigermothDetail));
            break;
        case 2:
            memcpy((void*)&play_tigermoth, (void*)&play_tigermoth_level2, sizeof(TigermothDetail));
            break;
        case 3:
            memcpy((void*)&play_tigermoth, (void*)&play_tigermoth_level3, sizeof(TigermothDetail));
            break;
        case 4:
            memcpy((void*)&play_tigermoth, (void*)&play_tigermoth_level4, sizeof(TigermothDetail));
            break;
        case 5:
            memcpy((void*)&play_tigermoth, (void*)&play_tigermoth_level5, sizeof(TigermothDetail));
            break;
        case 6:
            memcpy((void*)&play_tigermoth, (void*)&play_tigermoth_level6, sizeof(TigermothDetail));
            break;
        case 7:
            memcpy((void*)&play_tigermoth, (void*)&play_tigermoth_level7, sizeof(TigermothDetail));
            break;
        case 8:
            memcpy((void*)&play_tigermoth, (void*)&play_tigermoth_level8, sizeof(TigermothDetail));
            break;
        case 9:
            memcpy((void*)&play_tigermoth, (void*)&play_tigermoth_level9, sizeof(TigermothDetail));
            break;
        case 10:
            memcpy((void*)&play_tigermoth, (void*)&play_tigermoth_level10, sizeof(TigermothDetail));
            break;
        default:
            memcpy((void*)&play_tigermoth, (void*)&play_tigermoth_level11, sizeof(TigermothDetail));
            int bonuslife = (Level - 11) << 3;
            TigermothSegment* segarray = &play_tigermoth.Head;
            for(int idx = 0; idx < 11; idx++)
            {
                segarray[idx].Health += bonuslife;
            }
            break;
    }
    play_tigermoth.Row3Left.X  = play_tigermoth.Row3Centre.X - (24 << 8);
    play_tigermoth.Row3Left.Y  = play_tigermoth.Row3Centre.Y;
    play_tigermoth.Row3Right.X = play_tigermoth.Row3Centre.X + (24 << 8);
    play_tigermoth.Row3Right.Y = play_tigermoth.Row3Centre.Y;
    play_tigermoth.Row2Left.X  = play_tigermoth.Row2Centre.X - (24 << 8);
    play_tigermoth.Row2Left.Y  = play_tigermoth.Row2Centre.Y;
    play_tigermoth.Row2Right.X = play_tigermoth.Row2Centre.X + (24 << 8);
    play_tigermoth.Row2Right.Y = play_tigermoth.Row2Centre.Y;
    play_tigermoth.Row1Left.X  = play_tigermoth.Row1Centre.X - (24 << 8);
    play_tigermoth.Row1Left.Y  = play_tigermoth.Row1Centre.Y;
    play_tigermoth.Row1Right.X = play_tigermoth.Row1Centre.X + (24 << 8);
    play_tigermoth.Row1Right.Y = play_tigermoth.Row1Centre.Y;
    play_tigerbulletdelay = TIGER_BULLET_DELAY;
    play_tigerbulletframe = 0;
}

void ControlPlayer()
{
    // Check D-Pad Movement
    if( (keysHeld() & KEY_LEFT) == KEY_LEFT && player_x > BULLET_MIN_X + 4 )
    {
        player_x--;
    }
    if( (keysHeld() & KEY_RIGHT) == KEY_RIGHT && player_x < BULLET_MAX_X - 4 )
    {
        player_x++;
    }

    if( (keysHeld() & KEY_UP) == KEY_UP && player_y > 4 )
    {
        player_y--;
    }
    if( (keysHeld() & KEY_DOWN) == KEY_DOWN && player_y < SCREEN_HEIGHT - 4 )
    {
        player_y++;
    }

    // Check (A) button Fire
    if(player_a_cooldown_current > 0)
    {
        player_a_cooldown_current--;
    }
    if((keysHeld() & KEY_A) == KEY_A && player_a_cooldown_current == 0)
    {
        int ang = player_a_spread * -5;
        for(int i = 0; i <= player_a_spread; i++)
        {
            SpawnBullet(player_x, player_y, ang + (i * 10), 4, 1, 1, Bullet_PlayerStandard);
        }
        player_a_cooldown_current = player_a_cooldown;
    }

    // Check (B) button Fire
    if(player_b_cooldown_current > 0)
    {
        player_b_cooldown_current--;
    }
    if((keysHeld() & KEY_B) == KEY_B && player_b_cooldown_current == 0)
    {
        for(int i = -120; i <= 120; i += 4)
        {
            SpawnBullet(player_x, player_y, i, 5, 3, 1, Bullet_PlayerStandard);
        }
        player_b_cooldown_current = player_b_cooldown;
    }
}

void ControlTigermoth()
{
    // Process Bullet Commands
    play_tigerbulletdelay--;
    if( play_tigerbulletdelay == 0 )
    {
        TigermothSegment* segarray = &play_tigermoth.Head;
        for(int idx = 0; idx < 11; idx++)
        {
            if(segarray[idx].SpriteID != 0 && segarray[idx].Health > 0)
            {
                int patternindex = (segarray[idx].BulletPattern << 5) + play_tigerbulletframe;
                int spreadindex = play_tigermoth_patterns[patternindex];
                if( spreadindex > 0 )
                {
                    ProcessSpread( segarray[idx].X >> 8, (segarray[idx].Y >> 8) + 12, &play_tigermoth_shotspreads[spreadindex - 1] );
                }
            }
        }
        play_tigerbulletdelay = TIGER_BULLET_DELAY;
        play_tigerbulletframe++;
        play_tigerbulletframe &= 0x001F;
    }

    // Calculate Next Move
    play_tigermoth.Row6MoveX[0] = play_tigermoth.Row3MoveX[TIGERMOTH_SEGMENT_DELAY-1];
    play_tigermoth.Row6MoveY[0] = play_tigermoth.Row3MoveY[TIGERMOTH_SEGMENT_DELAY-1];
    for(int cpy = TIGERMOTH_SEGMENT_DELAY-1; cpy > 0; cpy--)
    {
        play_tigermoth.Row3MoveX[cpy] = play_tigermoth.Row3MoveX[cpy - 1];
        play_tigermoth.Row3MoveY[cpy] = play_tigermoth.Row3MoveY[cpy - 1];
    }
    play_tigermoth.Row3MoveX[0] = play_tigermoth.Row2MoveX[TIGERMOTH_SEGMENT_DELAY-1];
    play_tigermoth.Row3MoveY[0] = play_tigermoth.Row2MoveY[TIGERMOTH_SEGMENT_DELAY-1];
    for(int cpy = TIGERMOTH_SEGMENT_DELAY-1; cpy > 0; cpy--)
    {
        play_tigermoth.Row2MoveX[cpy] = play_tigermoth.Row2MoveX[cpy - 1];
        play_tigermoth.Row2MoveY[cpy] = play_tigermoth.Row2MoveY[cpy - 1];
    }
    play_tigermoth.Row2MoveX[0] = play_tigermoth.Row1MoveX[TIGERMOTH_SEGMENT_DELAY-1];
    play_tigermoth.Row2MoveY[0] = play_tigermoth.Row1MoveY[TIGERMOTH_SEGMENT_DELAY-1];
    for(int cpy = TIGERMOTH_SEGMENT_DELAY-1; cpy > 0; cpy--)
    {
        play_tigermoth.Row1MoveX[cpy] = play_tigermoth.Row1MoveX[cpy - 1];
        play_tigermoth.Row1MoveY[cpy] = play_tigermoth.Row1MoveY[cpy - 1];
    }
    play_tigermoth.Row1MoveX[0] = play_tigermoth.HeadMoveX[TIGERMOTH_SEGMENT_DELAY-1];
    play_tigermoth.Row1MoveY[0] = play_tigermoth.HeadMoveY[TIGERMOTH_SEGMENT_DELAY-1];
    for(int cpy = TIGERMOTH_SEGMENT_DELAY-1; cpy > 0; cpy--)
    {
        play_tigermoth.HeadMoveX[cpy] = play_tigermoth.HeadMoveX[cpy - 1];
        play_tigermoth.HeadMoveY[cpy] = play_tigermoth.HeadMoveY[cpy - 1];
    }
    play_tigermoth.HeadMoveX[0] = ( sini(play_tigermoth.Direction) * play_tigermoth.Velocity) >> 2;
    play_tigermoth.HeadMoveY[0] = (-cosi(play_tigermoth.Direction) * play_tigermoth.Velocity) >> 2;

    // Adjust direction


    if( play_tigermoth.Head.Y < (8 << 8) )
    {
        if( play_tigermoth.Direction <  100 ) { play_tigermoth.Direction += 20; }
        if( play_tigermoth.Direction >= 260 ) { play_tigermoth.Direction -= 20; }
    }
    else if( play_tigermoth.Head.Y > ((play_level < 14 ? 50 : 80) << 8) )
    {
        if( play_tigermoth.Direction <  180 && play_tigermoth.Direction >  60 ) { play_tigermoth.Direction -= 20; }
        if( play_tigermoth.Direction >= 180 && play_tigermoth.Direction < 260 ) { play_tigermoth.Direction += 20; }
    }
    else
    {
        switch(ranval() & 0x1F)
        {
            case 1:
                play_tigermoth.Direction += 2;
                break;
            case 2:
                play_tigermoth.Direction -= 2;
                break;
            case 3:
                play_tigermoth.Direction += 6;
                break;
            case 4:
                play_tigermoth.Direction -= 6;
                break;
            case 5:
                play_tigermoth.Direction += 10;
                break;
            case 6:
                play_tigermoth.Direction -= 10;
                break;
            case 12:
                play_tigermoth.Direction = 180 - play_tigermoth.Direction;
                break;
            case 13:
                play_tigermoth.Direction = 180;
                break;

            case 14:
                if( play_tigermoth.Velocity < play_level + 2 )
                {
                    play_tigermoth.Velocity++;
                }
                break;
            case 15:
                if( play_tigermoth.Velocity > play_level )
                {
                    play_tigermoth.Velocity--;
                }
                break;
        }
    }
    if( play_tigermoth.Direction <    0 ) { play_tigermoth.Direction += 360; }
    if( play_tigermoth.Direction >= 360 ) { play_tigermoth.Direction -= 360; }
}

void UpdateTigermoth()
{
    // Move Tigermoth
    play_tigermoth.Row6Centre.X += play_tigermoth.Row6MoveX[0];
    play_tigermoth.Row6Centre.Y += play_tigermoth.Row6MoveY[0];
    play_tigermoth.Row3Centre.X += play_tigermoth.Row3MoveX[0];
    play_tigermoth.Row3Centre.Y += play_tigermoth.Row3MoveY[0];
    play_tigermoth.Row3Left.X   += play_tigermoth.Row3MoveX[0];
    play_tigermoth.Row3Left.Y   += play_tigermoth.Row3MoveY[0];
    play_tigermoth.Row3Right.X  += play_tigermoth.Row3MoveX[0];
    play_tigermoth.Row3Right.Y  += play_tigermoth.Row3MoveY[0];
    play_tigermoth.Row2Centre.X += play_tigermoth.Row2MoveX[0];
    play_tigermoth.Row2Centre.Y += play_tigermoth.Row2MoveY[0];
    play_tigermoth.Row2Left.X   += play_tigermoth.Row2MoveX[0];
    play_tigermoth.Row2Left.Y   += play_tigermoth.Row2MoveY[0];
    play_tigermoth.Row2Right.X  += play_tigermoth.Row2MoveX[0];
    play_tigermoth.Row2Right.Y  += play_tigermoth.Row2MoveY[0];
    play_tigermoth.Row1Centre.X += play_tigermoth.Row1MoveX[0];
    play_tigermoth.Row1Centre.Y += play_tigermoth.Row1MoveY[0];
    play_tigermoth.Row1Left.X   += play_tigermoth.Row1MoveX[0];
    play_tigermoth.Row1Left.Y   += play_tigermoth.Row1MoveY[0];
    play_tigermoth.Row1Right.X  += play_tigermoth.Row1MoveX[0];
    play_tigermoth.Row1Right.Y  += play_tigermoth.Row1MoveY[0];


    if(play_tigermoth.Head.X + play_tigermoth.HeadMoveX[0] < (80 << 8))
    {
        play_tigermoth.HeadMoveX[0] = (80 << 8) - play_tigermoth.Head.X;
        play_tigermoth.Direction = 360 - play_tigermoth.Direction;
    }
    if(play_tigermoth.Head.X + play_tigermoth.HeadMoveX[0] > (160 << 8))
    {
        play_tigermoth.HeadMoveX[0] = (160 << 8) - play_tigermoth.Head.X;
        play_tigermoth.Direction = 360 - play_tigermoth.Direction;
    }
    play_tigermoth.Head.X += play_tigermoth.HeadMoveX[0];
    play_tigermoth.Head.Y += play_tigermoth.HeadMoveY[0];

    // Let's pretend we're in an array of segments, so we can process easier
    TigermothSegment* segarray = &play_tigermoth.Head;
    for(int idx = 0; idx < 11; idx++)
    {
        // TODO: Explosions at some point?
        if(segarray[idx].SpriteID == 0 || segarray[idx].Health == 0)
        {
            OAM[idx + 1].attr0 |= OBJ_DISABLE;
        }
        else
        {
            OAM[idx + 1].attr0 = OBJ_Y((segarray[idx].Y >> 8) - 16) | ATTR0_COLOR_16 | ATTR0_SQUARE;
            OAM[idx + 1].attr1 = OBJ_X((segarray[idx].X >> 8) - 16) | ATTR1_SIZE_32 | ((idx - 1) % 3 == 2 ? OBJ_HFLIP : 0);
            OAM[idx + 1].attr2 = OBJ_CHAR(segarray[idx].SpriteID) | ATTR2_PRIORITY(2);
        }
    }
}

bool Bullet_PlayerCurved(int BulletIndex)
{
    if( bullets[BulletIndex].direction < 0 ) { bullets[BulletIndex].direction += 360; }
    if( bullets[BulletIndex].direction > 180 ) { bullets[BulletIndex].direction += 4; }
    if( bullets[BulletIndex].direction < 180 && bullets[BulletIndex].direction > 0 ) { bullets[BulletIndex].direction -= 4; }
    if( bullets[BulletIndex].direction >= 360 ) { bullets[BulletIndex].direction -= 360; }
    //if( bullets[BulletIndex].direction < 0 ) { bullets[BulletIndex].direction = 0; }
    return Bullet_PlayerStandard(BulletIndex);
}

bool Bullet_PlayerStandard(int BulletIndex)
{
    // Check hitting Tigermoth parts, if so, cause damage
    TigermothSegment* segarray = &play_tigermoth.Head;  // Let's pretend we're in an array of segments, so we can process easier

    for(int idx = 0; idx < 11; idx++)
    {
        if(segarray[idx].SpriteID != 0 && segarray[idx].Health > 0)
        {
            int tmx = segarray[idx].X;
            int tmy = segarray[idx].Y;

            if( bullets[BulletIndex].x > tmx - (10 << 8)
                    && bullets[BulletIndex].x < tmx + (10 << 8)
                    && bullets[BulletIndex].y > tmy - (10 << 8)
                    && bullets[BulletIndex].y < tmy + (10 << 8) )
            {
                // TODO: Detailed hitcheck?
                segarray[idx].Health--;
                if(segarray[idx].Health == 0) { player_score += 4 + (play_level * 2); } else { player_score++; }
                if( (player_score % 400) == 0 && player_a_spread < (player_score < 5000 ? 2 : 3)) { player_a_spread++; }
                return false;
            }
        }
    }

    return true;
}

bool Bullet_TigermothStandard(int BulletIndex)
{
    int bx = bullets[BulletIndex].x >> 8;
    int by = bullets[BulletIndex].y >> 8;
    if( bx >= player_x - 1 && bx <= player_x + 2 && by >= player_y - 1 && by <= player_y + 2 )
    {
        player_dead = 1;
        return false;
    }

    return true;
}

void ProcessSpread(int X, int Y, const ShotSpread* Spread)
{
    for(int i = Spread->StartAngle; i <= Spread->EndAngle; i += Spread->Spread)
    {
        SpawnBullet( X, Y, i, Spread->Velocity, Spread->Colour, 2, Spread->BulletUpdate );
    }
}
