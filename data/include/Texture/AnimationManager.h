#ifndef ANIMATIONMANAGER_CLASS_H
#define ANIMATIONMANAGER_CLASS_H

#include <map>
#include <string>

#include "Texture.h"
#include "Animation.h"
#include "../Timer.h"

struct AnimationManager
{   
      std::map<std::string, Animation*> Animations;

      AnimationManager() {

      }
                                    //KEY,                  TEXTURE ID,            FRAME_COUNT,   ROW,   COLLUM,    SPEED,      SIZE_W,           SIZE_H 
      void AddAnimation(std::string _animation_name, game::Texture* texture, int frame_per_row, int row, int line, int speed, float frame_W, float frame_H) {
            
            texture->texRect[_animation_name] = {(float)(row)*frame_W, (float)(line)*frame_H, frame_W, frame_H};
            
            
            Animations[_animation_name] = new Animation(texture, _animation_name, row, speed, frame_per_row, frame_W, frame_H);
      }

      
      void UpdateAnimation() {
            for(std::pair<std::string, Animation*> sheet : Animations) { 
                  if (sheet.second->frame < sheet.second->total_frame && timer.step % sheet.second->speed == 0) { 
                        sheet.second->texture->texRect[sheet.first].x = sheet.second->row*64 + sheet.second->frame*sheet.second->frame_W;
                        sheet.second->frame++;
                        if(sheet.second->frame >= sheet.second->total_frame) { sheet.second->frame = 0; }  
                  }
            }

            /*
            for(std::pair<std::string, Animation*> sheet : Animations) {   
                  if (sheet.second->frame < sheet.second->total_frame && timer.step % sheet.second->speed == 0) { 
                        sheet.second->texture->texRect[sheet.first].x = sheet.second->frame*sheet.second->frame_W;
                        sheet.second->frame++;
                        if(sheet.second->frame >= sheet.second->total_frame) { sheet.second->frame = 0; }  
                  }
            }

            */
      }
};

#endif