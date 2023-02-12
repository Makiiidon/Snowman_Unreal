// Fill out your copyright notice in the Description page of Project Settings.

// Inheritance

#include "SnowmanPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ASnowmanPawn::ASnowmanPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Creates a dummy Root component we can attach things to
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Creates a camera and a visible object
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	this->snowmanMeshComponent = (USceneComponent*)CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// Attach our camera and visible object to our root component. Offset and rotate the camera
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-0.f, 100.f, 100));
	OurCamera->SetRelativeRotation(FRotator(-45.f, -90, 0));
	snowmanMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASnowmanPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnowmanPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (alongX)
	{
		FVector location = GetTransform().GetLocation();
		location.X += this->movementX * DeltaTime * SPEED_MULTIPLIER;
		SetActorLocation(location);
	}

	if (alongY)
	{
		FVector location = GetTransform().GetLocation();
		location.Y += this->movementY * DeltaTime * SPEED_MULTIPLIER;
		SetActorLocation(location);
	}

}

// Called to bind functionality to input
void ASnowmanPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(MOVE_X_NAME, this, &ASnowmanPawn::MoveX);
	PlayerInputComponent->BindAxis(MOVE_Y_NAME, this, &ASnowmanPawn::MoveY);

}

void ASnowmanPawn::MoveX(float axisValue)
{
	this->movementX = FMath::Clamp(axisValue, -1.f, 1.f);
	if (this->movementX != 0.0f)
	{
		this->alongX = true;
		this->alongY = false;
	}
}

void ASnowmanPawn::MoveY(float axisValue)
{
	this->movementY = FMath::Clamp(axisValue, -1.f, 1.f);
	if (this->movementY != 0.0f)
	{
		this->alongX = false;
		this->alongY = true;
	}
}

