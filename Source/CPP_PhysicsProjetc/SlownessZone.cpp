#include "SlownessZone.h"
#include "BallPlayer.h"
#include "Components/StaticMeshComponent.h"

ASlownessZone::ASlownessZone()
{
    PrimaryActorTick.bCanEverTick = false;

    // Crée un StaticMeshComponent pour la zone
    SlownessMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SlownessMesh"));
    RootComponent = SlownessMesh;

    SlownessMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SlownessMesh->SetGenerateOverlapEvents(true);
}

void ASlownessZone::BeginPlay()
{
    Super::BeginPlay();

    // Ajouter les fonctions de collision pour l'entrée et la sortie
    SlownessMesh->OnComponentBeginOverlap.AddDynamic(this, &ASlownessZone::OnBallEnter);
    SlownessMesh->OnComponentEndOverlap.AddDynamic(this, &ASlownessZone::OnBallExit);
}

void ASlownessZone::OnBallEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("Enter"));
    ABallPlayer* Ball = Cast<ABallPlayer>(OtherActor);
    if (Ball && Ball->GetMesh())
    {
        // Ralentir la balle en modifiant sa vitesse
        FVector CurrentVelocity = Ball->GetMesh()->GetPhysicsLinearVelocity();
        Ball->GetMesh()->SetPhysicsLinearVelocity(CurrentVelocity * SlowFactor);
        
        UE_LOG(LogTemp, Warning, TEXT("Ball Slowed! New Velocity: %s"), *Ball->GetMesh()->GetPhysicsLinearVelocity().ToString());
    }
}

void ASlownessZone::OnBallExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    ABallPlayer* Ball = Cast<ABallPlayer>(OtherActor);
    if (Ball && Ball->GetMesh())
    {
        // Réinitialiser la vitesse de la balle (à sa vitesse d'origine)
        FVector CurrentVelocity = Ball->GetMesh()->GetPhysicsLinearVelocity();
        Ball->GetMesh()->SetPhysicsLinearVelocity(CurrentVelocity / SlowFactor);

        UE_LOG(LogTemp, Warning, TEXT("Ball Exited Slowness Zone, Speed Restored"));
    }
}
