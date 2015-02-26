set SDKDIR="C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\bin"
%SDKDIR%\signtool.exe sign /f ..\src\limetree07.pfx /p %1 /t "http://www.trustcenter.de/codesigning/timestamp" %2