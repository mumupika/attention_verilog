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
    int carry = 0;
    for(int i = b.size()-1; i >= 0; i--)
    {
        if(b[i]==0)
            continue;
        else
        {
            for(int j = a.size()-1; j>=0; j--)
            {
                int value = res[i+j+1] + a[j] + carry;
                res[i+j+1] = value & 1;
                carry = value >> 1;
            }
        }
    }
    res[0] = res[0] + carry; // 最后一位不能超过1.
    if(res[0] == 2)
        std::cerr << "Error! Overflowed!\n";
    return res;
}

/**
 * @brief 长整形加法。允許接受不同長度的向量。
 * @param a
 * @param b a,b 为向量。
 * @param length 需要返回的向量长度要求
 * @return 統一返回长度规定的向量。
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
    for(; ans_ind >= 0; ans_ind--)
    {
        int value = ans[ans_ind] + carry;
        carry = value >> 1;
        ans[ans_ind] = value & 1;
    }
    return ans;
}

/**
 * @brief 长整形减法。允許接受不同長度的向量。
 * @param a
 * @param b a,b 为向量。实现效果为 a - b.
 * @param length 需要返回的向量长度要求
 * @return 統一返回长度规定的向量。
 */
vector<int> vec_minus(vector<int> &a, vector<int> &b, int length)
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

    // 对b进行补码处理。
    vector<int> b_comp(b.size(),0);
    for(size_t i = 0; i < b.size(); i++)
    {
        if(b[i] == 0)
            b_comp[i] = 1;
        else
            b_comp[i] = 0;
    }

    int carry = 0;
    int val = b_comp[b_comp.size()-1] + 1 + carry;
    b_comp[b_comp.size()-1] = val & 1;
    carry = val << 1;
    for(int i = (int)b_comp.size()-2; i >= 0; i--)
    {
        if (carry == 0)
            break;
        else
        {
            val = b_comp[i] + carry;
            b_comp[i] = val & 1;
            carry = val << 1;
        }
    }
    vector<int> ans(length, 0);

    int b_ind = b_comp.size()-1;
    int ans_ind = length-1;
    carry = 0;
    for(int i = a.size()-1; i >= 0; i--)
    {
        int value = a[i] + b_comp[b_ind] + carry;
        ans[ans_ind] = value & 1;
        carry = value >> 1;

        b_ind--;
        ans_ind--;
    }
    for(;b_ind >= 0; b_ind--)
    {
        int value = b_comp[b_ind] + carry;
        ans[ans_ind] = value & 1;
        carry = value >> 1;
        ans_ind--;
    }
    for(; ans_ind >= 0; ans_ind--)
    {
        int value = ans[ans_ind] + carry;
        carry = value >> 1;
        ans[ans_ind] = value & 1;
    }
    return ans;
}