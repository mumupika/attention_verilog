#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

/**
 * @brief 近似计算softmax。采用A'[i,j]=(A[i,j]-min(A[:,j]))**2进行计算
 * @param a:输入二维向量a。
 * @return 返回一个注意力图。
 */
template<class T>
vector<vector<T> > softmax(vector<vector<T> > &a)
{
    // 1. 寻找到每一列的最小元素。
    try
    {
        if(!a.size())
            throw "Error! input vector is empty!";
        else if(!a[0].size())
            throw "a's size should be 2-dimension.";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    vector<T> min_col_elements(a[0].size(),0);
    vector<vector<T> > ans(a.size(), vector<T>(a[0].size(), 0));
    for(size_t j = 0; j < a[0].size(); j++)
    {
        vector<T> temp;
        for(size_t i = 0; i < a.size(); i++)
            temp.push_back(a[i][j]);
        
        min_col_elements[j] = *std::min_element(temp.begin(),temp.end());
    }
    
    for(size_t i = 0; i < a.size(); i++)
    {
        for(size_t j = 0; j < a[i].size(); j++)
            ans[i][j] = (a[i][j] - min_col_elements[j]) * (a[i][j] - min_col_elements[j]);
    }
    return ans;
}