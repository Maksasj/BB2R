#ifndef GUIELEMNT_CLASS_H
#define GUIELEMNT_CLASS_H

#include <iostream>
#include <string>

#include "../utilities/vector.h"

struct GuiElement
{
      vec2 pos; vec2 offset;

      GuiElement(vec2 _pos) {
            pos = _pos;
      } 

      virtual void Render() {};
      virtual void Update() {};
};

#endif