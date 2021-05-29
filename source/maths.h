
#pragma once

#include "gba.h"

// EE (8.8) maths in s16

/*

s16 EE_bytetoEE(s8 value, u8 fraction);
s16 EE_inttoEE(int value, u8 fraction);
s8 EE_EEtobyte(s16 value);
int EE_EEtoint(s16 value);

s16 EE_Add(s16 source, s16 value);
s16 EE_Sub(s16 source, s16 value);
s16 EE_Mul(s16 source, s16 value);
s16 EE_Div(s16 source, s16 value);

s16 EE_sin(int degrees);
s16 EE_cos(int degrees);
*/

int sini(int degrees);
int cosi(int degrees);

int directionto_points(u8 x1, u8 y1, u8 x2, u8 y2);
int directionto(int x, int y);

void raninit( u8 seed );
u8 ranval();
