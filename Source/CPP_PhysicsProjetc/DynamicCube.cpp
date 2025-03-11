// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicCube.h"

// Sets default values
ADynamicCube::ADynamicCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void ADynamicCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADynamicCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

