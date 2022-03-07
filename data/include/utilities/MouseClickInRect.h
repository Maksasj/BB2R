#ifndef MAUSECLICKINRECT_F
#define MAUSECLICKINRECT_F

#include <raylib.h>
#include "rect.h"
#include "vector.h"

bool MauseClickInRect(Rect rect, vec2 pos) {
      if(GetMousePosition().x > pos.x &&  GetMousePosition().x < pos.x + rect.w && GetMousePosition().y > pos.y && GetMousePosition().y < pos.y + rect.h) { return true; }
      return false;
}

#endif