// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HandTrackingDataComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRIPGENOBJECT_API UHandTrackingDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHandTrackingDataComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FString Filename = FPaths::ProjectDir() + TEXT("JointData.csv");

	FString CSVData;

	int32 TickCount;

	int32 LearningSampleCount;

	int32 LearningSampleNum;

	int32 TimeStep;

private:
	EHandDataLabel HandDataLabel;

	UPROPERTY()
	class UHandJoint* RightHandJoint;

	UPROPERTY()
	class UHandJoint* LeftHandJoint;

	FVector PreRightHandLocation;
	FQuat PreRightHandQuat;
	FVector PreLeftHandLocation;
	FQuat PreLeftHandQuat;

	UPROPERTY()
	class AVRPawn* OwnerPawn;

	UPROPERTY()
	UOculusXRHandComponent* OwnerRightHand;
	UPROPERTY()
	UOculusXRHandComponent* OwnerLeftHand;

	TArray<class UJointMeshComponent*> HandJointMeshes;

	UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
	TArray<FVector> HandJointRelativeLocations;

	UPROPERTY(VisibleAnywhere, Category = "Hand Joints")
	TArray<FRotator> HandJointRelativeRotations;

	

protected:
	UFUNCTION(BlueprintCallable)
	void StartWriteCSVData(EHandDataLabel _HandDataLabel,  class UHandJoint* _RightHandJoint,  class UHandJoint* _LeftHandJoint);

private:
	UFUNCTION()
	void Initialize_CSVData();

	UFUNCTION()
	void ExportHandDatasToCSV(class UOculusXRHandComponent* _Hand, TArray<class UJointMeshComponent*>& _HandJointMeshes, EHandDataLabel _HandDataLabel);

	UFUNCTION()
	void ExportRelativeHandDatasToCSV();

	void ExportHandDatasToCSV_Loop();

public:
	void CalculateRelativeJoint();
	
};
