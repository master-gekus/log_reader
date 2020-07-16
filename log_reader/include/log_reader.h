/**
* \file log_reader.h
*/

#pragma once
#ifndef LOG_READER_INCLUDED
#define LOG_READER_INCLUDED

class CPattern;
class CSearchEngine;
class ILogReaderResult;

/**
 * @brief The CLogReader class
 */
class CLogReader
{
public:
  CLogReader();
  ~CLogReader();

public:
  /**
   * @brief Открыть файл для обработки
   * @param name Имя файла
   * @return true, если файл успешно открыть и готов к обработке
   */
  bool Open(const wchar_t* name);

  /**
   * @brief Закрыть текущий открытый файл
   */
  void Close();

  /**
   * @brief Установить фильтр
   * @param filter строка фильтра
   * @return true, если строка фильтра корректна и фильтр установлен
   *
   * \note
   * Если при установке фильра файл уже открыт, то не происходит "перемотки" файла на начало, а дальнейшая
   * работа ведётся с той строки, на которой остановился предыдущий вызов \ref GetNextLine
   */
  bool SetFilter(const char *filter);

  /**
   * @brief Выдать следующую строку
   * @param buf буфер для помещения данных строки
   * @param bufsize размер буфера
   * @return true, если строка, включая терминирующий нулевой символ, помещена в буфер.
   *
   * Функция возвращает false в случае:
   * - файл не открыт
   * - больше нет подходящих строк (\sa IsEof).
   * - буфер недостаточно большой, чтобы разместить в нём всю строку.
   *
   * Буфер должен быть достаточно большим, чтобы вместить всю строку целиком, включая терминирующий нулевой символ.
   * В случае, если функция вернула false из-за недостаточного размера буфера, функция запишет в буфер максимально
   * возможное число символов, включая терминирующий нулевой символ.
   */
  bool GetNextLine(char *buf, const size_t bufsize);

  /**
   * @brief Проверка, достигнут ли конец файла
   * @return true, если достигнут конце файла или файл не открыт (\sa IsOpen)
   */
  bool IsEof() const;

private:
  bool _GetNextLine(ILogReaderResult *pResult, unsigned* pLine);

private:
  CPattern* m_pPattern;
  CSearchEngine* m_pEngine;
};

#endif // !LOG_READER_INCLUDED
