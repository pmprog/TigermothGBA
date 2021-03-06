
#include "maths.h"
#include "vars.h"

const int sine[] = {
      0 ,    4 ,    9 ,   13 ,   18 ,   22 ,   27 ,   31 ,   36 ,   40 ,   44 ,   49 ,   53 ,   58 ,   62 ,   66 ,   71 ,   75 ,   79 ,   83
 ,   88 ,   92 ,   96 ,  100 ,  104 ,  108 ,  112 ,  116 ,  120 ,  124 ,  128 ,  132 ,  136 ,  139 ,  143 ,  147 ,  150 ,  154 ,  158 ,  161
 ,  165 ,  168 ,  171 ,  175 ,  178 ,  181 ,  184 ,  187 ,  190 ,  193 ,  196 ,  199 ,  202 ,  204 ,  207 ,  210 ,  212 ,  215 ,  217 ,  219
 ,  222 ,  224 ,  226 ,  228 ,  230 ,  232 ,  234 ,  236 ,  237 ,  239 ,  241 ,  242 ,  243 ,  245 ,  246 ,  247 ,  248 ,  249 ,  250 ,  251
 ,  252 ,  253 ,  254 ,  254 ,  255 ,  255 ,  255 ,  256 ,  256 ,  256 ,  256 ,  256 ,  256 ,  256 ,  255 ,  255 ,  255 ,  254 ,  254 ,  253
 ,  252 ,  251 ,  250 ,  249 ,  248 ,  247 ,  246 ,  245 ,  243 ,  242 ,  241 ,  239 ,  237 ,  236 ,  234 ,  232 ,  230 ,  228 ,  226 ,  224
 ,  222 ,  219 ,  217 ,  215 ,  212 ,  210 ,  207 ,  204 ,  202 ,  199 ,  196 ,  193 ,  190 ,  187 ,  184 ,  181 ,  178 ,  175 ,  171 ,  168
 ,  165 ,  161 ,  158 ,  154 ,  150 ,  147 ,  143 ,  139 ,  136 ,  132 ,  128 ,  124 ,  120 ,  116 ,  112 ,  108 ,  104 ,  100 ,   96 ,   92
 ,   88 ,   83 ,   79 ,   75 ,   71 ,   66 ,   62 ,   58 ,   53 ,   49 ,   44 ,   40 ,   36 ,   31 ,   27 ,   22 ,   18 ,   13 ,    9 ,    4
 ,    0 ,   -4 ,   -9 ,  -13 ,  -18 ,  -22 ,  -27 ,  -31 ,  -36 ,  -40 ,  -44 ,  -49 ,  -53 ,  -58 ,  -62 ,  -66 ,  -71 ,  -75 ,  -79 ,  -83
 ,  -88 ,  -92 ,  -96 , -100 , -104 , -108 , -112 , -116 , -120 , -124 , -128 , -132 , -136 , -139 , -143 , -147 , -150 , -154 , -158 , -161
 , -165 , -168 , -171 , -175 , -178 , -181 , -184 , -187 , -190 , -193 , -196 , -199 , -202 , -204 , -207 , -210 , -212 , -215 , -217 , -219
 , -222 , -224 , -226 , -228 , -230 , -232 , -234 , -236 , -237 , -239 , -241 , -242 , -243 , -245 , -246 , -247 , -248 , -249 , -250 , -251
 , -252 , -253 , -254 , -254 , -255 , -255 , -255 , -256 , -256 , -256 , -256 , -256 , -256 , -256 , -255 , -255 , -255 , -254 , -254 , -253
 , -252 , -251 , -250 , -249 , -248 , -247 , -246 , -245 , -243 , -242 , -241 , -239 , -237 , -236 , -234 , -232 , -230 , -228 , -226 , -224
 , -222 , -219 , -217 , -215 , -212 , -210 , -207 , -204 , -202 , -199 , -196 , -193 , -190 , -187 , -184 , -181 , -178 , -175 , -171 , -168
 , -165 , -161 , -158 , -154 , -150 , -147 , -143 , -139 , -136 , -132 , -128 , -124 , -120 , -116 , -112 , -108 , -104 , -100 ,  -96 ,  -92
 ,  -88 ,  -83 ,  -79 ,  -75 ,  -71 ,  -66 ,  -62 ,  -58 ,  -53 ,  -49 ,  -44 ,  -40 ,  -36 ,  -31 ,  -27 ,  -22 ,  -18 ,  -13 ,   -9 ,   -4
 };

