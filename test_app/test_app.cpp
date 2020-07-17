#include <stdio.h>
#include <Windows.h>

#include <log_reader.h>

#include "ascii_string.h"

// Используем wmain вместо main на случай, если будет
// передаваться имя файла, содержащее не-ASCII символы.
int wmain(int argc, wchar_t** argv)
{
  if (argc != 3) {
    wprintf(L"Invalid usage.\n");
    return 1;
  }

  wprintf(L"Input file     : %s\n", argv[1]);
  wprintf(L"Search pattern : %s\n", argv[2]);

  CLogReader lr;

  if (!lr.SetFilter(CAsciiString(argv[2]))) {
    wprintf(L"Error set up filter. Possible invalid expression?\n");
    return 1;
  }

  if (!lr.Open(argv[1])) {
    wprintf(L"Error open input file. Possible file does not exists?\n");
    return 1;
  }

  unsigned long long count = 0;
  unsigned long long elapsed_time = ::GetTickCount64();

  // Базовая реализация
  /*
  char buffer[4096];
  while (lr.GetNextLine(buffer, sizeof (buffer))) {
    printf("%s\n", buffer);
    ++count;
  }
  */

  // Реализация с номерами строк
  char buffer[4096];
  unsigned line_number;
  while (lr.GetNextLine(buffer, sizeof (buffer), &line_number)) {
    printf("%7u: %s\n", line_number, buffer);
    ++count;
  }

  elapsed_time = ::GetTickCount64() - elapsed_time;

  wprintf(L"Searching finished, found %llu line(s) in %llu.%03u seconds.\n", count, elapsed_time / 1000ULL,
          static_cast<unsigned>(elapsed_time % 1000ULL));

  return 0;
}
