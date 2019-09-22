@echo Put me CollectedPSOs directory!
set PROJECT_NAME="ActionRPG"
set SHADER_FORMAT="GLSL_ES3_1_ANDROID"
set PROJECT_BUILD_PATH="%~dp0..\..\..\..\Build"
set PLATFORM_NAME="Android_ASTC"

mkdir "%PROJECT_BUILD_PATH%\%PLATFORM_NAME%\PipelineCaches"
cmd /k copy "%~dp0/%PROJECT_NAME%_%SHADER_FORMAT%.stablepc.csv" "%PROJECT_BUILD_PATH%\%PLATFORM_NAME%\PipelineCaches"
