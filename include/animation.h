#pragma once

#include "raylib.h"

struct Animation {
    int first;
    int last;
    int cur;
    int type;

    float speed;
    float duration_left;
};

void UpdateAnimation(Animation *self);

Rectangle GetAnimationFrame(Animation *self);
