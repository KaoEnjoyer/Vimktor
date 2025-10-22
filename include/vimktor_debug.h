#pragma once
#include <fstream>
#include <ios>
#include <string>

#define debugFile "debug.txt"

class Debug {
public:
  static void Log(const std::string &msg) {
    static Debug _instance;
    _instance.debugStream << msg << '\n';
    _instance.debugStream.flush();
  }

  std::fstream debugStream;

private:
  inline Debug() { debugStream.open(debugFile, std::ios_base::out); }
  inline ~Debug() { debugStream.close(); }
};
