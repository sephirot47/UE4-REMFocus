#pragma once

#include "Components/ActorComponent.h"
#include "CFocusable.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REMFOCUS_API UCFocusable : public UActorComponent
{
	GENERATED_BODY()

public:

	UCFocusable();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnFocusEnter() { }
	virtual void OnFocusExit() { }
};
