// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelTile.h"
#include "WallTile.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/PlayerStart.h"
#include "LevelGenarator.h"

// Sets default values
ALevelGenarator::ALevelGenarator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    MinRooms = 8;
    MaxRooms = 20;

}

// Called when the game starts or when spawned
void ALevelGenarator::BeginPlay()
{
	Super::BeginPlay();
    
//    AMyObject* Obj = World->SpawnActor<ALevelTile>(ToSpawn, spawnLocation, rotator, spawnParams);
//    
//    ISMComp = NewObject<UInstancedStaticMeshComponent>(Obj);
//    
//    ISMComp->RegisterComponent();
//    ISMComp->SetStaticMesh(SuperMesh);
//    Obj->AddInstanceComponent(ISMComp);
//    
//    FTransform InstanceTransform;
//    InstanceTransform.SetLocation(FVector::ZeroVector);
//    InstanceTransform.SetRotation(FQuat::Identity);
//    
//    ISMComp->AddInstance(InstanceTransform);
    
    
//    FVector Location(0.0f, 0.0f, 0.0f);
//    FRotator Rotation(0.0f, 0.0f, 0.0f);
//    FActorSpawnParameters SpawnInfo;
//    GetWorld()->SpawnActor<AWallTile>(Location, Rotation, SpawnInfo);
//    if(GEngine)
//    {
//        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Spawned Wall"));
//    }
//
//    FVector Location1(0.0f, 600.0f, 0.0f);
//     FRotator Rotation1(0.0f, 0.0f, 0.0f);
//     FActorSpawnParameters SpawnInfo1;
//     GetWorld()->SpawnActor<AWallTile>(Location1, Rotation1, SpawnInfo1);
//     if(GEngine)
//     {
//         GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Spawned Wall"));
//     }
//
//    FVector Location2(600.0f, 600.0f, 100.0f);
//    FRotator Rotation2(0.0f, 0.0f, 0.0f);
//    FActorSpawnParameters SpawnInfo2;
//    GetWorld()->SpawnActor<ALevelTile>(Location2, Rotation2, SpawnInfo2);
//    if(GEngine)
//    {
//        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Spawned LevelTile"));
//    }
    
    
    DungeonLayout();
}

// Called every frame
void ALevelGenarator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelGenarator::DungeonLayout()
{
    int RoomCount = FMath::RandRange(MinRooms, MaxRooms);
            if(GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("Number of rooms: %d"), RoomCount));
            }
    
    RoomStartRow = FMath::RandRange(0, MaxRooms-1);
    RoomStartCol = FMath::RandRange(0, MaxRooms-1);
    int RoomLayout[MaxRooms*2][MaxRooms*2];
    RoomLayout[RoomStartRow][RoomStartCol] = 1;
    
    int RoomLocationR[RoomCount];
    int RoomLocationC[RoomCount];
    
    int currentRow = RoomStartRow;
    int currentCol = RoomStartCol;
    int NewRow = 0;
    int NewCol = 0;
    
    RoomLocationR[0] = currentRow;
    RoomLocationC[0] = currentCol;
    
    for (int idx = 0; idx < RoomCount; idx++)
    {
        bool validSpot = false;
        while(!validSpot)
        {
            int Axis = FMath::RandRange(0, 1);
            int Direction = FMath::RandRange(0, 1);
            if (Axis == 0)
            {
                if (Direction == 0)
                {
                    if(RoomLayout[currentRow+1][currentCol] != 1)
                    {
                        validSpot = true;
                        NewRow =currentRow+1;
                        NewCol = currentCol;
                    }
                    
                } else
                {
                    if(RoomLayout[currentRow-1][currentCol] != 1)
                    {
                        validSpot = true;
                        NewRow = currentRow-1;
                        NewCol = currentCol;
                    }
                    
                }
            } else
            {
                if (Direction == 0)
                {
                    if(RoomLayout[currentRow][currentCol+1] != 1)
                    {
                        validSpot = true;
                        NewRow =currentRow;
                        NewCol = currentCol+1;
                    }
                    
                } else
                {
                    if(RoomLayout[currentRow][currentCol-1] != 1)
                    {
                        validSpot = true;
                        NewRow = currentRow;
                        NewCol = currentCol-1;
                    }
                    
                }
            }
        }
        RoomLayout[NewRow][NewCol] = 1;
        currentRow = NewRow;
        currentCol = NewCol;
        RoomLocationR[idx+1] = currentRow;
        RoomLocationC[idx+1] = currentCol;
        
    }
    
    
    int LayoutTest[][5] = { {1, 1, 1,0,0}, {1, 0, 0,0,0}, {1,0,0,0,0}, {1,1,1,0,0},{1,0,0,0,0}};


      RoomCount = 9;
    MaxRooms = 5;
      RoomLocationR[13];
      RoomLocationC[13];
      RoomLocationR[0] = 0;
      RoomLocationC[0] = 0;
    
      RoomLocationR[1] = 0;
      RoomLocationC[1] = 1;
    
      RoomLocationR[2] = 0;
      RoomLocationC[2] = 2;
    
    RoomLocationR[3] = 1;
    RoomLocationC[3] = 0;
    
    RoomLocationR[4] = 2;
    RoomLocationC[4] = 0;
    
    RoomLocationR[5] = 3;
    RoomLocationC[5] = 0;
    
    RoomLocationR[6] = 3;
    RoomLocationC[6] = 1;
    
    RoomLocationR[7] = 3;
    RoomLocationC[7] = 2;
    
    RoomLocationR[8] = 4;
    RoomLocationC[8] = 0;
    
