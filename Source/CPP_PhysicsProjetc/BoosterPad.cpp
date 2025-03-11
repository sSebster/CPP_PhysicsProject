#include "BoosterPad.h"
#include "BallPlayer.h"
#include "Components/StaticMeshComponent.h"

ABoosterPad::ABoosterPad()
{
	PrimaryActorTick.bCanEverTick = false;

	// Crée et attache le mesh du booster
	BoosterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoosterMesh"));
	RootComponent = BoosterMesh;

	// Active les événements de collision
	BoosterMesh->SetNotifyRigidBodyCollision(true);
	BoosterMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ABoosterPad::BeginPlay()
{
	Super::BeginPlay();

	// Bind la méthode de collision
	BoosterMesh->OnComponentHit.AddDynamic(this, &ABoosterPad::OnBallHit);
}

void ABoosterPad::OnBallHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Vérifie si l'acteur en collision est une BallPlayer
	ABallPlayer* BallPlayer = Cast<ABallPlayer>(OtherActor);
	if (BallPlayer && BallPlayer->GetMesh())
	{
		// Calcule la direction vers l'avant du BoosterPad
		FVector BoostDirection = GetActorForwardVector();

		// Applique l'impulsion pour propulser la balle
		BallPlayer->GetMesh()->AddImpulse(BoostDirection * BoostForce);

		UE_LOG(LogTemp, Warning, TEXT("Ball boostée dans la direction : %s"), *BoostDirection.ToString());
	}
}
