#include "include/vimktor.h"
#include "include/vimktor_debug.h"
#include <expected>
#include <iostream>

int main(int argc, char **argv) {
  // std::cout << argc << " " << argv[0] << " " << argv[1];
  Vimktor app = Vimktor();
  if (argc > 1) {
    std::string fileName;
    strcpy(fileName.data(), argv[1]);
    app.LoadFile(fileName);
  }
  app.Init();
  app.Loop();
  app.End();
  // app.m_sequence.setLineTo(0, "okej okej nic nie wiem nic nie wiem");
}
