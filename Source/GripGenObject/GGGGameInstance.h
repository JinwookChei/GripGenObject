// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GGGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GRIPGENOBJECT_API UGGGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	int32 LearningSampleNum = 20;

	int32 TimeStep = 80;
};
