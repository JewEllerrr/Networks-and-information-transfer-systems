#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <list>
using namespace std;

void coder_decoder(vector<bool> g, size_t k, vector<bool> e, vector<bool> m);
vector<bool> division(vector<bool> c, vector<bool> h);
vector<bool> check_sum(vector<bool> m, size_t r_size, vector<bool> g);
int vector_weight(vector<bool> v);
int deg(vector<bool> g);
vector<bool> rand_arr(size_t k);
vector<bool> rand_arr(size_t k, size_t w);
vector<bool> vector_a(vector<bool> m, vector<bool> c);
vector<bool> vector_b(vector<bool> a, vector<bool> e);
bool sindrom(vector<bool> b, vector<bool> g);

// все что связано с допом
vector<bool> Print(int* ar, int n);
void dop(vector<bool> g, vector<bool> m, vector<vector<bool>> e, size_t d);
bool NextSet(int* ar, int n, int m);
vector<vector<bool>> error_book(int size);
//

void coder_decoder(vector<bool> g, size_t k, vector<bool> e, vector<bool> m)
{
	for (int l = 0; l < m.size(); l++)
		cout << m[l] << ' ';
	cout << " - sended message m" << endl;

	cout << k << " - the number of information symbols of the sended message m (k)" << endl;
	
	for (int l = 0; l < g.size(); l++)
		cout << g[l] << ' ';
	cout << " - vector of the generating polynomial (g)" << endl;
	int r_size = deg(g);
	cout << r_size << " - degree of the generating polynomial (deg(g) = r)" << endl;
	vector<bool> c = check_sum(m, r_size, g); // контрольная сумма
	for (int l = 0; l < c.size(); l++)
		cout << c[l] << ' ';
	cout << " - check sum" << endl;
	vector<bool> a = vector_a(m, c);
	for (int l = 0; l < a.size(); l++)
		cout << a[l] << ' ';
	cout << " - vector a" << endl;

	for (int l = 0; l < e.size(); l++)
		cout << e[l] << ' ';
	cout << " - error vector" << endl;

	vector<bool> b = vector_b(a, e);
	for (int l = 0; l < b.size(); l++)
		cout << b[l] << ' ';
	cout << " - vector b (a+e)" << endl;
	if (sindrom(b, g))
		cout << "There were errors (E = 1) \n";
	else 
		cout << "No errors (E = 0) \n";
}

bool sindrom(vector<bool> b, vector<bool> g) 
{
	vector<bool> res = division(b, g);

	for (int i = 0; i < res.size(); i++)
		if (res[i] == 1) return true;
	
	return false;
}

vector<bool> vector_a(vector<bool> m, vector<bool> c)
{

	for (int i = 0; i < c.size(); i++)
		m.push_back(c[i]);

	return m;
}

vector<bool> vector_b(vector<bool> a, vector<bool> e) 
{
	if (e.size() < a.size())
		throw runtime_error("vector_size(e) < vector_size(a) \n");

	else
		for (int i = 0; i < a.size(); i++)
			a[i] = a[i] ^ e[i];

	return a;
}

vector<bool> check_sum(vector<bool> m, size_t r_size, vector<bool> g)
{
	vector<bool> c = m;
	vector<bool> res;

	for (int i = 0; i < r_size; i++) 
		c.push_back(0);

	c = division(c, g);

	/*for (int l = 0; l < c.size(); l++)
		cout << c[l] << ' ';
	cout << " - ccccccccccc" << endl;*/

	// размер вектора с должен быть равен deg(m)
	for (int i = 0; i < deg(g); i++)
		res.push_back(c[c.size() - i - 1]);

	reverse(res.begin(), res.end());

	return res;
}

vector<bool> division(vector<bool> c, vector<bool> h) 
{
	bool div = true;
	vector<bool> g;
	if (c.size() < h.size() && vector_weight(c) < vector_weight(h))
		return c;

	for (int i = 0; i < c.size() - h.size(); i++)
		g.push_back(0);

	for (int i = 0; i < h.size(); i++)
		g.push_back(h[i]);
	
	while (div)
	{
		int i, j = 0;
		for (i = 0; i < c.size(); i++)
			if (c[i] == 1) break;
		
		for (j = 0; j < g.size(); j++)
			if (g[j] == true) break;
	
		if (i > j)
			break;
		
		for (int k = j; k < g.size(); k++)
		{
			c[i] = c[i] ^ g[j];
			i++;
			j++;
		}
		i = 0;
		j = 0;
	}
	return c;
}

int vector_weight(vector<bool> v) 
{
	int res = 0;

	for (int i = 0; i < v.size(); i++)
		if (v[i] == 1) res++;	

	return res;
}

