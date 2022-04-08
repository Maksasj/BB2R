#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <iostream>
#include <string>
#include <map>
#include <raylib.h>

#include "../Defines.h"
#include "../Utilities/key_exist.h"
#include "../Utilities/vector.h"

namespace game
{
    struct Texture
    {   
        Image img;
        Texture2D texture;
        std::map<std::string, Rectangle> texRect;
        Rectangle static_rect;

        vec2 offset;

        int size_w, size_h; int image_w, image_h;

        Texture(std::string img_path, ivec2 _size, vec2 frame_size, vec2 _offset) {
            img = LoadImage(img_path.c_str());
            ImageResizeNN(&img, _size.x*4, _size.y*4);
            image_w = img.width; image_h = img.height;
            
            static_rect = {0, 0, frame_size.x*4, frame_size.y*4};
            offset = {_offset.x*4, _offset.y*4};

            texture = LoadTextureFromImage(img);  

            UnloadImage(img);
        }
        
        void Render(std::string _state, float x, float y) {
            if (key_exists(texRect, _state)) {
                DrawTextureRec(texture, texRect[_state], Vector2{x + offset.x, y + offset.y}, RAYWHITE);
            } else {
                DrawTextureRec(texture, static_rect, Vector2{x + offset.x, y + offset.y}, RAYWHITE);
            }
        }
    };
}
#endif