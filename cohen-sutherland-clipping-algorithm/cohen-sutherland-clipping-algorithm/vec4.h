//
//  vec3.h
//  Lab2
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#pragma once

#include <cmath>
#include <iostream>

namespace egc {

class vec4
{
public:
    union
    {
        float x;
        float r;
    };
    
    union
    {
        float y;
        float g;
    };
    
    union
    {
        float z;
        float b;
    };
    
    union
    {
        float w;
        float a;
    };
    
    //=========================================
    //constructors
    //=========================================
    
    //default constructor creates a zero vector
    vec4()
    {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
    }
    
    //creates a vector (fX, fY, fZ, fW)
    vec4(float fX, float fY, float fZ, float fW)
    {
		x = fX;
		y = fY;
		z = fZ;
		w = fW;
    }
    
    //copy constructor
    vec4(const vec4 &srcVector)
    {
		x = srcVector.x;
		y = srcVector.y;
		z = srcVector.z;
		w = srcVector.w;
    }
    
    //=========================================
    //
    //=========================================
    
    bool operator ==(const vec4& srcVector) const
    {
        return (std::abs(x - srcVector.x) < std::numeric_limits<float>::epsilon()) && (std::abs(y - srcVector.y) < std::numeric_limits<float>::epsilon()) && (std::abs(z - srcVector.z) < std::numeric_limits<float>::epsilon()) && (std::abs(w - srcVector.w) < std::numeric_limits<float>::epsilon());
    }
    
    friend std::ostream& operator<< (std::ostream &out, const vec4& srcVector);
    
    //=========================================
    //4D vector operations
    //TO BE IMPLEMENTED
    //=========================================
    
    // Assignment operator
    vec4& operator =(const vec4& srcVector) {
        x = srcVector.x;
        y = srcVector.y;
        z = srcVector.z;
        w = srcVector.w;
        return *this;
    }

    // Addition operator
    vec4 operator +(const vec4& srcVector) const {
        return vec4(x + srcVector.x, y + srcVector.y, z + srcVector.z, w + srcVector.w);
    }

    // Compound addition operator
    vec4& operator +=(const vec4& srcVector) {
        x += srcVector.x;
        y += srcVector.y;
        z += srcVector.z;
        w += srcVector.w;
        return *this;
    }

    // Scalar multiplication operator
    vec4 operator *(float scalarValue) const {
        return vec4(x * scalarValue, y * scalarValue, z * scalarValue, w * scalarValue);
    }

    // Subtraction operator
    vec4 operator -(const vec4& srcVector) const {
        return vec4(x - srcVector.x, y - srcVector.y, z - srcVector.z, w - srcVector.w);
    }

    // Compound subtraction operator
    vec4& operator -=(const vec4& srcVector) {
        x -= srcVector.x;
        y -= srcVector.y;
        z -= srcVector.z;
        w -= srcVector.w;
        return *this;
    }

    // Unary minus operator
    vec4 operator -() const {
        return vec4(-x, -y, -z, -w);
    }

    // Length calculation
    float length() const {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    // Normalize the vector
    vec4& normalize() {
        float len = length();
        if (len != 0) {
            x /= len;
            y /= len;
            z /= len;
            w /= len;
        }
        return *this;
    }
};
    
    inline std::ostream& operator<< (std::ostream &out, const vec4& srcVector)
    {
        out << "(" << srcVector.x << ", " << srcVector.y << ", " << srcVector.z << ", " << srcVector.w << ")";
        return out;
    }
      
}
