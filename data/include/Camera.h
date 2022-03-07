#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <iostream>


namespace game
{
      struct Camera
      {   
      float x, y;
      Camera() {
            x = 0;
            y = 0;
      }

      };
}
game::Camera camera;

#endif