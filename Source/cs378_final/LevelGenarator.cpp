// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelGenarator.h"
#include "LevelTile.h"
#include "WallTile.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/PlayerStart.h"


// Sets default values
ALevelGenarator::ALevelGenarator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    MinRooms = 8;
    MaxRooms = 10;
    MapBounds = MaxRooms*2;
    RoomCount = FMath::RandRange(MinRooms, MaxRooms);
    MaxTilePerRoom = MapBounds;
    RoomStartDone = false;
    
//    MAKE SURE TO FREE RESOURCES
    
    //Allocate MapTiles
//    MapTiles = (int **)FMemory::Malloc(sizeof(int)*MapBounds);
//    for(int i = 0; i < MapBounds; i++)
//    {
//        if(MapTiles)
//        {
//            MapTiles[i] = (int *)FMemory::Malloc(sizeof(int)*MapBounds);
//        }
//    }
//
//    //Allocate Tile Location Info
//    for(int i = 0; i<RoomCount; i++)
//    {
//        RoomTileCount.Add(i, 0);
//        int *RowArr = (int *)FMemory::Malloc(sizeof(int)*MaxTilePerRoom);
//        int *ColArr = (int *)FMemory::Malloc(sizeof(int)*MaxTilePerRoom);
//        RoomRows.Add(i, RowArr);
//        RoomCols.Add(i, ColArr);
//
//    }
    
    
    
    //Get Meshes for building dungeon
    static ConstructorHelpers::FObjectFinder<UStaticMesh> FloorAsset (TEXT("StaticMesh'/Game/MedievalDungeon/Meshes/Architecture/Dungeon/SM_Floor.SM_Floor'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> WallAsset (TEXT("StaticMesh'/Game/MedievalDungeon/Meshes/Architecture/Dungeon/SM_Dungeon_Wall.SM_Dungeon_Wall'"));

    //Set Meshes
    if (FloorAsset.Succeeded())
    {
        if(GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Found Constructor Floor"));
        }
        Tile = FloorAsset.Object;
    }
    if(WallAsset.Succeeded())
    {
        if(GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Found Constructor Wall"));
        }
        Wall = WallAsset.Object;
    }
    
    
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
    
    
    
    
    TArray<FMap2dArray> MapStuffs;
    Check2.Add(FMap2dArray());
    Check2[0].Add(0);
    Check2[0].Set(0, 1209);
    
    if(GEngine)
    {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Value: %d"), Check2[0][0]));
    }
    
    
    
    
    
//    SetupMapData();
//    DungeonLayout();
//    GrowRooms();
}

// Called every frame
void ALevelGenarator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ALevelGenarator::SetupMapData()
{
     
    //Allocate MapTiles
    MapTiles = (int **)FMemory::Malloc(sizeof(int)*MapBounds);
    for(int i = 0; i < MapBounds; i++)
    {
        if(MapTiles)
        {
            MapTiles[i] = (int *)FMemory::Malloc(sizeof(int)*MapBounds);
            for(int j = 0; j < MapBounds; j++)
            {
                MapTiles[i][j] = 0;
            }
        }
    }

    //Allocate Tile Location Info
    for(int i = 1; i<=RoomCount; i++)
    {
        RoomTileCount.Add(i, 0);
        int *RowArr = (int *)FMemory::Malloc(sizeof(int)*MaxTilePerRoom);
        int *ColArr = (int *)FMemory::Malloc(sizeof(int)*MaxTilePerRoom);
        for(int j = 0; j < MaxTilePerRoom; j++)
        {
            RowArr[j] = 0;
            ColArr[j] = 0;
        }
        RoomRows.Add(i, RowArr);
        RoomCols.Add(i, ColArr);
    }
    
    //Allocate Adjacency Matrix
    AdjMatrix = (int**)FMemory::Malloc(sizeof(int)*RoomCount);
    for(int i = 0; i < RoomCount; i++)
    {
        if(AdjMatrix)
        {
            AdjMatrix[i] = (int *)FMemory::Malloc(sizeof(int)*RoomCount);
            for(int j = 0; j < RoomCount; j++)
            {
                AdjMatrix[i][j] = 0;
            }

        }
    }
    
    
}

void ALevelGenarator::PlaceRoomStarts()
{
    
    for(int RoomNum = 1; RoomNum <= RoomCount; RoomNum++)
    {
        
        int iteration = 0;
        bool ValidRoom = false;
        while(iteration < 15 && !ValidRoom)
        {
            int RowVal = 0;
            int ColVal = 0;
            if(RoomNum == 1)
            {
                RowVal = FMath::RandRange(0, MapBounds-1);
                ColVal = FMath::RandRange(0, 3);
            } else if(RoomNum == RoomCount)
            {
                RowVal = FMath::RandRange(0, MapBounds-1);
                ColVal = FMath::RandRange(MapBounds-3, MapBounds-1);
            } else
            {
                RowVal = FMath::RandRange(0, MapBounds-1);
                ColVal = FMath::RandRange(0, MapBounds-1);
            }
            if(CheckValidSpot(RowVal, ColVal, RoomNum))
            {
                MapTiles[RowVal][ColVal] = RoomNum;
                RoomTileCount.Add(RoomNum, 1);
                if(RoomRows.Contains(RoomNum))
                {
                    RoomRows[RoomNum][0] = RowVal;
                }
                if(RoomCols.Contains(RoomNum))
                {
                    RoomCols[RoomNum][0] = ColVal;
                }
            }
            FVector FloorLocation(0.f+600.f*RowVal,0.f+600.f*ColVal,75.f);
            SpawnFloor(FloorLocation);
            ValidRoom = true;
            iteration+=1;
            if(ValidRoom && RoomNum ==1)
            {
                RoomStartRow = RowVal;
                RoomStartCol = ColVal;
            } else if(ValidRoom && RoomNum == RoomCount)
            {
                RoomEndRow = RowVal;
                RoomEndCol = ColVal;
            }
        }
        if(iteration > 15)
        {
            if(GEngine)
            {
                    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("Room Number: %d could not be placed"), RoomNum));
            }
        }
    }
    
    
    //debug
