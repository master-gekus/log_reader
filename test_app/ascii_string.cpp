#include "ascii_string.h"

#include <Windows.h>

CAsciiString::CAsciiString(const wchar_t* sourse)
	: data_(NULL)
	, size_(0)
{
	int len = ::WideCharToMultiByte(CP_ACP, 0, sourse, -1, NULL, 0, NULL, NULL);
	if (0 >= len) {
		return;
	}

	size_ = static_cast<size_t>(len);
	data_ = static_cast<char*>(malloc(len));
	::WideCharToMultiByte(CP_ACP, 0, sourse, -1, data_, len, NULL, NULL);
}

CAsciiString::~CAsciiString()
{
	free(data_);
}
