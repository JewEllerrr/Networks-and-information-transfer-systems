#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <list>
using namespace std;

void coder_decoder(vector<bool> g, size_t k, vector<bool> e, vector<bool> m);
vector<bool> division(vector<bool> c, vector<bool> h);
vector<bool> check_sum(vector<bool> m, vector<bool> g);
int vector_weight(vector<bool> v);
int deg(vector<bool> g);
vector<bool> rand_arr(size_t k);
vector<bool> rand_arr(size_t k, size_t w);
vector<bool> vector_a(vector<bool> m, vector<bool> c);
vector<bool> vector_b(vector<bool> a, vector<bool> e);
bool sindrom(vector<bool> b, vector<bool> g);

vector<bool> Print(int* ar, int n);
void dop(vector<bool> g, vector<bool> m, vector<vector<bool>> e, size_t d, size_t k_l);
bool NextSet(int* ar, int n, int m);
vector<vector<bool>> error_book(int size);
