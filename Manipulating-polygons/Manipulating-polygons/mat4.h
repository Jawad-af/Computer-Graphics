//
//  mat4.h
//  Lab3_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#pragma once

#include <algorithm>
#include <iostream>
#include "vec4.h"

namespace egc {
    class mat4
    {
    public:
        //==============================================
        //matrixData is stored in column-major order
        //  m00  m04   m08  m12
        //  m01  m05   m09  m13
        //  m02  m06   m10  m14
        //  m03  m07   m11  m15
        //
        //  matrixData[] = {m00, m01, m02, m03,
        //                  m04, m05, m06, m07,
        //                  m08, m09, m10, m11,
        //                  m12, m13, m14, m15}
        //==============================================
        float matrixData[16];

        //==============================================
        //constructors
        //==============================================

        //default constructor creates an identity matrix
        mat4()
        {
            for (int i = 0; i < 16; i++) {
                matrixData[i] = (i % 5) ? 0.0f : 1.0f;
            }
        }

        mat4(const float* srcMatrix)
        {
            std::copy(srcMatrix, srcMatrix + 16, matrixData);
        }

        //==============================================
        // TO BE IMPLEMENTED
        //==============================================
        mat4& operator =(const mat4& srcMatrix)
        {
            std::copy(srcMatrix.matrixData, srcMatrix.matrixData + 16, matrixData);
            return *this;
        }

        mat4 operator *(float scalarValue) const
        {
            mat4 result;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    result.at(i, j) = this->at(i, j) * scalarValue;
                }
            }
            return result;
        }

        mat4 operator *(const mat4& srcMatrix) const
        {
            mat4 result;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    float sum = 0.0f;
                    for (int k = 0; k < 4; k++)
                    {
                        sum += this->at(i, k) * srcMatrix.at(k, j);
                    }
                    result.at(i, j) = sum;
                }
            }
            return result;
        }

        vec4 operator *(const vec4& srcVector) const
        {
            vec4 result;
            float addition_result[4];
            for (int i = 0; i < 4; i++)
            {
                float sum = 0.0f;
                for (int j = 0; j < 4; j++)
                {
                    sum += this->at(i, j);
                }
                addition_result[i] = sum;
            }
            result.x = addition_result[0];
            result.y = addition_result[1];
            result.z = addition_result[2];
            result.w = addition_result[3];
            return result;
        }

        mat4 operator +(const mat4& srcMatrix) const
        {
            mat4 result;
            for (int i = 0; i < 16; i++)
            {
                result.matrixData[i] = this->matrixData[i] + srcMatrix.matrixData[i];
            }
            return result;
        }

        //get element by (row, column)
        float& at(int i, int j)
        {
            return matrixData[i + (j * 4)];
        }

        const float& at(int i, int j) const
        {
            return matrixData[i + (j * 4)];
        }

        mat3 remove_row_and_col_4x4(int this_row, int this_col) const
        {
            mat3 result;
            int k = 0;
            for (int i = 0; i < 4; i++)
            {
                if (i == this_row)
                    continue;
                int l = 0;
                for (int j = 0; j < 4; j++)
                {
                    if (j == this_col)
                        continue;
                    result.at(k, l) = this->at(i, j);
                    l++;
                }
                k++;
            }
            return result;
        }

        float determinant() const
        {
            float determinant = 0.0f;
            for (int i = 0; i < 1; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    mat3 temp_matrix;
                    temp_matrix = remove_row_and_col_4x4(i, j);
                    if (j % 2 == 0)
                        determinant += this->at(i, j) * temp_matrix.determinant();
                    else determinant += (-1.00) * this->at(i, j) * temp_matrix.determinant();
                }
            }
            return determinant;
        }

        mat4 inverse() const {
            mat4 result;

            float det = determinant();
            if (det == 0) {
                return result;
            }

            float invDet = 1.0f / det;

            // CALCULATE THE COFACTORS AND ADJUGATE MATRIX
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    // CONSTRUCT THE SUBMATRIX WITHOUT THE CURRENT ROW AND COLUMN
                    float subMatrix[9];
                    int subMatrixIndex = 0;
                    for (int row = 0; row < 4; ++row) {
                        if (row == i) continue;
                        for (int col = 0; col < 4; ++col) {
                            if (col == j) continue;
                            subMatrix[subMatrixIndex++] = matrixData[row + col * 4];
                        }
                    }
                    // THE DETERMINANT OF THE SUBMATRIX
                    float minorDet = subMatrix[0] * (subMatrix[4] * subMatrix[8] - subMatrix[5] * subMatrix[7])
                        - subMatrix[1] * (subMatrix[3] * subMatrix[8] - subMatrix[5] * subMatrix[6])
                        + subMatrix[2] * (subMatrix[3] * subMatrix[7] - subMatrix[4] * subMatrix[6]);
                    // CALCULATE THE COFACTOR AND ASSIGN TO THE ADJUGATE MATRIX
                    float sign = ((i + j) % 2 == 0) ? 1.0f : -1.0f;
                    result.at(j, i) = minorDet * sign * invDet; // TRANSPOSE WHILE ASSIGNING
                }
            }
            return result;
        }

        mat4 transpose() const
        {
            mat4 result;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    result.at(i, j) = this->at(j, i);
                }
            }
            return result;
        }

        //==============================================
        friend std::ostream& operator<< (std::ostream& out, const mat4& srcMatrix);

        bool operator ==(const mat4& srcMatrix) const
        {
            for (int i = 0; i < 16; i++)
                if (std::abs(matrixData[i] - srcMatrix.matrixData[i]) >= std::numeric_limits<float>::epsilon()) {
                    return false;
                }
            return true;
        }
    };

    inline std::ostream& operator<< (std::ostream& out, const mat4& srcMatrix)
    {
        for (int i = 0; i < 4; i++)
            out << srcMatrix.matrixData[i] << "\t" << srcMatrix.matrixData[i + 4] << "\t" << srcMatrix.matrixData[i + 8] << "\t" << srcMatrix.matrixData[i + 12] << "\n";
        return out;
    };
}