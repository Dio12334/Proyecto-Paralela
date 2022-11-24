#include "Display.h"
#include <iostream>

Display::Display(std::vector <Point> points): m_Points(points){
    std::cout << "number of points: " << m_Points.size() << std::endl;
}

bool Display::Init(){
 
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if(sdlResult != 0){
        SDL_Log("No se pudo inicializar SDL: %s", SDL_GetError());
        return false;
    }
    m_Window = SDL_CreateWindow("TSP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 300,0);
    if(!m_Window){
        SDL_Log("Falla en la creación de la ventana: %s", SDL_GetError());
        return false;
    }
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    m_IsRunning = true;

    return true;
}

void Display::Runloop(){

    while(m_IsRunning){
        ProcessInput();
        GenerateOutput();
    }
}

void Display::Shutdown(){
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Renderer);
    SDL_Quit();
}
void Display::run(){
    if(Init())
        Runloop();

    Shutdown();
}
        
void Display::ProcessInput(){

    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                m_IsRunning = false;
                break;
        }
    }
}

void Display::GenerateOutput(){

    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_Renderer);

    int offset = 4;
    int scale = 5;
    SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
    for(auto point: m_Points)
        SDL_RenderDrawPoint(m_Renderer, scale*point.x + offset, scale*point.y + offset);
    
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    for(int i = 0; i < m_Points.size() - 1; ++i){
        SDL_RenderDrawLine(m_Renderer, scale*m_Points[i].x + offset, scale*m_Points[i].y + offset, scale*m_Points[i + 1].x + offset, scale*m_Points[i + 1].y + offset);
    }

    SDL_RenderPresent(m_Renderer);
}