// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGenarator.generated.h"

UCLASS()
class CS378_FINAL_API ALevelGenarator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelGenarator();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int MinRooms;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int MaxRooms;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int RoomStartRow;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int RoomStartCol;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    UFUNCTION(BlueprintCallable)
    void DungeonLayout();

};