//    for(int i = 1; i <=RoomCount; i++ )
//    {
//        if(GEngine)
//        {
//                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("ROOM: %d COL: %d"), i, RoomRows[i][0]));
//        }
//        if(GEngine)
//        {
//                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("ROOM: %d COL: %d"), i, RoomCols[i][0]));
//        }
//
//    }
    
    
    
//    CleanUp();
    
}
bool ALevelGenarator::UpdateAdjMatrix(int r, int c, int room1, int room2)
{
    MapTiles[r][c] = -1;
    AdjMatrix[room1][room2] = 1;
    AdjMatrix[room2][room1] = 1;
    return true;
}

int* ALevelGenarator::GetEdgeTile(int CurrentRoom)
{
    static int Coords[2];
    Coords[0] = -1;
    Coords[1] = -1;
    
    //Choose random tile trying to find edge of this room
    int idx = 0;
    
//    if(GEngine)
//    {
//        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("MAXTILEPERROOM: %d"), MaxTilePerRoom));
//    }
    
    while (idx < MaxTilePerRoom)
    {
        int CurrentNumTiles = RoomTileCount[CurrentRoom];
        if(CurrentNumTiles < MaxTilePerRoom)
        {
            int TileSelection = FMath::RandRange(0, CurrentNumTiles-1);
            int CurrentRow = RoomRows[CurrentRoom][TileSelection];
            int CurrentCol = RoomCols[CurrentRoom][TileSelection];
            if(ValidEdgeTileCheck(CurrentRow, CurrentCol, CurrentRoom))
            {
                Coords[0] = CurrentRow;
                Coords[1] = CurrentCol;
                return Coords;
            }
        } else
        {
            return Coords;
        }
        idx+=1;
    }
    
    //debug
//    if(GEngine)
//    {
//        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("OUT OF WHILE LOOP GET EDGE"));
//    }
    return Coords;
}
bool ALevelGenarator::PlaceAdditionalRoom(int Row, int Col, int CurrentRoom)
{
    
    int RDirection[] = {0,0,1,-1};
    int CDirection[] = {1,-1,0,0};
    
    for(int i = 0; i < 4; i++)
    {
        //Choose direction
        int DirectionIndex = FMath::RandRange(0, 3);
        int ProposedR = Row+RDirection[i];
        int ProposedC = Col+CDirection[i];
        if(CheckValidSpot(ProposedR, ProposedC, CurrentRoom))
        {
            FVector FloorLocation(0.f+600.f*ProposedR,0.f+600.f*ProposedC,75.f);
            SpawnFloor(FloorLocation);
            UpdateMapData(ProposedR, ProposedC, CurrentRoom);
//            GoneWithoutPlacing = 0;
//
//            if(GEngine)
//            {
//                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Growing Room"));
//            }
            return true;
        }
    }
    //debug
//    if(GEngine)
//    {
//        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("NO ROOM PLACED"));
//    }
    return false;
    
}

