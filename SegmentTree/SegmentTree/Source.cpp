#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>

using namespace std;
typedef  long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

const int N = 1048576 + 6, M = 1e9 + 7, OO = 0x3f3f3f3f;
class SegmentTree{
private:
	vi A, st;
	int n;
	int left(int p){ return p << 1; }
	int right(int p){ return (p << 1) + 1; }
	void build(int p, int L, int R){ // O(n)
		if (L == R){ // if range is one element then it is the min for this range
			st[p] = L; 
			return;
		}
		build(left(p), L, (L + R) / 2); // build left subtree
		build(right(p), (L + R) / 2 + 1, R); // build right subtree

		int p1 = st[left(p)], p2 = st[right(p)]; // store values of my two childs
		st[p] = (A[p1] <= A[p2] ? p1 : p2); // assign to me the one with min value in the original array
	}

	int rmq(int p, int L, int R, int i, int j){
		if (R < i || L > j) return -1; // return -1 if outside of range
		if (L >= i && R <= j) return st[p]; // return the stored value if you are inside the range

		int p1 = rmq(left(p), L, (L + R) / 2, i, j); // get RMQ for the left and right childs
		int p2 = rmq(right(p), (L + R) / 2 + 1, R, i, j); 
		if (p1 == -1) return p2;  // if one child was outside the range return the other
		if (p2 == -1) return p1;
		return (A[p1] <= A[p2] ? p1 : p2); // if both were inside return the minimum one
	}
	void update(int p, int L, int R, int idx, int val){
		if (L == R){ // if idx is found update and return
			A[idx] = val;
			return;
		}
		
		
		if (idx <= (L + R) / 2) update(left(p), L, (L + R) / 2, idx, val); // update left
		else update(right(p), (L + R) / 2 + 1, R, idx, val); // update right

		int p1 = st[left(p)]; // store values of left & right subtree one of them may change (only one)
		int p2 = st[right(p)];
		st[p] = (A[p1] <= A[p2] ? p1 : p2); // my value is the minimum of the two values
	}
public:
	SegmentTree(const vi &_A) {
		A = _A; n = (int)A.size(); // copy content for local usage
		st.assign(4 * n, 0); // create large enough vector of zeroes
		build(1, 0, n - 1); // recursive build
	}
	int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }
	void update(int idx, int val){ update(1, 0, n - 1, idx, val); }
};
class Pirates{
	int n; vi A, st, lazy;

