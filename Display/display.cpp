#include "display.h"
#include <SDL2/SDL_render.h>
#include <iostream>

#define WINDOWSIZE 600

Display::Display(std::vector <Point> points): m_Points(points){}

bool Display::Init(){
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if(sdlResult != 0){
        SDL_Log("\n[ERR] No se pudo inicializar SDL: %s", SDL_GetError());
        return false;
    }
    m_Window = SDL_CreateWindow("TSP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOWSIZE, WINDOWSIZE,0);
    if(!m_Window){
        SDL_Log("\n[ERR] Falla en la creación de la ventana: %s", SDL_GetError());
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

	auto puntos = m_Points;

	unsigned int minX, maxX, minY, maxY;
	for(size_t i = 0; i < puntos.size(); ++i){
		if(i == 0){
			minX = maxX = puntos[i].x;
			minY = maxY = puntos[i].y;
		}
		if(puntos[i].x < minX) minX = puntos[i].x; 
		if(puntos[i].y < minY) minY = puntos[i].y; 
		if(puntos[i].x > maxX) maxX = puntos[i].x; 
		if(puntos[i].y > maxY) maxY = puntos[i].y; 
	}
	
	int sizeX = maxX - minX, sizeY = maxY - minY;

	for(size_t i = 0; i < puntos.size(); ++i){
		puntos[i].x *= WINDOWSIZE/sizeX - 10;
		puntos[i].y *= WINDOWSIZE/sizeY - 10;
	}


	for(size_t i = 0; i < puntos.size(); ++i){
		if(i == 0){
			minX = maxX = puntos[i].x;
			minY = maxY = puntos[i].y;
		}
		if(puntos[i].x < minX) minX = puntos[i].x; 
		if(puntos[i].y < minY) minY = puntos[i].y; 
		if(puntos[i].x > maxX) maxX = puntos[i].x; 
		if(puntos[i].y > maxY) maxY = puntos[i].y; 
	}
	
	sizeX = maxX - minX; sizeY = maxY - minY;

    int offsetX = (WINDOWSIZE - sizeX)/2, offsetY = (WINDOWSIZE - sizeY)/2;
    int scale = 1;
    SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
    for(auto point: puntos){
		SDL_Rect rec{
			point.x + offsetX - 3,
			point.y + offsetY - 3,
			6,
			6
		};
		SDL_RenderFillRect(m_Renderer, &rec);
	}
	
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    for(int i = 0; i < puntos.size() - 1; ++i){
        SDL_RenderDrawLine(m_Renderer, scale*puntos[i].x + offsetX, scale*puntos[i].y + offsetY, scale*puntos[i + 1].x + offsetX, scale*puntos[i + 1].y + offsetY);
    }

    SDL_RenderPresent(m_Renderer);
}
