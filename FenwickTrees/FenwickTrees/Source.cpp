#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

class FenwickTree{
	vi ft;

public:
	FenwickTree(){}
	FenwickTree(int n){ ft.assign(n + 1, 0); }
	int LSOne(int n){
		return n & (-n);
	}
	void init(int n){ ft.assign(n + 1, 0); }
	int rsq(int b){
		int sum = 0; for (; b; b -= LSOne(b)) sum += ft[b];
		return sum;
	}
	int rsq(int a, int b){
		return rsq(b) - (a <= 1 ? 0 : rsq(a));
	}
	void adjust(int k, int v){
		for (; k <= ft.size(); k += LSOne(k)) ft[k] += v;
	}
	int smallestIndex(int cf){
		for (int k = 1; k < ft.size(); k++) if (rsq(k) >= cf) return k;
		return -1;
	}
};

class FloatFenwickTree : public FenwickTree{
	void adjust(double k, int v){
		k = k * 100;
		adjust((int)k, v);
	}
};
int main(){
	int f[] = { 2, 4, 5, 5, 6, 6, 6, 7, 7, 8, 9 }; // m = 11 scores
	FenwickTree ft(10); // declare a Fenwick Tree for range [1..10]
	// insert these scores manually one by one into an empty Fenwick Tree
	for (int i = 0; i < 11; i++) ft.adjust(f[i], 1); // this is O(k log n)
	printf("%d\n", ft.rsq(1, 1)); // 0 => ft[1] = 0
	printf("%d\n", ft.rsq(1, 2)); // 1 => ft[2] = 1
	printf("%d\n", ft.rsq(1, 6)); // 7 => ft[6] + ft[4] = 5 + 2 = 7
	printf("%d\n", ft.rsq(1, 10)); // 11 => ft[10] + ft[8] = 1 + 10 = 11
	printf("%d\n", ft.rsq(3, 6)); // 6 => rsq(1, 6) - rsq(1, 2) = 7 - 1
	ft.adjust(5, 2); // update demo
	printf("%d\n", ft.rsq(1, 10)); // now 13
	printf("%d\n", ft.smallestIndex(7));
	return 0;
}