const int cosine[] = {
    256 ,  256 ,  256 ,  256 ,  255 ,  255 ,  255 ,  254 ,  254 ,  253 ,  252 ,  251 ,  250 ,  249 ,  248 ,  247 ,  246 ,  245 ,  243 ,  242
 ,  241 ,  239 ,  237 ,  236 ,  234 ,  232 ,  230 ,  228 ,  226 ,  224 ,  222 ,  219 ,  217 ,  215 ,  212 ,  210 ,  207 ,  204 ,  202 ,  199
 ,  196 ,  193 ,  190 ,  187 ,  184 ,  181 ,  178 ,  175 ,  171 ,  168 ,  165 ,  161 ,  158 ,  154 ,  150 ,  147 ,  143 ,  139 ,  136 ,  132
 ,  128 ,  124 ,  120 ,  116 ,  112 ,  108 ,  104 ,  100 ,   96 ,   92 ,   88 ,   83 ,   79 ,   75 ,   71 ,   66 ,   62 ,   58 ,   53 ,   49
 ,   44 ,   40 ,   36 ,   31 ,   27 ,   22 ,   18 ,   13 ,    9 ,    4 ,    0 ,   -4 ,   -9 ,  -13 ,  -18 ,  -22 ,  -27 ,  -31 ,  -36 ,  -40
 ,  -44 ,  -49 ,  -53 ,  -58 ,  -62 ,  -66 ,  -71 ,  -75 ,  -79 ,  -83 ,  -88 ,  -92 ,  -96 , -100 , -104 , -108 , -112 , -116 , -120 , -124
 , -128 , -132 , -136 , -139 , -143 , -147 , -150 , -154 , -158 , -161 , -165 , -168 , -171 , -175 , -178 , -181 , -184 , -187 , -190 , -193
 , -196 , -199 , -202 , -204 , -207 , -210 , -212 , -215 , -217 , -219 , -222 , -224 , -226 , -228 , -230 , -232 , -234 , -236 , -237 , -239
 , -241 , -242 , -243 , -245 , -246 , -247 , -248 , -249 , -250 , -251 , -252 , -253 , -254 , -254 , -255 , -255 , -255 , -256 , -256 , -256
 , -256 , -256 , -256 , -256 , -255 , -255 , -255 , -254 , -254 , -253 , -252 , -251 , -250 , -249 , -248 , -247 , -246 , -245 , -243 , -242
 , -241 , -239 , -237 , -236 , -234 , -232 , -230 , -228 , -226 , -224 , -222 , -219 , -217 , -215 , -212 , -210 , -207 , -204 , -202 , -199
 , -196 , -193 , -190 , -187 , -184 , -181 , -178 , -175 , -171 , -168 , -165 , -161 , -158 , -154 , -150 , -147 , -143 , -139 , -136 , -132
 , -128 , -124 , -120 , -116 , -112 , -108 , -104 , -100 ,  -96 ,  -92 ,  -88 ,  -83 ,  -79 ,  -75 ,  -71 ,  -66 ,  -62 ,  -58 ,  -53 ,  -49
 ,  -44 ,  -40 ,  -36 ,  -31 ,  -27 ,  -22 ,  -18 ,  -13 ,   -9 ,   -4 ,    0 ,    4 ,    9 ,   13 ,   18 ,   22 ,   27 ,   31 ,   36 ,   40
 ,   44 ,   49 ,   53 ,   58 ,   62 ,   66 ,   71 ,   75 ,   79 ,   83 ,   88 ,   92 ,   96 ,  100 ,  104 ,  108 ,  112 ,  116 ,  120 ,  124
 ,  128 ,  132 ,  136 ,  139 ,  143 ,  147 ,  150 ,  154 ,  158 ,  161 ,  165 ,  168 ,  171 ,  175 ,  178 ,  181 ,  184 ,  187 ,  190 ,  193
 ,  196 ,  199 ,  202 ,  204 ,  207 ,  210 ,  212 ,  215 ,  217 ,  219 ,  222 ,  224 ,  226 ,  228 ,  230 ,  232 ,  234 ,  236 ,  237 ,  239
 ,  241 ,  242 ,  243 ,  245 ,  246 ,  247 ,  248 ,  249 ,  250 ,  251 ,  252 ,  253 ,  254 ,  254 ,  255 ,  255 ,  255 ,  256 ,  256 ,  256
 };



