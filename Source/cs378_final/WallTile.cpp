// Fill out your copyright notice in the Description page of Project Settings.


#include "WallTile.h"

// Sets default values
AWallTile::AWallTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
       WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
    //    FVector MeshScale = FVector(100.f, 100.f, 100.f);
    //    WallMesh->SetWorldScale3D(100.f);
        this->SetRootComponent(WallMesh);
        static ConstructorHelpers::FObjectFinder<UStaticMesh> WallAsset (TEXT("StaticMesh'/Game/MedievalDungeon/Meshes/Architecture/Dungeon/SM_Dungeon_Wall.SM_Dungeon_Wall'"));
        if (WallAsset.Succeeded())
            {
                if(GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Found Wall"));
                }
                WallMesh->SetStaticMesh(WallAsset.Object);
            }

}

// Called when the game starts or when spawned
void AWallTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

