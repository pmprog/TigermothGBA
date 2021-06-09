
#include "stage_play.h"

const ShotSpread play_tigermoth_shotspreads[] = {
  //  X,   Y,Sprd,Col,Vel, Method
  { 180, 180,   1,  7,  4, Bullet_TigermothStandard }, //  1 : Straight Shot
  { 170, 190,  10, 14,  3, Bullet_TigermothStandard }, //  2 : Mini Spread
  { 160, 200,  10, 13,  3, Bullet_TigermothStandard }, //  3 : Mid Spread
  { 100, 260,  10, 13,  3, Bullet_TigermothStandard }, //  4 : Wide Spread
  {  90, 180,  10, 13,  2, Bullet_TigermothStandard }, //  5 : Right Quarter
  { 180, 270,  10, 13,  2, Bullet_TigermothStandard }, //  6 : Left Quarter
  {  90, 180,   5, 13,  2, Bullet_TigermothStandard }, //  7 : Right Quarter (Tight)
  { 180, 270,   5, 13,  2, Bullet_TigermothStandard }, //  8 : Left Quarter (Tight)
  {   0, 360,  60, 10,  1, Bullet_TigermothStandard }, //  9 : Full Surround
  {  20, 370,  60, 10,  1, Bullet_TigermothStandard }, // 10 : Full Surround
  {  40, 370,  60, 10,  1, Bullet_TigermothStandard }, // 11 : Full Surround
};

const int play_tigermoth_patterns[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //  0 : No shot
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //  1 : Slow shot
  0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //  2 : Mini Spread
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //  3 : Wide Spread
  5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //  4 : Quarter spread right
  6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //  5 : Quarter spread left
  5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //  6 : Quarter spread right (Tight)
  6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //  7 : Quarter spread left (Tight)
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //  8 : Mid Spread
  1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, //  9 : Fast Shot
  1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, // 10 : Mid Shot
  1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, // 11 : Rapid Fire
  9, 0,10, 0,11, 0, 9, 0,10, 0,11, 0, 9, 0,10, 0,11, 0, 9, 0,10, 0,11, 0, 9, 0,10, 0,11, 0, 9, 0, // 12 : Covering all bases :)
  9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 13 : Covering all bases - Slowly
};
