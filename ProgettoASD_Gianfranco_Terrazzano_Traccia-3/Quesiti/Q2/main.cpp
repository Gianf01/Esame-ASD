#include "Graph.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void AddEdge(fstream & ,string ,string , Graph<int> &);

int main(){
fstream my_file;
string ch, line;
Graph<int> simpleGraph;

 AddEdge(my_file, ch, line, simpleGraph);
 auto tot=simpleGraph.kruskalMST();
 cout << "\nPeso minimo: "<< tot << endl;
 simpleGraph.printMST();
auto tot2=simpleGraph.kruskalMST2();
cout << "\nSecondo peso minimo: "<< tot2 << endl;
simpleGraph.printMST2();

}
void AddEdge(fstream &my_file,string ch,string line, Graph<int> &simpleGraph){
 int N,M,i,a,b,c;
	my_file.open("input0_3_2.txt", ios::in);
	if (!my_file) {
		cout << "File not created!" <<endl;
	}
	else {
		cout << "File aperto con successo" <<endl; 
	}
    getline(my_file, ch);
    cout << ch <<endl;
    int comma = ch.find(" "); 
    string ch1 = ch.substr(0, comma); 
    string ch2 = ch.substr(comma + 1); 
    cout << "Numero città: " << ch1 << " Numero tratte: " << ch2 << endl;
  
     try { 
            N = stoi(ch1); 
            M = stoi(ch2);
        }
        catch(std::invalid_argument& e){
            cout <<"Nodo non valido, inserire un intero nel file di input!"<<endl;
            abort();
        }
        catch(std::out_of_range& e){
            cout <<"Sei andato oltre il limite dell'int!"<<endl;
            abort();
       }
    if((N<1 || N>1000) || (M<0 || M>10000)){
     cout << "Modificare le città/tratte in ingresso!"<<endl;
     abort();
    }
    i=1;
    while (i<=M) {
        cout <<"\n"<<"Iterazione numero :"<< i << "\n" << endl;
        getline(my_file, line);
        auto comma2= line.find(" "); 
        string line1 = line.substr(0, comma2); 
        string linetmp = line.substr(comma2 +1);
        auto comma3=linetmp.find(" ");
        string line2= linetmp.substr(0, comma3);
        string line3 = linetmp.substr(comma3 +1); 
        cout << "Città: " << line1 << " Tratta: " << line2 << " Costo della tratta : " << line3 << endl;
        try {
            a = stoi(line1);
            b = stoi(line2);
            c = stoi(line3);
        }
        catch(std::invalid_argument& e){
            cout <<"Nodo non valido, inserire un intero nel file di input!"<<endl;
            abort();
        }
        catch(std::out_of_range& e){
            cout <<"Sei andato oltre il limite dell'int!"<<endl;
            abort();
       }
        if (c<1 || c>10000){
            cout<<"Costo non valido, modificare il file di ingresso!"<<endl;
            abort();
        }
        auto tmp1= new Node<int>(a);
        auto tmp2 = new Node<int>(b);
        auto tmp3= c;
        simpleGraph.addNode(tmp1);
        simpleGraph.addNode(tmp2);
        simpleGraph.Add_Edge(simpleGraph.getID(tmp1),simpleGraph.getID(tmp2), c);
        i++;
    }
}