#include<iostream>
#include<vector>
#include<random>
#include<fstream>

#include "src/headers.hpp"

using namespace std;
int main(int argc, char *argv[])
{
    system("clear");
    int query_seed = 1;
    int key_seed = 2;
    int value_seed = 3;
    if(argc < 2)
    {
        cout << "Using default seed: query=1, key=2, value=3;\n\n";
    }
    else if(argc == 2)
    {
        cout << "Input with one seed. So using query=<input>, key=query+1, value=query+2;\n\n";
        query_seed = atoi(argv[1]);
        key_seed = query_seed + 1;
        value_seed = key_seed + 1;
    }
    else if(argc == 4)
    {
        query_seed = atoi(argv[1]);
        key_seed = atoi(argv[2]);
        value_seed = atoi(argv[3]);
        cout << "using seed: key: " << key_seed << " query: " << query_seed << " value: " << value_seed << "\n\n";
    }
    ofstream key_file("../attention/datas/key.txt");
    ofstream query_file("../attention/datas/query.txt");
    ofstream value_file("../attention/datas/value.txt");
    ofstream ground_truth("../attention/datas/attention_test.txt");

    std::default_random_engine engine(2048);
    std::uniform_real_distribution<double> generator(0, 255);

    // file << "*** Test matrix_multiply. ***\n";
    
    vector<vector<double> > query = random_query(0, 2, query_seed);
    vector<vector<double> > key = random_key(0, 2, key_seed);
    vector<vector<double> > value = random_value(0, 2, value_seed);
    
    vector<vector<double> > query_fix = matrix2fix(query, 16);
    vector<vector<double> > key_fix = matrix2fix(key, 16);
    vector<vector<double> > value_fix = matrix2fix(value, 16);

    vector<vector<vector<int> > > value_container = matrix2container(value_fix, 16);

    output_transpose_4(query_fix, std::string("query"),16,std::cout);
    output_transpose_4(query_fix, std::string("query"),16,query_file);
    output_4(key_fix, std::string("key"),16,std::cout);
    output_4(key_fix, std::string("key"),16,key_file);

    vector<vector<vector<int> > > attn_fix = matrix_fix_multiplication_container(key_fix,query_fix);
    output_pure(attn_fix, std::string("attention block"),std::cout);

    vector<vector<vector<int> > > attn_quant = quantify_matrix_container(attn_fix, 1);
    output_pure(attn_quant, std::string("attention quant"),std::cout);

    vector<vector<vector<int> > > softmaxed = softmax_fixed_container(attn_quant);
    output_pure(softmaxed, std::string("softmax"),std::cout);
    

    vector<vector<vector<int> > > soft_quant = quantify_matrix_container(softmaxed,1);
    output_pure(soft_quant, std::string("soft quant"),std::cout);

    output(value_fix, std::string("value"),16,std::cout);
    output(value_fix, std::string("value"),16,value_file);


    vector<vector<vector<int> > > second_fix = matrix_fix_multiplication_container(value_container,soft_quant);
    output_pure_transpose_4(second_fix, std::string("second output"), std::cout);

    vector<vector<vector<int> > > final_output = quantify_matrix_container(second_fix,1);
    output_pure_transpose_4(final_output, std::string("final output"), std::cout);
    output_pure_transpose_4(final_output, std::string("final output"), ground_truth);
    return 0;
}