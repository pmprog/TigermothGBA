
#pragma once

typedef void(*StageUpdate)();

void SetStage(StageUpdate Next);

void pmprog_update();
void menu_update();
void menu2_update();
void play_update();
void setuparena_update();
void gameover_update();

