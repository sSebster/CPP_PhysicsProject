// Fill out your copyright notice in the Description page of Project Settings.


#include "BallPlayer.h"
#include "EnhancedInputComponent.h"

// Sets default values
ABallPlayer::ABallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	SetRootComponent(Mesh);

	// Active la physique sur la balle
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(true);

	Mesh->OnComponentHit.AddDynamic(this, &ABallPlayer::OnHit);

}

// Called when the game starts or when spawned
void ABallPlayer::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	
	// Active la physique
	Mesh->SetSimulatePhysics(true);

	// Désactive la gravité si nécessaire (pour tester le mouvement uniquement)
	Mesh->SetEnableGravity(true);
}

// Called every frame
void ABallPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	IsOnGround();
}

void ABallPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Si la balle touche le sol, réinitialise IsJumping
	//UE_LOG(LogTemp, Warning , TEXT("HIT"));
	if (HitComponent && OtherComp && OtherComp->IsA(UPrimitiveComponent::StaticClass()))
	{
		IsJumping = false;
		CanDoubleJump = false;
		//UE_LOG(LogTemp, Warning , TEXT("Reset jump"));
	}
	if(!HitComponent)
	{
		IsJumping = true;
	}
}

void ABallPlayer::IsOnGround()
{
	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0, 0, 100.0f); // Trace 50 unités sous la balle

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // Ignore le joueur lui-même

	Grounded = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);
}
