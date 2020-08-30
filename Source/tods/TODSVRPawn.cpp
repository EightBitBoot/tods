// Fill out your copyright notice in the Description page of Project Settings.


#include "TODSVRPawn.h"

// Sets default values
ATODSVRPawn::ATODSVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Setup basic scene needs
	m_scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	m_movementController = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementController"));

	//Init camera
	m_cameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VR Camera Root"));
	m_cameraRoot->SetupAttachment(m_scene);
	m_cameraRoot->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
	m_cameraRoot->SetRelativeScale3D(FVector::OneVector);

	m_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("HMD Camera"));
	m_camera->SetupAttachment(m_cameraRoot);
	m_camera->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
	m_camera->SetRelativeScale3D(FVector::OneVector);

	//Motion controller setup
	m_leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left_Controller"));
	m_leftController->SetShowDeviceModel(true);
	m_leftController->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
	m_leftController->SetRelativeScale3D(FVector::OneVector);
	
	m_leftController->MotionSource = FXRMotionControllerBase::LeftHandSourceId;
	m_leftController->SetupAttachment(m_cameraRoot);
	
	m_rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right_Controller"));
	m_rightController->SetShowDeviceModel(true);
	m_rightController->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
	m_rightController->SetRelativeScale3D(FVector::OneVector);
	
	m_rightController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	m_rightController->SetupAttachment(m_cameraRoot);

}

// Called when the game starts or when spawned
void ATODSVRPawn::BeginPlay()
{
	Super::BeginPlay();
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Type::Floor);

	gPoints = UOculusFunctionLibrary::GetGuardianPoints(EBoundaryType::Boundary_PlayArea, false);
	if (gPoints.Num() != 0)
	{
		for (int i = 0; i < gPoints.Num(); i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("Point #%d: X: %f Y: %f Z: %f\n"), i, gPoints[i].X, gPoints[i].Y, gPoints[i].Z);
		}

		TArray<FBatchedLine> lines;
		
		ULineBatchComponent* LineBatchComponent = GetWorld()->PersistentLineBatcher;
		for (auto i = 0; i < gPoints.Num(); i++)
		{
			FVector start;
			FVector end;
			if (i != gPoints.Num() - 1)
			{
				start = FVector(gPoints[i].X, gPoints[i].Y, gPoints[i].Z);
				end = FVector(gPoints[i+1].X, gPoints[i+1].Y, gPoints[i+1].Z);
			}
			else
			{
				start = FVector(gPoints[i].X, gPoints[i].Y, gPoints[i].Z);
				end = FVector(gPoints[0].X, gPoints[0].Y, gPoints[0].Z);
			}
			UE_LOG(LogTemp, Warning, TEXT("Adding line to the array\n"));

			FBatchedLine line = FBatchedLine(start,
				end,
				FLinearColor(0, 0, 0, 0.5),
				10000, // for long period draw
				5,
				4
			);
			lines.Add(line);
		}
		LineBatchComponent->DrawLines(lines);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Gardiummmmmm\n"));
	}		
	
}

// Called every frame
void ATODSVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATODSVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

