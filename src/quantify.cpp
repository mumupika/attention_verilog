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
        std::cerr << "Error! Truncating size should be 34!\n";
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
        std::cerr << "Error! Truncating size should be 34!\n";
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
 * @brief 饱和近似到最大的正值。（因为我们的输入均为非负数）。
 * @param 长整形向量，长度为34或26.
 * @return 长整形16或24bits向量。
 */
vector<int> vec_sat(vector<int> &a)
{
}