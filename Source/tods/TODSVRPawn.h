// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "HeadMountedDisplay.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h"
#include "Components/SceneComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "OculusFunctionLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/LineBatchComponent.h"

#include "TODSVRPawn.generated.h"

UCLASS()
class TODS_API ATODSVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATODSVRPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) //Root scene
	USceneComponent* m_scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) //Movement controller
	UFloatingPawnMovement* m_movementController;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) //Root camera
	USceneComponent* m_cameraRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) //Actual camera
	UCameraComponent* m_camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMotionControllerComponent* m_leftController;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMotionControllerComponent* m_rightController;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FVector> gPoints;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
