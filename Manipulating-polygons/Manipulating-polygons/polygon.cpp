//
// Created by adi on 09.03.2022.
//

#include "polygon.h"

namespace egc {


    polygon::polygon() {

    }

    void polygon::addVertex(vec3 vertex) {

        this->vertices.push_back(vertex);
    }

    void polygon::clearVertices() {

        this->vertices.clear();
    }

    void polygon::draw(SDL_Renderer *windowRenderer) {

        if (this->vertices.size() >= 2) {

            SDL_SetRenderDrawColor(windowRenderer, 0, 0, 255, 255);
            SDL_RenderDrawLine(
                    windowRenderer,
                    static_cast<int>(this->vertices.at(0).x),
                    static_cast<int>(this->vertices.at(0).y),
                    static_cast<int>(this->vertices.at(1).x),
                    static_cast<int>(this->vertices.at(1).y));
        }
    }


}