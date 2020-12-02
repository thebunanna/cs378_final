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
    int MapBounds;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int RoomCount;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int MaxTilePerRoom;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int RoomStartRow;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int RoomStartCol;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int RoomEndRow;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int RoomEndCol;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMesh* Tile;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMesh* Wall;
    
    int** MapTiles;
    
    TMap<int, int> RoomTileCount;
    
    TMap<int, int*> RoomRows;
    
    TMap<int, int*> RoomCols;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    UFUNCTION(BlueprintCallable)
    void DungeonLayout();
    
    UFUNCTION(BlueprintCallable)
    void SpawnFloor(FVector vec);
    
    UFUNCTION(BlueprintCallable)
    void SpawnWall(FVector vec, FRotator rot);
    
    UFUNCTION(BlueprintCallable)
    bool CheckValidSpot(int r, int c, int room);
    
    UFUNCTION(BlueprintCallable)
    void PlaceRoomStarts();
    
    UFUNCTION()
    void SetupMapData();
    
    UFUNCTION()
    void CleanUp();
    

};
