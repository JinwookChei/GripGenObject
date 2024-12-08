// Fill out your copyright notice in the Description page of Project Settings.


#include "JointMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h" 

UJointMeshComponent::UJointMeshComponent()
{
    // Static Mesh �ε�
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
    if (MeshAsset.Succeeded())
    {
        
        this->SetStaticMesh(MeshAsset.Object);
        UE_LOG(LogTemp, Warning, TEXT("Mesh loaded successfully!   %s"), *MeshAsset.Object.GetName());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load mesh."));
    }   

    // �⺻ ������Ƽ ���� (�ɼ�)
    SetMobility(EComponentMobility::Movable); // �̵� ���� ���� ����
    //SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    //// ���͸��� ���� (�ɼ�)
    //static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Engine/BasicShapes/BasicShapeMaterial"));
    //if (MaterialAsset.Succeeded())
    //{
    //    this->SetMaterial(0, MaterialAsset.Object);
    //}
}

void UJointMeshComponent::SetHandJointType(EHandJointType _HandJointType)
{
	HandJointType = _HandJointType;
}

EHandJointType UJointMeshComponent::GetHandJointType()
{
	return HandJointType;
}
