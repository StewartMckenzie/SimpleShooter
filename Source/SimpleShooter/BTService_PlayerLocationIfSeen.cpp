// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_PlayerLocationIfSeen.h"
#include "kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = "Update Player Location If Seen";
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController *EnemyController = OwnerComp.GetAIOwner();
    if (EnemyController == nullptr)
    {
        return;
    }

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (PlayerPawn == nullptr)
    {
        return;
    }

    if (EnemyController->LineOfSightTo(PlayerPawn))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}
