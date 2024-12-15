#ifndef HEADERS_H_
#define HEADERS_H_
using namespace std;

// #include "data_generator.cpp"
vector<vector<double> > random_query(double low, double high, int seed);
vector<vector<double> > random_key(double low, double high, int seed);
vector<vector<double> > random_value(double low, double high, int seed);
vector<vector<double> > random_generate(double low, double high, int type, int seed);

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
vector<vector<double> > softmax_fixed(vector<vector<double> > &a);
vector<vector<double> > softmax_standard(vector<vector<double> > &a);

// #include "vector_ops.cpp"
vector<int> vec_mul(vector<int> &a, vector<int> &b);
vector<int> vec_add(vector<int> &a, vector<int> &b, int length);
vector<int> vec_minus(vector<int> &a, vector<int> &b, int length);

// #include "quantify.cpp"
vector<int> vec_truncate(vector<int> &a);
vector<int> vec_round(vector<int> &a);
vector<int> vec_sat(vector<int> &a);
vector<int> vec_wrap(vector<int> &a);
vector<vector<double> > quantify_matrix(vector<vector<double > > &a, int strategy, int fix_point);
#endif