#ifndef TIMER_CLASS_H
#define TIMER_CLASS_H

#include <iostream>
#include <raylib.h>
#include <stdio.h>

struct Timer
{   
      int step;
      double deltaTime;

      Timer() {
            step = 0;
            deltaTime = GetFrameTime();  
      }
      void Update() {
            deltaTime = GetFrameTime();
            step++;
      }
};

Timer timer;

#endif