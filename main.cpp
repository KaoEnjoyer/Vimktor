#include "include/vimktor.h"
#include "include/vimktor_debug.h"
#include <expected>
#include <iostream>

int main() {
  Vimktor app = Vimktor();
  app.Init();
  app.Loop();
  app.End();
  // app.m_sequence.setLineTo(0, "okej okej nic nie wiem nic nie wiem");
}
