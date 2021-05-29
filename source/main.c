
#include "gba.h"
#include "stages.h"
#include "tigermoth_bin.h"
#include "vars.h"
#include "bullets.h"

StageUpdate activestage = pmprog_update;

int main(void)
{
	irqInit();
	irqSet( IRQ_VBLANK, mmVBlank );	// Maxmod VBlank
	irqEnable(IRQ_VBLANK);

	InitC64Palette();

	SetBitmapMode(true);

	InitBullets();

    raninit( 44 );

	// Upload graphics data (half the image data)
	//CpuFastSet(polymath_font_bin, (u16*)BITMAP_OBJ_BASE_ADR,(polymath_font_bin_size/4) | COPY32);
	CpuFastSet(tigermoth_bin, (u16*)BITMAP_OBJ_BASE_ADR,(tigermoth_bin_size/4) | COPY32);

	// initialise maxmod with soundbank and 8 channels
    mmInitDefault( (mm_addr)soundbank_bin, 8 );

	while (1)
	{
		VBlankIntrWait();
		mmFrame();
		scanKeys();
		activestage();
	}
}

void SetStage(StageUpdate Next)
{
	frame_delay = 0;
	frame_time = 0;
	stage_initialised = 0;
	activestage = Next;
}
