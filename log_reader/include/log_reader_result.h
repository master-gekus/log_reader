/**
* \file log_reader_result.h
*/

#pragma once
#ifndef LOG_READER_RESULT_H_INCLUDED
#define LOG_READER_RESULT_H_INCLUDED

#include <stdint.h>

/**
 * @brief ILogReaderResult интерфейс для получения результата произвольной длины.
 */
class ILogReaderResult
{
public:
  ILogReaderResult();
  virtual ~ILogReaderResult();

public:
  /**
   * @brief write - запись части результата
   * @param data Данные для записи. Никогда не может быть NULL
   * @param size Размер записываемых данных. Никодна не может быть 0.
   * @return Количество реально записанных байт. 0, если дальнейшая запись результата невозможна.
   *
   * Обязательный для перекрытия метов, в который передаются данные для записи результата.
   * По возможности данные передаются единым блоком, однако в случае большого объёма возможно
   * несколько вызовов.
   */
  virtual uint64_t write(const void* data, size_t size) = 0;

  /**
   * @brief close - завершение передачи данных.
   *
   * Функция вызывается после завершения передачи всех данных и может быть использована для некоторых
   * завершающих действий - например, для добавления терминирующего нуля.
   *
   * Не обязательна для перекрытия. Реализация по умолчанию не делает ничего.
   */
  virtual void close();
};

#endif // !LOG_READER_RESULT_H_INCLUDED
