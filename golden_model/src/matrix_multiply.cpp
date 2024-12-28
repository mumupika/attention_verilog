#include<iostream>
#include<vector> 
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
        if ((v1[0].size()!=4 && v2.size()!=4) && (v1[0].size()!=8 && v2.size()!=8))
            throw "Dimension not 4 or 8!.";
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
    if(v1[0].size()==4)
    {
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
    }
    else if(v1[0].size() == 8)
    {
        for(size_t i = 0; i < ans.size(); i++)
        {
            for (size_t j = 0; j < ans[i].size(); j++)
            {
                // v1(i,0-3), v2(0-3,j);
                double a1 = v1[i][0], b1 = v2[0][j];
                double a2 = v1[i][1], b2 = v2[1][j];
                double a3 = v1[i][2], b3 = v2[2][j];
                double a4 = v1[i][3], b4 = v2[3][j];
                double a5 = v1[i][4], b5 = v2[4][j];
                double a6 = v1[i][5], b6 = v2[5][j];
                double a7 = v1[i][6], b7 = v2[6][j];
                double a8 = v1[i][7], b8 = v2[7][j];

                // change to 16 bits.
                vector<int> a1_fixed = float2byte(a1,16), b1_fixed = float2byte(b1,16);
                vector<int> a2_fixed = float2byte(a2,16), b2_fixed = float2byte(b2,16);
                vector<int> a3_fixed = float2byte(a3,16), b3_fixed = float2byte(b3,16);
                vector<int> a4_fixed = float2byte(a4,16), b4_fixed = float2byte(b4,16);
                vector<int> a5_fixed = float2byte(a5,16), b5_fixed = float2byte(b5,16);
                vector<int> a6_fixed = float2byte(a6,16), b6_fixed = float2byte(b6,16);
                vector<int> a7_fixed = float2byte(a7,16), b7_fixed = float2byte(b7,16);
                vector<int> a8_fixed = float2byte(a8,16), b8_fixed = float2byte(b8,16);

                // 16 bits to 32 bits.
                vector<int> mul_1 = vec_mul(a1_fixed, b1_fixed);
                vector<int> mul_2 = vec_mul(a2_fixed, b2_fixed);
                vector<int> mul_3 = vec_mul(a3_fixed, b3_fixed);
                vector<int> mul_4 = vec_mul(a4_fixed, b4_fixed);
                vector<int> mul_5 = vec_mul(a5_fixed, b5_fixed);
                vector<int> mul_6 = vec_mul(a6_fixed, b6_fixed);
                vector<int> mul_7 = vec_mul(a7_fixed, b7_fixed);
                vector<int> mul_8 = vec_mul(a8_fixed, b8_fixed);

                // add them.
                vector<int> add_1 = vec_add(mul_1,mul_2, 33);
                vector<int> add_2 = vec_add(mul_3,mul_4, 33);
                vector<int> add_3 = vec_add(mul_5,mul_6, 33);
                vector<int> add_4 = vec_add(mul_7,mul_8, 33);

                vector<int> res_1 = vec_add(add_1,add_2, 34);  
                vector<int> res_2 = vec_add(add_3,add_4, 34);

                vector<int> res = vec_add(res_1, res_2, 35);

                ans[i][j] = byte2float(res);
            }
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

/**
 * @brief 提供进行整型int64或浮点数double的矩阵乘法。
 * @param 两个矩阵。其中检查第二个维度为4.
 */
vector<vector<vector<int> > > matrix_fix_multiplication_container(vector<vector<double> > &v1, vector<vector<double> > &v2)
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
        if ((v1[0].size()!=4 && v2.size()!=4) && (v1[0].size()!=8 && v2.size()!=8))
            throw "Dimension not 4 or 8!.";
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
    vector<vector<vector<int> > > ans(v1.size(), vector<vector<int> > (v2[0].size()));
    // 3. apply the multiplication. O(n^3)
    if(v1[0].size()==4)
    {
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

                ans[i][j]=res;
            }
        }
    }
    else if(v1[0].size() == 8)
    {
        for(size_t i = 0; i < ans.size(); i++)
        {
            for (size_t j = 0; j < ans[i].size(); j++)
            {
                // v1(i,0-3), v2(0-3,j);
                double a1 = v1[i][0], b1 = v2[0][j];
                double a2 = v1[i][1], b2 = v2[1][j];
                double a3 = v1[i][2], b3 = v2[2][j];
                double a4 = v1[i][3], b4 = v2[3][j];
                double a5 = v1[i][4], b5 = v2[4][j];
                double a6 = v1[i][5], b6 = v2[5][j];
                double a7 = v1[i][6], b7 = v2[6][j];
                double a8 = v1[i][7], b8 = v2[7][j];

                // change to 16 bits.
                vector<int> a1_fixed = float2byte(a1,16), b1_fixed = float2byte(b1,16);
                vector<int> a2_fixed = float2byte(a2,16), b2_fixed = float2byte(b2,16);
                vector<int> a3_fixed = float2byte(a3,16), b3_fixed = float2byte(b3,16);
                vector<int> a4_fixed = float2byte(a4,16), b4_fixed = float2byte(b4,16);
                vector<int> a5_fixed = float2byte(a5,16), b5_fixed = float2byte(b5,16);
                vector<int> a6_fixed = float2byte(a6,16), b6_fixed = float2byte(b6,16);
                vector<int> a7_fixed = float2byte(a7,16), b7_fixed = float2byte(b7,16);
                vector<int> a8_fixed = float2byte(a8,16), b8_fixed = float2byte(b8,16);

                // 16 bits to 32 bits.
                vector<int> mul_1 = vec_mul(a1_fixed, b1_fixed);
                vector<int> mul_2 = vec_mul(a2_fixed, b2_fixed);
                vector<int> mul_3 = vec_mul(a3_fixed, b3_fixed);
                vector<int> mul_4 = vec_mul(a4_fixed, b4_fixed);
                vector<int> mul_5 = vec_mul(a5_fixed, b5_fixed);
                vector<int> mul_6 = vec_mul(a6_fixed, b6_fixed);
                vector<int> mul_7 = vec_mul(a7_fixed, b7_fixed);
                vector<int> mul_8 = vec_mul(a8_fixed, b8_fixed);

                // add them.
                vector<int> add_1 = vec_add(mul_1,mul_2, 33);
                vector<int> add_2 = vec_add(mul_3,mul_4, 33);
                vector<int> add_3 = vec_add(mul_5,mul_6, 33);
                vector<int> add_4 = vec_add(mul_7,mul_8, 33);

                vector<int> res_1 = vec_add(add_1,add_2, 34);  
                vector<int> res_2 = vec_add(add_3,add_4, 34);

                vector<int> res = vec_add(res_1, res_2, 35);

                ans[i][j]=res;
            }
        }
    }
    return ans;
}

