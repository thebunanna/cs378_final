// Fill out your copyright notice in the Description page of Project Settings.


//#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "LevelTile.h"

// Sets default values
ALevelTile::ALevelTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
//    FloorComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FLOOR"));
//    FloorComponent->RegisterComponent();
//    UStaticMeshComponent* FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FLOORMESH"));
//    static ConstructorHelpers::FObjectFinder<UStaticMesh> FloorAsset (TEXT("StaticMesh'/Game/MedievalDungeon/Meshes/Architecture/Dungeon/SM_Floor.SM_Floor'"));
//
//    TestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TEST"));
//    this->SetRootComponent(TestMesh);
//
////    RootComponent = TestMesh;
//
//    if (FloorAsset.Succeeded())
//    {
//        if(GEngine)
//        {
//            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Found Floor"));
//        }
////        UStaticMesh * newMesh->SetStaticMesh(FloorAsset.Object);
////        FloorMesh->SetStaticMesh(FloorAsset.Object);
////        FloorComponent->SetStaticMesh(FloorAsset.Object);
////        FloorComponent->SetFlags(RF_Transactional);
////        this->AddInstanceComponent(FloorComponent);
//
//
//        TestMesh->SetStaticMesh(FloorAsset.Object);
////        TestMesh->SetRelativeLocation(FVector(70.f, 0.f, 0.f));
//
//    }
////    RootComponent = FloorComponent;
//    FTransform InstanceTransform;
//    InstanceTransform.SetLocation(FVector::ZeroVector);
//    InstanceTransform.SetRotation(FQuat::Identity);
//    FloorComponent->AddInstance(InstanceTransform);
    
//    static ConstructorHelpers::FObjectFinder<UStaticMesh> FloorAsset (TEXT("StaticMesh'/Game/MedievalDungeon/Meshes/Architecture/Dungeon/SM_Floor.SM_Floor'"));
//    TestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TEST"));
//    this->SetRootComponent(TestMesh);
//
//    FVector MeshScale = FVector(1000.f, 1000.f, 1000.f);
//    TestMesh->SetWorldScale3D(MeshScale);
//    if (FloorAsset.Succeeded())
//        {
//            if(GEngine)
//            {
//                GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Found Floor"));
//            }
//            TestMesh->SetStaticMesh(FloorAsset.Object);
//            FVector MeshScale = FVector(1000.f, 1000.f, 1000.f);
//            TestMesh->SetWorldScale3D(MeshScale);
//
//    //
//        }
    
//    static ConstructorHelpers::FObjectFinder<UStaticMesh> FloorAsset (TEXT("StaticMesh'/Game/MedievalDungeon/Meshes/Architecture/Dungeon/SM_Floor.SM_Floor'"));
//    TestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TEST"));
//    FVector MeshScale = FVector(1000.f, 1000.f, 1000.f);
//    TestMesh->SetWorldScale3D(MeshScale);
//    this->SetRootComponent(TestMesh);
//
//    TestMesh->SetWorldScale3D(MeshScale);
//    if (FloorAsset.Succeeded())
//        {
//            if(GEngine)
//            {
//                GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Found Floor"));
//            }
//            TestMesh->SetStaticMesh(FloorAsset.Object);
//            TestMesh->SetWorldScale3D(MeshScale);
//
//    //
//        }
    
    
    FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
//    FVector MeshScale = FVector(100.f, 100.f, 100.f);
//    FloorMesh->SetWorldScale3D(100.f);
    this->SetRootComponent(FloorMesh);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> FloorAsset (TEXT("StaticMesh'/Game/MedievalDungeon/Meshes/Architecture/Dungeon/SM_Floor.SM_Floor'"));
//    static ConstructorHelpers::FObjectFinder<UStaticMesh> WallAsset (TEXT("StaticMesh'/Game/MedievalDungeon/Meshes/Architecture/Dungeon/SM_Dungeon_Wall.SM_Dungeon_Wall'"));
    if (FloorAsset.Succeeded())
        {
            if(GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Found Floor"));
            }
            FloorMesh->SetStaticMesh(FloorAsset.Object);
        }
    
    
    

}

// Called when the game starts or when spawned
void ALevelTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

