@ECHO OFF
set EnableNuGetPackageRestore=true
set SDKDIR="C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\bin"
set version=2.1

REM go to correct directory if not so already
cd ..\src
cd src

REM delete prio build output
del bin\copy-unc-path-%version%.exe

REM build the DLLs and sign them
msbuild /t:Rebuild /p:Configuration=Release;Platform=Win32 CopyUncPath\CopyUncPath.vcxproj
%SDKDIR%\signtool.exe sign /f ..\src\copyuncpath.pfx /t "http://timestamp.verisign.com/scripts/timstamp.dll" bin\cpp\CopyUncPath_x86.dll
msbuild /t:Rebuild /p:Configuration=Release;Platform=x64 CopyUncPath\CopyUncPath.vcxproj
%SDKDIR%\signtool.exe sign /f ..\src\copyuncpath.pfx /t "http://timestamp.verisign.com/scripts/timstamp.dll" bin\cpp\CopyUncPath_x64.dll

REM build the MSI installers for 32- and 64-bit
msbuild /t:Rebuild /p:Configuration=Release;Platform=x86 Installer\Installer.wixproj
msbuild /t:Rebuild /p:Configuration=Release;Platform=x64 Installer\Installer.wixproj

REM build the bootstrapper to combine 32- and 64-bit MSI into one exe
msbuild /t:Rebuild /p:Configuration=Release;Platform=x86 Bootstrapper\Bootstrapper.wixproj

REM ... and last but not least, sign the installer exe
REM signing the bootstrapper not possible at the moment due to the engine.exe in the bootstrapper not signed
REM %SDKDIR%\signtool.exe sign /f ..\src\copyuncpath.pfx /t "http://timestamp.verisign.com/scripts/timstamp.dll" bin\copy-unc-path.exe
ren bin\copy-unc-path.exe copy-unc-path-%version%.exe