void ALevelGenarator::UpdateMapData(int Row, int Col, int CurrentRoom)
{
    int Tiles = RoomTileCount[CurrentRoom]+1;
    RoomTileCount.Add(CurrentRoom, Tiles);
    RoomRows[CurrentRoom][Tiles] = Row;
    RoomCols[CurrentRoom][Tiles] = Col;
    MapTiles[Row][Col] = CurrentRoom;
    
}

void ALevelGenarator::GrowRooms()
{
    int iterations = 0;
    int CurrentRoom = 1;
    int GoneWithoutPlacing = 0;
    bool ValidFreeSpace = true;
    
    int roomsmade = 0;
    int noedge = 0;
    
//    (MapBounds-MinRooms)*(MapBounds-MinRooms)
    while(ValidFreeSpace && iterations < (MapBounds+2)*(MapBounds*2))
    {
        if(CurrentRoom > RoomCount)
        {
            CurrentRoom = 1;
        }
        //Roll to grow this room or not
        //FIX OR CHANGE TODO
        int PlaceRoom = FMath::RandRange(1, 1);
        if(PlaceRoom)
        {
            //debug
//            if(GEngine)
//            {
//                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("Try Place Room: %d"), iterations));
//            }
            
            int* Coords = GetEdgeTile(CurrentRoom);
            int Row = Coords[0];
            int Col = Coords[1];
            //Use EdgeTile to select a spot to grow
            if(Row != -1 && Col != -1)
            {

//                if(GEngine)
//                {
//                    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("EDGE FOUND"));
//                }
                
                if(PlaceAdditionalRoom(Row, Col, CurrentRoom))
                {
                    //debug
//                    if(GEngine)
//                    {
//                        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("PLACED A ROOM: %d"), iterations));
//                    }
                    roomsmade = roomsmade+1;
                    GoneWithoutPlacing = 0;
                }
                else
                    GoneWithoutPlacing+=1;
            } else
            {
                noedge = noedge +1;
            }
            iterations+=1;
        }
        //Breaking out if we havent been able to place a room;
        if(GoneWithoutPlacing == RoomCount*2){
            //debug
//            if(GEngine)
//            {
//                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("GONE WITHOUT PLACING"));
//            }
            ValidFreeSpace = false;
        }
        CurrentRoom+=1;
    }
    //debug
//    if(GEngine)
//    {
//        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("TOTAL ROOMS MADE: %d"), roomsmade));
//    }
//    if(GEngine)
//    {
//        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("TOTAL EDGES NOT FOUND: %d"), noedge));
//    }
    //CleanUp();
}
bool ALevelGenarator::ValidEdgeTileCheck(int r, int c, int room)
{
    int RDirection[] = {0,0,1,-1};
    int CDirection[] = {1,-1,0,0};
    for(int i = 0; i < 4; i++)
    {
        if(CheckBounds(r+RDirection[i], c+CDirection[i]) && this->CheckValidSpot(r+RDirection[i], c+CDirection[i], room))
        {
            if(MapTiles[r][c] == room)
                return true;
        }
    }
    return false;
    
}