	int left(int p){ return p << 1; }
	int right(int p){ return (p << 1) + 1; }
	void build(int p, int L, int R){
		if (L > R) return;
		if (L == R) {
			st[p] = A[L];
			return;
		}
		build(left(p), L, (L + R) / 2);
		build(right(p), (L + R) / 2 + 1, R);

		st[p] = st[left(p)] + st[right(p)];
	}
	int rsq(int p, int L, int R, int i, int j){
		if (L > R) return 0;

		if (lazy[p] != -1){ // if there is a postponed update do it now
			if (lazy[p] == 0)
				st[p] = 0;
			else if (lazy[p] == 1)
				st[p] = (R - L + 1);
			else
				st[p] = (R - L + 1) - st[p];
			if (L != R){ // set the lazy flags for children
				if (lazy[p] == 2){
					if (lazy[left(p)] == -1) lazy[left(p)] = 2;
					else if (lazy[left(p)] == 0) lazy[left(p)] = 1;
					else if (lazy[left(p)] == 2) lazy[left(p)] = -1;
					else lazy[left(p)] = 0;

					if (lazy[right(p)] == -1) lazy[right(p)] = 2;
					else if (lazy[right(p)] == 0) lazy[right(p)] = 1;
					else if (lazy[right(p)] == 2) lazy[right(p)] = -1;
					else lazy[right(p)] = 0;
				}
				else{
					lazy[left(p)] = lazy[p]; // set lazy of left & right child to the same postponed operation
					lazy[right(p)] = lazy[p];
				}
			}
			lazy[p] = -1; // no postponed update for node p
		}

		if (L > j || R < i) return 0; // return 0 if out of range
		if (L >= i && R <= j) return st[p]; // return the ans if in range

		int p1 = rsq(left(p), L, (L + R) / 2, i, j); // get the ans from left & right childs
		int p2 = rsq(right(p), (L + R) / 2 + 1, R, i, j);
		return p1 + p2;
	}
	void update(int p, int L, int R, int i, int j, int op){
		if (L > R) return;

		if (lazy[p] != -1){ // if there is a postponed update do it now
			if (lazy[p] == 0)
				st[p] = 0;
			else if (lazy[p] == 1)
				st[p] = (R - L + 1);
			else
				st[p] = (R - L + 1) - st[p];
			if (L != R){ // set the lazy flags for children
				if (lazy[p] == 2){
					if (lazy[left(p)] == -1) lazy[left(p)] = 2;
					else if (lazy[left(p)] == 0) lazy[left(p)] = 1;
					else if (lazy[left(p)] == 2) lazy[left(p)] = -1;
					else lazy[left(p)] = 0;

					if (lazy[right(p)] == -1) lazy[right(p)] = 2;
					else if (lazy[right(p)] == 0) lazy[right(p)] = 1;
					else if (lazy[right(p)] == 2) lazy[right(p)] = -1;
					else lazy[right(p)] = 0;
				}
				else{
					lazy[left(p)] = lazy[p]; // set lazy of left & right child to the same postponed operation
					lazy[right(p)] = lazy[p];
				}
			}
			lazy[p] = -1; // no postponed update for node p
		}

		if (L > j || R < i) return; // return if out of range


		if (L >= i && R <= j){ // if completely inside the range update yourself
			if (op == 0)
				st[p] = 0;
			else if (op == 1)
				st[p] = (R - L + 1);
			else
				st[p] = (R - L + 1) - st[p];
			if (L != R){ // set the lazy flags for children
				if (op == 2){
					if (lazy[left(p)] == -1) lazy[left(p)] = 2;
					else if (lazy[left(p)] == 0) lazy[left(p)] = 1;
					else if (lazy[left(p)] == 2) lazy[left(p)] = -1;
					else lazy[left(p)] = 0;

					if (lazy[right(p)] == -1) lazy[right(p)] = 2;
					else if (lazy[right(p)] == 0) lazy[right(p)] = 1;
					else if (lazy[right(p)] == 2) lazy[right(p)] = -1;
					else lazy[right(p)] = 0;
				}
				else{
					lazy[left(p)] = op; // set lazy of left & right child to the same postponed operation
					lazy[right(p)] = op;
				}
			}
			return;
		}

		update(left(p), L, (L + R) / 2, i, j, op); // recurse to update left & right
		update(right(p), (L + R) / 2 + 1, R, i, j, op);
		st[p] = st[left(p)] + st[right(p)]; // recalculate this node using the left & right nodes
	}
public:
	Pirates(const vi& _A){
		A = _A; n = (int)_A.size();
		st.assign(4 * n, 0); lazy.assign(4 * n, -1);
		build(1, 0, n - 1);
	}
	int rsq(int i, int j){ return rsq(1, 0, n - 1, i, j); }
	void update(int i, int j, int op){ update(1, 0, n - 1, i, j, op); }
};
int T, m, t, q; vi pirates;
char str[N];
int main() {
	scanf("%d", &T);
	for (int c = 1; c <= T; ++c){
		pirates.clear();
		scanf("%d", &m);
		for (int i = 0; i < m; ++i){
			scanf("%d", &t);
			scanf("%s", str);
			
			for (int i = 0; i < t; ++i) for (int j = 0; str[j]; ++j) pirates.push_back(str[j] - '0');
		}
		scanf("%d", &q);
		Pirates p(pirates);
		printf("Case %d:\n", c);
		int qs = 1;
		while (q--){
			char op; int a, b; scanf("\n%c %d %d", &op, &a, &b);
			if (op ==  'F') p.update(a, b, 1);
			else if (op == 'E') p.update(a, b, 0);
			else if (op == 'I') p.update(a, b, 2);
			else if (op == 'S') printf("Q%d: %d\n", qs++, p.rsq(a, b));
		}
	}
	return 0;
}