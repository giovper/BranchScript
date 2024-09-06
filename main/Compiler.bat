@echo off
setlocal

REM Source directory and output executable name
set "SRC_DIR=%~dp0src"
set "EXEC_NAME=%~dp0BranchScript.exe"
set "OBJ_DIR=%~dp0obj"

REM Create the temporary directory for object files if it doesn't exist
if not exist "%OBJ_DIR%" mkdir "%OBJ_DIR%"

REM Compile all .cpp files into object files
echo Compiling all .cpp files...
for /r "%SRC_DIR%" %%f in (*.cpp) do (
    echo Compiling %%f
    g++ -c "%%f" -o "%OBJ_DIR%\%%~nxf.obj"
)

REM Check for compilation errors before linking
if errorlevel 1 (
    echo Compilation error. Aborting.
    exit /b 1
)

REM Link all object files into a single executable
echo Creating the executable %EXEC_NAME%...
g++ -o "%EXEC_NAME%" "%OBJ_DIR%\*.obj"

REM Clean up temporary object files
echo Cleaning up temporary object files...
del /q "%OBJ_DIR%\*.obj"
rmdir "%OBJ_DIR%"

echo Compilation completed. Executable created: %EXEC_NAME%
pause
