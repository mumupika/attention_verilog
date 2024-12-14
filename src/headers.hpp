#ifndef HEADERS_H_
#define HEADERS_H_
using namespace std;
#include "vector_ops.hpp"

// #include "data_generator.cpp"
vector<vector<double> > random_query(double low, double high);
vector<vector<double> > random_key(double low, double high);
vector<vector<double> > random_value(double low, double high);
vector<vector<double> > random_generate(double low, double high, int type);

// #include "fix_convert.cpp"
vector<int> __float2byte_16(double a);
vector<int> __float2byte_32(double a);
vector<int> __float2byte_33(double a);
vector<int> __float2byte_34(double a);
vector<int> __float2byte_64(double a);
double __byte2float_16(vector<int> &a);
double __byte2float_32(vector<int> &a);
double __byte2float_33(vector<int> &a);
double __byte2float_34(vector<int> &a);
double __byte2float_64(vector<int> &a);
vector<int> float2byte(double a, int length);
double byte2float(vector<int> a);
vector<vector<double> > matrix2fix(vector<vector<double> > &a, int length);

// #include "matrix_multiply.cpp"
vector<vector<double> > matrix_fix_multiplication(vector<vector<double> > &v1, vector<vector<double> > &v2);

vector<vector<double> > matrix_multiplication(vector<vector<double> > &v1, vector<vector<double> > &v2);

// #include "matrix_output.cpp"
ostream & operator << (ostream& os, vector<vector<double> > &v);
ostream & operator << (ostream& os, vector<vector<int> > &v);

ostream & operator << (ostream& os, vector<double> &v);
ostream & operator << (ostream& os, vector<int> &v);

// #include "softmax.cpp"
vector<vector<double> > softmax(vector<vector<double> > &a);
#endif