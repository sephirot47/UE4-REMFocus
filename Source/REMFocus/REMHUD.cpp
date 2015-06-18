#include "REMFocus.h"
#include "REMHUD.h"

AREMHUD::AREMHUD()
{
}

void AREMHUD::DrawHUD()
{
	Super::DrawHUD();

	for (int i = 0; i < iconsToBeDrawn.Num(); ++i)
	{
		DrawTextureInfo dti = iconsToBeDrawn[i];
		DrawTextureSimple(dti.texture, dti.x, dti.y, dti.scale);
	}
	iconsToBeDrawn.Empty();
}

void AREMHUD::DrawTextureHUD(UTexture2D &texture, float x, float y, float scale)
{
	DrawTextureInfo dti;
	dti.texture = &texture;
	dti.x = x; dti.y = y; dti.scale = scale;
	iconsToBeDrawn.Add(dti);
}