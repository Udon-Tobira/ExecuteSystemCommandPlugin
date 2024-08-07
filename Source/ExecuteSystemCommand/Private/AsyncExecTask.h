// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class FAsyncExecTask: public FNonAbandonableTask {
	friend class FAutoDeleteAsyncTask<FAsyncExecTask>;

public:
	FAsyncExecTask(TFunction<void()> InTask);

private:
	void                DoWork();
	FORCEINLINE TStatId GetStatId() const {
		RETURN_QUICK_DECLARE_CYCLE_STAT(FAsyncExecTask,
		                                STATGROUP_ThreadPoolAsyncTasks);
	}

private:
	TFunction<void()> Task;
};
