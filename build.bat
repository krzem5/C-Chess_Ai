@echo off
cls
set _INCLUDE=%INCLUDE%
set INCLUDE=../src/include;%INCLUDE%
if exist build rmdir /s /q build
mkdir build
cd build
if %1.==. goto dbg
if %1==-r (
	cl /c /permissive- /utf-8 /GS /W3 /Zc:wchar_t /Gm- /sdl /Zc:inline /fp:precise /D "NDEBUG"  /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /errorReport:none /WX /Zc:forScope /Gd /Oi /FC /EHsc /nologo /diagnostics:column /GL /Gy /Zi /O2 /Oi /MT ../src/main.c ../src/chess_ai/*.c&&link *.obj /OUT:chess_ai.exe /DYNAMICBASE "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /MACHINE:X64 /SUBSYSTEM:CONSOLE /ERRORREPORT:none /NOLOGO /TLBID:1 /WX /LTCG /OPT:REF /INCREMENTAL:NO /OPT:ICF&&goto run
	goto end
)
:dbg
cl /c /permissive- /GS /utf-8 /W3 /Zc:wchar_t /Gm- /sdl /Zc:inline /fp:precise /D "_DEBUG"  /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /errorReport:none /WX /Zc:forScope /Gd /Oi /FC /EHsc /nologo /diagnostics:column /ZI /Od /RTC1 /MTd ../src/main.c ../src/chess_ai/*.c&&link *.obj /OUT:chess_ai.exe /DYNAMICBASE "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /MACHINE:X64 /SUBSYSTEM:CONSOLE /ERRORREPORT:none /NOLOGO /TLBID:1 /WX /DEBUG /INCREMENTAL&&goto run
goto end
:run
del *.obj
del *.pdb
del *.exp
del *.ilk
del *.idb
cls
chess_ai.exe
:end
cd ..
set INCLUDE=%_INCLUDE%
