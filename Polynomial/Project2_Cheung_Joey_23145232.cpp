#include <iostream>
#include <fstream>
#include <string> 
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <memory>

using namespace std; 

//global variables
ifstream inputFile;
ofstream outputFile;

class Node {
private:
    friend class PolynomialList; 
public:
    int exponent;
    int coefficient;
    string var;
    char op;
    Node* n;
    //overload operator = uses l-values
    Node& operator=(const Node &rhs) = default;
    //regular constructor
    Node() {
        this->coefficient = 0;
        this->exponent = 0;
        this->var = " ";
        this->op = ' ';
        this->n = nullptr;
    }

    //Move Constructor
    Node(Node &&source) {
        n = new Node();
        n = source.n; 
        source.n = nullptr;
    } 
    
    //Deep copy constructor
    Node(const Node &source) {
        n = new Node();
        n = source.n;

        cout<<"Copy constructor- Deep - data copy: " << n <<endl;
    }
};

class PolynomialList {
public:
    Node *front = new Node();

    //regular constructor
PolynomialList() {
    front->n = nullptr;
}

//Deep copy constructor
PolynomialList(const PolynomialList &source) {
    front = new Node; //allocate storage
    *front = *source.front;

    cout << "Copy constructor-Deep- data copy: " << front->n <<endl; 
}

//method for calculation
void outputPolynomial() {
    Node *current;
    current = this->front;
    while(current->n != nullptr) {
        outputFile <<current->n->coefficient << current->n->var << "^" <<
        current->n->exponent<<endl;
        current = current->n;
    }
}

void calculate() {
    Node *current = this->front;
    Node *previous = this->front; 

	while (current != nullptr) {
        previous = current;
        current = current->n;//so it skips the dummy
        if (current->n == nullptr)break; 
        if (current->exponent == current->n->exponent && current->var == current->n->var) {
            Node *temp;
            temp = current->n;
            current->coefficient = current->coefficient + current->n->coefficient;
            previous->n = current;
            current->n = current->n->n;
            delete temp;
        }
    }
    outputPolynomial();
}

void separate(char* arr, int n) {
    int counter {0};
    char op {' '};
    int c {0};
    char v {' '};
    char e {' '};

    for(int i = 0; i < n; counter = i) {
         op = ' ';
         c = 0;
         v = ' ';
         e = ' ';

        if(arr[i] == '+' || arr[i] == '-') {
            op = arr[i];
            counter++;
        }

        switch(arr[i]) {
            case '+':
                for(counter; counter < n; counter++) {
                    switch(arr[counter]) {
                        case '^':
                            e = arr[counter + 1] - '0';
                            counter++;
                            break;
                        case 'x':
                            v = arr[counter];
                            break; 
                        case '+':
                            goto add_node;
                            break;
                        case '-':
                            goto add_node;
                            break;
                        default:
                            if(isdigit(arr[counter])) {   
                                int result = 0; 
                                for(counter; arr[counter] != '\0'; counter++) {
                                    if(arr[counter] == '+' || arr[counter] == '-' || arr[counter] == 'x')break; 
                                    result +=  atoi(&arr[counter]);
                                }
                                if(arr[counter] == 'x' && arr[counter + 1] == '^') {
                                    v = arr[counter]; 
                                }
                                else if(arr[counter] == 'x' && arr[counter + 1] != '^') {
                                    v = arr[counter];
                                    e = 1; 
                                }
                                else if(arr[counter] != 'x') {
                                    v = 0;
                                    e = 0;
                                }

                                c = result;
                                if(arr[counter] == '+' || arr[counter] == '-')
                                    goto add_node;
                            }  
                            break;
                    }
                }
            case '-':
                for(counter; counter < n; counter++) {
                    switch(arr[counter]) {   
                        case '^':
                            e = arr[counter + 1] - '0';
                            counter++;
                            break;

                        case 'x':
                            v = arr[counter];
                            break; 

                        case '+':
                            goto add_node;
                            break;
                        
                        case '-':
                            goto add_node;
                            break;

                        default:
                            if(isdigit(arr[counter])) {
                                int result = 0; 

                                for(counter; arr[counter] != '\0'; counter++) {
                                    if(arr[counter] == '+' || arr[counter] == '-' || arr[counter] == 'x')break;
                                    result += atoi(&arr[counter]); 
                                }
                                if(arr[counter] == 'x' && arr[counter + 1] == '^') {
                                    v = arr[counter]; 
                                }
                                else if(arr[counter] == 'x' && arr[counter + 1] != '^') {
                                    v = arr[counter];
                                    e = 1; 
                                }
                                else if(arr[counter] != 'x') {
                                    v = 0;
                                    e = 0;
                                }

                                c = result;
                                if(arr[counter] == '+' || arr[counter] == '-')
                                    goto add_node;
                            }
                            break; 
                    }
                }
            default:
                break;
        }
        add_node:
        build(c, v, e, op);
        i = counter; 
    }
        //send list
        calculate();
    }
void build(int c, char v, char e, char op) {
    Node *current = this->front; 
    Node* newNode = new Node; 

    if (c == 0) {
        c = 1; 
    }
    if(op == '-') {
        c = -(c);
    }
    if(op == '+') {
        c = +(c);
    }

    newNode->coefficient = c;
    newNode->var = v;
    newNode->exponent = e;
    newNode->op = op; 

    if(current->n == nullptr) {
        current->n = newNode;
        newNode->n = nullptr; 
        return;
    }
    else {
        while(current->n != nullptr) {
            if(newNode->exponent >= current->n->exponent) {
                Node* temp;
                temp = current->n;
                current->n = newNode;
                newNode->n = temp; 
                break;
            }
            else if(current->n == nullptr) {
                current->n = newNode;
                newNode->n = nullptr; 
                break;
            }
            
            current = current->n;// pointing to the next one
        }
    }
    return;
}

void load(int n) {
    char* arr = new char[n]; 
    char a;

    for(int i = 0; i < n; i++) {
        inputFile >> a;
        arr[i] = a;  
    }

    separate(arr, n);
}

};

int main(int argc, char *argv[]) {
    PolynomialList obj;
    int n = 32;//length of poly
    inputFile.open(argv[1]);
    outputFile.open(argv[2]);

    if(inputFile.is_open()) {
        obj.load(n);
    }
    else {
        cerr<<"Could not open file" <<endl;
        return 1;
    }
    
    inputFile.close(); 
    outputFile.close();
}
