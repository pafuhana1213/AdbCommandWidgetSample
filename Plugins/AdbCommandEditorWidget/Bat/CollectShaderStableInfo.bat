@echo Put me CollectedPSOs directory!
cmd /k forfiles /p "%~dp0..\..\..\..\Saved\Cooked" /m *.scl.csv /s /c "cmd /c copy /z @path "%~dp0"
