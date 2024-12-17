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

    output(query_fix, std::string("query"));
    cout << "\n" << query_fix << "\n";
    output(key_fix, std::string("key"));
    cout << "\n" << key_fix << "\n";
    output(value_fix, std::string("value"));
    cout << "\n" << value_fix << "\n"; 
    return 0;
}