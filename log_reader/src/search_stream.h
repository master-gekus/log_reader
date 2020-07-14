/**
* \file search_stream.h
*/

#pragma once
#ifndef ISEARCHSTREAM_H_INCLUDED
#define ISEARCHSTREAM_H_INCLUDED

#include <stdint.h>

/**
 * @brief ISearchStream - интерфейс для источника поиска
 */
class ISearchStream
{
protected:
  ISearchStream();
public:
  virtual ~ISearchStream();
};

#endif // !ISEARCHSTREAM_H_INCLUDED
