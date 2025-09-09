#include "vimktor.h"
#include <expected>
#include <iostream>

int main() {
  Vimktor app = Vimktor();
	//ok ej
  app.Init();
  app.Loop();
  app.End();
}
