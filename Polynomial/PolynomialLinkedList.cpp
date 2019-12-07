#include<iostream>
#include <fstream>
#include <sstream>
#include<vector>
#include<algorithm>
using namespace std;

struct Node {
    int coefficient, power;
    struct Node* next;
};

void create_node(int x, int y, struct Node **temp) { 
    struct Node *r, *z; 
    z = *temp; 
    if(z == NULL) { 
        r =(struct Node*)malloc(sizeof(struct Node)); 
        r->coefficient = x; 
        r->power = y; 
        *temp = r; 
        r->next = (struct Node*)malloc(sizeof(struct Node)); 
        r = r->next; 
        r->next = NULL; 
    } 
    else { 
        r->coefficient = x; 
        r->power = y; 
        r->next = (struct Node*)malloc(sizeof(struct Node)); 
        r = r->next; 
        r->next = NULL; 
    } 
} 

void polyadd(struct Node *poly1, struct Node *poly2, struct Node *poly) {
    while(poly1->next && poly2->next) { 
        // If power of 1st polynomial is greater then 2nd, then store 1st as it is 
        // and move its pointer 
        if(poly1->power > poly2->power) { 
            poly->power = poly1->power; 
            poly->coefficient = poly1->coefficient; 
            poly1 = poly1->next; 
        } 
          
        // If power of 2nd polynomial is greater then 1st, then store 2nd as it is 
        // and move its pointer 
        else if(poly1->power < poly2->power) { 
            poly->power = poly2->power; 
            poly->coefficient = poly2->coefficient; 
            poly2 = poly2->next; 
        } 
          
        // If power of both polynomial numbers is same then add their coefficients 
        else { 
            poly->power = poly1->power; 
            poly->coefficient = poly1->coefficient + poly2->coefficient; 
            poly1 = poly1->next; 
            poly2 = poly2->next; 
        } 
          
        // Dynamically create new node 
        poly->next = (struct Node *)malloc(sizeof(struct Node)); 
        poly = poly->next; 
        poly->next = NULL; 
    } 
    while(poly1->next || poly2->next) { 
        if(poly1->next) { 
            poly->power = poly1->power; 
            poly->coefficient = poly1->coefficient; 
            poly1 = poly1->next; 
        } 
        if(poly2->next) { 
            poly->power = poly2->power; 
            poly->coefficient = poly2->coefficient; 
            poly2 = poly2->next; 
        } 
        poly->next = (struct Node *)malloc(sizeof(struct Node)); 
        poly = poly->next; 
        poly->next = NULL; 
    } 
} 

void polysub(struct Node *poly1, struct Node *poly2, struct Node *poly) {
    while(poly1->next && poly2->next) { 
        // If power of 1st polynomial is greater then 2nd, then store 1st as it is 
        // and move its pointer 
        if(poly1->power > poly2->power) { 
            poly->power = poly1->power; 
            poly->coefficient = poly1->coefficient; 
            poly1 = poly1->next; 
        } 
          
        // If power of 2nd polynomial is greater then 1st, then store 2nd as it is 
        // and move its pointer 
        else if(poly1->power < poly2->power) { 
            poly->power = poly2->power; 
            poly->coefficient = poly2->coefficient; 
            poly2 = poly2->next; 
        } 
          
        // If power of both polynomial numbers is same then add their coefficients 
        else { 
            poly->power = poly1->power; 
            poly->coefficient = poly1->coefficient - poly2->coefficient; 
            poly1 = poly1->next; 
            poly2 = poly2->next; 
        } 
          
        // Dynamically create new node 
        poly->next = (struct Node *)malloc(sizeof(struct Node)); 
        poly = poly->next; 
        poly->next = NULL; 
    } 
    while(poly1->next || poly2->next) { 
        if(poly1->next) { 
            poly->power = poly1->power; 
            poly->coefficient = poly1->coefficient; 
            poly1 = poly1->next; 
        } 
        if(poly2->next) { 
            poly->power = poly2->power; 
            poly->coefficient = poly2->coefficient; 
            poly2 = poly2->next; 
        } 
    } 
} 

void polymult(struct Node *poly1, struct Node *poly2, struct Node *poly) {
    struct Node *temp1, *temp2;
    temp1 = poly1;
    temp2 = poly2;

    while(temp1) {
        while(temp2) {
            poly->coefficient = (temp1->coefficient) * (temp2->coefficient);
            poly->power = (temp1->power) + (temp2->power);
            poly->next = (struct Node *)malloc(sizeof(struct Node)); 
            poly = poly->next; 
            poly->next = NULL;
            temp2 = temp2->next;
        }
        temp2 = poly2;
        temp1 = temp1->next;
    }
} 

struct sort_pred {
    bool operator()(const std::pair<int,int> &left, const std::pair<int,int> &right) {
        return left.second < right.second;
    }
};

void sort(struct Node* &start, struct Node* incoming){
	Node* holder = (struct Node *)malloc(sizeof(struct Node));
    holder->power = incoming->power;
	holder->coefficient = incoming->coefficient;
	holder->next = NULL;
    
	Node * current = (struct Node *)malloc(sizeof(struct Node)); 
	current = start;
    
    if(!(current->next)){
		if(current->power == holder->power){
			current->coefficient = (current->coefficient) + (holder->coefficient);
			return;
		}
		else{
			current->next = holder;
			return;
		}
	}//end*/
	
	if(current->power < holder->power){		
		holder->next = current;
		current->next = NULL;
		start = holder;
		return;
	}
	
	if(current->power == incoming->power){
		current->coefficient = (current->coefficient) + (holder->coefficient);
		return;
	}
   
	while(current -> next){
		Node * temp = (struct Node *)malloc(sizeof(struct Node)); 
		temp = current->next;
        
        if(holder->power > temp->power){
			holder->next = temp;
			current->next = holder;
			return;
		}
		
		if(holder->power == temp->power){
			temp->coefficient = (temp->coefficient) + (holder->coefficient);
			return;
		}
		
		current = current->next;
	}
	current->next = holder;
}

