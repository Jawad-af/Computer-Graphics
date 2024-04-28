//
//  mat3.h
//  Lab3_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#pragma once

#include <algorithm>
#include <iostream>
#include "vec3.h"

namespace egc {
    class mat3
    {
    public:
        //==============================================
        //matrixData is stored in column-major order
        //  m0  m3   m6
        //  m1  m4   m7
        //  m2  m5   m8
        //
        //  matrixData[] = {m0, m1, m2,
        //                  m3, m4, m5,
        //                  m6, m7, m8}
        //==============================================
        float matrixData[9];
        
        //==============================================
        //constructors
        //==============================================
        
        //default constructor creates an identity matrix
        mat3()
        {
            for (int i = 0; i < 9; i++) {
                matrixData[i] = (i % 4) ? 0.0f : 1.0f;
            }
        }
        
        mat3(const float* srcMatrix)
        {
            std::copy(srcMatrix, srcMatrix + 9, matrixData);
        }
        
        //==============================================
        // TO BE IMPLEMENTED
        //==============================================
        mat3& operator =(const mat3& srcMatrix)
        {
            std::copy(srcMatrix.matrixData, srcMatrix.matrixData + 9, matrixData);
            return *this;
        }
        mat3 operator *(float scalarValue) const
        {
            mat3 result;
            for (int i = 0; i < 9; ++i) {
                result.matrixData[i] = matrixData[i] * scalarValue;
            }
            return result;
        }
        mat3 operator *(const mat3& srcMatrix) const
        {
            mat3 result;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    float sum = 0.0f;
                    for (int k = 0; k < 3; ++k) {
                        sum += this->at(i, k) * srcMatrix.at(k, j);
                    }
                    result.at(i, j) = sum;
                }
            }
            return result;
        }
        vec3 operator *(const vec3& srcVector) const
        {
            return vec3(
                srcVector.x * matrixData[0] + srcVector.y * matrixData[3] + srcVector.z * matrixData[6],
                srcVector.x * matrixData[1] + srcVector.y * matrixData[4] + srcVector.z * matrixData[7],
                srcVector.x * matrixData[2] + srcVector.y * matrixData[5] + srcVector.z * matrixData[8]
            );
        }
        mat3 operator +(const mat3& srcMatrix) const
        {
            mat3 result;
            for (int i = 0; i < 9; ++i) {
                result.matrixData[i] = matrixData[i] + srcMatrix.matrixData[i];
            }
            return result;
        }
        //get element by (row, column)
        float& at(int i, int j) { return matrixData[i + (j * 3)]; }
        const float& at(int i, int j) const { return matrixData[i + (j * 3)]; }

        // Determinant calculation
        float determinant() const
        {
            int result;
            int sum1 = this->at(0, 0) * ((this->at(1, 1) * this->at(2, 2)) - (this->at(2, 1) * this->at(1, 2)));
            int sum2 = this->at(0, 1) * ((this->at(1, 0) * this->at(2, 2)) - (this->at(2, 0) * this->at(1, 2)));
            int sum3 = this->at(0, 2) * ((this->at(1, 0) * this->at(2, 1)) - (this->at(2, 0) * this->at(1, 1)));
            return result = sum1 - sum3 + sum3;
        }
        
        float calculate_2x2_determinant(float* matrix) const
        {
            return (matrix[0] * matrix[3]) - (matrix[2] * matrix[1]);
        }

        float* remove_row_and_col_3x3(int this_row, int this_col) const
        {
            float* result = new float[4];
            int k = 0;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (i == this_row || j == this_col)
                        continue;
                    else
                    {
                        float value = this->at(i, j);
                        result[k++] = value;
                    }
                }
            }
            return result;
        }

        mat3 generate_matrix_of_minors() const
        {   
            mat3 result;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    float *temp_matrix;
                    temp_matrix = remove_row_and_col_3x3(i, j);
                    int determinant = calculate_2x2_determinant(temp_matrix);
                    result.at(i, j) = determinant;
                    free(temp_matrix);
                }
            }
            return result;
        }
        
        // Inverse calculation
        mat3 inverse() const
        {   
            mat3 result;
            const float cofactors[9] = {1.00, -1.00, 1.00, -1.00, 1.00, -1.00, 1.00, -1.00, 1.00};
            int determinant = this->determinant();
            if (determinant != 0)
            {   
                mat3 matrix_of_minors = generate_matrix_of_minors();
                for (int i = 0; i < 9; i++)
                    matrix_of_minors.matrixData[i] *= cofactors[i];

                matrix_of_minors = matrix_of_minors.transpose();
                result = matrix_of_minors.operator*(1.0f/determinant);
            }
            return result;
        }
        
        // Transpose calculation
        mat3 transpose() const
        {
            mat3 result;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    result.at(j, i) = this->at(i, j);
                }
            }
            return result;
        }
        
        //==============================================
        friend std::ostream& operator<< (std::ostream &out, const mat3& srcMatrix);
        
        bool operator ==(const mat3& srcMatrix) const
        {
            for (int i = 0; i < 9; i++)
                if (std::abs(matrixData[i] - srcMatrix.matrixData[i]) >= std::numeric_limits<float>::epsilon()) {
                    return false;
                }
            return true;
        }
    };
    
    inline std::ostream& operator<< (std::ostream &out, const mat3& srcMatrix)
    {
        for(int i = 0; i < 3; i++)
            out << srcMatrix.matrixData[i] << "\t" << srcMatrix.matrixData[i + 3] << "\t" << srcMatrix.matrixData[i + 6] << "\n";
        return out;
    };
}