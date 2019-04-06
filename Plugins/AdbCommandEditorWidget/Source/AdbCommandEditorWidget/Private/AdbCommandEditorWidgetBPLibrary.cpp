// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AdbCommandEditorWidgetBPLibrary.h"
#include "AdbCommandEditorWidget.h"

#include "Modules/ModuleManager.h"
#include "Interfaces/IAndroidDeviceDetectionModule.h"
#include "Interfaces/IAndroidDeviceDetection.h"
#include "AndroidRuntimeSettings.h"
#include "Misc/App.h"
#include "IDesktopPlatform.h"
#include "DesktopPlatformModule.h"
#include "SlateApplication.h"
#include "AsyncWork.h"
#include "HAL/PlatformFilemanager.h"

/* UAdbCommandEditorWidgetBPLibrary
 *****************************************************************************/
UAdbCommandEditorWidgetBPLibrary::UAdbCommandEditorWidgetBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FString UAdbCommandEditorWidgetBPLibrary::GetAdbPath()
{
	auto &AndroidDeviceDetection = FModuleManager::GetModuleChecked<IAndroidDeviceDetectionModule>("AndroidDeviceDetection");
	IAndroidDeviceDetection* DeviceDetection = AndroidDeviceDetection.GetAndroidDeviceDetection();

	return DeviceDetection->GetADBPath();
}

bool UAdbCommandEditorWidgetBPLibrary::ExecuteAdbCommand(FString CommandLine, FString& OutStdOut, FString& OutStdErr, int32& OutErrorCode)
{
	OutStdOut.Empty();
	OutStdErr.Empty();
	FPlatformProcess::ExecProcess(*GetAdbPath(), *CommandLine, &OutErrorCode, &OutStdOut, &OutStdErr);

	if (OutErrorCode != 0)
	{
		return false;
	}
	return true;
}

void UAdbCommandEditorWidgetBPLibrary::ParseIntoArrayLines(FString SourceString, TArray<FString>& OutArray)
{
	SourceString.ParseIntoArrayLines(OutArray);
}

FString UAdbCommandEditorWidgetBPLibrary::GetAndroidPackageName()
{
	FString PackageName = GetMutableDefault<UAndroidRuntimeSettings>()->PackageName;
	if (PackageName.Contains("[PROJECT]"))
	{
		PackageName = PackageName.Replace(TEXT("[PROJECT]"), FApp::GetProjectName());
	}

	return PackageName;
}

FString UAdbCommandEditorWidgetBPLibrary::OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes)
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	TArray<FString> OutOpenFilenames;

	DesktopPlatform->OpenFileDialog(
		FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr),
		DialogTitle,
		DefaultPath,
		DefaultFile,
		FileTypes,
		EFileDialogFlags::None,
		OutOpenFilenames
	);

	if (OutOpenFilenames.Num() == 0)
	{
		return "";
	}

	return OutOpenFilenames[0];
}

bool UAdbCommandEditorWidgetBPLibrary::CreateDirectory(FString Path)
{
	return FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*Path);
}


/* UAsyncActionExecuteAdbCommand
 *****************************************************************************/

UAsyncActionExecuteAdbCommand::UAsyncActionExecuteAdbCommand(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{}

UAsyncActionExecuteAdbCommand* UAsyncActionExecuteAdbCommand::AsyncExecuteAdbCommand(UObject* WorldContextObject, FString CommandLine)
{
	UAsyncActionExecuteAdbCommand* Action = NewObject<UAsyncActionExecuteAdbCommand>();
	Action->TmpCommandLine = CommandLine;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UAsyncActionExecuteAdbCommand::Activate()
{
	AsyncExecuteAdbCommandTask = new FAsyncTask<FAsyncExecuteAdbCommandTask>(TmpCommandLine);
	AsyncExecuteAdbCommandTask->GetTask().Completed.AddDynamic(this, &UAsyncActionExecuteAdbCommand::Finish);
	AsyncExecuteAdbCommandTask->StartBackgroundTask();
}

void UAsyncActionExecuteAdbCommand::Finish( FString StdOut, FString StdErr, int32 ErrorCode, bool bResult)
{
	AsyncTask(ENamedThreads::GameThread, [this, StdOut, StdErr, ErrorCode, bResult]()
	{
		Completed.Broadcast(StdOut, StdErr, ErrorCode, bResult);
		SetReadyToDestroy();

		AsyncExecuteAdbCommandTask->EnsureCompletion();
		delete AsyncExecuteAdbCommandTask;
	});
}