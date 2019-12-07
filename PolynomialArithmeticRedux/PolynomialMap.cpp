#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

class Polynomial {
public:
    map<int, int> polynomial;
    
public:

    //Checks to see if it was already indexed and if true then adds the coefficient to the value
    bool indexed(int coefficient, int power) {
        map<int, int>::iterator iterator = polynomial.find(power);
        if (iterator != polynomial.end()) {
            iterator->second += coefficient;
            return true;
        }
        return false;
    }

    // Checks if the variables have been mapped
    void mapVariables(int coefficient, int power) {
        if (!(indexed(coefficient, power))) {
            polynomial[power] = {coefficient};
        }
    }

    //Adds the first polynomial to the second one which will naturally happen by the indexed method if it hasn't been mapped already
    Polynomial &operator+(const Polynomial &other) {
        Polynomial *sum = new Polynomial();
        for (auto i: this->polynomial) {
            sum->mapVariables(i.second, i.first);
        }
        for (auto j: other.polynomial) {
            sum->mapVariables(j.second, j.first);
        }
        return *sum;
    }

    //This does the same thing except multiples the second value (coefficient) by -1 then adds the polynomials together
    Polynomial &operator-(const Polynomial &other) {
        Polynomial *difference = new Polynomial();
        for (auto i: this->polynomial) {
            difference->mapVariables(i.second, i.first);
        }
        for (auto j: other.polynomial) {
            difference->mapVariables((-1 * j.second), j.first);
        }
        return *difference;
    }

    //Multiples the coefficients together then adds the power then checks if the variables have been mapped
    Polynomial &operator*(const Polynomial &other) {
        Polynomial *product = new Polynomial();
        for (auto i: this->polynomial) {
            for (auto j: other.polynomial) {
                product->mapVariables((i.second * j.second), (i.first + j.first));
            }
        }
        return *product;
    }
};

int main() {
    
    Polynomial polynomials[2], sum, difference, product;
    ifstream in("input.txt");
    ofstream myFile;
    myFile.open("output.txt");
    
    string line;
    int count = 0, coefficient, power;
    while (getline(in, line)) {
        stringstream ss(line);
        while (ss >> coefficient >> power) {
            cout << coefficient << "," <<  power << "   ";
            polynomials[count].mapVariables(coefficient,power);
        }
        cout << "\n";
        count++;
    }
    in.close();
    
    myFile << "First polynomial: \n\n";
    
    map<int, int>::iterator it;
    for (it = polynomials[0].polynomial.begin(); it != polynomials[0].polynomial.end(); ++it) {
        if (it->second != 0) {
            if (it == polynomials[0].polynomial.begin()) {
                myFile << it->second << "^" << it->first;
            } else if (it->second < 0) {
                myFile << " - " << (it->second * -1) << "^" << it->first;
            } else {
                myFile << " + " << it->second << "^" << it->first;
            }
        }
    }
    
    myFile << "\n\nSecond polynomial: \n\n";
    
    for (it = polynomials[1].polynomial.begin(); it != polynomials[1].polynomial.end(); ++it) {
        if (it->second != 0) {
            if (it == polynomials[1].polynomial.begin()) {
                myFile << it->second << "^" << it->first;
            } else if (it->second < 0) {
                myFile << " - " << (it->second * -1) << "^" << it->first;
            } else {
                myFile << " + " << it->second << "^" << it->first;
            }
        }
    }
    
    myFile << "\n\nFirst canonical polynomial: \n\n";   
    
    map<int, int>::reverse_iterator rit;
    for (rit = polynomials[0].polynomial.rbegin(); rit != polynomials[0].polynomial.rend(); ++rit) {
        if (rit->second != 0) {
            if (rit == polynomials[0].polynomial.rbegin()) {
                myFile << rit->second << "^" << rit->first;
            } else if (rit->second < 0) {
                myFile << " - " << (rit->second * -1) << "^" << rit->first;
            } else {
                myFile << " + " << rit->second << "^" << rit->first;
            }
        }
    }
    
    myFile << "\n\nSecond canonical polynomial: \n\n";
    
    for (rit = polynomials[1].polynomial.rbegin(); rit != polynomials[1].polynomial.rend(); ++rit) {
        if (rit->second != 0) {
            if (rit == polynomials[1].polynomial.rbegin()) {
                myFile << rit->second << "^" << rit->first;
            } else if (rit->second < 0) {
                myFile << " - " << (rit->second * -1) << "^" << rit->first;
            } else {
                myFile << " + " << rit->second << "^" << rit->first;
            }
        }
    }
    
    sum=polynomials[0]+polynomials[1];
    myFile << "\n\nSum: \n\n";
    
    for (rit = sum.polynomial.rbegin(); rit != sum.polynomial.rend(); ++rit) {
        if (rit->second != 0) {
            if (rit == sum.polynomial.rbegin()) {
                myFile << rit->second << "^" << rit->first;
            } else if (rit->second < 0) {
                myFile << " - " << (rit->second * -1) << "^" << rit->first;
            } else {
                myFile << " + " << rit->second << "^" << rit->first;
            }
        }
    }
    
    myFile << "\n\nDifference: \n\n";
    difference=polynomials[0]-polynomials[1];

    for (rit = difference.polynomial.rbegin(); rit != difference.polynomial.rend(); ++rit) {
        if (rit->second != 0) {
            if (rit == difference.polynomial.rbegin()) {
                myFile << rit->second << "^" << rit->first;
            } else if (rit->second < 0) {
                myFile << " - " << (rit->second * -1) << "^" << rit->first;
            } else {
                myFile << " + " << rit->second << "^" << rit->first;
            }
        }
    }
    
    myFile << "\n\nProduct: \n\n";
    product=polynomials[0]*polynomials[1];
    
    for (rit = product.polynomial.rbegin(); rit != product.polynomial.rend(); ++rit) {
        if (rit->second != 0) {
            if (rit == product.polynomial.rbegin()) {
                myFile << rit->second << "^" << rit->first;
            } else if (rit->second < 0) {
                myFile << " - " << (rit->second * -1) << "^" << rit->first;
            } else {
                myFile << " + " << rit->second << "^" << rit->first;
            }
        }
    }
    
    return 0;
}
