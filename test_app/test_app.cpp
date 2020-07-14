#include <stdio.h>

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

  wprintf(L"Trying open file: %s\n", argv[1]);

  CLogReader lr;

  if (!lr.SetFilter(CAsciiString(argv[2]))) {
    wprintf(L"Invalid filter: %s\n", argv[2]);
    return 1;
  }
    return 0;
}
