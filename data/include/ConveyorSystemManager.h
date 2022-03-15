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

      void Update() {
            for (auto con_sys : ConveyorSystems) {
                  con_sys.Update();
            }
      }

      int CreateSystem() {
            ConveyorSystem conv_sys;
            ConveyorSystems.push_back(conv_sys);
            return ConveyorSystems.size() - 1;
      }
};

#endif