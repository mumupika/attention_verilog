#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include "headers.hpp"
using namespace std;

/**
 * @brief 将长整形转换成16进制。
 */
string vec2hex(vector<int> &a)
{
    int count = -1;
    string number = "";
    int value = 0;
    for(int i = (int)a.size()-1; i >= 0; i--)
    {
        count++;
        value += (a[i]==1) ? (1 << count) : 0;
        if((count+1) % 4 == 0)
        {
            count = -1;
            switch(value)
            {
                case 0: number += "0"; break;
                case 1: number += "1"; break;
                case 2: number += "2"; break;
                case 3: number += "3"; break;
                case 4: number += "4"; break;
                case 5: number += "5"; break;
                case 6: number += "6"; break;
                case 7: number += "7"; break;
                case 8: number += "8"; break;
                case 9: number += "9"; break;
                case 10: number += "A"; break;
                case 11: number += "B"; break;
                case 12: number += "C"; break;
                case 13: number += "D"; break;
                case 14: number += "E"; break;
                case 15: number += "F"; break;
                default:
                    std::cerr << "Error! Your algorithm is wrong!\n";
                    exit(-1);
            }
            value = 0;
        }
    }
    // 最后尾部处理。
    if(count >= 0)
    {
        switch(value)
        {
            case 0: number += "0"; break;
            case 1: number += "1"; break;
            case 2: number += "2"; break;
            case 3: number += "3"; break;
            case 4: number += "4"; break;
            case 5: number += "5"; break;
            case 6: number += "6"; break;
            case 7: number += "7"; break;
            case 8: number += "8"; break;
            case 9: number += "9"; break;
            case 10: number += "A"; break;
            case 11: number += "B"; break;
            case 12: number += "C"; break;
            case 13: number += "D"; break;
            case 14: number += "E"; break;
            case 15: number += "F"; break;
            default:
                std::cerr << "Error! Your algorithm is wrong!\n";
                exit(-1);
        }
    }
    std::reverse(number.begin(),number.end());
    return number;
}

/**
 * @brief 根据生成的随机数组转换成16进制数并传入到文件中。
 * @param a:需要转换的16进制数。
 * @param name: 转换的矩阵名称。
 * @return: 没有返回值。
 */
void input(vector<vector<double> > &a, string name = std::string(""))
{
    ofstream file("data.txt");
    int count = 1;
    file << name << "\n\n";
    for(size_t i = 0; i < a.size(); i++)
    {
        for(size_t j = 0; j < a[i].size(); j++)
        {
            vector<int> current_byte = float2byte(a[i][j], 16);
            string number = vec2hex(current_byte);
            file << number << "  ";
            if(count % 4 == 0)
                file << "\n";
            count++;
        }
    }
    file << "\n";
}

/**
 * @brief 根据生成的随机数组转换成16进制数并传入到文件中。
 * @param a:需要转换的16进制数。
 * @param name: 转换的矩阵名称。
 * @return: 没有返回值。
 */
void output(vector<vector<double> > &a, string name = std::string(""))
{
    int count = 1;
    cout << name << "\n\n";
    for(size_t i = 0; i < a.size(); i++)
    {
        for(size_t j = 0; j < a[i].size(); j++)
        {
            vector<int> current_byte = float2byte(a[i][j], 16);
            string number = vec2hex(current_byte);
            cout << number << "  ";
            if(count % 8 == 0)
                cout << "\n";
            count++;
        }
    }
    cout << "\n";
}