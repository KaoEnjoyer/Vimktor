#include "include/vimktor_debug.h"

#include <fstream>
#include <ios>

static Debug debug;
static void VimktorDebugLog(const std::string &msg) { debug.Log(msg); }
