@echo off
echo RUNNING

REM Run as scheduled task: LoanerLaptops, daily at 11am
REM Runs powershell script that calls a jar file
REM All related files are located in same directory, LLProgram

REM Run the powershell script and output to log file
powershell -file C:\users\bdeven01\LLPrograms\RunJava.ps1 > loanerLog.txt

REM Open log file so user remembers to view it
loanerLog.txt