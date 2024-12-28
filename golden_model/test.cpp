#include<iostream>
#include<vector>
#include<random>
#include<fstream>

#include "src/headers.hpp"

using namespace std;
int main()
{
    system("clear");
    // ofstream file("test.txt");

    std::default_random_engine engine(2048);
    std::uniform_real_distribution<double> generator(0, 255);

    // file << "*** Test matrix_multiply. ***\n";
    
    vector<vector<double> > query = random_query(0, 5, 1);
    vector<vector<double> > key = random_key(0, 5, 2);
    vector<vector<double> > value = random_value(0, 5, 3);
    
    vector<vector<double> > query_fix = matrix2fix(query, 16);
    vector<vector<double> > key_fix = matrix2fix(key, 16);
    vector<vector<double> > value_fix = matrix2fix(value, 16);

    output_transpose(query_fix, std::string("query"),16);
    cout << "\n" << query_fix << "\n";
    output_4(key_fix, std::string("key"),16);
    cout << "\n" << key_fix << "\n";
    output(value_fix, std::string("value"),16);
    cout << "\n" << value_fix << "\n"; 

    vector<vector<double> > attn_fix = matrix_fix_multiplication(key_fix,query_fix);
    output(attn_fix, std::string("attention block"),34);
    cout << "\n" << attn_fix << "\n";

    vector<vector<double> > attn_quant = quantify_matrix(attn_fix, 1, 34);
    output(attn_quant, std::string("attention quant"), 16);
    cout << "\n" << attn_quant << "\n";
    return 0;
}