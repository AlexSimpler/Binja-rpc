@echo off
move /y bin\Binja-rpc.dll %appdata%\"Binary Ninja"\plugins > nul 2> nul
if NOT errorlevel == 1 (
echo Successfully updated the plugin. 
)else (
echo Failed. Did you forget to close Binary Ninja?
)
ping 127.0.0.1 -n 2 > NUL