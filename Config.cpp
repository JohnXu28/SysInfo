#include <stdafx.h>
#include <SysInfo\config.h>
#include <windows.h>

using namespace CONFIG;
#if Config_NULL
Config<CONFIG_NULL> con;
#elif Config_Reg
Config<ConfigReg> con;
#elif Config_TXT
Config<ConfigTXT>
#else //default
Config<ConfigINI> con;
#endif //Config

namespace CONFIG {
	const int MaxStrLength = 128;
};
/********************************************************************
Config   Export Funstion
********************************************************************/
extern "C" int ConfigFile(INSTR FileName)
{
	return con.Initial(FileName);
}

extern "C" int ConfigGetInt(INSTR Section, INSTR Key, int Default)
{
	return con.GetInt(Section, Key, Default);
}

extern "C" int ConfigGetString(INSTR Section, INSTR Key, INSTR Default, INSTR lpBuf)
{
	return con.GetString(Section, Key, Default, lpBuf);
}

extern "C" int ConfigSetInt(INSTR Section, INSTR Key, int Value)
{
	return con.GetInt(Section, Key, Value);
}

extern "C" int ConfigSetString(INSTR Section, INSTR Key, INSTR lpBuf)
{
	return con.SetString(Section, Key, lpBuf);
}

/********************************************************************
Config   Export Funstion Show Message
********************************************************************/
extern "C" int ConfigFile2(INSTR FileName)
{
	cout << "ConfigFile : " << FileName << endl;
	return con.Initial(FileName);
}

extern "C" int ConfigGetInt2(INSTR Section, INSTR Key, int Default)
{
	int ret = con.GetInt(Section, Key, Default);
	cout << "Get " << "[ " << Section << " : " << Key << " ] = " << ret << endl;
	return ret;
}

extern "C" int ConfigGetString2(INSTR Section, INSTR Key, INSTR Default, INSTR lpBuf)
{
	int ret = con.GetString(Section, Key, Default, lpBuf);
	cout << "Get " << "[ " << Section << " : " << Key << " ] = " << lpBuf << endl;
	return ret;
}

extern "C" int ConfigSetInt2(INSTR Section, INSTR Key, int Default)
{
	int ret = con.SetInt(Section, Key, Default);
	cout << "Set " << "[ " << Section << " : " << Key << " ] = " << ret << endl;
	return ret;
}

extern "C" int ConfigSetString2(INSTR Section, INSTR Key, INSTR lpBuf)
{
	int ret = con.SetString(Section, Key, lpBuf);
	cout << "Set " << "[ " << Section << " : " << Key << " ] = " << lpBuf << endl;
	return ret;
}

/********************************************************************
Config config
********************************************************************/
template<class config>
int Config<config>::Initial(INSTR Path)//Does't check anything in this version.
{
	return m_config.Initial(Path);
}

template<class config>
int Config<config>::GetInt(INSTR Section, INSTR Key, int Default)
{
	return m_config.GetInt(Section, Key, Default);
}

template<class config>
int Config<config>::GetString(INSTR Section, INSTR Key, INSTR Default, INSTR lpBuf)
{
	return m_config.GetString(Section, Key, Default, lpBuf);
}


template<class config>
int Config<config>::SetInt(INSTR Section, INSTR Key, int Value)
{
	return m_config.SetInt(Section, Key, Value);
}

template<class config>
int Config<config>::SetString(INSTR Section, INSTR Key, INSTR lpBuf)
{
	return m_config.SetString(Section, Key, lpBuf);
}

/********************************************************************
INI Class (Ini File)
********************************************************************/
int ConfigINI::Initial(INSTR Path)//Does't check anything in this version.
{
	if (Path != nullptr)
		m_Path.assign(Path);
	return 0;
};

int ConfigINI::GetInt(INSTR Section, INSTR Key, int Default)
{
	if (m_Path.empty() != true)
		return GetPrivateProfileInt(Section, Key, Default, (INSTR)m_Path.c_str());
	else
		return Default;
}


int ConfigINI::GetString(INSTR Section, INSTR Key, INSTR Default, INSTR lpBuf)
{
	if (m_Path.empty() != true)
		return GetPrivateProfileString(Section, Key, Default, (LPSTR)lpBuf, 128, m_Path.c_str());
	else
		return 0;
}


int ConfigINI::SetInt(INSTR Section, INSTR Key, int Value)
{
	if (m_Path.empty() != true)
	{
		INSTR TempCh[16];
		string tempstr = string(itoa(Value, (char*)TempCh, 10));
		return WritePrivateProfileString(Section, Key, m_Path.c_str(), m_Path.c_str());
	}
	else
		return -1;
}

int ConfigINI::SetString(INSTR Section, INSTR Key, INSTR lpBuf)
{
	if (m_Path.empty() != true)
		return WritePrivateProfileString(Section, Key, lpBuf, m_Path.c_str());
	else
		return -1;
}

/********************************************************************
Config Reg
********************************************************************/
ConfigReg::ConfigReg()
{
	m_Path = "Software\\Avision\\R025_AV\\";
}

ConfigReg::~ConfigReg()
{}

int ConfigReg::Initial(INSTR Path)//Does't check anything in this version.
{
	if (Path != nullptr)
		m_Path = m_Path + string(Path);
	return 0;
}

