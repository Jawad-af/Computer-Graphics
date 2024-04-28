//
//  transformations.hpp
//  Lab4_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#pragma once

#include "vec2.h"
#include "vec3.h"
#include "mat3.h"
#include "mat4.h"

namespace egc {
    const double PI = atan(1.0) * 4;
    
    //transformation matrices in 2D
    mat3 translate(const vec2 translateArray)
    {
        float identity[] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        mat3 translation_matrix(identity);
        translation_matrix.at(0, 2) = translateArray.x;
        translation_matrix.at(1, 2) = translateArray.y;
        return translation_matrix;
    }

    mat3 translate(float tx, float ty)
    {
        float identity[] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        mat3 translation_matrix(identity);
        translation_matrix.at(0, 2) = tx;
        translation_matrix.at(1, 2) = ty;
        return translation_matrix;
    }
    
    mat3 scale(const vec2 scaleArray)
    {
        float identity[] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        mat3 scale_matrix(identity);
        scale_matrix.at(0, 0) = scaleArray.x;
        scale_matrix.at(1, 1) = scaleArray.y;
        return scale_matrix;
    }

    mat3 scale(float sx, float sy)
    {
        float identity[] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        mat3 scale_matrix(identity);
        scale_matrix.at(0, 0) = sx;
        scale_matrix.at(1, 1) = sy;
        return scale_matrix;
    }
    
    mat3 rotate(float angle)
    {
        float rad_angle = angle * PI / 180;
        float identity[] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        mat3 rotate_matrix(identity);
        rotate_matrix.at(0, 0) = cos(rad_angle);
        rotate_matrix.at(0, 1) = -sin(rad_angle);
        rotate_matrix.at(1, 0) = sin(rad_angle);
        rotate_matrix.at(1, 1) = cos(rad_angle);

        return rotate_matrix;
    }

    //transformation matrices in 3D
    
    mat4 translate(const vec3 translateArray)
    {
        float identity[] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        mat4 translation_matrix(identity);
        translation_matrix.at(0, 3) = translateArray.x;
        translation_matrix.at(1, 3) = translateArray.y;
        translation_matrix.at(2, 3) = translateArray.z;
        return translation_matrix;
    }
    mat4 translate(float tx, float ty, float tz)
    {
        float identity[] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        mat4 translation_matrix(identity);
        translation_matrix.at(0, 3) = tx;
        translation_matrix.at(1, 3) = ty;
        translation_matrix.at(2, 3) = tz;
        return translation_matrix;
    }
    
    mat4 scale(const vec3 scaleArray)
    {
        float identity[] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        mat4 scale_matrix(identity);
        scale_matrix.at(0, 0) = scaleArray.x;
        scale_matrix.at(1, 1) = scaleArray.y;
        scale_matrix.at(2, 2) = scaleArray.z;
        return scale_matrix;
    }

    mat4 scale(float sx, float sy, float sz)
    {
        float identity[] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        mat4 scale_matrix(identity);
        scale_matrix.at(0, 0) = sx;
        scale_matrix.at(1, 1) = sy;
        scale_matrix.at(2, 2) = sz;
        return scale_matrix;
    }
    
    mat4 rotateX(float angle)
    {
        float rad_angle = angle * PI / 180;
        float identity[] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        mat4 rotation_matrix(identity);
        rotation_matrix.at(1, 1) = cos(rad_angle);
        rotation_matrix.at(1, 2) = -sin(rad_angle);
        rotation_matrix.at(2, 1) = sin(rad_angle);
        rotation_matrix.at(2, 2) = cos(rad_angle);
        return rotation_matrix;
    }

    mat4 rotateY(float angle)
    {
        float rad_angle = angle * PI / 180;
        float identity[] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        mat4 rotation_matrix(identity);
        rotation_matrix.at(0, 0) = cos(rad_angle);
        rotation_matrix.at(0, 2) = sin(rad_angle);
        rotation_matrix.at(2, 0) = -sin(rad_angle);
        rotation_matrix.at(2, 2) = cos(rad_angle);
        return rotation_matrix;
    }

    mat4 rotateZ(float angle)
    {
        float rad_angle = angle * PI / 180;
        float identity[] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        mat4 rotation_matrix(identity);
        rotation_matrix.at(0, 0) = cos(rad_angle);
        rotation_matrix.at(0, 1) = -sin(rad_angle);
        rotation_matrix.at(1, 0) = sin(rad_angle);
        rotation_matrix.at(1, 1) = cos(rad_angle);
        return rotation_matrix;
    }
}