//TODO
//MAKE CHECK BOUNDS FUNCTION/BREAK SOME FUNCTIONS UP


//MAIN QUESTIONS
//1 HOW TO DO LEVEL SPAWN ACRTOR? SHOULD I JUST TELEPORT CHARACTER
//2 TRACK DOWN A BUG CASUSING CRASH WHEN EXITING GAME SOMETHING TO DO WITH MEMORY ALLOCATION?
//3 GAME AWARDS THING WE PRESENTING ON MONDAY? DO WE NEED TO PRESENT EARLIER?

bool ALevelGenarator::CheckBounds(int r, int c)
{
    if(r < 0)
        return false;
    if(c < 0)
        return false;
    if(r >= MapBounds)
        return false;
    if(c >= MapBounds)
        return false;
    return true;
}

bool ALevelGenarator::PathExists(int room1, int room2)
{
    if(room1 < 0 || room2 < 0)
    {
        if(GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("NEGATIVE ROOM"));
        }
        
    }
    if(room1 >= RoomCount || room2 >=RoomCount)
    {
        if(GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("BIG ROOM NUM"));
        }
    }
//    if(AdjMatrix[room1][room2] ==1 || AdjMatrix[room2][room1] ==1)
//    {
//        return true;
//    }
    return false;
}

void ALevelGenarator::BuildPath(int r, int c, int room1, int room2)
{
    if(r == 0 && c== 0)
    {
        FVector FloorLocation(0.f+600.f*r,0.f+600.f*c,75.f);
        SpawnFloor(FloorLocation);
        UpdateAdjMatrix(r, c, room1, room2);
        
        
    }
}
bool ALevelGenarator::CheckValidSpot(int r, int c, int room)
{
    int RDirection[] = {0,0,1,-1};
    int CDirection[] = {1,-1,0,0};
    
    
    if(!CheckBounds(r, c))
    {
        return false;
    }
    
    
    if(MapTiles[r][c] == 0)
    {
//        TODO FIX
        for(int i = 0; i < 4; i++)
        {
            if(CheckBounds(r+RDirection[i],c+CDirection[i]))
            {
                int NearbyValue = MapTiles[r+RDirection[i]][c+CDirection[i]];
                if(NearbyValue != 0 && NearbyValue!= room)
                {
//                    if(RoomStartDone && !PathExists(NearbyValue, room))
//                    {
//                        if(GEngine)
//                        {
//                            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("NO PATH"));
//                        }
////                        //MAKE PATH
////                        BuildPath(r, c, NearbyValue, room);
//                    }
                    return false;
                }
            }
        }
        return true;

    }
    return false;
    
}