int ConfigReg::GetInt(INSTR Section, INSTR Key, int Default)
{
	HKEY hkey;
	if (Section == nullptr)
		return -1;
	string path = m_Path + string(Section);
	int Data = -1;	int strlength = 4;   int DataType = REG_DWORD;
	if (RegCreateKey(HKEY_LOCAL_MACHINE, path.c_str(), &hkey) == ERROR_SUCCESS)
	{
		if (RegQueryValueEx(hkey, Key, nullptr, (LPDWORD)&DataType, (LPBYTE)&Data, (LPDWORD)&strlength) != ERROR_SUCCESS)
			Data = Default;

		RegCloseKey(hkey);
	}

	if (Data == Default)
		SetInt(Section, Key, Default);
	return Data;
}

int ConfigReg::GetString(INSTR Section, INSTR Key, INSTR Default, INSTR lpBuf)
{//Max str length 128;
	HKEY hkey;
	if (Section == nullptr)
		return -1;

	int ret = -1; int strlength = 128; int DataType = REG_SZ;
	string path = m_Path + string(Section);
	if (RegCreateKey(HKEY_LOCAL_MACHINE, path.c_str(), &hkey) == ERROR_SUCCESS)
	{
		if (RegQueryValueEx(hkey, Key, nullptr, (LPDWORD)&DataType, (LPBYTE)lpBuf, (LPDWORD)&strlength) != ERROR_SUCCESS)
			memcpy((void*)lpBuf, (void*)Default, MaxStrLength);
		else
			ret = 1;
		RegCloseKey(hkey);
	}

	if (ret == -1)
		SetString(Section, Key, (INSTR)Default);
	return ret;
}

int ConfigReg::SetInt(INSTR Section, INSTR Key, int Value)
{
	if (Section == nullptr)
		return -1;

	HKEY hkey;
	string path = m_Path + string(Section);

	int ret = -1;

	if (RegCreateKey(HKEY_LOCAL_MACHINE, path.c_str(), &hkey) == ERROR_SUCCESS)
	{
		if (RegSetValueEx(hkey, Key, 0, (DWORD)REG_DWORD, (LPBYTE)&Value, 4) == ERROR_SUCCESS)
			ret = 1;
		RegCloseKey(hkey);
	}

	return ret;
}

int ConfigReg::SetString(INSTR Section, INSTR Key, INSTR lpBuf)
{//Max str length 128;	
	if (Section == nullptr)
		return -1;

	HKEY hkey;
	string path = m_Path + string(Section);
	int ret = -1;
	if (RegCreateKey(HKEY_LOCAL_MACHINE, path.c_str(), &hkey) == ERROR_SUCCESS)
	{
		if (RegSetValueEx(hkey, Key, 0, (DWORD)REG_SZ, (LPBYTE)lpBuf, MaxStrLength) == ERROR_SUCCESS)
			ret = 1;
		RegCloseKey(hkey);
	}

	return ret;
}

/********************************************************************
Config TXT
********************************************************************/
ConfigTXT::ConfigTXT()
{
}

ConfigTXT::~ConfigTXT()
{
}


int ConfigTXT::Initial(INSTR Path)
{
	m_Path.assign(Path);

	return ReadTxt();
}

int ConfigTXT::GetInt(INSTR Section, INSTR Key, int Default)
{
	string temp_section(Section), temp_key(Key);
	map<string, string> map_temp = txt_data[temp_section];
	if (map_temp.count(temp_key))
		return atoi(map_temp[temp_key].c_str());

	return Default;
}

int ConfigTXT::GetString(INSTR Section, INSTR Key, INSTR Default, INSTR lpBuf)
{
	string temp_section(Section), temp_key(Key);
	map<string, string> map_temp = txt_data[temp_section];
	if (map_temp.count(temp_key))
		memcpy((void*)lpBuf, (void*)map_temp[temp_key].c_str(), 128);
	else
		memcpy((void*)lpBuf, Default, 128);

	return 0;
}

int ConfigTXT::SetInt(INSTR Section, INSTR Key, int Value)
{
	return 0;
}

int ConfigTXT::SetString(INSTR Section, INSTR Key, INSTR lpBuf)
{
	return 0;
}

int ConfigTXT::ReadTxt()
{
	fstream file;
	file.open(m_Path.c_str(), ios::in);
	if (!file.is_open())
		return -1;

	string line, header, end("end"), last, key, value;
	while (file >> header)
	{
		int index_node = (int)header.find("//");
		if (index_node != -1)//If find out "//", skip the row! 
		{
			getline(file, line);
			continue;
		}
		last = header;
		last.append(end);

		map<string, string> map_ss;
		map_ss.clear();
		line.clear();
		getline(file, line);

		for (int index = 0; index < 1000; index++)//Max(the row of each option) < 1000  	  
		{
			line.clear();
			getline(file, line);
			if (line == last)
				break;   //when some row == header+end, break;

			index_node = (int)line.find("//");
			if (index_node != -1)
			{
				continue;
			}

			string c_temp;//use to store the no-space word

			for (int i = 0; i < (int)line.length(); i++)
			{
				if (line.at(i) != ' ')
					c_temp.push_back(line.at(i));
			}

			key.clear();
			value.clear();

			basic_string <INSTR>::size_type index_equal = c_temp.find("=");
			if (index_equal == -1)
			{
				cout << "txt error: The row" << c_temp << "  = is lost!" << endl;
				cout << "We can not process it !" << endl;
				continue;
			}

			int check = 0;//If the INSTR is after the "=", check =1; else check = 0;
			for (int index1 = 0; index1 < (int)c_temp.length(); index1++)
			{
				if (c_temp.at(index1) == ('='))
					check = 1;
				else
				{
					if (check == 0)
						key.push_back(c_temp.at(index1));
					else
						value.push_back(c_temp.at(index1));
				}
			}
			map_ss[key] = value;
		}

		txt_data[header] = map_ss;
	}

	return 0;
}
