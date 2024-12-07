// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VRPawn.h"
#include "HandJoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRIPGENOBJECT_API UHandJoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHandJoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, Category = "HandType")
	EHandType HandType;

protected:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Wrist_Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Thumb0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Thumb1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Thumb2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Thumb3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Thumb_Tip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Index1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Index2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Index3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Index_Tip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Middle1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Middle2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Middle3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Middle_Tip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Ring1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Ring2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Ring3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Ring_Tip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Pinky0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Pinky1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Pinky2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Pinky3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JointMesh")
	class UJointMeshComponent* Pinky_Tip;

private:
	TArray<UJointMeshComponent*> JointArray;

	int32 JointCount = 23;


public:
	int32 GetJointCount();

	TArray<UJointMeshComponent*> GetJointArray();

	FVector GetWristRootWorldLocation();

	FRotator GetWristRootWorldRotation();
	
};
