
// singleton ?
#include "common.h"
#include <ncurses.h>
class InputManager {
public:
  InputManager &Get() {
    static InputManager _instance;
    return _instance;
  };
  void GetCmdBuffer() = delete;
  VimktorEvent_t GetEvent(WINDOW *win, VimktorMode_t mode);
  InputManager(const InputManager &) = delete;
  InputManager &operator=(const InputManager &) = delete;

private:
  uint32_t inputCh;

  VimktorEvent_t IsEscapePressed();
  VimktorEvent_t GetInputInsert();
  VimktorEvent_t GetInputNormal();
  InputManager();
};
