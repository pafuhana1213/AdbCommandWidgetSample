// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "Kismet/BlueprintAsyncActionBase.h"

#include "AdbCommandEditorWidgetBPLibrary.generated.h"



UCLASS()
class UAdbCommandEditorWidgetBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "AdbCommandEditorWidget")
	static FString GetAdbPath();

	UFUNCTION(BlueprintCallable, Category = "AdbCommandEditorWidget")
	static bool ExecuteAdbCommand(FString CommandLine, FString& OutStdOut, FString& OutStdErr, int32& OutErrorCode);

	UFUNCTION(BlueprintCallable, Category = "AdbCommandEditorWidget")
	static void ParseIntoArrayLines(FString SourceString, TArray<FString>& OutArray);

	UFUNCTION(BlueprintCallable, Category = "AdbCommandEditorWidget")
	static FString GetAndroidPackageName();

	UFUNCTION(BlueprintCallable, Category = "AdbCommandEditorWidget")
	static FString OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes);

	UFUNCTION(BlueprintCallable, Category = "AdbCommandEditorWidget")
	static bool CreateDirectory(FString Path);
};


/* UAsyncActionExecuteAdbCommand
 *****************************************************************************/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FAsyncExecuteAdbCommandCompleted, FString, CommandLine, FString, StdOut, FString, StdErr, int32, ErrorCode, bool, bResult);

class FAsyncExecuteAdbCommandTask : public FNonAbandonableTask
{
	friend class FAutoDeleteAsyncTask<FAsyncExecuteAdbCommandTask>;

public:
	FAsyncExecuteAdbCommandTask(FString CL)
		: CommandLine(CL)
	{
	}

	void DoWork()
	{
		FString OutStdOut;
		FString OutStdErr;
		int32 OutErrorCode = 0;
		bool Result = UAdbCommandEditorWidgetBPLibrary::ExecuteAdbCommand(CommandLine, OutStdOut, OutStdErr, OutErrorCode);

		Completed.Broadcast(CommandLine, OutStdOut, OutStdErr, OutErrorCode, Result);
	}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FAsyncExecTask, STATGROUP_ThreadPoolAsyncTasks);
	}

	void AddToCompletedDelegate(FAsyncExecuteAdbCommandCompleted::FDelegate& delegate)
	{
		Completed.Add(delegate);
	}

	FAsyncExecuteAdbCommandCompleted Completed;

private:
	FString CommandLine;

};

UCLASS()
class UAsyncActionExecuteAdbCommand : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FAsyncExecuteAdbCommandCompleted Completed;

private:
	FString TmpCommandLine;

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "AdbCommandEditorWidget")
	static UAsyncActionExecuteAdbCommand* AsyncExecuteAdbCommand(UObject* WorldContextObject, FString CommandLine);

	virtual void Activate() override;

	UFUNCTION()
	void Finish(FString CommandLine, FString StdOut, FString StdErr, int32 ErrorCode, bool bResult);

private:
	FAsyncTask<FAsyncExecuteAdbCommandTask>* AsyncExecuteAdbCommandTask;
};
