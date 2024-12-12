#include<iostream>
#include<vector>
using namespace std;

/**
 * @brief 提供进行整型int64或浮点数double的矩阵乘法。
 * @param 两个矩阵。
 */
template<class T>
vector<vector<T> > matrix_multiplication(vector<vector<T> > &v1, vector<vector<T> > &v2)
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
    vector<vector<T> > ans(v1.size(), vector<T> (v2[0].size(),0));
    // 3. apply the multiplication. O(n^3)
    for(size_t i = 0; i < ans.size(); i++)
    {
        for(size_t j = 0; j < ans[i].size(); j++)
        {
            for(size_t k = 0; k < v2.size(); k++)
                ans[i][j] += v1[i][k] * v2[k][j];
        }
    }
    return ans;
}