#include "REMFocus.h"
#include "REMPlayer.h"


AREMPlayer::AREMPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AREMPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AREMPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AREMPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

