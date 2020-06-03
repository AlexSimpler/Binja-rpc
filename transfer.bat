@echo off
move /y .\bin\Binja-rpc.dll "C:\Users\admob\AppData\Roaming\Binary Ninja\plugins"
ping 127.0.0.1 -n 3 > NUL