//    RoomLocationR[9] = 0;
//    RoomLocationC[9] = 3;
//
//    RoomLocationR[10] = 0;
//    RoomLocationC[10] = 4;
//
//    RoomLocationR[11] = 1;
//    RoomLocationC[11] = 4;
//
//    RoomLocationR[12] = 2;
//    RoomLocationC[12] = 4;
    
    
    
    for (int i = 0; i < RoomCount; i++)
    {
//        if(GEngine)
//        {
//            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("%d"), RoomLocationR[i]));
//            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%d"), RoomLocationC[i]));
//        }
        FVector Location(0.0f+600.f*RoomLocationR[i], 0.0f+600.f*RoomLocationC[i], 100.0f);
        FRotator Rotation(0.0f, 0.0f, 0.0f);
        FActorSpawnParameters SpawnInfo;
        GetWorld()->SpawnActor<ALevelTile>(Location, Rotation, SpawnInfo);
        if(GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Spawned Room: %d"), i));
        }
        
        //CHECK TO RIGHT COL
        if((RoomLocationC[i] +1 < MaxRooms*2 && LayoutTest[RoomLocationR[i]][RoomLocationC[i]+1] == 0)|| RoomLocationC[i]+1 >=MaxRooms*2)
        {
            FVector Location1(0.0f+600.f*RoomLocationR[i], 0.0f+600.f*(RoomLocationC[i]+1), 120.0f);
            FRotator Rotation1(0.0f, -90.0f, 0.0f);
            FActorSpawnParameters SpawnInfo1;
            GetWorld()->SpawnActor<AWallTile>(Location1, Rotation1, SpawnInfo1);
            if(GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("Spawned Wall Right"));
            }

        }

        //CHECK TO LEFT COL
       if((RoomLocationC[i] -1 >=0 && LayoutTest[RoomLocationR[i]][RoomLocationC[i]-1] == 0)||
          RoomLocationC[i]-1 < 0)
       {
           FVector Location1(0.0f+600.f*RoomLocationR[i], 0.0f+600.f*(RoomLocationC[i]), 120.0f);
           FRotator Rotation1(0.0f, -90.0f, 0.0f);
           FActorSpawnParameters SpawnInfo1;
           GetWorld()->SpawnActor<AWallTile>(Location1, Rotation1, SpawnInfo1);
           if(GEngine)
           {
               GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, TEXT("Spawned Wall Left"));
           }

       }

        //CHECK TO ABOVE ROW
        if((RoomLocationR[i] +1 < MaxRooms*2 && LayoutTest[RoomLocationR[i]+1][RoomLocationC[i]] == 0) || RoomLocationR[i]+1 >=MaxRooms*2)
        {
            FVector Location1(0.0f+600.f*(RoomLocationR[i]+1), 0.0f+600.f*RoomLocationC[i], 120.0f);
            FRotator Rotation1(0.0f, 0.0f, 0.0f);
            FActorSpawnParameters SpawnInfo1;
            GetWorld()->SpawnActor<AWallTile>(Location1, Rotation1, SpawnInfo1);
            if(GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("Spawned Wall Above"));
            }

        }
//        if((RoomLocationR[i] +1 < MaxRooms && RoomLayout[RoomLocationR[i]+1][RoomLocationC[i]] != 0))
//        {
//            if(GEngine)
//            {
//                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BLOCKED"));
//            }
//
//        }
        

        //CHECK TO BELOW ROW
        if((RoomLocationR[i] -1 >=0 && LayoutTest[RoomLocationR[i]-1][RoomLocationC[i]] == 0) || RoomLocationR[i]-1 < 0)
        {
            FVector Location1(0.0f+600.f*(RoomLocationR[i]), 0.0f+600.f*RoomLocationC[i], 120.0f);
            FRotator Rotation1(0.0f, 0.0f, 0.0f);
            FActorSpawnParameters SpawnInfo1;
            GetWorld()->SpawnActor<AWallTile>(Location1, Rotation1, SpawnInfo1);
            if(GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Spawned Wall Below"));
            }

        }





    }
    
    //SPAWN PLAYER START
    FActorSpawnParameters SpawnInfo;
    SpawnInfo.Owner = this;
    SpawnInfo.Instigator = NULL;
    SpawnInfo.bDeferConstruction = false;
    FVector Loc(50.0f+600.f*RoomLocationR[0], 50.0f+600.f*RoomLocationC[0], 150.0f);
     
//    APlayerStart* PlayerStart = GetWorld()->SpawnActor<APlayerStart>(APlayerStart::StaticClass(), Loc ,FRotator::ZeroRotator, SpawnInfo );
    
    GetWorld()->SpawnActor<APlayerStart>(Loc, FRotator::ZeroRotator, SpawnInfo);
    


}

