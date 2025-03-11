#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlownessZone.generated.h"

class UStaticMeshComponent;

UCLASS()
class CPP_PHYSICSPROJETC_API ASlownessZone : public AActor
{
	GENERATED_BODY()

public:
	ASlownessZone();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBallEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
					 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
					 bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBallExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
					UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category = "Slowness")
	float SlowFactor = 0.5f; // Facteur de ralentissement (0.5 = 50%)

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* SlownessMesh;
};
