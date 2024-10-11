#include "log_monitor.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(const char *program_name) {
  printf("Usage: %s [-r] [-f <level>] -i <file>\n", program_name);
  printf("  -r             Display all changes in real time\n");
  printf("  -f <level>     Level filtering (CRITICAL, WARNING, INFO, "
         "DEBUG)\n");
  printf("  -i <file>      Path to log file\n");
  printf("  -h, --help     Show this help\n");
}

int main(int argc, char *argv[]) {
  const char *file_name = NULL;
  const char *filter_level = NULL;
  int real_time = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
      file_name = argv[++i];
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      print_usage(argv[0]);
      return EXIT_SUCCESS;
    } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
      filter_level = argv[++i];
    } else if (strcmp(argv[i], "-r") == 0) {
      real_time = 1;
    }
  }

  if (!file_name) {
    fprintf(stderr, "Usage: %s -i <file> [-f <level>] [-r] [-h]\n", argv[0]);
    return EXIT_FAILURE;
  }

  start_log_monitor(file_name, filter_level, real_time);

  return EXIT_SUCCESS;
}
