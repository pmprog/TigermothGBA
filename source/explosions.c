
#include "explosions.h"

void ClearExplosions()
{
    u8 expls = 0;
    for(int idx = 15; idx < 45; idx++)
    {
        OAM[idx].attr0 |= OBJ_DISABLE;
    }
}

void CreateExplosion(int X, int Y)
{
    for(int idx = 15; idx < 45; idx++)
    {
        if( (OAM[idx].attr0 & OBJ_DISABLE) == OBJ_DISABLE )
        {
            OAM[idx].attr0 = OBJ_Y(Y - 16) | ATTR0_COLOR_16 | ATTR0_SQUARE;
            OAM[idx].attr1 = OBJ_X(X - 16) | ATTR1_SIZE_32;
            OAM[idx].attr2 = OBJ_CHAR( 596 ) | ATTR2_PRIORITY(2);
            return;
        }
    }
}

void UpdateExplosions()
{
    for(int idx = 15; idx < 45; idx++)
    {
        if( (OAM[idx].attr0 & OBJ_DISABLE) == 0 )
        {
            // TODO: Advance Explosion Graphics, and disable at end
            int nextframe = OBJ_CHAR( OAM[idx].attr2 ) + 16;
            OAM[idx].attr2 = OBJ_CHAR( nextframe ) | ATTR2_PRIORITY(2);
            if( nextframe > 628 )
            {
                OAM[idx].attr0 |= OBJ_DISABLE;
            }
        }
    }
}

int CountExplosions()
{
    u8 expls = 0;
    for(int idx = 15; idx < 45; idx++)
    {
        if( (OAM[idx].attr0 & OBJ_DISABLE) == 0 )
        {
            expls++;
        }
    }
    return expls;
}
