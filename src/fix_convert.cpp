#include<iostream>
#include<vector>
#include<cmath>
#include<cstdint>
#define LL long long
using namespace std;

/**
 * @brief 在这里将整数转换成为八位整数+八位小数。
 * @param a:浮点数
 * @return byte_container,16bits.
 */
vector<int> __float2byte_16(double a)
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
 * @return byte_container,32bits.
 */
vector<int> __float2byte_32(double a)
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
 * @brief 在这里将整数转换成为17位整数+16位小数。
 * @param a:浮点数。
 * @return byte_container,32bits.
 */
vector<int> __float2byte_33(double a)
{
    int integer = floor(a);
    double fraction = a - integer;
    // pad integer.
    vector<int> byte_container(33,0);
    for(int i = 16; i >= 0; i--)
    {
        byte_container[i] = integer & 1;
        integer >>= 1;
    }
    // pad fraction.
    for(int i = 17; i <= 32; i++)
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
 * @return byte_container, 34bits
 */
vector<int> __float2byte_34(double a)
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
 * @brief 在这里将整数转换成为18位整数+16位小数。
 * @param a:浮点数。
 * @return byte_container, 34bits
 */
vector<int> __float2byte_35(double a)
{
    int integer = floor(a);
    double fraction = a - integer;
    // pad integer.
    vector<int> byte_container(35,0);
    for(int i = 18; i >= 0; i--)
    {
        byte_container[i] = integer & 1;
        integer >>= 1;
    }
    // pad fraction.
    for(int i = 19; i <= 34; i++)
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
 * @brief 在这里将整数转换成为三十二位位整数+三十二位小数。
 * @param a:浮点数
 * @return byte_container,64bits.
 */
vector<int> __float2byte_64(double a)
{
    int integer = floor(a);
    double fraction = a - integer;
    // pad integer.
    vector<int> byte_container(64,0);
    for(int i = 31; i >= 0; i--)
    {
        byte_container[i] = integer & 1;
        integer >>= 1;
    }
    // pad fraction.
    for(int i = 32; i <= 63; i++)
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
 * @brief 将16位byteContainer转换成浮点数。
 * @param a:bytecontainer.
 * @return 转换成的浮点数。
 */
double __byte2float_16(vector<int> &a)
{
    int integer = 0;
    double fraction = 0;
    // The integer part.
    for(int i = 7; i >= 0; i--)
    {
        integer += (a[i] == 1) ? 1 << (7-i) : 0;
    }
    // The fraction part.
    double mask = 1.0;
    for(int i = 8; i <= 15; i++)
    {
        mask /= 2.0;
        fraction += (a[i]==1) ? mask : 0;
    }
    double ans = integer + fraction;
    return ans;
}

/**
 * @brief 将32位byteContainer转换成浮点数。
 * @param a:bytecontainer.
 * @return 转换成的浮点数。
 */
double __byte2float_32(vector<int> &a)
{
    int integer = 0;
    double fraction = 0;
    // The integer part.
    for(int i = 15; i >= 0; i--)
    {
        integer += (a[i] == 1) ? 1 << (15-i) : 0;
    }
    // The fraction part.
    double mask = 1.0;
    for(int i = 16; i <= 31; i++)
    {
        mask /= 2.0;
        fraction += (a[i]==1) ? mask : 0;
    }
    double ans = integer + fraction;
    return ans;
}

/**
 * @brief 将33位byteContainer转换成浮点数。
 * @param a:bytecontainer.
 * @return 转换成的浮点数。
 */
double __byte2float_33(vector<int> &a)
{
    int integer = 0;
    double fraction = 0;
    // The integer part.
    for(int i = 16; i >= 0; i--)
    {
        integer += (a[i] == 1) ? 1 << (16-i) : 0;
    }
    // The fraction part.
    double mask = 1.0;
    for(int i = 17; i <= 32; i++)
    {
        mask /= 2.0;
        fraction += (a[i]==1) ? mask : 0;
    }
    double ans = integer + fraction;
    return ans;
}

/**
 * @brief 将34位byteContainer转换成浮点数。
 * @param a:bytecontainer.
 * @return 转换成的浮点数。
 */
double __byte2float_34(vector<int> &a)
{
    int integer = 0;
    double fraction = 0;
    // The integer part.
    for(int i = 17; i >= 0; i--)
    {
        integer += (a[i] == 1) ? 1 << (17-i) : 0;
    }
    // The fraction part.
    double mask = 1.0;
    for(int i = 18; i <= 33; i++)
    {
        mask /= 2.0;
        fraction += (a[i]==1) ? mask : 0;
    }
    double ans = integer + fraction;
    return ans;
}

/**
 * @brief 将34位byteContainer转换成浮点数。
 * @param a:bytecontainer.
 * @return 转换成的浮点数。
 */
double __byte2float_35(vector<int> &a)
{
    int integer = 0;
    double fraction = 0;
    // The integer part.
    for(int i = 18; i >= 0; i--)
    {
        integer += (a[i] == 1) ? 1 << (17-i) : 0;
    }
    // The fraction part.
    double mask = 1.0;
    for(int i = 19; i <= 34; i++)
    {
        mask /= 2.0;
        fraction += (a[i]==1) ? mask : 0;
    }
    double ans = integer + fraction;
    return ans;
}

/**
 * @brief 将34位byteContainer转换成浮点数。
 * @param a:bytecontainer.
 * @return 转换成的浮点数。
 */
double __byte2float_64(vector<int> &a)
{
    int integer = 0;
    double fraction = 0;
    // The integer part.
    for(int i = 31; i >= 0; i--)
    {
        integer += (a[i] == 1) ? 1 << (17-i) : 0;
    }
    // The fraction part.
    double mask = 1.0;
    for(int i = 32; i <= 63; i++)
    {
        mask /= 2.0;
        fraction += (a[i]==1) ? mask : 0;
    }
    double ans = integer + fraction;
    return ans;
}


/**
 * @brief 对外使用接口。
 * @param a: 需要进行转换的浮点数。
 * @param length: 需要的长度。
 * @return 一定长度的byte_container, 16/32/33/34/35/64bits.
 */
vector<int> float2byte(double a, int length)
{
    switch(length)
    {
        case 16: return __float2byte_16(a);
        case 32: return __float2byte_32(a);
        case 33: return __float2byte_33(a);
        case 34: return __float2byte_34(a);
        case 35: return __float2byte_35(a);
        case 64: return __float2byte_64(a);
        default: 
            std::cerr << "No fixed length provided!\n";
            exit(-1);
    }
}

/**
 * @brief 对外使用转换接口。通过长度大小自动识别长度。
 * @param a: 需要进行转换的byteContainer.
 * @return 转换成的浮点数。
 */
double byte2float(vector<int> a)
{
    switch(a.size())
    {
        case 16: return __byte2float_16(a);
        case 32: return __byte2float_32(a);
        case 33: return __byte2float_33(a);
        case 34: return __byte2float_34(a);
        case 35: return __byte2float_35(a);
        case 64: return __byte2float_64(a);
        default: 
            std::cerr << "No fixed length container provided!\n";
            exit(-1);
    }
}

/**
 * @brief 将矩阵转换成固定的浮点数。
 * @param a: (ref), 直接进行原地修改。
 * @param length: byteContainer长度。
 */
vector<vector<double> > matrix2fix(vector<vector<double> > &a, int length)
{
    vector<vector<double> > ans(a.size(), vector<double>(a[0].size(),0));
    try
    {
        if(!a.size() || !a[0].size())
            throw "Error! vector is empty.\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    for(size_t i = 0; i < a.size(); i++)
    {
        for (size_t j = 0; j < a[0].size(); j++)
        {
            ans[i][j] = byte2float(float2byte(a[i][j], length));
        }
    }
    return ans;
}