#ifndef CONVEYORSYSTEMMANAGER_CLASS_H
#define CONVEYORSYSTEMMANAGER_CLASS_H

#include <iostream>
#include <deque>

#include "Timer.h"
#include "ConveyorSystem.h"

struct ConveyorSystemManager
{   
      std::vector<ConveyorSystem> ConveyorSystems;

      ConveyorSystemManager() {

      }
};

#endif