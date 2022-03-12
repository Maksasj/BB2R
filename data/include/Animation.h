#ifndef ANIMATION_CLASS_H
#define ANIMATION_CLASS_H

#include <iostream>
#include <stdio.h>

#include "Texture.h"

struct Animation
{   
    std::string AnimationID;
    game::Texture* texture;

    int row, speed, frame, total_frame, frame_W, frame_H;

    Animation(game::Texture* _TEXTURE, std::string _AnimationID, int _row, int _speed, int _frame_per_row, int _frame_W, int _frame_H) {
        AnimationID = _AnimationID;
        texture = _TEXTURE;
        speed = _speed;
        row = _row;

        frame_W = _frame_W; frame_H = _frame_H;

        total_frame = _frame_per_row;
        frame = 0;
    }
};


#endif