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

// Базовый функционал
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
   * - больше нет подходящих строк
   * - буфер недостаточно большой, чтобы разместить в нём всю строку
   *
   * Буфер должен быть достаточно большим, чтобы вместить всю строку целиком, включая терминирующий нулевой символ.
   * В случае, если функция вернула false из-за недостаточного размера буфера, функция запишет в буфер максимально
   * возможное число символов, включая терминирующий нулевой символ.
   */
  bool GetNextLine(char *buf, const size_t bufsize);

// Расширенный функционал
public:
  /**
   * @brief Выдать следующую строку
   * @param buf Буфер для помещения данных строки
   * @param bufsize Размер буфера
   * @param line_number Указатель на переменную для получения номера строки (может быть NULL, если номер
   *                    строки не нужен. Строки нумеруются с 1.
   * @return true, если строка, включая терминирующий нулевой символ, помещена в буфер.
   *
   * \overload
   */
  bool GetNextLine(char *buf, const size_t bufsize, unsigned *line_number);

  /**
   * @brief Выдать следующую строку через интерфейс
   * @param pResult Ссылка на интерфейс
   * @return
   * @return true, если строка, включая терминирующий нулевой символ, помещена в буфер.
   *
   * \overload
   */
  bool GetNextLine(ILogReaderResult& pResult);

private:
  bool _GetNextLine(ILogReaderResult *pResult);

private:
  CPattern* m_pPattern;
  CSearchEngine* m_pEngine;
};

inline bool CLogReader::GetNextLine(ILogReaderResult& pResult)
{
  return _GetNextLine(&pResult);
}

#endif // !LOG_READER_INCLUDED
