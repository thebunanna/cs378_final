// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "LevelTile.generated.h"

UCLASS()
class CS378_FINAL_API ALevelTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UInstancedStaticMeshComponent* FloorComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* TestMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* FloorMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
