// Fill out your copyright notice in the Description page of Project Settings.

#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "BallPlayer.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h"
#include "BallPlayerController.h"


//UPROPERTY(EditAnywhere, Category = "Input")
//TObjectPtr<UInputMappingContext> BallMappingContext;

//UPROPERTY(EditAnywhere, Category = "Input")
//TObjectPtr<UInputAction> MoveAction;

//UPROPERTY(EditAnywhere, Category = "Input")
//TObjectPtr<UInputAction> JumpAction;


void ABallPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Récupérer le Enhanced Input Local Player Subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// Ajouter le contexte d'entrée de Paddle
		if (BallMappingContext)
		{
			Subsystem->AddMappingContext(BallMappingContext, 0);
		}
	}
}

// Configuration des liaisons Input
void ABallPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Caster le composant Enhanced Input
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Liaison de l'action IA_MovePaddle à la fonction MovePaddle
		if (MoveBallAction)
		{
			EnhancedInput->BindAction(MoveBallAction, ETriggerEvent::Triggered, this, &ABallPlayerController::MoveMethod);
		}
		if (JumpBallAction)
		{
			EnhancedInput->BindAction(JumpBallAction, ETriggerEvent::Started, this, &ABallPlayerController::OnJumpStarted);
			EnhancedInput->BindAction(JumpBallAction, ETriggerEvent::Completed, this, &ABallPlayerController::OnJumpCompleted);
		}
		EnhancedInput->BindAction(GetCube, ETriggerEvent::Triggered, this, &ABallPlayerController::AttractCubes);
		EnhancedInput->BindAction(RepulseCube, ETriggerEvent::Started, this, &ABallPlayerController::RepulseCubes);
	}
}

void ABallPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	NearbyCubes.Empty();
	for (TActorIterator<ADynamicCube> CubeItr(GetWorld()); CubeItr; ++CubeItr)
	{
		float Distance = FVector::Dist(GetPawn()->GetActorLocation(), CubeItr->GetActorLocation());
		if (Distance <= 1000.0f)
		{
			NearbyCubes.Add(*CubeItr);
		}
	}
}

void ABallPlayerController::MoveMethod(const FInputActionValue& Value)
{
    ABallPlayer* BallPlayer = Cast<ABallPlayer>(GetPawn());

    // Vérifie que le Pawn est valide
    if (!BallPlayer || !BallPlayer->BallCamera || !BallPlayer->GetMesh())
    {
        UE_LOG(LogTemp, Error, TEXT("BallPlayer, BallCamera ou Mesh est NULL !"));
        return;
    }

    // Récupère la direction forward et right de la caméra
    const FVector ForwardDirection = BallPlayer->BallCamera->GetForwardVector(); // Direction dans laquelle la caméra regarde
    const FVector RightDirection = BallPlayer->BallCamera->GetRightVector(); // Direction à droite de la caméra

    // Normalise les directions pour éviter des forces trop importantes
    const FVector NormalizedForward = ForwardDirection.GetSafeNormal();
    const FVector NormalizedRight = RightDirection.GetSafeNormal();

    // Applique une force en fonction de la direction du vecteur d'input
    // On suppose ici que la valeur de l'input correspond à une entrée dans les axes X et Y pour ZQSD

    // Si on appuie sur W ou S, cela correspond à la direction forward ou backward
    const float ForwardInput = Value.Get<FVector2d>().X;  // Y correspond au mouvement avant/arrière (ZQSD)
    // Si on appuie sur A ou D, cela correspond à la direction droite/gauche
    const float RightInput = -Value.Get<FVector2d>().Y;    // X correspond au mouvement droite/gauche (ZQSD)

    // Debugging : Vérifie les vecteurs forward et right pour voir si ça correspond à ce que tu attends
    //UE_LOG(LogTemp, Warning, TEXT("Forward: %s, Right: %s"), *NormalizedForward.ToString(), *NormalizedRight.ToString());

    // Calcul de la force en fonction des inputs
    const FVector Force = (NormalizedForward * ForwardInput + NormalizedRight * RightInput) * 100000.0f; // Ajuste le facteur de force

    // Ajoute la force au Mesh de la balle
    BallPlayer->GetMesh()->AddForce(Force);

    // Debugging : Trace une ligne pour afficher la direction dans laquelle la balle devrait aller
    const FVector BallPosition = BallPlayer->GetActorLocation();
    const FVector LineEnd = BallPosition + Force.GetSafeNormal() * 500.0f; // Affiche une ligne dans la direction de la force
    //DrawDebugLine(GetWorld(), BallPosition, LineEnd, FColor::Red, false, 0.1f, 0, 2.0f);

    // Affiche dans le log la direction de la force
    //UE_LOG(LogTemp, Warning, TEXT("Force: %s"), *Force.ToString());
}



