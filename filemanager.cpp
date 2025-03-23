#include "filemanager.h"
#include <filesystem>

FileManager::FileManager (){
  m_path = fs::current_path();
}

void FileManager::handleInput(char ch) {
  basicInput(ch);
}

