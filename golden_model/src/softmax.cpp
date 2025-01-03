#include<vector>
#include<iostream>
#include<algorithm>
#include "headers.hpp"
using namespace std;

vector<int> findmin(vector<vector<int> > &temp)
{
    vector<int> container=temp[0];
    for(int i = 0; i < temp.size(); i++)
    {
        for(int j = 0; j < temp[i].size(); j++)
        {
            if(temp[i][j] < container[j])
            {
                container = temp[i];
                break;
            }
            else if(temp[i][j] > container[j])
                break;
        }
    }
    return container;
}

/**
 * @brief 近似计算softmax。采用A'[i,j]=(A[i,j]-min(A[:,j]))**2进行计算
 * @param a:输入二维向量a。
 * @return 返回一个注意力图。
 */
vector<vector<double> > softmax_fixed(vector<vector<double> > &a)
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
    vector<double> min_col_elements(a[0].size(),0);
    vector<vector<double> > ans(a.size(), vector<double>(a[0].size(), 0));
    for(size_t j = 0; j < a[0].size(); j++)
    {
        vector<double> temp;
        for(size_t i = 0; i < a.size(); i++)
            temp.push_back(a[i][j]);
        
        min_col_elements[j] = *std::min_element(temp.begin(),temp.end());
    }
    
    for(size_t i = 0; i < a.size(); i++)
    {
        for(size_t j = 0; j < a[i].size(); j++)
        {
            vector<int> op1=float2byte(a[i][j], 16);
            vector<int> op2=float2byte(min_col_elements[j], 16);
            vector<int> minus = vec_minus(op1, op2, 16);
            vector<int> mul = vec_mul(minus, minus);
            ans[i][j]=byte2float(mul);
        }
    }
    return ans;
}

/**
 * @brief 近似计算softmax。采用A'[i,j]=(A[i,j]-min(A[:,j]))**2进行计算
 * @param a:输入二维向量a。
 * @return 返回一个注意力图。
 */
vector<vector<vector<int> > > softmax_fixed_container(vector<vector<vector<int> > > &a)
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
    vector<vector<int> > min_col_elements(a[0].size());
    vector<vector<vector<int> > > ans(a.size(), vector<vector<int> >(a[0].size()));
    for(size_t j = 0; j < a[0].size(); j++)
    {
        vector<vector<int> > temp;
        for(size_t i = 0; i < a.size(); i++)
            temp.push_back(a[i][j]);
        
        min_col_elements[j] = findmin(temp);
    }
    
    for(size_t i = 0; i < a.size(); i++)
    {
        for(size_t j = 0; j < a[i].size(); j++)
        {
            vector<int> op1=a[i][j];
            vector<int> op2=min_col_elements[j];
            vector<int> minus = vec_minus(op1, op2, 16);
            vector<int> mul = vec_mul(minus, minus);
            ans[i][j]=mul;
        }
    }
    return ans;
}

/**
 * @brief 近似计算softmax。采用A'[i,j]=(A[i,j]-min(A[:,j]))**2进行计算
 * @param a:输入二维向量a。
 * @return 返回一个注意力图。
 */
vector<vector<double> > softmax_standard(vector<vector<double> > &a)
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
    vector<double> min_col_elements(a[0].size(),0);
    vector<vector<double> > ans(a.size(), vector<double>(a[0].size(), 0));
    for(size_t j = 0; j < a[0].size(); j++)
    {
        vector<double> temp;
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