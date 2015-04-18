;Setup Program for PixShot

[Setup]
AppName=PixShot 0.9
AppVersion=0.9
AppVerName=PixShot 0.9
AppCopyright=Copyright (C) 2014, PixShot.org
AppContact=support@pixshot.org
AppPublisher=pixshot.org
AppPublisherURL=http://www.pixshot.org
AppSupportURL=http://www.pixshot.org
AllowRootDirectory=no
Compression=lzma2
CloseApplications=yes
DefaultDirName={pf}\PixShot
DefaultGroupName=Pixshot
InfoAfterFile=README.txt
LicenseFile=LICENSE.txt
PrivilegesRequired=lowest
OutputBaseFilename=Setup
;SetupIconFile=pixshot.ico
SetupLogging=Yes
ShowTasksTreeLines=yes
ShowLanguageDialog=no
TimeStampsInUTC=yes
UninstallDisplayIcon={app}\PixShot.exe
UninstallDisplayName=PixShot
UsePreviousAppDir=yes
;WizardImageFile=pixshot.bmp
 
[Files]
Source: "../src/release/PixShot.exe"; DestDir: "{app}"
Source: "QtCore4.dll"; DestDir: "{app}"
Source: "QtGui4.dll"; DestDir: "{app}"
Source: "QtNetwork4.dll"; DestDir: "{app}"
Source: "QtXml4.dll"; DestDir: "{app}"
Source: "mingwm10.dll"; DestDir: "{app}"
Source: "libgcc_s_dw2-1.dll"; DestDir: "{app}"
Source: "GPL.html"; DestDir: "{app}"
Source: "COPYING.txt"; DestDir: "{app}"
Source: "LICENSE.txt"; DestDir: "{app}"
Source: "README.txt"; DestDir: "{app}"

[Icons]
Name: "{group}\PixShot"; Filename: "{app}\PixShot.exe"; WorkingDir: "{app}"
Name: "{group}\ReadMe"; Filename: "{app}\README.txt"
Name: "{group}\Website"; Filename: "http://www.pixshot.org"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"

[UninstallDelete]
Type: files; Name: "{app}\preferences.ini"
