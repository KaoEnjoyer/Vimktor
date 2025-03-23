#include "window.h"
#include <filesystem>

namespace fs = std::filesystem;


class FileManager : private Window {
public: 
  FileManager();
  FileManager(std::string path); 
  void handleInput(char ch) override;

inline  fs::path GetPath() {return m_path;};
private:
  fs::path m_path;

};