void ALevelGenarator::DungeonLayout()
{
    
    
    //Floor
    FVector FloorLocation(0.f,0.f,75.f);
    
    //RightCol
    FVector LocationTest1(0.0f, 0.0f+600.f*1, 70.f);
    FRotator RotationTest1(0.0f, -90.0f, 0.0f);
    
    //LeftCol
    FVector LocationTest2(0.0f, 0.0f, 70.f);
    FRotator RotationTest2(0.0f, -90.0f, 0.0f);
    
    //AboveRow
    FVector LocationTest3(0.0f+600.f*1, 0.0f, 70.f);
    FRotator RotationTest3(0.0f, 0.0f, 0.0f);
    
    //BelowRow
    FVector LocationTest4(0.0f, 0.0f, 70.f);
    FRotator RotationTest4(0.0f, 0.0f, 0.0f);
    
    
    //Arr for level tile spots
    //Map with row coords
    //Map with col coords
    PlaceRoomStarts();
    RoomStartDone = true;
    
    
    
    return;
    
    
    
    
    
    
    
//    int value = 5;
//    int *Rooms = (int *)FMemory::Malloc(sizeof(int)*value);
//    for (int idx = 0; idx < 5; idx++)
//    {
//        Rooms[idx] = 0;
//
//
//    }
//
//    int **arr = (int **)FMemory::Malloc(sizeof(int)*value);
//    for(int i = 0; i < value; i++)
//    {
//        arr[i] = (int *)FMemory::Malloc(sizeof(int)*value);
//    }
//    for(int r = 0; r < value; r++)
//    {
//        for(int c = 0; c < value; c++)
//        {
//            arr[r][c] = 0;
//            if(GEngine)
//            {
//                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Yup"));
//            }
//        }
//    }
//
//    TMap<int, int**> FruitMap;
//    FruitMap.Add(5, arr);



    
    
    
    return;
    
//    //SPAWN PLAYER START
//    FActorSpawnParameters SpawnInfo;
//    SpawnInfo.Owner = this;
//    SpawnInfo.Instigator = NULL;
//    SpawnInfo.bDeferConstruction = false;
//    FVector Loc(50.0f+600.f*RoomLocationR[0], 50.0f+600.f*RoomLocationC[0], 150.0f);
//
////    APlayerStart* PlayerStart = GetWorld()->SpawnActor<APlayerStart>(APlayerStart::StaticClass(), Loc ,FRotator::ZeroRotator, SpawnInfo );
//
//    GetWorld()->SpawnActor<APlayerStart>(Loc, FRotator::ZeroRotator, SpawnInfo);
//


}
void ALevelGenarator::SpawnFloor(FVector vec)
{
    
//    if(GEngine)
//    {
//        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Spawning Floor"));
//    }
    UStaticMeshComponent* FloorMesh = NewObject<UStaticMeshComponent>(this);
    FloorMesh->SetStaticMesh(Tile);
    FloorMesh->RegisterComponent();
    FloorMesh->SetMobility(EComponentMobility::Movable);
    FloorMesh->SetWorldLocationAndRotation(vec, FRotator::ZeroRotator);
    FloorMesh->SetMobility(EComponentMobility::Static);

    
}
void ALevelGenarator::SpawnWall(FVector vec, FRotator rot)
{
    UStaticMeshComponent* WallMesh = NewObject<UStaticMeshComponent>(this);
    WallMesh->SetStaticMesh(Wall);
    WallMesh->RegisterComponent();
    WallMesh->SetMobility(EComponentMobility::Movable);
    WallMesh->SetWorldLocationAndRotation(vec, rot);
    WallMesh->SetMobility(EComponentMobility::Static);
    
}

void ALevelGenarator::CleanUp()
{
    //Free map subarrays
    for(int i = 0; i < MapBounds; i++)
    {
        if(MapTiles)
        {
            if(MapTiles[i])
            {
                FMemory::Free(MapTiles[i]);
            }
        }
        
    }
    //Free overall array
    if(MapTiles)
    {
        FMemory::Free(MapTiles);
    }
    
    //Free adj subarrays
    for(int i = 0; i < RoomCount; i++)
    {
        if(AdjMatrix)
        {
            if(AdjMatrix[i])
            {
                FMemory::Free(AdjMatrix[i]);
            }
        }
    }
    
    //Free overall adj matrix
    if(AdjMatrix)
    {
        FMemory::Free(AdjMatrix);
    }
    
    for(int i = 1; i <=RoomCount; i++)
    {
        if(RoomRows[i])
        {
            FMemory::Free(RoomRows[i]);
        }
        if(RoomCols[i])
        {
            FMemory::Free(RoomCols[i]);
        }
    }
    
    
}

