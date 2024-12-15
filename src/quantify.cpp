#include<vector>
#include<iostream>
#include "headers.hpp"
using namespace std;

/**
 * @brief truncate。将34bits长整形转换成16bits的短整形。
 * @param a:长整形向量，长度为34或24.
 * @return 长整形16bits向量。
 */
vector<int> vec_truncate(vector<int> &a)
{
    if(a.size()!=34 && a.size()!=24)
    {
        std::cerr << "Error! Truncating size should be 34 or 24!\n";
        exit(-1);
    }
    vector<int> ans;
    if(a.size() == 34)
        ans = vector<int>(a.begin(),a.begin()+26);
    else
        ans = vector<int>(a.begin(),a.begin()+16);
    return ans;
}

/**
 * @brief round。将34bits长整形舍入成16bits的短整形。
 * @param a:长整形向量，长度为34或24.
 * @return 长整形16或26bits向量。
 */
vector<int> vec_round(vector<int> &a)
{
    if(a.size()!=34 && a.size()!=24)
    {
        std::cerr << "Error! Truncating size should be 34 or 24!\n";
        exit(-1);
    }
    vector<int> ans;
    if (a.size()==34)
        ans = vector<int>(a.begin(),a.begin()+26);
    else
        ans = vector<int>(a.begin(),a.begin()+16);
    
    int carry = (a[ans.size()] + 1) >> 1;
    if (carry == 0) 
        return ans;
    for(int i = (int)ans.size()-1; i>=0; i--)
    {
        int val = ans[i] + carry;
        carry = val << 1;
        ans[i] = val & 1;
    }
    return ans;
}

/**
 * @brief 饱和近似到最大的正值。（因为我们的输入均为非负数）。注意无符号数。
 * @param 长整形向量，长度为34或26.
 * @return 长整形16或24bits向量。
 */
vector<int> vec_sat(vector<int> &a)
{
    if(a.size() != 34 || a.size() != 26)
    {
        std::cerr << "Error! Saturation size should be 34 or 26!\n";
        exit(-1);
    }
    vector<int> ans(a.begin()+10, a.end());
    // 1. 判断是否发生了溢出情况。
    int flag = 0;
    for(int i = 0; i < 10; i++)
    {
        if(a[i] == 1)
        {
            flag = 1;
            break;
        }
    }
    if(!flag) return ans;
    // 2. 针对溢出情况对症下药。返回最大正值（无符号）。
    for(size_t i = 0; i < ans.size(); i++)
        ans[i] = 1;
    return ans;
}

/**
 * @brief 直接对高位进行截断。
 * @param 长整形向量，长度为34或26.
 * @return 长整形16或24bits向量。
 */
vector<int> vec_wrap(vector<int> &a)
{
     if(a.size() != 34 || a.size() != 26)
    {
        std::cerr << "Error! Saturation size should be 34 or 26!\n";
        exit(-1);
    }
    vector<int> ans(a.begin()+10, a.end());
    return ans;
}

/**
 * @brief 对矩阵进行量化。输入矩阵应当均为26位对应的float。
 * @param a:输入的二维矩阵。
 * @param strategy:进行量化的策略。1 -round+sat; 2 - round+wrap; 3 - trunc+sat; 4 - trunc + wrap.
 * @return 经过量化并且重新转换后的矩阵。
 */
