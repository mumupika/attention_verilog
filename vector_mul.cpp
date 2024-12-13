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