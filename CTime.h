#ifndef __CTime__
#define __CTime__

#ifdef WIN32
#include <windows.h>
#define CurrentTime		GetTickCount64()
#else
#include "SysInfo.h"
#define CurrentTime		time(NULL)
#endif //WIN32

#include <time.h>
#include <fstream>
#include <iostream>
#include <string>
/**
@defgroup	Time_Module Time Module.

@detail Just for counting time easily.

Simple Example : You can using this module to estimate processing time. 
@ref TimeExample
@image html  ..\Tiff_STL\sheep2.jpg 
*/

/**
@page pageTime Time Examples

<CENTER><b>Time Example.</b></CENTER>

@section secTimeExample Time Example.
For more info see page \ref TimeExample.

@subsection TimeExample Processing Time Example.
@code
#inlcude <SysInfo/Time>

main(int argc, _TCHAR* argv[]))
{
	TimeCount time;
	time.Start("Processing 1");
	//....Processing 1.
	time.End();

	time.Start("Processing 2");
	//....Processing 2.
	time.End();
	
}     
@endcode 

@code
You will get this msg in dos mode.
Processing 1 : ....
Processing 2 : ....
@endcode 
*/

using namespace std; 
namespace CONFIG{
class TimeCount
	{
	public:
		TimeCount(const char *str)
		{
			m_ID = str;
			Start("New ID");
			m_Total = 0;
		}

		TimeCount(void)
		{Reset();};

		~TimeCount(void){};

		void Start(const char *str = nullptr)
		{
			m_Start = CurrentTime;
			if(str != nullptr)
				cout << m_ID << "(Start) : " << str << endl;
//			else
//				cout << m_ID << "(Start)." << endl;
		}

		void Stop(const char *str = nullptr)
		{
			Pause(str);

			cout << m_ID << "(";

			if(str != nullptr)
				cout << "Stop) :  " << str  << "(count : " << m_Total << ")"<< endl;
			else
				cout << "Stop) :  " << "(count : " << m_Total << ")"<< endl;

			Reset();//Reset Total time.

			//m_Start = GetTickCount();//ReStart.
		}

		ULONGLONG Pause(const char *str = nullptr)
		{
			m_Stop  = CurrentTime;
			ULONGLONG count = m_Stop - m_Start; 
			m_Total += count;		

			if(str != nullptr)
				cout << m_ID << "(Pause) : " << str  << "(count : " << count << ")"<< endl;

			return m_Total;

			//m_Start = GetTickCount();//ReStart.
		}

		void Reset()
		{m_Total = 0;}

		void DisPlay(const char *str = nullptr)
		{
			if(str != nullptr)
				cout << "Total : " << str << m_Total << endl;
			else
				cout << "Total : " << m_Total << endl;
		}

#ifdef WIN32
		void GetTime(int &Day, int &Month, int &Year, int &Hour, int &Minute, int &Sec)
		{
			SYSTEMTIME st;	
			GetSystemTime(&st);
			Day = st.wDay;
			Month = st.wMonth;
			Year = st.wYear;
			Hour = st.wHour + 8;
			if(Hour > 24)
				Hour -= 24;
			Minute = st.wMinute;
			Sec = st.wSecond;			
		}
#else
		void GetTime(int &Day, int &Month, int &Year, int &Hour, int &Minute, int &Sec)
		{}
#endif //WIN32
	private:
		ULONGLONG m_Start;
		ULONGLONG m_Stop;
		ULONGLONG m_Total;	
		string m_ID;
	};

//Macro
#define TIME_COUNT

#ifdef TIME_COUNT
#define TIME_ID(ID)			TimeCount timecount(ID); 
#define TIME_START(MSG)		timecount.Start(MSG);
#define TIME_STOP(MSG)		timecount.Stop(MSG);
#define TIME_PAUSE(MSG)		timecount.Pause(MSG);
#define TIME_MSG(MSG)		cout << MSG << endl;
#else
#define TIME_ID(ID)			
#define TIME_START(ID) 
#define TIME_STOP(MSG) 
#define TIME_PAUSE(MSG)
#define TIME_MSG(MSG)	
#endif//TIME_COUNT

};//CONFIG
using namespace CONFIG;

#endif //__CTime__