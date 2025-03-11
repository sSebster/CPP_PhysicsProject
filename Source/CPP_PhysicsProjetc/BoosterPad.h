#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoosterPad.generated.h"

// Forward declaration
class UStaticMeshComponent;

UCLASS()
class CPP_PHYSICSPROJETC_API ABoosterPad : public AActor
{
	GENERATED_BODY()

public:
	ABoosterPad();

protected:
	virtual void BeginPlay() override;

	// Méthode appelée lors de la collision
	UFUNCTION()
	void OnBallHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Force appliquée sur le BallPlayer
	UPROPERTY(EditAnywhere, Category = "BoosterPad")
	float BoostForce = 150000.0f;

	// Mesh du booster
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BoosterMesh;
};
