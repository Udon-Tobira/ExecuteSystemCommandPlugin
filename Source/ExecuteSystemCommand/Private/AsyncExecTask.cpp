// Fill out your copyright notice in the Description page of Project Settings.

#include "AsyncExecTask.h"

FAsyncExecTask::FAsyncExecTask(TFunction<void()> InTask) : Task(InTask) {}

void FAsyncExecTask::DoWork() {
	Task();
}
