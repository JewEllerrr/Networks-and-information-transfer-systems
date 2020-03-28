#include "Header.h"
using namespace std;

/**
 * The program generates a codeword (vector a). 
 * Based on this codeword and the error vector, a sequence (vector b) is generated at the channel output.
 * According to the adopted sequence, a decision is made about the presence of errors in the channel.
 * @param g - vector of the generating polynomial
 * @param k - the number of information symbols of the sended message m
 * @param e - error vector
 * @param m - informational sequence (the length of the vector can be either less or more than k)
 */
void coder_decoder(vector<bool> g, size_t k, vector<bool> e, vector<bool> m)
{
	for (int l = 0; l < m.size(); l++)
		cout << m[l] << ' ';
	cout << " - sended message m" << endl;

	cout << k << " the number of information symbols of the sended message m (k)" << endl;
	
	for (int l = 0; l < g.size(); l++)
		cout << g[l] << ' ';
	cout << " - vector of the generating polynomial (g)" << endl;

	cout << deg(g) << " - degree of the generating polynomial (deg(g) = r)" << endl;
	vector<bool> c = check_sum(m, g);
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
	cout << " - vector b (a + e)" << endl;
	if (sindrom(b, g))
		cout << "There were errors (E = 1) \n";
	else 
		cout << "No errors (E = 0) \n";
}

/**
 * @param b - vector b (a + e)
 * @param g - vector of the generating polynomial
 * @return true - the decoder decides that errors have occurred (E = 1)
 * @return false - the decoder decides that there was no error (E = 0)
 */
bool sindrom(vector<bool> b, vector<bool> g) 
{
	vector<bool> res = division(b, g);
	// check from the end
	for (int i = res.size() - 1; i >= 0; i--)
		if (res[i] == 1) return true;
	
	return false;
}

/**
 * @param m - informational sequence (the length of the vector can be either less or more than k)
 * @param c - check sum (the length of this vector = deg(g(x)))
 * @return vector a <=> a(x) = m(x)*x^r + c(x)
 */
vector<bool> vector_a(vector<bool> m, vector<bool> c)
{
	for (int i = 0; i < c.size(); i++)
		m.push_back(c[i]);

	return m;
}

/**
 * @param a - codeword
 * @param e - error vector
 * @return vector b - received message (a + e)
 */
vector<bool> vector_b(vector<bool> a, vector<bool> e) 
{
	if (e.size() != a.size())
		throw runtime_error("vector_size(e) < vector_size(a) \n");
	else
		for (int i = 0; i < a.size(); i++)
			a[i] = a[i] ^ e[i];

	return a;
}

/**
 * @param m - informational sequence (the length of the vector can be either less or more than k)
 * @param g - vector of the generating polynomial
 * @return check sum - c(x) = m(x)x^r mod g(x), the degree of the polynomial c(x) is less than or equal to r − 1
 */
vector<bool> check_sum(vector<bool> m, vector<bool> g)
{
	vector<bool> c = m;
	vector<bool> res;

	for (int i = 0; i < deg(g); i++)
		c.push_back(0);

	c = division(c, g);

	// the size of the vector c must be equal to deg(g) 
	// for example if result of division 01 but deg(g) = 4, then next code make it to 0001)
	for (int i = 0; i < deg(g); i++)
		res.push_back(c[c.size() - i - 1]);

	reverse(res.begin(), res.end());

	return res;
}

/**
 * Modulo division
 * @param v - binary vector (polynomial)
 * @param h - binary vector (polynomial)
 * @return binary vector (polynomial) - remainder of the division
 */
vector<bool> division(vector<bool> v, vector<bool> h) 
{
	vector<bool> g;
	if (v.size() < h.size() && vector_weight(v) < vector_weight(h))
		return v;

	// need vectors of the same size
	// for example: v = 1101; h = 01 -> vector h becomes 0001
	for (int i = 0; i < v.size() - h.size(); i++)
		g.push_back(0);

	for (int i = 0; i < h.size(); i++)
		g.push_back(h[i]);
	
	while (true)
	{
		int i, j = 0;
		for (i = 0; i < v.size(); i++)
			if (v[i] == 1) break;
		
		for (j = 0; j < g.size(); j++)
			if (g[j] == 1) break;
	
		if (i > j)
			break;
		
		for (int k = j; k < g.size(); k++)
		{
			v[i] = v[i] ^ g[j];
			i++;
			j++;
		}
		i = 0;
		j = 0;
	}
	return v;
}

