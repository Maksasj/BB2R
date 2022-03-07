#ifndef FONT_CLASS_H
#define FONT_CLASS_H

#include <iostream>
#include <raylib.h>
#include <string>

namespace game {
      struct font
      {
            Font *Rfont;

            font(std::string _path) {
                  Rfont = new Font(LoadFontEx(_path.c_str(), 72, nullptr, 1000));
            } 
      };
}
#endif