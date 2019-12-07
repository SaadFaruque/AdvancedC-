#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

class InvertedIndex {
private:
    map<string, pair<int, vector<int>>> index;
public:

    void add(string s, int row, int col) {
        bool indexOrNot = false;
        map<std::string, std::pair<int, vector<int>>>::iterator i = index.find(s);
        
        if (i != index.end()) {
            i->second.first += 1;
            i->second.second.push_back(row);
            i->second.second.push_back(col);
            indexOrNot = true;
        }
        
        if (!indexOrNot) index[s] = {1, {row, col}};
    }
    
    void print() {
        int count = 0;
        for (auto i: index) {
            cout << i.first << " " << i.second.first<<"[";
            
            for (auto j: i.second.second) {
                
                if (count % 2 == 1) {
                    cout << j << ")";
                    count++;
                }
                
                else if (count % 2 == 0) {
                    cout << "(" << j << ",";
                    count++;
                } 
            }
            cout << "]" << endl << endl;
            count = 0;
        }
    }
};

int main(int argc, char *argv[]) {
    InvertedIndex i;
    int count = 1;
    size_t col;
    string w;
    ifstream in(argv[1]);
    string l;
    if (in) {
        while (getline(in, l)) {
            stringstream ss(l);
            while (ss >> w) {
                col = l.find(w);
                for (int i = 0; i < w.length(); i++) {
                    if (w[i] == ',' || w[i] == '.') {
                        w.erase(w.begin() + i);
                    }
                }
                i.add(w, count, int(col));
            }
            count += 1;
        }
    }
    in.close();
    i.print();
    return 0;
}
