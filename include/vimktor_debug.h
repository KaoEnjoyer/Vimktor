#pragma once
#include <fstream>
#include <ios>
#include <string>

static void VimktorDebugLog(const std::string &msg);

static const char *debufFile = "debug.txt";
class Debug {
public:
  inline Debug() { debugStream.open(debufFile, std::ios_base::out); }
  inline ~Debug() { debugStream.close(); }
  inline void Log(const std::string &msg) {
    debugStream << "ok" << msg << '\n';
    debugStream.flush();
  }

private:
  std::fstream debugStream;
};
