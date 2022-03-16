#ifndef CONVEYORSYSTEM_CLASS_H
#define CONVEYORSYSTEM_CLASS_H

#include <iostream>
#include <deque>

#include "Timer.h"
#include "World.h"
#include "prototype/Conveyor_Belt.h"

struct ConveyorSystem
{   
      std::deque<ConveyorBelt*> Conveyor_Belts;
      World *world;

      ConveyorSystem() {
            world = _world;
      }

      void addConveyorBelt(ConveyorBelt* conv) {
            Conveyor_Belts.push_back(conv);
      }

      void Update() {
            if (timer.step % 120 == 0) {
                  for (int i = Conveyor_Belts.size() - 1; i >= 0; i--) {
                        if (Conveyor_Belts[i] != Conveyor_Belts.back()) {
                              if(Conveyor_Belts[i]->locked == true) {
                                    if(Conveyor_Belts[i + 1]->locked == false) {
                                          Conveyor_Belts[i]->locked = false;
                                          Conveyor_Belts[i + 1]->locked = true;
                                          Conveyor_Belts[i + 1]->item =  Conveyor_Belts[i]->item;
                                          Conveyor_Belts[i + 1]->item->x = Conveyor_Belts[i + 1]->x;
                                          Conveyor_Belts[i + 1]->item->y = Conveyor_Belts[i + 1]->y;
                                    }
                              }
                        } else {
                              // 1 UP // 2 DOWN // 3 LEFT // 4 RIGHT
                              if(Conveyor_Belts[i]->direction == 1) {
                                    
                              } else if(Conveyor_Belts[i]->direction == 2) {
                                    
                              } else if(Conveyor_Belts[i]->direction == 3) {
                                    
                              } else if(Conveyor_Belts[i]->direction == 4) {
                                    
                              }
                        }
                  }
            }
      }  
};

#endif