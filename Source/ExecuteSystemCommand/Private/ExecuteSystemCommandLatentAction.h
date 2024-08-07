// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Internal class for UExecuteSystemCommandAsync::ExecuteSystemCommandAsync
 */
class FExecuteSystemCommandLatentAction: public FPendingLatentAction {
public:
	FExecuteSystemCommandLatentAction(const FLatentActionInfo& InLatentInfo,
	                                  const FString&           Command);

public:
	// this function is called every frame to check if it has finished.
	virtual void UpdateOperation(FLatentResponse& Response) override;

	/* internal fields */
private:
	bool IsRunning = false;

	FName          ExecutionFunction;
	int32          OutputLink;
	FWeakObjectPtr CallbackTarget;
};
