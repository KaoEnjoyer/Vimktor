#include "include/vimktor.h"
#include <expected>
#include <iostream>

int main() {
  Vimktor app = Vimktor();

  app.Init();
  app.Loop();
  app.End();
  //
  // app.m_sequence.setLineTo(0, "okej okej nic nie wiem nic nie wiem");
  app.m_sequence.addLine("okej nie wime ");
  for (int i = 0; i < app.m_sequence.size(); i++) {
    std::cout << app.m_sequence.getStringAt(i) << std::endl;
  }
}
