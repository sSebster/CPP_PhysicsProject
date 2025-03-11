// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "BallPlayer.generated.h"

UCLASS()
class CPP_PHYSICSPROJETC_API ABallPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABallPlayer();

	// Permet d'accéder au Mesh depuis d'autres classes
	UStaticMeshComponent* GetMesh() const { return Mesh; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysiqueCamera")
	UCameraComponent* BallCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Jump")
	bool IsJumping;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Jump")
	bool CanDoubleJump;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Jump")
	bool HasDoubleJump;

	void IsOnGround();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Jump")
	bool Grounded;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	//UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	//TObjectPtr<UInputAction> MoveAction;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	//TObjectPtr<UInputAction> JumpAction;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	//TObjectPtr<UInputMappingContext> IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	           FVector NormalImpulse,
	           const FHitResult& Hit);
};
