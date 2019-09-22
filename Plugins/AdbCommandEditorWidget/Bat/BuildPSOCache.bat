@echo Put me CollectedPSOs directory!
set EDITOR-CMD_PATH="D:\Epic Games\UE_4.23\Engine\Binaries\Win64\UE4Editor-Cmd.exe"
set UPROJECT_PATH="D:\UnrealProject\ActionRPG\ActionRPG.uproject"
set PROJECT_NAME="ActionRPG"
set SHADER_FORMAT="GLSL_ES3_1_ANDROID"

%EDITOR-CMD_PATH% %UPROJECT_PATH% -run=ShaderPipelineCacheTools expand "%~dp0/*.rec.upipelinecache" "%~dp0/*.scl.csv" "%~dp0/%PROJECT_NAME%_%SHADER_FORMAT%.stablepc.csv"
cmd /k
