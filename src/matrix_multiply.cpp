#include<iostream>
#include<vector> 
#include "vector_ops.hpp"
#include "headers.hpp"
using namespace std;

#ifndef matrix_fix_
#define matrix_fix_
/**
 * @brief 提供进行整型int64或浮点数double的矩阵乘法。
 * @param 两个矩阵。其中检查第二个维度为4.
 */
vector<vector<double> > matrix_fix_multiplication(vector<vector<double> > &v1, vector<vector<double> > &v2)
{
    // 1. Assert the two vector can perform the multiplication.
    try
    {
        /* code */
        if (v1.size() == 0)
            throw "v1 size should not be zero.";
        if (v2.size() == 0)
            throw "v2 size should not be zero.";
        if (v1[0].size() != v2.size())
            throw "-1";
        if (v1[0].size()!=4 || v2.size()!=4)
            throw "Dimension not 4.";
    }
    catch(const std::exception& e)
    {
        if (e.what() != std::string("-1"))
            std::cerr << e.what() << '\n';
        else
            std::cerr << "The size of v1:(" << v1.size() << ',' << v1[0].size() << ") is not compatible "
                << "with the size of v2:(" << v2.size() << ',' << v2[0].size() << ") for matrix multiplication.\n";
    }
    // 2. To get the size of the multiplicated matrix.
    vector<vector<double> > ans(v1.size(), vector<double> (v2[0].size(),0));
    // 3. apply the multiplication. O(n^3)
    for(size_t i = 0; i < ans.size(); i++)
    {
        for (size_t j = 0; j < ans[i].size(); j++)
        {
            // v1(i,0-3), v2(0-3,j);
            double a1 = v1[i][0], b1 = v2[0][j];
            double a2 = v1[i][1], b2 = v2[1][j];
            double a3 = v1[i][2], b3 = v2[2][j];
            double a4 = v1[i][3], b4 = v2[3][j];

            // change to 16 bits.
            vector<int> a1_fixed = float2byte(a1,16), b1_fixed = float2byte(b1,16);
            vector<int> a2_fixed = float2byte(a2,16), b2_fixed = float2byte(b2,16);
            vector<int> a3_fixed = float2byte(a3,16), b3_fixed = float2byte(b3,16);
            vector<int> a4_fixed = float2byte(a4,16), b4_fixed = float2byte(b4,16);
            
            // 16 bits to 32 bits.
            vector<int> mul_1 = vec_mul(a1_fixed, b1_fixed);
            vector<int> mul_2 = vec_mul(a2_fixed, b2_fixed);
            vector<int> mul_3 = vec_mul(a3_fixed, b3_fixed);
            vector<int> mul_4 = vec_mul(a4_fixed, b4_fixed);
            
            // add them.
            vector<int> add_1 = vec_add(mul_1,mul_2, 33);
            vector<int> add_2 = vec_add(mul_3,mul_4, 33);
            vector<int> res = vec_add(add_1,add_2, 34);  

            ans[i][j] = byte2float(res);
        }
    }
    return ans;
}
#endif

/**
 * @brief 提供进行浮点数double的矩阵乘法。
 * @param 两个矩阵。常规矩阵乘法进行对拍。
 */
vector<vector<double> > matrix_multiplication(vector<vector<double> > &v1, vector<vector<double> > &v2)
{
    // 1. Assert the two vector can perform the multiplication.
    try
    {
        /* code */
        if (v1.size() == 0)
            throw "v1 size should not be zero.";
        if (v2.size() == 0)
            throw "v2 size should not be zero.";
        if (v1[0].size() != v2.size())
            throw "-1";
        if (v1[0].size()!=4 || v2.size()!=4)
            throw "Dimension not 4.";
    }
    catch(const std::exception& e)
    {
        if (e.what() != std::string("-1"))
            std::cerr << e.what() << '\n';
        else
            std::cerr << "The size of v1:(" << v1.size() << ',' << v1[0].size() << ") is not compatible "
                << "with the size of v2:(" << v2.size() << ',' << v2[0].size() << ") for matrix multiplication.\n";
    }
    // 2. To get the size of the multiplicated matrix.
    vector<vector<double> > ans(v1.size(), vector<double> (v2[0].size(),0));
    // 3. apply the multiplication. O(n^3)
    for(size_t i = 0; i < ans.size(); i++)
    {
        for (size_t j = 0; j < ans[i].size(); j++)
        {
            for(size_t k = 0; k < v2.size(); k++)
                ans[i][j] += v1[i][k] * v2[k][j];

        }
    }
    return ans;
}