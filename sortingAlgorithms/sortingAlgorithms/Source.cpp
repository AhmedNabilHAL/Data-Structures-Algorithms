#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class NumList {
private:
	vector<int> list;
public:

	// constructor that takes an array of numbers
	NumList(int *arr, int len){
		for (int i = 0; i < len; i++) list.push_back(arr[i]);
	}
	NumList(const vector<int>& vect){
		list = vect;
	}
	// prints the array
	void print()
	{
		cout << "Before: "; for (int n : list) cout << n << ' ';
		cout << endl;
	}

	// Insertion Sort
	// Time: O(n^2)
	// Space: O(1), in place
	vector<int> insertionSort(){
		vector<int> ret = list;
		for (int i = 1; i < ret.size(); ++i){
			int tmp = ret[i]; int j;
			for (j = i; j > 0 && tmp < ret[j - 1]; --j) swap(ret[j], ret[j - 1]);
			ret[j] = tmp;
		}
		return ret;
	}

	// Selection Sort
	// Time: O(n^2)
	// Space: O(1), in place
	vector<int> selectionSort(){
		vector<int> ret = list;
		for (int i = 0; i < ret.size(); ++i){
			int minidx = i;
			for (int j = i + 1; j < ret.size(); ++j) if (ret[j] < ret[minidx]) minidx = j;
			swap(ret[i], ret[minidx]);
		}
		return ret;
	}

	// Shell Sort
	// Time: O(n^2), theta(n^3/2)
	// Space: O(1), in place
	vector<int> shellSort(){
		vector<int> ret = list;
		for (int gap = ret.size() / 2; gap > 0; gap /= 2){
			for (int i = gap; i < ret.size(); ++i){
				int tmp = ret[i]; int j;
				for (j = i; j >= gap && tmp < ret[j - gap]; j -= gap) swap(ret[j], ret[j - gap]);
				ret[j] = tmp;
			}
		}
		return ret;
	}

	void merge(vector<int>& ret, int st, int m, int en){
		vector<int> L, R;
		int mid = m;

		for (int i = st; i <= mid; ++i) L.push_back(ret[i]);
		for (int i = mid + 1; i <= en; ++i) R.push_back(ret[i]);

		int k = st, le = 0, ri = 0;
		while (le < L.size() && ri < R.size()){
			if (L[le] < R[ri]) ret[k] = L[le++];
			else ret[k] = R[ri++];
			k++;
		}
		while (le < L.size()) ret[k++] = L[le++];
		while (ri < R.size()) ret[k++] = R[ri++];
	}

	// Merge Sort
	// Time: O(n*lg(n))
	// Space: O(n)
	vector<int> mergeSort(){
		vector<int> ret = list;
		
		for (int subsz = 1; subsz <= list.size(); subsz *= 2){
			for (int left_start = 0; left_start < list.size(); left_start += 2 * subsz)
			{
				// Find ending point of left subarray. mid+1 is starting  
				// point of right 
				int mid = min(left_start + subsz - 1, (int)list.size() - 1);

				int right_end = min(left_start + 2 * subsz - 1, (int)list.size() - 1);

				// Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end] 
				merge(ret, left_start, mid, right_end);
			}
		}
		
		return ret;
	}
	int partition(vector<int>& ret, int le, int ri){
		int x = ret[le];
		int i = le;
		for (int j = le + 1; j <= ri; ++j){
			if (ret[j] < x){
				++i;
				swap(ret[j], ret[i]);
			}
		}
		swap(ret[le], ret[i]);
		return i;
	}
	void quickSort(vector<int>& ret, int le, int ri){
		if (le >= ri) return;
		int mid = partition(ret, le, ri);
		quickSort(ret, le, mid - 1);
		quickSort(ret, mid + 1, ri);
		
	}
	vector<int> quickSort(){
		vector<int> ret = list;
		quickSort(ret, 0, list.size() - 1);
		return ret;
	}

	vector<int> countSort(){
		vector<int> ret(list.size()), count; int mx = 0, min = 0; for (int i = 0; i < list.size(); ++i) if (list[i] > mx) mx = list[i]; else if (list[i] < min) min = list[i];
		count.assign(-min + mx + 1, 0);

		for (int n : list) count[n + -min]++;
		for (int i = 1; i < count.size(); ++i) count[i] = count[i] + count[i - 1];
		for (int i = list.size() - 1; i >= 0; --i) ret[--count[list[i] + -min]] = list[i];
		return ret;
	}

	// adds a num to end of the array
	void append(int n){
		list.push_back(n);
	}

};

int main()
{
	vector<int> vect{ 10, 8, 7, 7, 3, 2, 1, 0, -100 };
	NumList list(vect);
	list.print();

	vect = list.insertionSort();
	for (int n : vect) cout << n << ' ';
	cout << endl;

	vect = list.selectionSort();
	for (int n : vect) cout << n << ' ';
	cout << endl;

	vect = list.shellSort();
	for (int n : vect) cout << n << ' ';
	cout << endl;
	
	vect = list.mergeSort();
	for (int n : vect) cout << n << ' ';
	cout << endl;

	vect = list.quickSort();
	for (int n : vect) cout << n << ' ';
	cout << endl;

	vect = list.countSort();
	for (int n : vect) cout << n << ' ';
	cout << endl;

	return 0;
}