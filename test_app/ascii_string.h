#pragma once

#include <stddef.h>

class CAsciiString
{
public:
	CAsciiString(const wchar_t* sourse);
	~CAsciiString();

public:
	bool empty() const;
	const char* c_str() const;
	operator const char* () const;

private:
	char *data_;
	size_t size_;
};

inline bool CAsciiString::empty() const
{
	return (NULL != data_) && (0 < size_);
}

inline const char* CAsciiString::c_str() const
{
	return data_;
}

inline CAsciiString::operator const char* () const
{
	return data_;
}
