// Fill out your copyright notice in the Description page of Project Settings.


#include "BallPlayer.h"
#include "EnhancedInputComponent.h"

// Sets default values
ABallPlayer::ABallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABallPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABallPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABallPlayer::Move);
	Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABallPlayer::Jump);
}

void ABallPlayer::Move(const FInputActionValue& InputValue)
{
	const FVector VectorDirection = FVector(InputValue.Get<FVector2d>().X,InputValue.Get<FVector2d>().Y,0);
	Mesh->AddImpulse(VectorDirection);
}

void ABallPlayer::Jump(const FInputActionValue& InputValue)
{
	const FVector2d VectorDirection = InputValue.Get<FVector2d>();
}

