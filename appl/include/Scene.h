#pragma once
#include "SDL.h"
#include <vector>
#include "Sphere.h"

class Scene 
{
public:
    Scene(int w, int h, SDL_Renderer*);
    ~Scene();
    void Update(float delta_time);
    std::vector<Sphere> Spheres;

private:
    int Width;
    int Height;
    SDL_Renderer* Renderer;
    
};