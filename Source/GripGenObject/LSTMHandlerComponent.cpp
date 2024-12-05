// Fill out your copyright notice in the Description page of Project Settings.


#include "LSTMHandlerComponent.h"


// Sets default values for this component's properties
ULSTMHandlerComponent::ULSTMHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULSTMHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
    InitializeNNEModel();
}


// Called every frame
void ULSTMHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
    ExecuteNNETickInference();
}

void ULSTMHandlerComponent::InitializeNNEModel()
{
    // Example for automated loading
    if (NNEModelData)
    {
        UE_LOG(LogTemp, Display, TEXT("NNEModelData loaded %s"), *NNEModelData->GetName());
        // You can use PreLoadedModelData here to create a model and corresponding model instance(s)
        // PreLoadedModelData will be unloaded when the owning object or actor unloads

         // Example for model creation
        TWeakInterfacePtr<INNERuntimeCPU> Runtime = UE::NNE::GetRuntime<INNERuntimeCPU>(FString("NNERuntimeORTCpu"));
        if (Runtime.IsValid())
        {
            ModelHelper = MakeShared<FMyModelHelper>();

            // TUniquePtr -> TSharedPtr�� �ٲ����?
            TSharedPtr<UE::NNE::IModelCPU> Model = Runtime->CreateModelCPU(NNEModelData);

            if (Model.IsValid())
            {
                ModelHelper->ModelInstance = Model->CreateModelInstanceCPU();

                if (ModelHelper->ModelInstance.IsValid())
                {
                    ModelHelper->bIsRunning = false;

                    // Example for querying and testing in- and outputs
                    TConstArrayView<UE::NNE::FTensorDesc> InputTensorDescs = ModelHelper->ModelInstance->GetInputTensorDescs();
                    checkf(InputTensorDescs.Num() == 1, TEXT("The current example supports only models with a single input tensor"));
                    UE_LOG(LogTemp, Warning, TEXT("InputTensorDescsNum : %d"), InputTensorDescs.Num());

                    UE::NNE::FSymbolicTensorShape SymbolicInputTensorShape = InputTensorDescs[0].GetShape();
                    checkf(SymbolicInputTensorShape.IsConcrete(), TEXT("The current example supports only modelswithout  variable input tensor dimensions"));
                    UE_LOG(LogTemp, Warning, TEXT("SymbolicInputTensorShape.IsConcrete() : %s"), SymbolicInputTensorShape.IsConcrete() ? TEXT("True") : TEXT("False"));


                    TArray<UE::NNE::FTensorShape> InputTensorShapes = { UE::NNE::FTensorShape::MakeFromSymbolic(SymbolicInputTensorShape) };
                    ModelHelper->ModelInstance->SetInputTensorShapes(InputTensorShapes);
                    UE_LOG(LogTemp, Warning, TEXT("InputTensorShapesNum : %d"), InputTensorShapes.Num());

                    TConstArrayView<UE::NNE::FTensorDesc> OutputTensorDescs = ModelHelper->ModelInstance->GetOutputTensorDescs();
                    checkf(OutputTensorDescs.Num() == 1, TEXT("The current example supports only models with a single output tensor"));
                    UE_LOG(LogTemp, Warning, TEXT("OutputTensorDescsNum : %d"), OutputTensorDescs.Num());

                    UE::NNE::FSymbolicTensorShape SymbolicOutputTensorShape = OutputTensorDescs[0].GetShape();
                    checkf(SymbolicOutputTensorShape.IsConcrete(), TEXT("The current example supports only models without variable output tensor dimensions"));
                    UE_LOG(LogTemp, Warning, TEXT("SymbolicOutputTensorShape.IsConcrete() : %s"), SymbolicOutputTensorShape.IsConcrete() ? TEXT("True") : TEXT("False"));

                    TArray<UE::NNE::FTensorShape> OutputTensorShapes = { UE::NNE::FTensorShape::MakeFromSymbolic(SymbolicOutputTensorShape) };
                    UE_LOG(LogTemp, Warning, TEXT("OutputTensorShapesNum : %d"), OutputTensorShapes.Num());


                    for (int i = 0; i < SymbolicInputTensorShape.Rank(); i++)
                    {
                        TConstArrayView<int32> View = SymbolicInputTensorShape.GetData();
                        UE_LOG(LogTemp, Display, TEXT("Input View [%d]: %d"), i, View[i]);
                    }

                    for (int i = 0; i < SymbolicOutputTensorShape.Rank(); i++)
                    {
                        TConstArrayView<int32> View = SymbolicOutputTensorShape.GetData();
                        UE_LOG(LogTemp, Display, TEXT("Output View [%d]: %d"), i, View[i]);
                    }

                    // Example for creating in- and outputs
                    ModelHelper->InputData.SetNumZeroed(InputTensorShapes[0].Volume());
                    ModelHelper->InputBindings.SetNumZeroed(1);
                    ModelHelper->InputBindings[0].Data = ModelHelper->InputData.GetData();
                    ModelHelper->InputBindings[0].SizeInBytes = ModelHelper->InputData.Num() * sizeof(float);
                    UE_LOG(LogTemp, Display, TEXT("ModelHelper->InputData Num : %d"), ModelHelper->InputData.Num());


                    ModelHelper->OutputData.SetNumZeroed(OutputTensorShapes[0].Volume());
                    ModelHelper->OutputBindings.SetNumZeroed(1);
                    ModelHelper->OutputBindings[0].Data = ModelHelper->OutputData.GetData();
                    ModelHelper->OutputBindings[0].SizeInBytes = ModelHelper->OutputData.Num() * sizeof(float);
                    UE_LOG(LogTemp, Display, TEXT("ModelHelper->OutputData Num : %d"), ModelHelper->OutputData.Num());
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Failed to create the model instance"));
                    ModelHelper.Reset();
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to create the model"));
                ModelHelper.Reset();
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Cannot find runtime NNERuntimeORTCpu, please enable the corresponding plugin"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("NNEModelData is not set, please assign it in the editor"));
    }
}

void ULSTMHandlerComponent::ExecuteNNETickInference()
{
    if (ModelHelper.IsValid())
    {
        // Example for async inference
        if (!ModelHelper->bIsRunning)
        {
            // Process ModelHelper->OutputData from the previous run here
            // Fill in new data into ModelHelper->InputData here

            ModelHelper->InputData = TestPistolData;

            //UE_LOG(LogTemp, Display, TEXT("ModelHelper->InputData.Num() : %d"), ModelHelper->InputData.Num());
            for (int i = 0; i < ModelHelper->OutputData.Num(); i++)
            {
                UE_LOG(LogTemp, Display, TEXT("ModelHelper->OutputData : %f"), ModelHelper->OutputData[i]);
            }


            ModelHelper->bIsRunning = true;
            TSharedPtr<FMyModelHelper> ModelHelperPtr = ModelHelper;
            AsyncTask(ENamedThreads::AnyNormalThreadNormalTask, [ModelHelperPtr]()
                {
                    if (ModelHelperPtr->ModelInstance->RunSync(ModelHelperPtr->InputBindings, ModelHelperPtr->OutputBindings) != UE::NNE::IModelInstanceCPU::ERunSyncStatus::Ok)
                    {
                        UE_LOG(LogTemp, Error, TEXT("Failed to run the model"));
                    }
                    AsyncTask(ENamedThreads::GameThread, [ModelHelperPtr]()
                        {
                            ModelHelperPtr->bIsRunning = false;
                        });
                });
        }
    }
}

