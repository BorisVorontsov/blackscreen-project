//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.IniFiles.hpp>
#pragma hdrstop

#include "ApplicationSettings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

const String TApplicationSettings::m_strSettingsFileName = L"Settings.ini";

TApplicationSettings::TApplicationSettings() : m_bDecreaseBrightness(false), m_intBrightnessThreshold(0),
	m_intRecentColorIndex(0)
{

	//

}
//---------------------------------------------------------------------------
TApplicationSettings::~TApplicationSettings()
{

	//

}
//---------------------------------------------------------------------------
void TApplicationSettings::ReadSettings()
{

	String strAppPath = ExtractFilePath(Application->ExeName);
	String strSettingsFile = strAppPath + m_strSettingsFileName;

	if (!FileExists(strSettingsFile))
		this->WriteSettings();

	TIniFile *pSettings = new TIniFile(strSettingsFile);

	m_bDecreaseBrightness = pSettings->ReadBool(L"General", L"DecreaseBrightness", false);
	m_intBrightnessThreshold = pSettings->ReadInteger(L"General", L"BrightnessThreshold", 0);
	m_intRecentColorIndex = pSettings->ReadInteger(L"General", L"RecentColorIndex", 0);

	delete pSettings;

}
//---------------------------------------------------------------------------
void TApplicationSettings::WriteSettings()
{

	String strAppPath = ExtractFilePath(Application->ExeName);
	String strSettingsFile = strAppPath + m_strSettingsFileName;

	TIniFile *pSettings = new TIniFile(strSettingsFile);

	pSettings->WriteBool(L"General", L"DecreaseBrightness", m_bDecreaseBrightness);
	pSettings->WriteInteger(L"General", L"BrightnessThreshold", m_intBrightnessThreshold);
	pSettings->WriteInteger(L"General", L"RecentColorIndex", m_intRecentColorIndex);

	delete pSettings;

}
//---------------------------------------------------------------------------
