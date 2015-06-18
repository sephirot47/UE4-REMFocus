#pragma once

#include "Components/ActorComponent.h"
#include "CFocusable.h"
#include "REMHUD.h"
#include "CFocuser.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REMFOCUS_API UCFocuser : public UActorComponent
{
	GENERATED_BODY()

private:
	UCFocusable *currentFocus;
	float GetFocusability(AActor *focusableActor);
	void CalculateFocus();

	FVector2D GetFocusScreenPoint();
	void DrawCrosshair();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite) UTexture2D *crosshairTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float crosshairScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float maxFocusDistance;

	UCFocuser();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Returns the current focus captured by the CFocuser Component
	//Returns null if there's no current focus
	UCFocusable* GetFocus() { return currentFocus; }
};
