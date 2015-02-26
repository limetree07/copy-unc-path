set SDKDIR="C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\bin"
%SDKDIR%\signtool.exe sign /f ..\src\copyuncpath.pfx /t "http://timestamp.verisign.com/scripts/timstamp.dll" %1