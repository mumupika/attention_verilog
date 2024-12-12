#include<iostream>
#include<vector>
#include<cmath>
#include<cstdint>
using namespace std;

/**
 * @brief 在这里将整数转换成为八位整数+八位小数。
 * @param a:浮点数。
 */
vector<int> __float2byte_16(double &a)
{
    int integer = floor(a);
    double fraction = a - integer;
    // pad integer.
    vector<int> byte_container(16,0);
    for(int i = 7; i >= 0; i--)
    {
        byte_container[i] = integer & 1;
        integer >>= 1;
    }
    // pad fraction.
    for(int i = 8; i <= 15; i++)
    {
        fraction *= 2;
        if(fraction >= 1)
        {
            fraction -= 1;
            byte_container[i] = 1;
        }
        else
            byte_container[i] = 0;
    }
    return byte_container;
}

/**
 * @brief 在这里将整数转换成为16位整数+16位小数。
 * @param a:浮点数。
 */
vector<int> __float2byte_32(double &a)
{
    int integer = floor(a);
    double fraction = a - integer;
    // pad integer.
    vector<int> byte_container(32,0);
    for(int i = 15; i >= 0; i--)
    {
        byte_container[i] = integer & 1;
        integer >>= 1;
    }
    // pad fraction.
    for(int i = 16; i <= 31; i++)
    {
        fraction *= 2;
        if(fraction >= 1)
        {
            fraction -= 1;
            byte_container[i] = 1;
        }
        else
            byte_container[i] = 0;
    }
    return byte_container;
}

/**
 * @brief 在这里将整数转换成为18位整数+16位小数。
 * @param a:浮点数。
 */
vector<int> __float2byte_34(double &a)
{
    int integer = floor(a);
    double fraction = a - integer;
    // pad integer.
    vector<int> byte_container(34,0);
    for(int i = 17; i >= 0; i--)
    {
        byte_container[i] = integer & 1;
        integer >>= 1;
    }
    // pad fraction.
    for(int i = 18; i <= 33; i++)
    {
        fraction *= 2;
        if(fraction >= 1)
        {
            fraction -= 1;
            byte_container[i] = 1;
        }
        else
            byte_container[i] = 0;
    }
    return byte_container;
}


/**
 * @brief 对外使用接口。
 * @param a: 需要进行转换的浮点数。
 * @param length: 需要的长度。
 */
vector<int> float2byte(double a, int length)
{
    switch(length)
    {
        case 16: return __float2byte_16(a);
        case 32: return __float2byte_32(a);
        case 34: return __float2byte_34(a);
        default: 
            std::cerr << "No fixed length provided!" << std::endl;
            exit(-1);
    }
}
