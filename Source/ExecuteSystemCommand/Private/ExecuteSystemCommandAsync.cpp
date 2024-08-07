// Fill out your copyright notice in the Description page of Project Settings.

#include "ExecuteSystemCommandAsync.h"

#include "AsyncExecTask.h"
#include "ExecuteSystemCommandLatentAction.h"

void UExecuteSystemCommandAsync::ExecuteSystemCommandAsync(
    const UObject* WorldContextObject, FLatentActionInfo LatentActionInfo,
    const FString& Command) {
	check(WorldContextObject != nullptr);

	const auto World = GEngine->GetWorldFromContextObject(
	    WorldContextObject, EGetWorldErrorMode::Assert);
	check(World != nullptr);

	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();

	LatentActionManager.AddNewAction(
	    LatentActionInfo.CallbackTarget, LatentActionInfo.UUID,
	    new FExecuteSystemCommandLatentAction(LatentActionInfo, Command));
}
