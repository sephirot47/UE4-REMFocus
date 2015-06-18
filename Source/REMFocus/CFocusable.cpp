#include "REMFocus.h"
#include "CFocusable.h"

UCFocusable::UCFocusable()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
}

void UCFocusable::BeginPlay()
{
	Super::BeginPlay();
}

void UCFocusable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}