//package com.pack;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.Iterator;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.text.ParseException;

//Apache POI 3.17 - all jar files linked
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;
import org.apache.poi.hssf.usermodel.HSSFDateUtil;

/* This program reads from file share *** and prompts the user when dates in column 'Date in' are past the current date.
* Written By: Brittany Deventer
* Sources: 
* http://www.seleniumeasy.com/jxl-tutorials/how-to-read-excel-file-using-java
* This is a sample program from the source above.  used as a starting point to build upon
* 
* 2/11:  I'd like to expand on this program:  
*  If a loaner is past due, I'd like an email to be sent to the required technician.
*  If no technician is in the notes, then an email should be sent to the entire team.  
*/


public class ReadXlsx {
	
	//@SuppressWarnings("deprecation")
	public void readXLSXFile(String fileName) throws ParseException
	{
		InputStream XlsxFileToRead = null;
		Workbook workbook = null;
		try 
		{
			XlsxFileToRead = new FileInputStream(fileName);
			
			//Getting the workbook instance for xlsx file
			workbook  = new XSSFWorkbook(XlsxFileToRead);
		} catch (FileNotFoundException e) 
		{
			e.printStackTrace();
		} catch (IOException e) 
		{
			e.printStackTrace();
		}

		//getting the first sheet from the workbook using sheet name. 
		Sheet sheet = workbook.getSheetAt(0);
		Row row;
		
		//Iterating all the rows in the sheet
		Iterator<Row> rows = sheet.rowIterator(); //returns iterator of the PHYSICAL rows (those that are defined --> have content)

		/*
		* Pseudo code:
		* Iterate rows and find "Overlook" lines
		* Iterate cells and find the "Scheduled Return Date" column
		* Compare date in column to current date
		* If date in column has passed, send a prompt to me stating: loaner number, date due, ticket number and notes (or maybe the whole line?)
		*/
		
		java.util.Date cDate = getCurrentDate();
		
		//Iterate through all rows
		while (rows.hasNext()) 
		{
			row = (Row) rows.next();
				
			//Find cells with string types
			//if (row.getCell(0).getCellType() == Cell.CELL_TYPE_STRING) 
			//{
				
				String site = "Overlook";
				
				//If Overlook asset
				if (row.getCell(0).getRichStringCellValue().getString().trim().equals(site)) 
				{					
					if(HSSFDateUtil.isCellDateFormatted(row.getCell(9)))
					{
						java.util.Date dd = row.getCell(9).getDateCellValue();
						
						//System.out.println(dd + " RowNum: " + row.getRowNum());
						
						//Now compare current date to due date and prompt user
						if (dd != null)
						{
							if (cDate.compareTo(dd) == 0)
							{
								//Loaner [] is DUE TODAY.  \nLoaned to: [].  \nNotes: [].
								System.out.println("Loaner: " + row.getCell(1) + " is DUE TODAY\n Loaned to: " + row.getCell(7) + ".\n Notes: " + row.getCell(11) + "\n");
								//If a tech's name is in the notes, email that tech (use switch or a bunch of if thens)
							} else if (cDate.compareTo(dd) < 0)
							{
								//System.out.println("Not due yet\n");
							} else if (cDate.compareTo(dd) > 0)
							{
								System.out.println("Loaner: " + row.getCell(1) + " is PAST DUE\n Loaned to: " + row.getCell(7) + ".\n Notes: " + row.getCell(11) + "\n");
							}
						}
					}
				}
			//}
		}
		System.out.println();
		try 
		{
			XlsxFileToRead.close();
			//System.out.println("[*]FILE CLOSED");
		} catch (IOException e) 
		{
			e.printStackTrace();
		}
	}
	/*
	//Finds tech in notes column and sends email
	public void emailTech()
	{
		System.out.println(row.getCell(7))
	}
	*/
	//Gets current date
	public java.util.Date getCurrentDate()
	{
		//create Current Date variable
		DateFormat df = new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");
		Calendar cd = Calendar.getInstance();
		
		java.util.Date cDate = cd.getTime();
		System.out.println("\n[+] Current Date: " + df.format(cDate) + "\n\n");
		return cDate;
	}

	public static void main(String[] args) throws ParseException
	{
		if (args.length == 0) {
			System.out.println("Please use syntax: \n java ReadXlsx [filepath to excel]");
		} 
		else {
			System.out.println("-----------------------\n[*] ReadXlsx checks the exported Loaner Laptop pool from AHS Sharepoint site \n[*] File path is hardcoded into program\n -------------- \n\n");
			ReadXlsx DT = new ReadXlsx();
			
			try {
				DT.readXLSXFile(args[0]);	
			}
			catch(ArrayIndexOutOfBoundsException exception){
				System.out.println("No filepath found in arg[0]");
			}
			System.out.println("\n\n[*] END PROGRAM\n\n\n");
		}
		
	}

}
