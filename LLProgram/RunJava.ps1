# This script opens an excel file linked to sharepoint, allows it to update, then closes the file. 
# The script then calls a java file, which checks the status of the sharepoint file.
# All output is logged in loanerLog.txt
# Written By: Brittany Deventer
# 2/3/2018 


# Define the file full name.
$FilePath = "\LLProgram\LoanerLaptops.xlsx"
$logPath = "\LLProgram\loanerLog.txt"
$jobPath = "\LLProgram\LoanerLaotops.jar"

# Check whether the file exists.
if (-NOT (Test-Path $FilePath)){
	WBScript.Quit
}

# Create a new Excel-instance, display it and open the file.
$objExcel = New-Object -ComObject Excel.Application

# Set whether to see file open or not
$objExcel.Visible = $false

# Open file and save to Workbook variable
$WorkBook = $objExcel.Workbooks.Open($FilePath)

# Excel file is set to refresh Sharepoint data at startup
$WorkBook.RefreshAll()
#refresh again for good measure
$WorkBook.RefreshAll()

# Save the workbook and clean up.
$objExcel.ActiveWorkbook.Save()
$objExcel.Workbooks.Close()
$objExcel.Quit()
#$objExcel = Null

# Let the user notice what we did.
Start-Sleep 5

# Run LoanerLaptops.jar and append to log file
java -jar $jobPath $FilePath | Add-Content $logPath

# Open log file
ii $logPath

