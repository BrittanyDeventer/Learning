@echo off

::start

echo    :::::::::::::::::::::::::::::::::::::::::::::::::
echo   :::::::::::::::::::::::::::::::::::::::::::::::::::
echo  :::         Auto Load for Windows 7 and 10        :::
echo ::::            Brittany Deventer - ISS            ::::
echo  :::           Version 1.0 - March 11, 2018        :::
echo  :::          Modified from the Legendary          :::
echo   ::            William Griffin Scripts            ::
echo   :::::::::::::::::::::::::::::::::::::::::::::::::::
echo    :::::::::::::::::::::::::::::::::::::::::::::::::
echo.
echo.

cls

set packageLocation=\USMT\USMT10
set overlookBackupTarget=\Client Backups
set localTarget=c:\USMT10\

:: Ask for hostname of old computer
set /p Hostname=What is the hostname of the old computer?=%

cls

:: Instantiate variables
::echo instantiating variables
set local=0
set cbu=0
set ct=0 
set blc=0

:: Find backup on local or share 
echo Finding backup location...
IF EXIST "C:\userstate\%Hostname%" (@echo files found on local computer) && set local=1 && set ct=1
IF EXIST "%overlookBackupTarget%\%Hostname%" (@echo files found on Overlook Share) && set cbu=1 && set ct=1

pause

cls
::IF /i %local% == 1 && %cbu% == 1 (set blc=1)
::pause
:: Ask to choose a a backup location
IF /i %ct% == 1 (@echo Please choose a backup location to load)
@echo:

::pause
IF /i %local% == 1 (@echo Option 1 Load from Local UserState file)
IF /i %local% == 1 (@echo|set /p="Backed up on: ")
IF Exist "C:\UserState\date.file" (type C:\UserState\date.file )
IF /i %local% == 1 (@echo|set /p="Backed up by: ")
IF Exist "C:\UserState\user.file" (type C:\UserState\user.file )
IF /i %local% == 1 (@echo:)

IF /i %cbu% == 1 (@echo Option 2 Load from Overlook Client Backups)
IF /i %cbu% == 1 (@echo|set /p="Backed up on: ")
IF Exist "\\mpcl01fl\iss\public\Overlook\Client Backups\%Hostname%\Userstate\date.file" (type "\Client Backups\%Hostname%\userstate\date.file" )
IF /i %cbu% == 1 (@echo|set /p="Backed up by: ")
IF Exist "\\mpcl01fl\iss\public\Overlook\Client Backups\%Hostname%\Userstate\user.file" (type "\Client Backups\%Hostname%\userstate\user.file" )
IF /i %cbu% == 1 (@echo:)

IF /i %ct% == 0 (@echo Could not find file!!)
IF /i %ct% == 0 (GOTO END)


:: Input chosen backup location
IF /i %ct% == 1 (set /p backupOption= Backup Option?=%)
::ELSE set backupOption=2

::echo %backupOption%

::pause

:: Determine 32 or 64 bit OS
c:
IF EXIST "%PROGRAMFILES(x86)%" (set bit=amd64) ELSE (set bit=x86)


:: Copy USMT10 files to the local C: drive
robocopy %packageLocation% %localTarget% /E /xx > NUL 2>&1

echo robocopy complete
::pause

:: Go to correct upload section
if /i %backupOption% == 1 (GOTO local)
if /i %backupOption% == 2 (GOTO share)


:local

:: Run USMT Load state for correct OS
echo Running loadstate

C:\USMT10\%bit%\loadstate.exe /config:c:\USMT10\%bit%\config.xml /i:\USMT10\%bit%\settings_5.xml /i:\USMT10\%bit%\settings_6.xml /i:\USMT10\%bit%\settings_8.xml /i:\USMT10\%bit%\MappedDrivesAndPrinters.xml /ue:* /ui:AHS\* /c /v:5 C:\UserState\%Hostname%\ /l:C:\UserState\%HostName%_load.log

cls
echo loadstate complete
::pause
:: Copy the Printer script config to the new PC
echo Transfering Printer settings
IF Exist c:\Userstate\print.INI (xcopy "c:\Userstate\print.INI" "C:\Program Files (x86)\PrinterScript\" /e /-y)

:: Copy the PCView config to the new PC if it exists
:: 3/13/18: can probably get rid of this...
IF EXIST C:\Userstate\PCView.cfg (xcopy "C:\Userstate\PCView.cfg" "C:\Program Files\McKesson\PCView32\" /e /-y)

:: Set Authenticated users to power users
echo Setting power users to authenticated users
net localgroup "power users" "nt authority\authenticated users" /add

:: determine if the description was backed up, sets if yes
IF EXIST "c:\Userstate\Description.file" (GOTO SetDes)



:: End program
:End
echo End of Program
pause
EXIT



:share
cls
:: copy backup to c drive
echo Copying backup from share to local
::pause
set localDrive=C:\
robocopy /E /xx /is "%overlookBackupTarget%\%hostname%" %localDrive% > NUL 2>&1

echo Copy successful
pause
GOTO local


:SetDes
echo Setting description
::pause
set /p description=<c:\userstate\description.file
reg add "HKLM\System\CurrentControlSet\Services\LanmanServer\Parameters" /f /v "srvcomment" /t REG_SZ /d "%Description%"
::pause
GOTO End