/**
 * @param v - binary vector
 * @return vector weight - for the case of binary vectors weight is equal to the number of units in the vector
 */
int vector_weight(vector<bool> v) 
{
	int res = 0;

	for (int i = 0; i < v.size(); i++)
		if (v[i] == 1) res++;	

	return res;
}

/**
 * @param v - binary vector (polynomial)
 * @return polynomial degree
 */
int deg(vector<bool> v) 
{
	int size_r = 0;

	for (int i = 0; i < v.size(); i++) 
	{
		if (v[i] == 1) 
		{
			size_r = v.size() - i - 1;
			break;
		}
	}
	return size_r;
}

/**
 * @param k - the number of information symbols of the sended message m
 * @return random size k binary vector
 */
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

/**
 * @param k - the number of information symbols of the sended message m
 * @param w - for the case of binary vectors weight is equal to the number of units in the vector
 * @return random size k binary vector with w number of units in it
 */
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

/**
 * Checking the operation of the encoder/decoder for the vector g with parameters n, k and d,
 * when the incorrect number of information symbols k + l was selected.
 * @param g - vector of the generating polynomial
 * @param m - informational sequence (the length of the vector can be either less or more than k)
 * @param e - error vector
 * @param d - hamming distance
 * @param k_l - the extended number of information symbols of the sended message m
 * @return All possible error vectors for w(e) <= d-1 and errors are not detected.
 */
void dop(vector<bool> g, vector<bool> m, vector<vector<bool>> e, size_t d, size_t k_l)
{
	if (m.size() < k_l)
	{
		reverse(m.begin(), m.end());
		while (m.size() < k_l)
			m.push_back(0);
		reverse(m.begin(), m.end());
	}

	for (int l = 0; l < m.size(); l++)
		cout << m[l] << ' ';
	cout << " - sended message m" << endl;

	for (int l = 0; l < g.size(); l++)
		cout << g[l] << ' ';
	cout << " - vector of the generating polynomial (g)" << endl;

	cout << deg(g) << " - degree of the generating polynomial (deg(g) = r)" << endl;

	vector<bool> c = check_sum(m, g);
	for (int l = 0; l < c.size(); l++)
		cout << c[l] << ' ';
	cout << " - check sum" << endl;

	vector<bool> a = vector_a(m, c);
	for (int l = 0; l < a.size(); l++)
		cout << a[l] << ' ';
	cout << " - vector a" << endl;

	// takes error book and checks conditions
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

/**
 * @param *ar - array
 * @param m = 2
 * @param n - length of array
 * @return next set of placements
 */
bool NextSet(int* ar, int m, int n)
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

/**
 * @param *ar - array
 * @param n - array length
 * @return error vector
 */
vector<bool> Print(int* ar, int n)
{
	//without comments, you can see the entire error book (placement with repetitions)
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

/**
 * @param size - size of error vector
 * @return error book - all placements with repetitions of a binary vector of length k
 */
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
	while (NextSet(ar, mm, n))
		er.push_back(Print(ar, mm));
	return er;
}

int main()
{
	srand(time(NULL));
	//vector<bool> g = { 1,0,1,0,1 };
	vector<bool> g = { 1,0,1,1 };
	//vector<bool> e = { 0,0,1,0,1,1,0 };
	//vector<bool> e = { 0,0,1,1,0,1,0,1 };
	vector<bool> m = { 1,0,1,1 };
	//vector<bool> m = { 1,0,1,0 };
	size_t k = m.size();
	size_t d = 3;
	//coder_decoder(g, k, e, m);
	//cout << endl << endl;
	size_t l = 6; // for additional task
	k += l;
	vector<vector<bool>> er = error_book(k + deg(g));
	dop(g, m, er, d, k);

	return 0;
}
