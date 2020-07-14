/**
* \file LogReader.h
*/

#pragma once
#ifndef LOG_READER_INCLUDED
#define LOG_READER_INCLUDED

#include <Windows.h>

class CLogReader
{
public:
	CLogReader();
	~CLogReader();

public:
	bool Open(const wchar_t* buffer);					// открытие файла, false - ошибка
	void Close();										// закрытие файла

	bool SetFilter(const char *filter);					// установка фильтра строк, false - ошибка
	bool GetNextLine(char *buf, const size_t bufsize);	// buf - буфер, bufsize - максимальная длина
														// запрос очередной найденной строки,
														// false - конец файла или ошибка
private:
	HANDLE m_hFile;
	HANDLE m_hMap;
};

#endif // !LOG_READER_INCLUDED
