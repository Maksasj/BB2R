#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <iostream>
#include <string>
#include <map>
#include <raylib.h>

#include "Defines.h"

template <typename T, typename Key>
bool key_exists(const T& container, const Key& key)
{
    return (container.find(key) != std::end(container));
}

namespace game
{
    struct Texture
    {   
        Image img;
        Texture2D texture;
        std::map<std::string, Rectangle> texRect;
        Rectangle static_rect;
        int size_w, size_h; int image_w, image_h;

        Texture(std::string img_path, int _size_w, int _size_h) {
            img = LoadImage(img_path.c_str());
            ImageResizeNN(&img, _size_w*4, _size_h*4);
            image_w = img.width; image_h = img.height;
            
            static_rect = {0, 0, 64, 64};

            texture = LoadTextureFromImage(img);  

            UnloadImage(img);
        }
        
        void Render(std::string _state, float x, float y) {
            if (key_exists(texRect, _state)) {
                DrawTextureRec(texture, texRect[_state], Vector2{x, y}, RAYWHITE);
            } else {
                DrawTextureRec(texture, static_rect, Vector2{x, y}, RAYWHITE);
            }
        }
    };
}
#endif