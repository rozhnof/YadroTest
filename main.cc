#include <iostream>
#include <fstream>
#include <ComputerClub.h>

int main(int argc, char** argv) {
  std::ifstream file(argv[1]);
  if (!file) {
    return 1;
  }

  ComputerClubRun(file, std::cout);

  return 0;
}