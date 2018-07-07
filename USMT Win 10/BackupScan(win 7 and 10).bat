@echo Off

:start

echo    :::::::::::::::::::::::::::::::::::::::::::::::::
echo   :::::::::::::::::::::::::::::::::::::::::::::::::::
echo  :::         Auto Scan for Windows 7 and 10        :::
echo ::::            Brittany Deventer - ISS            ::::
echo  :::           Version 1.0 - March 11, 2018        :::
echo  :::          Modified from the Legendary          :::
echo   ::            William Griffin Scripts            ::
echo   :::::::::::::::::::::::::::::::::::::::::::::::::::
echo    :::::::::::::::::::::::::::::::::::::::::::::::::
echo.

pause
cls

set packageLocation=\\mpcl01fl\shared\Departments\Client.Services\OverlookMC\USMT\USMT10
set overlookBackupTarget=\\mpcl01fl\SHARED\Departments\Client.Services\OverlookMC\Client Backups
set localTarget=c:\USMT10\

Echo Copying USMT10 to local machine (please be patient)
::Copy the USMT10 files to local machine.
robocopy %packageLocation%  %localTarget% /E > NUL 2>&1
echo .
echo Transfer complete

cls

::echo.
::echo Running USMT10 Backup Script. Backup image will be saved to %overlookBackupTarget%\%COMPUTERNAME%
::echo Please note this can take some time depending on data and computer specs...

::Execute ScanState

:: Add backup location options
echo Please choose a backup location
echo 1) Root of the C drive (default)
echo 2) Client Backups folder on overlook share

set /p backupLocation=Backup Location?=%

cls

:: Add in backup interval options
echo Backup user accounts that were active in the last:
echo 1) 60 Days (Standard)
echo 2) 120 Days
::echo 3) All (recommended for off domain PC's)

set /p backupInterval=Backup interval?=%

cls

:: Determine 32 or 64 bit OS so proper USMT package is used
c:
IF EXIST "%PROGRAMFILES(x86)%" (set bit=amd64) ELSE (set bit=x86)

cls

echo Running ScanState

:: Run USMT Scan state for correct OS
:: C:\USMT10\%bit%\scanstate.exe /i:\USMT10\%bit%\settings_5.xml /i:\USMT10\%bit%\settings_6.xml /i:\USMT10\%bit%\settings_8.xml /i:\USMT10\%bit%\MappedDrivesAndPrinters.xml /uel:60 /ue:* /ui:AHS\* /localonly /efs:copyraw /o /c /v:5 C:\UserState\%COMPUTERNAME% /l:C:\UserState\%COMPUTERNAME%\%COMPUTERNAME%_Scan.log
IF /i %backupInterval% == 1 (C:\USMT10\%bit%\scanstate.exe /i:\USMT10\%bit%\settings_5.xml /i:\USMT10\%bit%\settings_6.xml /i:\USMT10\%bit%\settings_8.xml /i:\USMT10\%bit%\MappedDrivesAndPrinters.xml /uel:60 /ue:* /ui:AHS\* /localonly /efs:copyraw /o /c /v:5 C:\UserState\%COMPUTERNAME% /l:C:\UserState\%COMPUTERNAME%\%COMPUTERNAME%_Scan.log)
IF /i %backupInterval% == 2 (C:\USMT10\%bit%\scanstate.exe /i:\USMT10\%bit%\settings_5.xml /i:\USMT10\%bit%\settings_6.xml /i:\USMT10\%bit%\settings_8.xml /i:\USMT10\%bit%\MappedDrivesAndPrinters.xml /uel:120 /ue:* /ui:AHS\* /localonly /efs:copyraw /o /c /v:5 C:\UserState\%COMPUTERNAME% /l:C:\UserState\%COMPUTERNAME%\%COMPUTERNAME%_Scan.log)

echo ScanState complete 
echo Creating additional config files

:: Back up the print.ini file
xcopy  /e /y "C:\Program Files (x86)\PrinterScript\print.INI" "c:\Userstate\"

:: Backup PCView config
IF EXIST "C:\Program Files\McKesson\PCView32\pcview.cfg" (xcopy /e /y "C:\Program Files\McKesson\PCView32\pcview.cfg" "c:\Userstate\")

:: Back up the Computer description
for /f "tokens=2*" %%a in ('reg query HKLM\System\CurrentControlSet\Services\LanmanServer\Parameters /v srvcomment') do set "Description=%%~b"
echo %Description% >"C:\userstate\Description.file"

:: Back up the user info for who backed it up
date /t >"C:\userstate\date.file"
echo %Username% >"C:\userstate\user.file"

:: Create the info txt file in the userstate to keep track of the who backed it up and when
date /t >"C:\userstate\Backup info.txt"
set | find "USERNAME" >> "C:\userstate\Backup info.txt"
hostname >> "C:\userstate\Backup info.txt"
echo %Description% >> "C:\userstate\Backup info.txt"

:: If backing up on share, copy files to share
if /i %backupLocation% == 2 (GOTO copy)

:: Else, default endpoint here
pause
EXIT

:: Copy files to client backups folder in share
:copy
cls
echo Now attempting to move Userstate file to Share
xcopy /e c:\userstate "%overlookBackupTarget%\%COMPUTERNAME%\UserState\"
::echo Transfer attempt complete
GOTO End

:End
::cls
echo End of Program
pause
EXIT


