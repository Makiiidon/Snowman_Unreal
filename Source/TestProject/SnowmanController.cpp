// Fill out your copyright notice in the Description page of Project Settings.


// ECS

#include "SnowmanController.h"

// Sets default values for this component's properties
USnowmanController::USnowmanController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USnowmanController::BeginPlay()
{
	Super::BeginPlay();
	
	
}


// Called every frame
void USnowmanController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (snowmanPawn->InputComponent) {
		this->snowmanPawn->InputComponent->BindAxis(MOVE_X_NAME, this, &USnowmanController::MoveX);
		this->snowmanPawn->InputComponent->BindAxis(MOVE_Y_NAME, this, &USnowmanController::MoveY);
	}

	if(alongX)
	{
		FVector location = this->snowmanPawn->GetTransform().GetLocation();
		location.X += this->movementX * DeltaTime * SPEED_MULTIPLIER;
		this->snowmanPawn->SetActorLocation(location);
	}

	if(alongY)
	{
		FVector location = this->snowmanPawn->GetTransform().GetLocation();
		location.Y += this->movementY * DeltaTime * SPEED_MULTIPLIER;
		this->snowmanPawn->SetActorLocation(location);
	}
}


void USnowmanController::MoveX(float axisValue)
{
	//UE_LOG(LogTemp, Display, TEXT("Move along X: %f"), axisValue);
	this->movementX = FMath::Clamp(axisValue, -1.f, 1.f);
	if(this->movementX != 0.0f)
	{
		this->alongX = true;
		this->alongY = false;
	}
}

void USnowmanController::MoveY(float axisValue)
{
	//UE_LOG(LogTemp, Display, TEXT("Move along Y: %f"), axisValue);
	this->movementY = FMath::Clamp(axisValue, -1.f, 1.f);
	if (this->movementY != 0.0f)
	{
		this->alongX = false;
		this->alongY = true;
	}
}



