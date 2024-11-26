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

	float TickCnt;

	EHandDataLabel HandDataLabel;

	class AVRPawn* OwnerPawn;
	UOculusXRHandComponent* OwnerRightHand;
	UOculusXRHandComponent* OwnerLeftHand;

protected:
	UFUNCTION(BlueprintCallable)
	void StartWriteCSVData(EHandDataLabel _HandDataLabel);


private:
	UFUNCTION()
	void Initialize_CSVData();

	UFUNCTION()
	void ExportHandDatasToCSV(class UOculusXRHandComponent* _Hand, TArray<class UJointMeshComponent*>& _HandJointMeshes, EHandDataLabel _HandDataLabel);

	void ExportHandDatasToCSV_Loop();
	
};
