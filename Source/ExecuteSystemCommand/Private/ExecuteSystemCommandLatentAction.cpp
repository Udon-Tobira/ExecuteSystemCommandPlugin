// Fill out your copyright notice in the Description page of Project Settings.

#include "ExecuteSystemCommandLatentAction.h"

#include "AsyncExecTask.h"

#if PLATFORM_WINDOWS
#include <process.h>
#endif

FExecuteSystemCommandLatentAction::FExecuteSystemCommandLatentAction(
    const FLatentActionInfo& InLatentInfo, const FString& Command)
    : ExecutionFunction(InLatentInfo.ExecutionFunction),
      OutputLink(InLatentInfo.Linkage),
      CallbackTarget(InLatentInfo.CallbackTarget) {
	auto AsyncExecTask =
	    new FAutoDeleteAsyncTask<FAsyncExecTask>([this, Command]() {
#if PLATFORM_WINDOWS
		    _wsystem(*Command);
#else
		    std::system(TCHAR_TO_UTF8(*Command));
#endif

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
