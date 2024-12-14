#include<iostream>
#include<vector>

using namespace std;

/**
 * @brief 输出vector。
 * @param 等待输出向量。
 */
ostream & operator << (ostream& os, vector<vector<double> > &v)
{
    size_t rows,cols;
    if(v.size() == 0)
        cols = 0;
    else
        cols = v[0].size();
    rows = v.size();

    os << "The size of vector:(" << rows << ',' << cols << ").\n";
    os << '[';
    for(size_t i = 0; i < rows; i++)
    {
        os << '[';
        for(size_t j = 0; j < cols; j++)
        {
            if (j == cols-1)
                os << v[i][j] << ']';
            else
                os << v[i][j] << ", ";
        }
        if (i == rows-1)
            os << "]\n";
        else
            os << ",\n ";
    }
    return os;
}

ostream & operator << (ostream& os, vector<vector<int> > &v)
{
    size_t rows,cols;
    if(v.size() == 0)
        cols = 0;
    else
        cols = v[0].size();
    rows = v.size();

    os << "The size of vector:(" << rows << ',' << cols << ").\n";
    os << '[';
    for(size_t i = 0; i < rows; i++)
    {
        os << '[';
        for(size_t j = 0; j < cols; j++)
        {
            if (j == cols-1)
                os << v[i][j] << ']';
            else
                os << v[i][j] << ", ";
        }
        if (i == rows-1)
            os << "]\n";
        else
            os << ",\n ";
    }
    return os;
}


ostream & operator << (ostream& os, vector<double> &v)
{
    os << "The length of the vector:" << v.size() << '\n';
    os << '[' ;
    for(size_t i = 0; i < v.size(); i++)
    {
        if(i == v.size()-1)
            os << v[i];
        else
            os << v[i] << ", ";
    }
    os << "]\n";
    os << "In compact output:\n";
    for(size_t i = 0; i < v.size(); i++)
    {
        os << v[i];
        if ((i+1) % 4==0)
            os << ' ';
    }
    os << '\n';
    return os;
}

ostream & operator << (ostream& os, vector<int> &v)
{
    os << "The length of the vector:" << v.size() << '\n';
    os << '[' ;
    for(size_t i = 0; i < v.size(); i++)
    {
        if(i == v.size()-1)
            os << v[i];
        else
            os << v[i] << ", ";
    }
    os << "]\n";
    os << "In compact output:\n";
    for(size_t i = 0; i < v.size(); i++)
    {
        os << v[i];
        if ((i+1) % 4==0)
            os << ' ';
    }
    os << '\n';
    return os;
}