/*___________________________________  Config.h   ______________________________________*/

/*       1         2         3         4         5         6         7         8        */
/*34567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*******************************************|********************************************/
/*
*   Copyright (c) 2012  Avision Corporation All rights reserved.
*
*   Copyright protection claimed includes all forms and matters of
*   copyrightable material and information now allowed by statutory or judicial
*   law or hereinafter granted, including without limitation, material generated
*   from the software programs which are displayed on the screen such as icons,
*   screen display looks, etc.
*
*******************************************|********************************************/
#pragma once

#ifdef WIN32
#pragma warning(disable:4996) //for function itoa.
#endif //WIN32

#include "Sysinfo.h"
#include <string>
#include <time.h>
#include<map>
#include<fstream>
#include<iostream>
using namespace std; 

#ifdef UNICODE
#define INSTR LPCWSTR
#else
#define INSTR LPCSTR
#endif//UNICODE

namespace CONFIG{
/**
* @defgroup	Config_Module Config Module.
* @brief		Get(Set) Config data Module. 
* @namespace	CONFIG
* @brief		CONFIG.
*
* @details 
*
* Simple Example: This example is a template of how to using this class to get(set) data from config.\n
* @ref ConfigExample
*/

/**
@page pageConfig Config Examples 

<CENTER><b>Get(Set) Config data Example.</b></CENTER>

@section secConfigExample Get(Set) Config data Example.
For more info see page \ref ConfigExample.

@subsection ConfigExample Get(Set) Config data Example 1 (Ini File).
@code

Data in "config.ini"
[Sec]
InFile  = In.tif
Data = 100
@endcode 

@code
main(int argc, _TINSTR* argv[]))
{
	//Setting Config file.
	ConfigFile(argv[1]);//or ConfigFile("Config.ini");

	//Get Data , you will got 100
	int data = ConfigGetInt("Sec", "Data", 0);

	//Data in "config.ini" will change to 1
	ConfigSetInt("Sec", "Key", 1);

	//Get String
	INSTR lpStr[128];
	ConfigGetString("Sec", "InFile", "Default", lpStr);
	//lpStr --> "In.tif"

	//Set String
	ConfigSetString("Sec", "InFile", "Default");
	//InFile --> "Default".
}            
@endcode 
*/
	extern "C" int ConfigFile(INSTR FileName);
	extern "C" int ConfigGetInt(INSTR Section, INSTR Key, int Default);
	extern "C" int ConfigGetString(INSTR Section, INSTR Key, INSTR Default, INSTR lpBuf);
	extern "C" int ConfigSetInt(INSTR Section, INSTR Key, int Value);
	extern "C" int ConfigSetString(INSTR Section, INSTR Key, INSTR lpBuf);

	extern "C" int ConfigFile2(INSTR FileName);
	extern "C" int ConfigGetInt2(INSTR Section, INSTR Key, int Default);
	extern "C" int ConfigGetString2(INSTR Section, INSTR Key, INSTR Default, INSTR lpBuf);

#define ConfigGetStr ConfigGetString
#define ConGetInt(Key, Default) ConfigGetInt(Name(), Key, Default)
#define ConGetStr(Key, Default, lpBuf) ConfigGetString(Name(), Key, Default, lpBuf)
#define ConSetInt(Key, Default) ConfigSetInt(Name(), Key, Default)
#define ConSetStr(Key, lpBuf) ConfigSetString(Name(), Key, lpBuf)

#define ConGetIntEx(Option, Key, Default) ConfigGetInt(Option, Key, Default)
#define ConGetStrEx(Option, Key, Default, lpBuf) ConfigGetString(Option, Key, Default, lpBuf)
#define ConSetIntEx(Option, Key, Value) ConfigSetInt(Option, Key, Value)
#define ConSetStrEx(Option, Key, lpBuf) ConfigSetString(Option, Key, lpBuf)

#define ConGetInt2(Key, Default) ConfigGetInt2(Name(), Key, Default)
#define ConGetStr2(Key, Default, lpBuf) ConfigGetString2(Name(), Key, Default, lpBuf)
#define ConSetInt2(Key, Default) ConfigSetInt2(Name(), Key, Default)
#define ConSetStr2(Key, lpBuf) ConfigSetString2(Name(), Key, lpBuf)

#define ConGetIntEx2(Option, Key, Default) ConfigGetInt2(Option, Key, Default)
#define ConGetStrEx2(Option, Key, Default, lpBuf) ConfigGetString2(Option, Key, Default, lpBuf)
#define ConSetIntEx2(Option, Key, Value) ConfigSetInt2(Option, Key, Value)
#define ConSetStrEx2(Option, Key, lpBuf) ConfigSetString2(Option, Key, lpBuf)

	/*
	Main of Config
	*/
	template<class config>
	class Config
	{
	public:
		Config(){};
		~Config(){};
		int Initial(INSTR Path);
		int GetInt(INSTR Section, INSTR Key, int Default);		
		int GetString(INSTR Section, INSTR Key, INSTR Default, INSTR lpBuf);
		int SetInt(INSTR Section, INSTR Key, int Value);
		int SetString(INSTR Section, INSTR Key, INSTR lpBuf);

	private:
		config m_config;
	};        

	class ConfigINI
	{
	public:
		ConfigINI(){m_Path.clear();};
		~ConfigINI(){};
		int Initial(INSTR Path);
		int GetInt(INSTR Section, INSTR Key, int Default);		
		int GetString(INSTR Section, INSTR Key, INSTR Default, INSTR lpBuf);
		int SetInt(INSTR Section, INSTR Key, int Value);
		int SetString(INSTR Section, INSTR Key, INSTR lpBuf);

	private:
		string m_Path;
	};

	class ConfigReg
	{
	public:
		ConfigReg();
		~ConfigReg();
		int Initial(INSTR Path);
		int GetInt(INSTR Section, INSTR Key, int Default);		
		int GetString(INSTR Section, INSTR Key, INSTR Default, INSTR lpBuf);
		int SetInt(INSTR Section, INSTR Key, int Value);
		int SetString(INSTR Section, INSTR Key, INSTR lpBuf);

	private:
		string m_Path;
	};

	class ConfigTXT
	{
	public:
		ConfigTXT();
		~ConfigTXT();
		int Initial(INSTR Path);
		int GetInt(INSTR Section, INSTR Key, int Default);		
		int GetString(INSTR Section, INSTR Key, INSTR Default, INSTR lpBuf);
		int SetInt(INSTR Section, INSTR Key, int Value);
		int SetString(INSTR Section, INSTR Key, INSTR lpBuf);
		int ReadTxt();

	private:
		string m_Path;
		map<string, map<string, string> > txt_data; 
	};

	class CONFIG_NULL
	{
	public:
		CONFIG_NULL(){};
		~CONFIG_NULL(){};
		int Initial(INSTR Path){return 0;};
		int GetInt(INSTR Section, INSTR Key, int Default){return 0;};
		int GetString(INSTR Section, INSTR Key, INSTR Default, INSTR lpBuf){return 0;};
		int SetInt(INSTR Section, INSTR Key, int Value){return 0;};
		int SetString(INSTR Section, INSTR Key, INSTR lpBuf){return 0;};;
	};
};//CONFIG

using namespace CONFIG;