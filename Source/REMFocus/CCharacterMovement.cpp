#include "REMFocus.h"
#include "CCharacterMovement.h"

UCCharacterMovement::UCCharacterMovement()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	rotSpeed = 75.0f;
}


void UCCharacterMovement::BeginPlay()
{
	Super::BeginPlay();
	actor = Cast<ACharacter>(GetOwner());

	CurrentRot = actor->GetActorRotation().Euler();
	this->GetOwner()->InputComponent->BindAxis("MoveForward", this, &UCCharacterMovement::HandleVerticalAxis);
	this->GetOwner()->InputComponent->BindAxis("MoveRight", this, &UCCharacterMovement::HandleHorizontalAxis);
	this->GetOwner()->InputComponent->BindAxis("MouseX", this, &UCCharacterMovement::HandleMouseX);
	this->GetOwner()->InputComponent->BindAxis("MouseY", this, &UCCharacterMovement::HandleMouseY);
}

void UCCharacterMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!MovementInput.IsZero())
	{
		MovementInput = MovementInput.SafeNormal() * speed;
		FVector minput3D(MovementInput.X, MovementInput.Y, 0.0f);
		if(actor) actor->AddMovementInput(minput3D);

		MovementInput = FVector2D::ZeroVector;
	}

	if (!RotationInput.IsZero())
	{
		CurrentRot += RotationInput * rotSpeed * DeltaTime;
		if (actor) actor->AddControllerPitchInput(RotationInput.Y * DeltaTime);
		if (actor) actor->AddControllerYawInput(RotationInput.Z * DeltaTime);

		RotationInput = FVector::ZeroVector;
	}
}

void UCCharacterMovement::HandleVerticalAxis(float v)
{
	FVector mov = actor->GetActorForwardVector() * FMath::Clamp<float>(v, -1.0f, 1.0f);
	MovementInput += FVector2D(mov.X, mov.Y);
}

void UCCharacterMovement::HandleHorizontalAxis(float v)
{
	FVector mov = actor->GetActorRightVector() * FMath::Clamp<float>(v, -1.0f, 1.0f);
	MovementInput += FVector2D(mov.X, mov.Y);
}

void UCCharacterMovement::HandleMouseX(float v)
{
	RotationInput.Z += v * rotSpeed;
}

void UCCharacterMovement::HandleMouseY(float v)
{
	RotationInput.Y += v * rotSpeed;
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, FString::SanitizeFloat(v));
}

