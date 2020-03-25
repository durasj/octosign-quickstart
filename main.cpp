#include <iostream>
#include <cstring>
#include <regex>
#include <errno.h>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "One of the operations required as first argument: meta, sign, verify";
    return 1;
  }

  if (strcmp(argv[1], "meta") == 0) {
    std::cout << "OK";
  } else if (strcmp(argv[1], "sign") == 0) {
    std::string new_name = std::regex_replace(argv[2], std::regex("\\..*$"), ".signed$0");
    if (rename(argv[2], new_name.c_str()) == -1) {
      std::cerr << "Error: " << strerror(errno) << std::endl;
      return 1;
    }
  } else if (strcmp(argv[1], "verify") == 0) {
    bool contains = std::regex_match(argv[2], std::regex(".*\\.signed(\\..*)?"));
    printf(contains ? "SIGNED" : "UNSIGNED");
  }
  return 0;
}

