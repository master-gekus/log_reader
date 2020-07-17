#include "search_stream_file_windowed.h"

CSearchStreamFileWindowed::CSearchStreamFileWindowed(const wchar_t* file_name, size_t window_size)
  : ISearchStreamGenericFile(file_name)
  , window_size_(window_size)
  , window_(NULL)
  , window_offset_(static_cast<uint64_t>(-1))
{
  if (16 > window_size_) {
    window_size_ = 16;
  }

  window_ = new char [window_size_];
  adjust_window(0);
}

CSearchStreamFileWindowed::~CSearchStreamFileWindowed()
{
  delete [] window_;
}

char CSearchStreamFileWindowed::at_(uint64_t offset)
{
  if ((!can_continue()) || (!adjust_window(offset))) {
    return '\0';
  }

  return window_[offset - window_offset_];
}

bool CSearchStreamFileWindowed::adjust_window(uint64_t offset)
{
  if (offset >= file_size_) {
    return false;
  }

  if ((static_cast<uint64_t>(-1) != window_offset_)
      && (offset >= window_offset_)
      && (offset < (window_offset_ + window_size_))) {
      return true;
  }

  // Вычислим новый отступ окна
  uint64_t half_size = window_size_ / 2;
  uint64_t new_offset = (offset < half_size) ? 0 : ((offset / half_size) * half_size);

  if (!seek(new_offset)) {
    return false;
  }

  read_window(((new_offset + window_size_) > file_size_) ? (file_size_ - new_offset) : window_size_);

  window_offset_ = new_offset;

  return true;
}

bool CSearchStreamFileWindowed::read_window(uint64_t to_read)
{
  size_t offset = 0;
  while (true) {
    DWORD read;
    if (!::ReadFile(file_, window_ + offset, static_cast<DWORD>(to_read), &read, NULL)) {
      error_ = true;
      return false;
    }
    if (to_read == static_cast<uint64_t>(read)) {
      break;
    }
    to_read -= read;
    offset += read;
  }
  return true;
}
