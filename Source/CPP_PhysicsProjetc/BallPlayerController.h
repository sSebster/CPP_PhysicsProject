// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DynamicCube.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "BallPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CPP_PHYSICSPROJETC_API ABallPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	// Associer les actions à des événements
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

private:
	// Fonction appelée pour déplacer la balle
	void MoveMethod(const FInputActionValue& Value);
	void OnJumpStarted();
	void OnJumpCompleted();

	// Fonction appelée pour faire sauter la balle
	//void JumpMethod(const FInputActionValue& Value);

	// Mapping Context pour Enhanced Input
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> BallMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveBallAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpBallAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> GetCube;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> RepulseCube;

	// Fonction pour attirer les cubes vers la balle
	void AttractCubes(const FInputActionValue& Value);

	// Fonction pour repousser les cubes de la balle
	void RepulseCubes(const FInputActionValue& Value);

	// Liste des cubes à attirer ou repousser
	TArray<ADynamicCube*> NearbyCubes;
};