int main() { 
    struct Node *polyholder = NULL,*polywhat = NULL, *poly1 = NULL, *poly2 = NULL, *polya = NULL, *polys = NULL, *polym = NULL; 
    
    ifstream in("input.txt");
    ofstream myFile;
    myFile.open("output.txt");
    
    string line1;
    string line2;
    if(in.good()) {
        getline(in, line1, '\n');
        getline(in, line2);
    }
    
    string buf1; 
	stringstream ss1(line1);
	vector<int> tokens1;
	while (ss1 >> buf1) {
		tokens1.push_back(atoi(buf1.c_str()));
	}
	
	string buf2; 
	stringstream ss2(line2);
	vector<int> tokens2;
	while (ss2 >> buf2) {
		tokens2.push_back(atoi(buf2.c_str()));
	}
	
	vector<int> powers1;
    vector<int> coefficients1;
	for (auto it = tokens1.begin(); it != tokens1.end(); ++it) {
        const auto index = distance(tokens1.begin(), it);
        if (index % 2 == 0) {
            coefficients1.push_back(*it);
        }
        else {
            powers1.push_back(*it);
        }
    }
    
    vector<int> powers2;
    vector<int> coefficients2;
	for (auto it = tokens2.begin(); it != tokens2.end(); ++it) {
        const auto index = distance(tokens2.begin(), it);
        if (index % 2 == 0) {
            coefficients2.push_back(*it);
        }
        else {
            powers2.push_back(*it);
        }
    }
    
    vector<pair <int, int>> vect1;
    vector<pair <int, int>> vect2;
    
    for(unsigned i = 0; i < coefficients1.size(); i++) {
        vect1.push_back(make_pair(coefficients1[i], powers1[i]));
    }
    
    for(unsigned i = 0; i < coefficients2.size(); i++) {
        vect2.push_back(make_pair(coefficients2[i], powers2[i]));
    }
    
    sort(vect1.rbegin(), vect1.rend(), sort_pred());
    sort(vect2.rbegin(), vect2.rend(), sort_pred());
    
    int x[vect1.size()];
    int y[vect1.size()];

    for(int i = 0; i < vect1.size(); i++) {
        x[i] = vect1[i].first;
        y[i] = vect1[i].second;
    }
    
    for (int i = 0; i < (sizeof(x)/sizeof(*x)); i++) {
        create_node(x[i],y[i], &poly1);
    }
    
    int q[vect2.size()];
    int r[vect2.size()];

    for(int i = 0; i < vect2.size(); i++) {
        q[i] = vect2[i].first;
        r[i] = vect2[i].second;
    }
    
    for (int i = 0; i < (sizeof(q)/sizeof(*q)); i++) {
        create_node(q[i],r[i], &poly2);
    }
    
    polya = (struct Node *)malloc(sizeof(struct Node)); 
    polys = (struct Node *)malloc(sizeof(struct Node)); 
    polym = (struct Node *)malloc(sizeof(struct Node)); 
    polyholder = (struct Node *)malloc(sizeof(struct Node)); 
    polywhat= (struct Node *)malloc(sizeof(struct Node)); 
    
    polyadd(poly1, poly2, polya); 
    polysub(poly1, poly2, polys);
    polymult(poly1, poly2, polyholder);
    polywhat->coefficient =0;
    polywhat->power = 0;
    polywhat->next = 0;
    polym->coefficient = 0;
    polym->power = 0;
    polym->next = 0;
    while(polyholder){
    	sort(polym, polyholder);
    	polyholder = polyholder->next;
    }
  
    myFile << "1st Polynomial: ";
    
    while(poly1->next != NULL) { 
        myFile << poly1->coefficient << "x^" << poly1->power; 
        poly1 = poly1->next; 
        if(poly1->next != NULL) 
            myFile << " + "; 
    } 

    myFile << "\n\n2nd Number: ";
     
    while(poly2->next != NULL) { 
        myFile << poly2->coefficient << "x^" << poly2->power; 
        poly2 = poly2->next; 
        if(poly2->next != NULL) 
            myFile << " + "; 
    } 
    
    myFile << "\n\nAdded polynomial: "; 
    
    while(polya->next != NULL) { 
        myFile << polya->coefficient << "x^" << polya->power; 
        polya = polya->next; 
        if(polya->next != NULL) 
            myFile << " + "; 
    } 
    
    myFile << "\n\nSubtracted polynomial: "; 
    
    while(polys->next != NULL) { 
        if(polys->coefficient == 0) {
            myFile << "";
            if(polys->next != NULL) 
                myFile << "";
        }
        else {
            myFile << polys->coefficient << "x^" << polys->power;
            if(polys->next != NULL) 
                myFile << " + ";
        }
        polys = polys->next; 
    } 
    myFile << "\n\nMultiplied polynomial: "; 
    
    while(polym->next != NULL) { 
        if(polym->coefficient == 0) {
            myFile << "";
            if(polym->next != NULL) 
                myFile << "";
        }
        else {
            myFile << polym->coefficient << "x^" << polym->power;
            if(polym->next != NULL) 
                myFile << " + ";
        }
        polym = polym->next; 
    } 
    
    return 0; 
} 
