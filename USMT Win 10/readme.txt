﻿Steps to Backup User Accounts:

1. Copy "BackupScan(win 7 and 10)" to machine you wish to backup
2. Right click file on local machine and "Run as Administrator"
3. Follow the prompts.
4. Script will notify when files have been uploaded to share or to local C: drive
5. You've done it.

Steps to Restore User Accounts on New Machine:

1. Copy "BackupLoad(win 7 and 10)" to machine you wish to send the backup to
2. Right click file on local machine and "Run as Administrator"
3. Enter the hostname when prompted, ie) "ovl066878"
4. Follow the prompts
5. Script will notify when complete.
6. Check that user folders migrated
7. Check description, power user settings and printer settings migrated.

Notes: 

- Both scripts must be run as administrator from the local machine NOT from the share (copy to desktop, right click script and run as admin)

- System Error 1378 is OKAY.  Just means power users have already been set

- Overwrite Print.INI if you want the old printers settings to transfer
	If printer setup script has run on newly imaged machine, the machine will have a print.ini file. They will NOT combine. It will be overwritten.