int deg(vector<bool> g) 
{
	int size_r = 0;

	for (int i = 0; i < g.size(); i++) 
	{
		if (g[i] == 1) 
		{
			size_r = g.size() - i - 1;
			break;
		}
	}
	return size_r;
}

vector<bool> rand_arr(size_t k)
{
	vector<bool> m;
	bool num;

	for (int i = 0; i < k; i++) 
	{
		num = rand() % 2;
		m.push_back(num);
	}
	return m;
}

vector<bool> rand_arr(size_t k, size_t w)
{
	vector<bool> e;
	if (k == w) 
	{
		for (int i = 0; i < k; i++)
			e.push_back(1);
	
		return e;
	}
	bool num;
	int count = 0;
	for (int i = 0; i < k; i++) 
	{
		num = rand() % 2;
		if (num == 1)
			count++;
		if (num == 1 && count <= w)
			e.push_back(num);
		else e.push_back(0);
	}
	while (count != w) 
	{
		for (int i = 0; i < k; i++) 
		{
			if (e[i] == 0) 
			{
				e[i] = 1;
				count++;
				break;
			}
		}
	}
	return e;
}
// 4 функции для допа
void dop(vector<bool> g, vector<bool> m, vector<vector<bool>> e, size_t d)
{
	//все тоже самое как в основе
	for (int l = 0; l < m.size(); l++)
		cout << m[l] << ' ';
	cout << " - sended message m" << endl;

	for (int l = 0; l < g.size(); l++)
		cout << g[l] << ' ';
	cout << " - vector of the generating polynomial (g)" << endl;
	int r_size = deg(g);
	cout << r_size << " - degree of the generating polynomial (deg(g) = r)" << endl;
	vector<bool> c = check_sum(m, r_size, g); // контрольная сумма
	for (int l = 0; l < c.size(); l++)
		cout << c[l] << ' ';
	cout << " - check sum" << endl;
	vector<bool> a = vector_a(m, c);
	for (int l = 0; l < a.size(); l++)
		cout << a[l] << ' ';
	cout << " - vector a" << endl;
	// dop принимает error book e и проверяет условия задания
	cout << "No errors (E = 0) and w(e) <= d-1, if:" << endl;
	for (int i = 0; i < e.size(); i++)
	{
		vector<bool> b = vector_b(a, e[i]);
		if (!sindrom(b, g) && vector_weight(e[i]) <= d-1)
		{
			cout << "e = ";
			for (int l = 0; l < e[i].size(); l++)
				cout << e[i][l] << ' ';
			cout << endl;
		}

	}
}
bool NextSet(int* ar, int n, int m)
{
	int j = m - 1;
	while (j >= 0 && ar[j] == n) j--;
	if (j < 0) return false;
	if (ar[j] >= n)
		j--;
	ar[j]++;
	if (j == m - 1) return true;
	for (int k = j + 1; k < m; k++)
		ar[k] = 0;
	return true;
}
vector<bool> Print(int* ar, int n)
{
	// если убрать комменты, можно увидеть всю книгу ошибок (формула размещения с повторениями)
	vector<bool> err_v;
	static int num = 1;
	//cout.width(3);
	//cout << num++ << ":  ";
	for (int i = 0; i < n; i++) 
	{
		//cout << ar[i] << " ";
		err_v.push_back(ar[i]);
	}
	//cout << endl;
	return err_v;
}
vector<vector<bool>> error_book(int size)
{
	vector<vector<bool>> er;
	int n = 1;
	int mm = size;
	int h = n > mm ? n : mm;
	int* ar;
	ar = new int[h];
	for (int i = 0; i < h; i++)
		ar[i] = 0;
	er.push_back(Print(ar, mm));
	while (NextSet(ar, n, mm))
		er.push_back(Print(ar, mm));
	return er;
}

int main()
{
	//srand(time(NULL));
	//vector<bool> g = { 1,0,1,1 }; //порождающий многочлен
	//int k = 4; //число информационных символов передаваемого сообщения m
	//vector<bool> e = { 1,1,0,1,0,0,1 }; // вектор ошибки
	//vector<bool> m = { 1,1,0,1 };
	////vector<bool> m = rand_arr(k); //информационная последовательность из l бит(l может быть как меньше, так и больше k)

	srand(time(NULL));
	vector<bool> g = { 1,1,0,1 }; //порождающий многочлен
	size_t k = 4; //число информационных символов передаваемого сообщения m
	size_t l = 2;
	k += l;
	size_t d = 4; //расстояние хэмминга
	vector<bool> e = { 0,0,1,1,0,1,0 }; // вектор ошибки
	vector<bool> m = { 1,0,1,0 };
	//vector<bool> m = rand_arr(k); //информационная последовательность из l бит(l может быть как меньше, так и больше k)
	vector<vector<bool>> er = error_book(k+deg(g));
	dop(g, m, er, d);
	//coder_decoder(g, k, e, m);



	return 0;
}