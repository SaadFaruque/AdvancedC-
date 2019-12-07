//Project 1
#include<iostream>
#include<cstdlib> 
#include<cassert> 
using namespace std;

template <class T> //forward declaration
ostream& operator<<(ostream& os, SA<T> s);

template <class T> class SA {
	private:
	int low, high;
	T* p;
	
	public:
	
	// default constructor
	// allows for writing things like SA a;
	SA(){low = 0; high = -1;p = NULL;}
	
	// 2 parameter constructor lets us write
	// SA x(10,20);
	SA(int l, int h) {
        if((h - l + 1) <= 0) {
            cout << "constructor error in bounds definition" << endl;
            exit(1);
        }
        low = l;
        high = h;
        p = new T[h - l + 1];
	}
	
	// single parameter constructor lets us
	// create a SA almost like a "standard" one by writing
	// SA x(10); and getting an array x indexed from 0 to 9
	SA(int i){low = 0; high = i - 1; p = new T[i];}
	// copy constructor for pass by value and
	// initialization
	SA(const SA & s){
        int size = s.high - s.low + 1;
        p = new T[size];
        for(int i = 0; i < size; i++)
            p[i] = s.p[i];
        low = s.low;
        high = s.high;
	}
	
	// destructor
	~SA(){
        delete [] p;
	}
	
	//overloaded [] lets us write
	//SA x(10,20); x[15]= 100;
	T& operator[](int i) {
        if(i < low || i > high) {
            cout << "index "<< i <<" out of range" << endl;
            exit(1);
        }
        return p[i - low];
	}
	
	// overloaded assignment lets us assign
	// one SA to another
	SA & operator=(const SA s) {
        if(this == &s) return *this;
        delete [] p;
        int size = s.high - s.low + 1;
        p = new T[size];
        for(int i = 0; i < size; i++)
            p[i] = s.p[i];
        low = s.low;
        high = s.high;
        return *this;
	}
	
	// overloads << so we can directly print SAs
	//template <class T>
	friend ostream& operator<< <T> (ostream& os, SA<T> s);
};
	
template <class T> ostream& operator<<(ostream& os, SA<T> s) {
    int size = s.high - s.low+1;
    for(int i = 0; i < size; i++)
    cout << s.p[i] << endl;
    return os;
}; 

//Matrix class
template<class M> class Matrix {
        
    SA<M>** matrix;
    int row, col, rowL, colL;
    
    public:
        Matrix() {
            row = 1;
            col = 1;
            rowL = 0;
            colL = 0;
            // allocates space with 1 object to it's address
            matrix = new SA<M>*[1];
            for (int i = 0; i < 1; i++) {
                matrix[i] = new SA<M>;
            }
        }
    
        //2 param for 2D array
        Matrix(int r, int c, int rl, int cl) {
            row = r;
            col = c;
            rowL = rl;
            colL = cl;
            
            //allocates space with r amount of objects to their address
            matrix = new SA<M>*[r];
            for(int i = 0; i < r; i++){
                // makes c amount of objects
                matrix[i] = new SA<M>(c);
            }
        }
        // gets the index of the array
        SA<M> &operator[](int i) {
            return *matrix[i];
        }
        
        Matrix<M> operator*(Matrix<M> a) {
                
            if (row != a.col || col != a.row) {
                cout << "Can't perform Matrix multiplication!" << endl;
            }
            Matrix<M> newMatrix(row, row, rowL, rowL);
            
            int sum = 0;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    int sum = 0;
                    for (int k = 0; k < col; k++) {
                        int temp = (*this)[i][k];
                        sum += temp *(a[k][j]);
                    }
                    newMatrix[i][j] = sum;
                }
            }
            return newMatrix;
        }
        void printMatrix(){
		
            for(int i = rowL; i < row; i++){
                for(int j = colL; j < col; j++){
                    cout << " " << (*this)[i][j];
                }
                cout << endl;
            }
            cout << endl;
        }
};

int main() {
    
    int *a = new int[4];
    int *b = new int[4];
    
    cout << "Enter rows, columns, row bounds and column bounds for matrix A" << endl;
    for (int i = 0; i < 4; i++) {
        cin >> a[i];
    }
    
    cout << "Enter rows, columns, row bounds and column bounds for Matrix A" << endl;
    
    for (int i = 0; i < 4; i++) {
        cin >> b[i];
    }
    
    Matrix<int> A(a[0], a[1], a[2], a[3]);
    Matrix<int> B(b[0], b[1], b[2], b[3]);
    Matrix<int> C;
    
    cout << "Enter values of Matrix A: " << endl;
	for (int i = 0; i < a[0]; i++){
		for (int j = 0; j < a[1]; j++) {
            cin >> A[i][j];
		}
	}
	
	cout << "Enter values of Matrix B: " << endl;
	for (int i = 0; i < b[0]; i++){
		for (int j = 0; j < b[1]; j++){
			cin >> B[i][j];
		}	
	}
	
	delete [] a;
    delete [] b;
	
    C =	A*B;
	
    cout << "Displaying Matrices" << endl << endl;
    
	A.printMatrix();
	B.printMatrix();
    C.printMatrix();

    return 0;
}
