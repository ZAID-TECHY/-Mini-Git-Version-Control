@echo off
REM Try to compile with g++ if available
where g++ >nul 2>nul
if %errorlevel%==0 (
    g++ .\*.cpp -std=c++11 -O2 -o .\mini_git.exe
    if %errorlevel%==0 (
        echo Build succeeded: mini_git.exe
        exit /b 0
    ) else (
        echo g++ failed to compile.
        exit /b 1
    )
) else (
    echo g++ not found in PATH. Please install MinGW-w64 or use Visual Studio Developer Command Prompt.
    exit /b 2
)