// Appelé lorsque l'input est pressé
void ABallPlayerController::OnJumpStarted()
{
	ABallPlayer* BallPlayer = Cast<ABallPlayer>(GetPawn());

	if (!BallPlayer || !BallPlayer->GetMesh())
	{
		//UE_LOG(LogTemp, Error, TEXT("BallPlayer ou Mesh introuvable pour Jump"));
		return;
	}

	// Premier saut si au sol
	if (!BallPlayer->IsJumping && BallPlayer->Grounded)
	{
		FVector JumpForce = FVector(0, 0, 300000.0f);
		BallPlayer->GetMesh()->AddImpulse(JumpForce);

		BallPlayer->IsJumping = true;
		BallPlayer->HasDoubleJump = false;
		//UE_LOG(LogTemp, Warning, TEXT("Premier saut effectué"));
	}
	// Double saut si disponible
	else if (BallPlayer->CanDoubleJump && !BallPlayer->Grounded)
	{
		FVector JumpForce = FVector(0, 0, 300000.0f);
		BallPlayer->GetMesh()->AddImpulse(JumpForce);

		BallPlayer->CanDoubleJump = false; // Désactive le double saut
		BallPlayer->HasDoubleJump = true;
		//UE_LOG(LogTemp, Warning, TEXT("Double saut effectué"));
	}
}

// Appelé lorsque l'input est relâché
void ABallPlayerController::OnJumpCompleted()
{
	ABallPlayer* BallPlayer = Cast<ABallPlayer>(GetPawn());
	if (!BallPlayer)
	{
		return;
	}

	// Réautorise le double saut après relâchement
	if (BallPlayer->IsJumping && !BallPlayer->HasDoubleJump)
	{
		BallPlayer->CanDoubleJump = true;
		//UE_LOG(LogTemp, Warning, TEXT("Input relâché : Double saut prêt"));
	}
}

void ABallPlayerController::AttractCubes(const FInputActionValue& Value)
{
	// Récupérer tous les cubes proches de la balle
	ABallPlayer* BallPlayer = Cast<ABallPlayer>(GetPawn());
	if (!BallPlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("BallPlayer introuvable"));
		return;
	}

	// Ajouter tous les cubes proches de la balle à la liste
	for (ADynamicCube* Cube : NearbyCubes)
	{
		if (Cube && Cube->IsValidLowLevel())
		{
			// Appliquer une force pour rapprocher chaque cube
			FVector Direction = (BallPlayer->GetActorLocation() - Cube->GetActorLocation()).GetSafeNormal();
			Direction.Normalize();  // Direction vers la balle

			// Attirer le cube lentement vers la balle
			float ForceMagnitude = 100000.0f;  // Ajuster la force pour être plus lent

			Cube->Mesh->AddForce(Direction*ForceMagnitude);
		}
	}
}

void ABallPlayerController::RepulseCubes(const FInputActionValue& Value)
{
	// Récupérer tous les cubes proches de la balle
	ABallPlayer* BallPlayer = Cast<ABallPlayer>(GetPawn());
	if (!BallPlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("BallPlayer introuvable"));
		return;
	}

	// Ajouter tous les cubes proches de la balle à la liste
	for (ADynamicCube* Cube : NearbyCubes)
	{
		if (Cube && Cube->IsValidLowLevel())
		{
			// Appliquer une force pour repousser chaque cube
			FVector Direction = (Cube->GetActorLocation() - BallPlayer->GetActorLocation()).GetSafeNormal();
			Direction.Normalize();  // Direction opposée à la balle

			// Repousser le cube
			float ForceMagnitude = 50000.0f;  // Ajuste la force selon tes besoins
			Cube->Mesh->AddImpulse(Direction * ForceMagnitude);
		}
	}
}
