#include "REMFocus.h"
#include "CFocuser.h"

UCFocuser::UCFocuser()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTex(TEXT("/Game/StarterContent/Textures/T_Spark_Core.T_Spark_Core"));
	crosshairTexture = CrosshairTex.Object;

	crosshairScale = 0.05f;
	maxFocusDistance = 5000.0f;
}

void UCFocuser::BeginPlay()
{
	Super::BeginPlay();
}

void UCFocuser::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CalculateFocus();
	if (currentFocus) DrawCrosshair();
}

float UCFocuser::GetFocusability(AActor *focusableActor)
{
	//Let's get the direction from the focuser to the focusable
	FVector dirToFocusable = focusableActor->GetActorLocation() - this->GetOwner()->GetActorLocation();
	dirToFocusable.Normalize();

	float dot = FVector::DotProduct(dirToFocusable, this->GetOwner()->GetActorForwardVector());
	if (dot >= 0.0f) //If the focusable is in front of the focuser (not behind basically, in an angle of 180 in front of him)
	{
		FVector p1 = GetOwner()->GetActorLocation(), p2 = focusableActor->GetActorLocation();
		float distance = FVector::Dist(p1, p2);
		if (distance <= maxFocusDistance) 
			return distance - dot * distance * 0.7f;
	}
	return -1.0f;
}


//Calculate the current focus
void UCFocuser::CalculateFocus()
{
	float minFocusability = 9999999.9f;
	UCFocusable *focus = nullptr;

	//For every actor in the scene
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		TArray<UCFocusable*> comps;
		ActorItr->GetComponents(comps); //Let comps be an array of all the UCFocusable components in the actor

		if (comps.Num() > 0) //If the actor actually contains a component of type UCFocusable
		{
			UCFocusable *focusable = comps[0]; //Get the UCFocusable component itself
			AActor *focusableActor = focusable->GetOwner(); //Get the owner actor, in order to do some transform maths
			float focusability = GetFocusability(focusableActor);
			if (focusability < minFocusability && focusability >= 0.0f)
			{
				minFocusability = focusability;
				focus = focusable;
			}
		}
	}

	if (focus && focus != currentFocus) focus->OnFocusEnter();
	if (currentFocus && focus != currentFocus) currentFocus->OnFocusExit();
	currentFocus = focus;
}

FVector2D UCFocuser::GetFocusScreenPoint()
{
	if (!currentFocus) return FVector2D::ZeroVector;
	FVector2D result;
	UGameplayStatics::GetPlayerController(GetOwner(), 0)->ProjectWorldLocationToScreen(currentFocus->GetOwner()->GetActorLocation(), result);
	return result;
}

void UCFocuser::DrawCrosshair()
{
	if (!currentFocus) return;

	AREMHUD *hud = Cast<AREMHUD>( UGameplayStatics::GetPlayerController(GetOwner(), 0)->GetHUD() );
	FVector2D screenPos = GetFocusScreenPoint();

	FVector p1 = GetOwner()->GetActorLocation(), p2 = currentFocus->GetOwner()->GetActorLocation();
	float distance = FVector::Dist(p1, p2);

	screenPos.X -= crosshairTexture->GetSurfaceWidth() * crosshairScale * 0.5f;
	screenPos.Y -= crosshairTexture->GetSurfaceHeight() * crosshairScale * 0.5f;
	hud->DrawTextureHUD(*crosshairTexture, screenPos.X, screenPos.Y, crosshairScale);
}