@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by PROTOCOL MANAGER.HPJ. >"hlp\Protocol Manager.hm"
echo. >>"hlp\Protocol Manager.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Protocol Manager.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Protocol Manager.hm"
echo. >>"hlp\Protocol Manager.hm"
echo // Prompts (IDP_*) >>"hlp\Protocol Manager.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Protocol Manager.hm"
echo. >>"hlp\Protocol Manager.hm"
echo // Resources (IDR_*) >>"hlp\Protocol Manager.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Protocol Manager.hm"
echo. >>"hlp\Protocol Manager.hm"
echo // Dialogs (IDD_*) >>"hlp\Protocol Manager.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Protocol Manager.hm"
echo. >>"hlp\Protocol Manager.hm"
echo // Frame Controls (IDW_*) >>"hlp\Protocol Manager.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Protocol Manager.hm"
REM -- Make help for Project PROTOCOL MANAGER


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\Protocol Manager.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\Protocol Manager.hlp" goto :Error
if not exist "hlp\Protocol Manager.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\Protocol Manager.hlp" Debug
if exist Debug\nul copy "hlp\Protocol Manager.cnt" Debug
if exist Release\nul copy "hlp\Protocol Manager.hlp" Release
if exist Release\nul copy "hlp\Protocol Manager.cnt" Release
echo.
goto :done

:Error
echo hlp\Protocol Manager.hpj(1) : error: Problem encountered creating help file

:done
echo.
