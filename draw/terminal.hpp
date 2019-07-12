#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

namespace Faceless {
class Terminal {
 public:
  Terminal() {
    winsize terminal_size;
    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &terminal_size) < 0) {
      width = 80;
      hight = 24;
    } else {
      width = terminal_size.ws_col;
      hight = terminal_size.ws_row;
    }
  }

 public:
  unsigned int width;
  unsigned int hight;
  unsigned int row_cursor;
};

};  // namespace Faceless