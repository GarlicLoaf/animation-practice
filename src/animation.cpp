#include "animation.h"

#include "globals.h"
#include "raylib.h"

void UpdateAnimation(Animation *self) {
    float dt = GetFrameTime();
    self->duration_left -= dt;

    if (self->duration_left <= 0.0) {
        self->duration_left = self->speed;
        self->cur = (self->cur + 1) % self->last;
    }
}

Rectangle GetAnimationFrame(Animation *self) {
    float x = (self->cur % self->last) * TILESET_SIZE;

    return Rectangle{x, self->type * 16.0f, TILESET_SIZE, TILESET_SIZE};
}
