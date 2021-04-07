import os
import subprocess
import sys



if (not os.path.exists("build")):
	os.mkdir("build")
else:
	for r,_,fl in os.walk("build"):
		for f in fl:
			os.remove(os.path.join(r,f))
tmp=os.getcwd()
os.chdir("build")
if ("--release" in sys.argv):
	if (os.name=="nt"):
		if (subprocess.run(["cl","/c","/permissive-","/GS","/utf-8","/W3","/Zc:wchar_t","/Gm-","/sdl","/Zc:inline","/fp:precise","/D","NDEBUG","/D","_WINDOWS","/D","_UNICODE","/D","UNICODE","/errorReport:none","/WX","/Zc:forScope","/Gd","/Oi","/FC","/EHsc","/nologo","/diagnostics:column","/GL","/Gy","/Zi","/O2","/Oi","/MT","../src/main.c","../src/chess_ai/*.c","/I","../src/include"]).returncode!=0 or subprocess.run(["link","*.obj","/OUT:chess_ai.exe","/DYNAMICBASE","kernel32.lib","user32.lib","gdi32.lib","winspool.lib","comdlg32.lib","advapi32.lib","shell32.lib","ole32.lib","oleaut32.lib","uuid.lib","odbc32.lib","odbccp32.lib","/MACHINE:X64","/SUBSYSTEM:CONSOLE","/ERRORREPORT:none","/NOLOGO","/TLBID:1","/WX","/LTCG","/OPT:REF","/INCREMENTAL:NO","/OPT:ICF"]).returncode!=0):
			os.chdir(tmp)
			sys.exit(1)
	else:
		if (subprocess.run(["x86_64-w64-mingw32-gcc","-c","-I","../src/include","../src/*.c","../src/chess_ai/*.c","-Wall","-O3"]) or subprocess.run(["x86_64-w64-mingw32-gcc","*.o","-Wall","-o","chess_ai.exe","-O3"])):
			os.chdir(tmp)
			sys.exit(1)
else:
	if (os.name=="nt"):
		if (subprocess.run(["cl","/c","/permissive-","/GS","/utf-8","/W3","/Zc:wchar_t","/Gm-","/sdl","/Zc:inline","/fp:precise","/D","_DEBUG","/D","_WINDOWS","/D","_UNICODE","/D","UNICODE","/errorReport:none","/WX","/Zc:forScope","/Gd","/Oi","/FC","/EHsc","/nologo","/diagnostics:column","/ZI","/Od","/RTC1","/MTd","../src/main.c","../src/chess_ai/*.c","/I","../src/include"]).returncode!=0 or subprocess.run(["link","*.obj","/OUT:chess_ai.exe","/DYNAMICBASE","kernel32.lib","user32.lib","gdi32.lib","winspool.lib","comdlg32.lib","advapi32.lib","shell32.lib","ole32.lib","oleaut32.lib","uuid.lib","odbc32.lib","odbccp32.lib","/MACHINE:X64","/SUBSYSTEM:CONSOLE","/ERRORREPORT:none","/NOLOGO","/TLBID:1","/WX","/DEBUG","/INCREMENTAL"]).returncode!=0):
			os.chdir(tmp)
			sys.exit(1)
	else:
		if (subprocess.run(["x86_64-w64-mingw32-gcc","-c","-I","../src/include","../src/*.c","../src/chess_ai/*.c","-Wall"]) or subprocess.run(["x86_64-w64-mingw32-gcc","*.o","-Wall","-o","chess_ai.exe"])):
			os.chdir(tmp)
			sys.exit(1)
os.chdir(tmp)
for r,_,fl in os.walk("build"):
	for f in fl:
		if (f[-4:]!=".exe"):
			os.remove(os.path.join(r,f))
if ("--run" in sys.argv):
	subprocess.run(["build/chess_ai.exe"])