/**
 * @brief 提供进行整型int64或浮点数double的矩阵乘法。
 * @param 两个矩阵。其中检查第二个维度为4.
 */
vector<vector<vector<int> > > matrix_fix_multiplication_container(vector<vector<vector<int> > > &v1, vector<vector<vector<int> > > &v2)
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
        if ((v1[0].size()!=4 && v2.size()!=4) && (v1[0].size()!=8 && v2.size()!=8))
            throw "Dimension not 4 or 8!.";
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
    vector<vector<vector<int> > > ans(v1.size(), vector<vector<int> > (v2[0].size()));
    // 3. apply the multiplication. O(n^3)
    if(v1[0].size()==4)
    {
        for(size_t i = 0; i < ans.size(); i++)
        {
            for (size_t j = 0; j < ans[i].size(); j++)
            {
                // v1(i,0-3), v2(0-3,j);
                vector<int> a1_fixed = v1[i][0], b1_fixed = v2[0][j];
                vector<int> a2_fixed = v1[i][1], b2_fixed = v2[1][j];
                vector<int> a3_fixed = v1[i][2], b3_fixed = v2[2][j];
                vector<int> a4_fixed = v1[i][3], b4_fixed = v2[3][j];

                // 16 bits to 32 bits.
                vector<int> mul_1 = vec_mul(a1_fixed, b1_fixed);
                vector<int> mul_2 = vec_mul(a2_fixed, b2_fixed);
                vector<int> mul_3 = vec_mul(a3_fixed, b3_fixed);
                vector<int> mul_4 = vec_mul(a4_fixed, b4_fixed);

                // add them.
                vector<int> add_1 = vec_add(mul_1,mul_2, 33);
                vector<int> add_2 = vec_add(mul_3,mul_4, 33);
                vector<int> res = vec_add(add_1,add_2, 34);  

                ans[i][j]=res;
            }
        }
    }
    else if(v1[0].size() == 8)
    {
        for(size_t i = 0; i < ans.size(); i++)
        {
            for (size_t j = 0; j < ans[i].size(); j++)
            {
                // v1(i,0-3), v2(0-3,j);
                vector<int> a1_fixed = v1[i][0], b1_fixed = v2[0][j];
                vector<int> a2_fixed = v1[i][1], b2_fixed = v2[1][j];
                vector<int> a3_fixed = v1[i][2], b3_fixed = v2[2][j];
                vector<int> a4_fixed = v1[i][3], b4_fixed = v2[3][j];
                vector<int> a5_fixed = v1[i][4], b5_fixed = v2[4][j];
                vector<int> a6_fixed = v1[i][5], b6_fixed = v2[5][j];
                vector<int> a7_fixed = v1[i][6], b7_fixed = v2[6][j];
                vector<int> a8_fixed = v1[i][7], b8_fixed = v2[7][j];

                // 16 bits to 32 bits.
                vector<int> mul_1 = vec_mul(a1_fixed, b1_fixed);
                vector<int> mul_2 = vec_mul(a2_fixed, b2_fixed);
                vector<int> mul_3 = vec_mul(a3_fixed, b3_fixed);
                vector<int> mul_4 = vec_mul(a4_fixed, b4_fixed);
                vector<int> mul_5 = vec_mul(a5_fixed, b5_fixed);
                vector<int> mul_6 = vec_mul(a6_fixed, b6_fixed);
                vector<int> mul_7 = vec_mul(a7_fixed, b7_fixed);
                vector<int> mul_8 = vec_mul(a8_fixed, b8_fixed);

                // add them.
                vector<int> add_1 = vec_add(mul_1,mul_2, 33);
                vector<int> add_2 = vec_add(mul_3,mul_4, 33);
                vector<int> add_3 = vec_add(mul_5,mul_6, 33);
                vector<int> add_4 = vec_add(mul_7,mul_8, 33);

                vector<int> res_1 = vec_add(add_1,add_2, 34);  
                vector<int> res_2 = vec_add(add_3,add_4, 34);

                vector<int> res = vec_add(res_1, res_2, 35);

                ans[i][j]=res;
            }
        }
    }
    return ans;
}