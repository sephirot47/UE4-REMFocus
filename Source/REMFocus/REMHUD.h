// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "REMHUD.generated.h"

UCLASS()
class REMFOCUS_API AREMHUD : public AHUD
{
	GENERATED_BODY()

private:
	struct DrawTextureInfo
	{
		UTexture2D *texture;
		float x, y, scale;
	};

	TArray<DrawTextureInfo> iconsToBeDrawn;

public:
	AREMHUD();
	virtual void DrawHUD() override;

	void DrawTextureHUD(UTexture2D &texture, float x, float y, float scale = 1.0f);
};
