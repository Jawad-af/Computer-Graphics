//
//  vec2.h
//  Lab2
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#pragma once

#include <cmath>
#include <iostream>
#include "vec3.h"
#include "vec4.h"

namespace egc {

class vec2
{
public:
    union
    {
        float x;
        float u;
    };
    
    union
    {
        float y;
        float v;
    };
    
    //=========================================
    //constructors
    //=========================================
    
    //default constructor creates a zero vector
    vec2()
    {
		x = 0.0f;
		y = 0.0f;
    }
    
    //creates a vector (fX, fY)
    vec2(float fX, float fY)
    {
		x = fX;
		y = fY;
    }
    
    //copy constructor
    vec2(const vec2 &srcVector)
    {
		x = srcVector.x;
		y = srcVector.y;
    }
    
    vec2(const egc::vec3 &srcVector)
    {
		x = srcVector.x;
		y = srcVector.y;
    }
    
    vec2(const egc::vec4 &srcVector)
    {
		x = srcVector.x;
		y = srcVector.y;
    }
    
    //=========================================
    //
    //=========================================
    
    bool operator ==(const vec2& srcVector) const
    {
        return (std::abs(x - srcVector.x) < std::numeric_limits<float>::epsilon()) && (std::abs(y - srcVector.y) < std::numeric_limits<float>::epsilon());
    }
    
    friend std::ostream& operator<< (std::ostream &out, const vec2& srcVector);
    
    //=========================================
    //2D vector operations
    //TO BE IMPLEMENTED
    //=========================================
    
    vec2& operator =(const vec2& srcVector) 
    {
        x = srcVector.x;
        y = srcVector.y;
        return *this;
    }

    vec2 operator +(const vec2& srcVector) const 
    {
        vec2 tempVec;
        tempVec.x = x + srcVector.x;
        tempVec.y = y + srcVector.y;
        return tempVec;
    }

    vec2& operator +=(const vec2& srcVector) 
    {
        x += srcVector.x;
        y += srcVector.y;
        return *this;
    }

    vec2 operator *(float scalarValue) const
    {
        vec2 tmpVec;
        tmpVec.x = x * scalarValue;
        tmpVec.y = y * scalarValue;
        return tmpVec;
    }

    vec2 operator -(const vec2& srcVector) const
    {
        vec2 tmpVec;
        tmpVec.x = x - srcVector.x;
        tmpVec.y = y - srcVector.y;
        return tmpVec;
    }
    vec2& operator -=(const vec2& srcVector)
    {
        x -= srcVector.x;
        y -= srcVector.y;
        return *this;
    }

    vec2 operator -() const
    {
        vec2 tmpVec;
        tmpVec.x = -x;
        tmpVec.y = -y;
        return tmpVec;
    }

    float length() const
    {
        float x1 = pow(x, 2);
        float y1 = pow(y, 2);
        float sum = x1 + y1;
        return sqrt(sum);
    }

    vec2& normalize()
    {
        float len = length();
        if (len != 0) {
            x = x / len;
            y = y / len;
        }
        return *this;
    }
};

    inline std::ostream& operator<< (std::ostream &out, const vec2& srcVector)
    {
        out << "(" << srcVector.x << ", " << srcVector.y << ")";
        return out;
    };

    
    float dotProduct(const vec2& v1, const vec2& v2)
    {
        float x, y, sum;
        x = v1.x * v2.x;
        y = v1.y * v2.y;
        sum = x + y;
        return sum;
    }
}