/*
s16 EE_bytetoEE(s8 value, u8 fraction)
{
    return 0;
}

s16 EE_inttoEE(int value, u8 fraction)
{
    return 0;
}

s8 EE_EEtobyte(s16 value)
{
    return 0;
}

int EE_EEtoint(s16 value)
{
    return 0;
}

s16 EE_Add(s16 source, s16 value)
{

}

s16 EE_Sub(s16 source, s16 value)
{

}

s16 EE_Mul(s16 source, s16 value)
{

}

s16 EE_Div(s16 source, s16 value)
{

}

s16 EE_sin(int degrees)
{
    return 0;
}

s16 EE_cos(int degrees)
{
    return 0;
}
*/

int sini(int degrees)
{
    int deg = degrees;
    if(deg < 0)
    {
        while(deg < 0)
        {
            deg += 360;
        }
    }
    if(deg >= 360)
    {
        while(deg >= 360)
        {
            deg -= 360;
        }
    }
    return sine[deg];
}

int cosi(int degrees)
{
    int deg = degrees;
    if(deg < 0)
    {
        while(deg < 0)
        {
            deg += 360;
        }
    }
    if(deg >= 360)
    {
        while(deg >= 360)
        {
            deg -= 360;
        }
    }
    return cosine[deg];
}

// atan2 replacement based on 
// https://github.com/MartinStokroos/fastCORDIC/blob/master/src/cordic.cpp#L74
int directionto_points(u8 x1, u8 y1, u8 x2, u8 y2)
{
    // atan2(destination.x - origin.x, origin.y - destination.y) * M_RAD_TO_DEG

    int x = (int)x2 - (int)x1;
    int y = (int)y1 - (int)y2;
    return directionto( x, y );
}

int directionto(int x, int y)
{
    int x0 = x;
    int y0 = y;
    int angle = 0;
    bool sign = false;
    int tmp = 0;

    if(y0 < 0)
    {
        x0 = -x0;
        y0 = -y0;
        angle = 180;
    }
    if(x0 < 0)
    {
        tmp = x0;
        x0 = y0;
        y0 = -tmp;
        angle += 90;
    }
    if(y0 > x0)
    {
        sign = true;
        angle += 90;
        tmp = x0;
        x0 = y0;
        y0 = tmp;
    }
    int curangle = 22;
    int phi = 0;
    u8 k = 0;
    int x1 = 0;
    int y1 = 0;
    while( k <= 4 )
    {
        //x1=cosi(k)
        k++;
    }
    int radius = x0;
    angle += ( sign ? -phi : +phi );
    return angle;
}

// Random Number Generator, adapted from
// http://burtleburtle.net/bob/rand/smallprng.html

#define rot(x,k) ( ( x << k ) | ( x >> (8 - k) ) )

u8 ranval()
{
    u8 e = randomsource.a - rot(randomsource.b, 5);
    randomsource.a = randomsource.b ^ rot(randomsource.c, 3);
    randomsource.b = randomsource.c + randomsource.d;
    randomsource.c = randomsource.d + e;
    randomsource.d = e + randomsource.a;
    return randomsource.d;
}

void raninit( u8 seed )
{
    u8 i;
    randomsource.a = 0x5E;
    randomsource.b = randomsource.c = randomsource.d = seed;
    for (i=0; i<20; ++i)
    {
        ranval();
    }
}

