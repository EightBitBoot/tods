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

