#pragma once

#include "../Graph/point.h"
#include <../SDL2/SDL.h>
#include <vector>

class Display{
    public:
        Display(std::vector <struct Point> points);
        bool Init();
        void Runloop();
        void Shutdown();
        void run();
    private:
        void ProcessInput();
        void GenerateOutput();
        std::vector<struct Point> m_Points;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        bool m_IsRunning;
};