// Fill out your copyright notice in the Description page of Project Settings.

#include "ExecuteSystemCommandLatentAction.h"

#include "AsyncExecTask.h"

FExecuteSystemCommandLatentAction::FExecuteSystemCommandLatentAction(
    const FLatentActionInfo& InLatentInfo, const FString& Command)
    : ExecutionFunction(InLatentInfo.ExecutionFunction),
      OutputLink(InLatentInfo.Linkage),
      CallbackTarget(InLatentInfo.CallbackTarget) {
	auto AsyncExecTask =
	    new FAutoDeleteAsyncTask<FAsyncExecTask>([this, Command]() {
		    std::system(TCHAR_TO_ANSI(*Command));
		    IsRunning = false;
	    });

	IsRunning = true;
	AsyncExecTask->StartBackgroundTask();
}

void FExecuteSystemCommandLatentAction::UpdateOperation(
    FLatentResponse& Response) {
	Response.FinishAndTriggerIf(IsRunning == false, ExecutionFunction, OutputLink,
	                            CallbackTarget);
}
