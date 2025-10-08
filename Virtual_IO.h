#ifndef __IO_Interface_H__
#define __IO_Interface_H__

#if (_WINDOWS)
	#include <Windows.h>
#else
	#include "SysInfo.h"
#endif

#include <fstream>
#include <cstring>

using namespace std;

class IO_INTERFACE
{
public:
	IO_INTERFACE(){};
	virtual ~IO_INTERFACE(){};
	virtual size_t Read(LPBYTE buffer, size_t size, size_t count) = 0;
	virtual size_t Write(LPBYTE buffer, size_t size, size_t count) = 0;
	virtual int Seek(int offset, int origin) = 0;
	virtual size_t Tell() = 0;
	virtual void* GetHandle() = 0;
	virtual void Close() = 0; //Same as Reset
	virtual bool IsOpen() = 0; //Check if file is open
};

class IO_File: public IO_INTERFACE
{
public:
	IO_File(const char *FileName, const char *Option);
	~IO_File();
	size_t Read(LPBYTE buffer, size_t size, size_t count);;
	size_t Write(LPBYTE buffer, size_t size, size_t count);
	int Seek(int offset, int origin);
	size_t Tell();
	void* GetHandle();
	void Close();
	bool IsOpen() { return (m_File != nullptr); } //Check if file is open

private:
	IO_File();
	FILE *m_File;
};

class IO_fstream: public IO_INTERFACE
{
public:
	IO_fstream(const char *FileName, int option);
	~IO_fstream();
	size_t Read(LPBYTE buffer, size_t size, size_t count);
	size_t Write(LPBYTE buffer, size_t size, size_t count);
	int Seek(int offset, int origin);
	size_t Tell();
	void* GetHandle();
	void Close(); //Same as Reset
	bool IsOpen() { return (m_fstream != nullptr); } //Check if file is open

private:
	IO_fstream();
	fstream *m_fstream;
};

class IO_Buf: public IO_INTERFACE
{
public:
	IO_Buf(LPBYTE Buffer, size_t Size);
	size_t Read(LPBYTE buffer, size_t size, size_t count);
	size_t Write(LPBYTE buffer, size_t size, size_t count);
	size_t Tell();
	int Seek(int offset, int origin);
	void* GetHandle();
	void Close(); //Same as Reset
	bool IsOpen() { return (m_Start != nullptr && m_End != nullptr); } //Check if buffer is open

private:
	IO_Buf(){};//Force using IO_Buf(Buffer, size);
	LPBYTE m_Start = nullptr, m_End = nullptr, m_Current = nullptr;
};

#endif //__IO_Interface_H__