#include<iostream>
#include<vector>
using namespace std;
/**
 * @brief 进行长整形乘法。
 * @param a
 * @param b: a 和 b 应该等长度。
 * @return 返回长度*2的向量。
 */
vector<int> vec_mul(vector<int> &a, vector<int> &b)
{
    try
    {
        if (a.size() != b.size())
            throw "size_error";
        else if (a.size()==0 || b.size()==0)
            throw "empty";
    }
    catch(const std::exception& e)
    {
        if(e.what() == std::string("size_error"))
            std::cerr << "The size are not the same, with a: "
                 << a.size() << " and b:" << b.size() << '\n';
        else
        {
            if(!a.size())
                std::cerr << "a is empty!\n";
            else
                std::cerr << "b is empty!\n";
        }
    }
    
    // Perform long long multiplication. 
    vector<int> res(a.size()+b.size(), 0);
    for(int i = b.size()-1; i >= 0; i--)
    {
        if(b[i]==0)
            continue;
        else
        {
            int carry = 0;
            for(int j = a.size()-1; j>=0; j--)
            {
                int value = res[i+j+1] + a[j] + carry;
                res[i+j+1] = value & 1;
                carry = value >> 1;
            }
            res[0] = res[0] + carry; // 最后一位不能超过1.
            if(res[0] == 2)
                std::cerr << "Error! Overflowed!\n";
        }
    }
    return res;
}

/**
 * @brief 长整形加法。允許接受不同長度的向量。
 * @param a
 * @param b a,b 为向量。
 * @param length 需要返回的向量长度要求
 * @return 統一返回長度為34bits的向量。
 */
vector<int> vec_add(vector<int> &a, vector<int> &b, int length)
{
    try
    {
        if (a.size()==0 || b.size()==0)
            throw "empty";
    }
    catch(const std::exception& e)
    {
        if(!a.size())
            std::cerr << "a is empty!\n";
        else
            std::cerr << "b is empty!\n";
    }


    vector<int> ans(length, 0);

    int b_ind = b.size()-1;
    int ans_ind = length-1;
    int carry = 0;
    for(int i = a.size()-1; i >= 0; i--)
    {
        int value = a[i] + b[b_ind] + carry;
        ans[ans_ind] = value & 1;
        carry = value >> 1;

        b_ind--;
        ans_ind--;
    }
    for(;b_ind >= 0; b_ind--)
    {
        int value = b[b_ind] + carry;
        ans[ans_ind] = value & 1;
        carry = value >> 1;
        ans_ind--;
    }
    if(ans_ind != 0) ans[ans_ind] += carry;
    return ans;
}