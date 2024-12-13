#include<iostream>
#include<vector>
#include<random>
#include<ctime>
using namespace std;

/**
 * @brief 生成随机Query矩阵，格式为8*4.
 * @param low: 左半闭区间。
 * @param high:右半开区间。
 * @return 一个随机生成Query矩阵。
 */
vector<vector<double> > random_query(double low, double high)
{
    std::default_random_engine engine(1234);
    std::uniform_real_distribution<double> generator(low, high);

    vector<vector<double> > query(8,vector<double>(4,0));
    for (size_t i = 0; i < query.size(); i++)
    {
        for(size_t j = 0; j < query[i].size(); j++)
            query[i][j] = generator(engine);
    }
    return query;
}

/**
 * @brief 生成随机Key矩阵，格式为4*8.
 * @param low: 左半闭区间。
 * @param high:右半开区间。
 * @return 一个随机生成Key矩阵。
 */
vector<vector<double> > random_key(double low, double high)
{
    std::default_random_engine engine(2345);
    std::uniform_real_distribution<double> generator(low, high);

    vector<vector<double> > key(4,vector<double>(8,0));
    for (size_t i = 0; i < key.size(); i++)
    {
        for(size_t j = 0; j < key[i].size(); j++)
            key[i][j] = generator(engine);
    }
    return key;
}

/**
 * @brief 生成随机Value矩阵，格式为8*4.
 * @param low: 左半闭区间。
 * @param high:右半开区间。
 * @return 一个随机生成Value矩阵。
 */
vector<vector<double> > random_value(double low, double high)
{
    std::default_random_engine engine(3456);
    std::uniform_real_distribution<double> generator(low, high);

    vector<vector<double> > value(8,vector<double>(4,0));
    for (size_t i = 0; i < value.size(); i++)
    {
        for(size_t j = 0; j < value[i].size(); j++)
            value[i][j] = generator(engine);
    }
    return value;
}

/**
 * @brief 生成随机矩阵，对外接口。
 * @param low: 左半闭区间。
 * @param high:右半开区间。
 * @param type: 1 - Q矩阵。 2 - K矩阵。 3 - V矩阵。
 * @return 一个随机生成矩阵。
 */
vector<vector<double> > random_generate(double low, double high, int type)
{
    switch(type)
    {
        case 1:
            /* Query Matrix */
            return random_query(low, high);
        case 2:
            /* Key Matrix */
            return random_key(low, high);
        case 3:
            /* Value Matrix */
            return random_value(low, high);
        default:
            std::cerr << "Error! Invalid type!\n";
            exit(-1);
    }
}