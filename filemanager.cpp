#include "filemanager.h"
#include <filesystem>

FileManager::FileManager() {
  m_path = fs::current_path();
  loadCurrentDir();
}

void FileManager::handleInput(char ch) { basicInput(ch); }

void FileManager::loadCurrentDir() {
  m_textbox->data.clear();
  for (auto el : fs::directory_iterator(m_path)) {
    m_textbox->data.push_back(el.path().filename().string());
  }
}
