#include <iostream>
#include <SDL2/SDL.h>
#include "transform.h"
#include "polygon.h"

using namespace egc;

//define window dimensions
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;

SDL_Window* window = NULL;
SDL_Renderer* windowRenderer = NULL;
SDL_Event currentEvent;

bool quit = false;

int mouseX, mouseY;

polygon p;

bool initWindow() {

    bool success = true;

    //Try to initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {

        std::cout << "SDL initialization failed" << std::endl;
        success = false;

    }
    else {

        //Try to create the window
        window = SDL_CreateWindow(
            "SDL Hello World Example",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

        if (window == NULL) {

            std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
            success = false;

        }
        else {

            // Create a renderer for the current window
            windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (windowRenderer == NULL) {

                std::cout << "Failed to create the renderer: " << SDL_GetError() << std::endl;
                success = false;

            }
            else {

                //Set background color
                SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);

                //Apply background color
                SDL_RenderClear(windowRenderer);
            }
        }
    }

    return success;
}

void initPolygon() {

    vec3 p1 = vec3(100.0f, 100.0f, 1.0f);
    vec3 p2 = vec3(400.0f, 100.0f, 1.0f);
    vec3 p3 = vec3(400.0f, 200.0f, 1.0f);
    vec3 p4 = vec3(100.0f, 200.0f, 1.0f);

    p.addLine(p1, p2);
    p.addLine(p2, p3);
    p.addLine(p3, p4);
    p.addLine(p4, p1);

    p.displayVertices();
}

void rotateLeft(egc::polygon* p)
{
    //calculate the center of the polygon
    vec3 center = vec3(0.0f, 0.0f, 0.0f);
    for (auto& vertex : p->vertices)
    {
        center += vertex;
    }
    center = center * (1.0f / p->vertices.size());

    //translate the center of the polygon to the origin
    for (auto& vertex : p->vertices)
    {
        vertex -= center;
    }

    //rotate the centered polygon
    mat3 rotationMat = rotate(-10);
    for (auto& vertex : p->vertices)
    {
        vertex = rotationMat * vertex;
    }

    //return the polygon to its updated positioin
    for (auto& vertex : p->vertices)
    {
        vertex += center;
    }
}

void rotateRight(egc::polygon* p)
{
    vec3 center(0.0f, 0.0f, 0.0f);
    for (const auto& vertex : p->vertices)
    {
        center += vertex;
    }
    center = center.operator*(1.0f / p->vertices.size());

    for (auto& vertex : p->vertices)
    {
        vertex -= center;
    }

    mat3 rotationMat = rotate(10);
    for (auto& vertex : p->vertices)
    {
        vertex = rotationMat * vertex;
    }

    for (auto& vertex : p->vertices)
    {
        vertex += center;
    }
}

void scaleUp(egc::polygon* p)
{
    //translate to the scaling center which is the vertex 0 of the polygon
    vec3 center = p->vertices.at(0);
    for (auto& vertex : p->vertices)
    {
        vertex -= center;
    }

    mat3 scalingMat = egc::scale(2.0f, 2.0f);
    for (auto& vertex : p->vertices)
    {
        vertex = scalingMat * vertex;
    }

    //translate the polygon to its updated position
    for (auto& vertex : p->vertices)
    {
        vertex += center;
    }
}

void scaleDown(egc::polygon* p)
{
    //translate to the scaling center which is the vertex 0 of the polygon
    vec3 center = p->vertices.at(0);
    for (auto& vertex : p->vertices)
    {
        vertex -= center;
    }

    mat3 scalingMat = egc::scale(1.0f / 2.0f, 1.0f / 2.0f);
    for (auto& vertex : p->vertices)
    {
        vertex = scalingMat * vertex;
    }

    //translate the polygon to its updated position
    for (auto& vertex : p->vertices)
    {
        vertex += center;
    }
}

void processEvents() {

    //Check for events in queue
    if (SDL_PollEvent(&currentEvent) != 0) {

        //User requests quit
        if (currentEvent.type == SDL_QUIT) {

            quit = true;
        }

        //Mouse event -> pressed button
        if (currentEvent.type == SDL_MOUSEBUTTONDOWN) {

            if (currentEvent.button.button == SDL_BUTTON_LEFT) {

                SDL_GetMouseState(&mouseX, &mouseY);
                std::cout << "Mouse click => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
            }
        }

        //Mouse event -> mouse movement
        if (currentEvent.type == SDL_MOUSEMOTION) {

            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LMASK) {

                SDL_GetMouseState(&mouseX, &mouseY);
                std::cout << "Mouse move => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
            }
        }

        //Keyboard event
        if (currentEvent.type == SDL_KEYDOWN) {

            switch (currentEvent.key.keysym.sym) {

            case SDLK_UP:
                scaleUp(&p);
                break;

            case SDLK_DOWN:
                scaleDown(&p);
                break;

            case SDLK_LEFT:
                rotateLeft(&p);
                break;

            case SDLK_RIGHT:
                rotateRight(&p);
                break;

            case SDLK_ESCAPE:
                quit = true;
                break;

            default:
                break;
            }
        }
    }
}

void drawFrame() {

    //Clear the background
    SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);
    SDL_RenderClear(windowRenderer);

    p.draw(windowRenderer);

    //Update window
    SDL_RenderPresent(windowRenderer);
}

void cleanup() {

    //Clear polygon
    p.clearVertices();

    //Destroy renderer
    if (windowRenderer) {

        SDL_DestroyRenderer(windowRenderer);
        windowRenderer = NULL;
    }

    //Destroy window
    if (window) {

        SDL_DestroyWindow(window);
        window = NULL;
    }

    //Quit SDL
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    //Initialize window
    if (!initWindow()) {

        std::cout << "Failed to initialize" << std::endl;
        return -1;
    }

    //Initialize polygon
    initPolygon();

    //Game loop
    while (!quit) {

        processEvents();
        drawFrame();
    }

    cleanup();
    return 0;
}
