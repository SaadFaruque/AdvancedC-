#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;

class SA {
	private:
		int low, high;
		int* p;
		
	public:
		SA() {
			low = 0;
			high = -1;
			p = NULL;
		}
		
		SA(int l, int h) {
			if ((h-1+1)<=0) {
				cout << "Constructor error in bounds definition" << endl;
				exit(1);
			}
			low = l;
			high = h;
			p = new int[h-l+1];
		}
		
		SA(int i) {
			low = 0;
			high = i-1;
			p = new int[i];
		}
		
		SA(const SA &s) {
			int size = s.high - s.low + 1;
			p = new int[size];
			for (int i=0; i<size ; i++)
				p[i] = s.p[i];
			low = s.low;
			high = s.high;
		}
		
		~SA() {
			delete[] p;
		}
		
		int& operator [](int i) {
			if (i<low || i>high) {
				cout << "Index " << i << " out of range" << endl;
				exit(1);
			}
			return p[i-low];
		}
		
		SA& operator =(const SA& s) {
			if (this == &s)
				return *this;
			delete[] p;
			int size = s.high - s.low + 1;
			p = new int[size];
			for (int i=0 ; i<size ; i++)
				p[i] = s.p[i];
			low = s.low;
			high = s.high;
			return *this;
		}
		
		int getlow() {
			return low;
		}
		
		int gethigh() {
			return high;
		}
		
		friend ostream& operator <<(ostream& os, SA& s);
};

ostream& operator <<(ostream& os, SA& s) {
	int size = s.high - s.low + 1;
	for (int i=0 ; i<size ; i++)
		os << "[" << s.p[i] << "]";
	cout << endl;
	return os;
}

void sort(SA &s) {
	int low = s.getlow();
	int high = s.gethigh();
	for (int i = low; i < high; i++) {
		for (int j = low ; j < high; j++) {
			if (s[j] > s[j + 1]) {
				int temp;
				temp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = temp;
			}	
		}
	}
}

int main() {
    
	SA a(10), b(3,5);
	b[3] = 5; b[4] = 4; b[5] = 3;
	for (int i = 0 ; i < 10; i++) a[i] = 10-i;
	
    cout << "Unsorted A" << endl;
    
    cout << a << endl;
    
    cout << "Unsorted B" << endl;
    
    cout << b << endl;
    
    sort(a);
    sort(b);
    
	cout << "A sorted\n";
	cout << a << endl;
	cout << "B sorted\n";
	cout << b;
}
