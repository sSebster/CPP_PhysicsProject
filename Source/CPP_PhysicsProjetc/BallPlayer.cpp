// Fill out your copyright notice in the Description page of Project Settings.


#include "BallPlayer.h"

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

}

