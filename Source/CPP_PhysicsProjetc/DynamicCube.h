// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicCube.generated.h"

UCLASS()
class CPP_PHYSICSPROJETC_API ADynamicCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADynamicCube();
	UStaticMeshComponent* GetMesh() const { return Mesh; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CubeMesh", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;
};
