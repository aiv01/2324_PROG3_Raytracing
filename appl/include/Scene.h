#pragma once
#include "SDL.h"

class Scene 
{
public:
    Scene(int w, int h, SDL_Renderer*);
    ~Scene();
    void Update(float delta_time);

private:
    int width;
    int height;
    SDL_Renderer* renderer;
};