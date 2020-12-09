// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerStart.h"
#include "LevelGenarator.generated.h"


USTRUCT()
struct FMap2dArray{
    GENERATED_BODY()
public:

    TArray<int> Ar;

    int operator[] (int32 i) {
        return Ar[i];
    }
    
    void Set(int i, int j){
        Ar[i]=j;
    }

    void Add(int i) {
        Ar.Add(i);
    }
};


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
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    APlayerStart* PlayerStart;
    
    UPROPERTY()
    bool RoomStartDone;
    
    int** MapTiles;
    
    int** AdjMatrix;
    
    UPROPERTY()
    TMap<int, int> RoomTileCount;
    
    TMap<int, int*> RoomRows;
    
    TMap<int, int*> RoomCols;
    
    UPROPERTY()
    TArray<FMap2dArray> Check2;
    
    UPROPERTY()
    TArray<FMap2dArray> MapOfTiles;
    
    UPROPERTY()
    TArray<FMap2dArray> Adjacency;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> VICTORYOBJ;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    virtual void PostInitializeComponents() override;

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
    
    UFUNCTION()
    void GrowRooms();
    
    UFUNCTION()
    bool ValidEdgeTileCheck(int r, int c, int room);
    
    UFUNCTION()
    bool CheckBounds(int r, int c);
    
//    UFUNCTION()
    int* GetEdgeTile(int Room);
    
    UFUNCTION()
    bool PlaceAdditionalRoom(int r, int c, int room);
    
    UFUNCTION()
    void UpdateMapData(int r, int c, int room);
    
    UFUNCTION()
    bool UpdateAdjMatrix(int r, int c, int room1, int room2);
    
    UFUNCTION()
    bool PathExists(int room1, int room2);
    
    UFUNCTION()
    void BuildPath(int r, int c, int room1, int room2);
    
    UFUNCTION()
    bool FullyConnected();
    
    UFUNCTION()
    int NextUnconnectedRoom(int Room);
    
    UFUNCTION()
    void PlaceWalls();
    
    UFUNCTION()
    bool WallCheck(int r, int c, int deltar, int deltac);
    
    UFUNCTION()
    void PlaceSpawn();
    
    UFUNCTION(BlueprintCallable)
    APlayerStart* GetPlayerStart();
    
    UFUNCTION()
    void PlaceEntities();
    
    UFUNCTION()
    void SpawnEnemies(int Roomidx, int NumberEnemies);
    
    UFUNCTION()
    void SpawnItems(int RoomNum, int items);

};
