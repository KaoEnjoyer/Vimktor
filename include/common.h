#pragma once

#define DEBUG_MODE 1
#define COLOR 1

enum VimktorErr_t {
  VIMKTOR_OK,
  MEMORY_ERROR,
  INVALID_ARRGUMENT,
  NULLEXCEPT,
  FILE_ERROR,
};

enum VimktorMode_t { INSERT, VISUAL, NORMAL };
