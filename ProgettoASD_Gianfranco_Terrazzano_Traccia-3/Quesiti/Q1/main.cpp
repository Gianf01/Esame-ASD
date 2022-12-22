#include "Graph.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
void showMenu();
void Remove_Edge(Graph<int> & );
void GetInput(fstream & ,string ,string , Graph<int> &);
void Find_edge(Graph<int> &);
void showWelcome();
void Add_Edge(Graph<int> &simpleGraph);
int main(int argc, char *argv[])
{
     fstream my_file;
     string ch, line;
     Graph<int> simpleGraph;
     int choice;     //menu choice
     int i=1;
     int s;
    
    GetInput(my_file, ch, line, simpleGraph);

    //constants for menu choices
     const int NodeList=1,
               AddEdge = 2,
              RemoveEdge = 3,
              FindEdge = 4,
              ShowEdgeList = 5,
              BFS= 6,
              EXIT= 7;
    
    do
    {
         showWelcome(); // Show Welcome screen
         showMenu(); // Display Menu
         cin >> choice;
         //Validate menu selection
         while ((choice != NodeList) && (choice !=AddEdge) && (choice != RemoveEdge) && (choice!=FindEdge) && (choice!=ShowEdgeList) && (choice !=BFS) && (choice != EXIT))
         {
               cin.clear();
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
               cout << "Per favore inserisci un opzione valida\n";
               cin >> choice;
         }
         
         //If user does not want to quit, proceed.
         if (choice != EXIT)
         {
          
                    switch (choice)
                    {
                         case NodeList:
                              simpleGraph.printNode();
                              break;
                           case AddEdge:
                                Add_Edge(simpleGraph);
                                break;
                           
                           case RemoveEdge:
                                Remove_Edge(simpleGraph);
                                break;
                                
                           case FindEdge:
                                Find_edge(simpleGraph);
                                break;
                           
                           case ShowEdgeList:
                                simpleGraph.printEdge();
                                break;

                            case BFS:
                                int s;
                                cout <<"Inserire indice nodo sorgente"<<endl;
                                while(!(cin >> s)){
                                   cin.clear();
                                   cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                   cout << "Per favore inserisci un indice valido!\n";
                                } 
                                auto tmpBFS=simpleGraph.getNodeAtIndex(s);
                                while(tmpBFS==nullptr){
                                   cin.clear();
                                   cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                   cout << "Nodo non valido, riprova!\n";
                                   while(!(cin >> s)){
                                          cin.clear();
                                          cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                          cout << "Per favore inserisci un indice valido!\n";
                                  }
                                   tmpBFS=simpleGraph.getNodeAtIndex(s);
                                } 
                                simpleGraph.BFS(tmpBFS);
                                break;
                    }
         }
         } while (choice != EXIT);
return 0;
}

void showMenu()
{    
    cout << "Selezionare una funzione"  << endl << endl
         << "1. Show Node List" <<endl
         << "2. AddEdge" << endl
         << "3. RemoveEdge" << endl
         << "4. FindEdge" << endl
         << "5. Show Edge List"<< endl 
         << "6. BFS"<< endl 
         << "7. EXIT" << endl 
         <<"\nN.B Le funzioni su gli Edge lavorano con gli indici, utilizzare Show Node List per estrapolare gli indici" <<endl << endl;
}

void showWelcome()
{
     cout << "\nRealizzazione della traccia Q1 progetto ASD\n" << endl << endl;
     system ("pause");
}

void GetInput(fstream &my_file,string ch,string line, Graph<int> &simpleGraph){
 int N,M,i,a,b;
	my_file.open("input0_3_1.txt", ios::in);
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
    cout << "Numero Nodi: " << ch1 << " Numero archi: " << ch2 << endl;
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
    if((N<0 || N>1000) || (M<0 || M>1000)){
     cout << "Modificare i nodi/archi in ingresso!"<<endl;
     abort();
    }
    i=1;
    while (i<=M) {
        cout <<"\n"<<"Iterazione numero :"<< i << "\n" << endl;
        getline(my_file, line);
        //cout << line <<endl;
        int comma2 = line.find(" "); 
        string line1 = line.substr(0, comma); 
        string line2 = line.substr(comma); 
        cout << "Nodo sorgente: " << line1 << " Nodo Destinazione: " << line2 << endl;
        try {
            a = stoi(line1);
            b = stoi(line2);
        }
        catch(std::invalid_argument& e){
            cout <<"Nodo non valido, inserire un intero nel file di input!"<<endl;
            abort();
        }
        catch(std::out_of_range& e){
            cout <<"Sei andato oltre il limite dell'int!"<<endl;
            abort();
       }
        
        auto tmp1= new Node<int>(a);
        auto tmp2 = new Node<int>(b);
        simpleGraph.addNode(tmp1);
        simpleGraph.addNode(tmp2);
        simpleGraph.AddEdge(simpleGraph.GetID(tmp1),simpleGraph.GetID(tmp2));
        i++;
    }
    cout<< "\ninput presi correttamente, benvenuti nel progetto!"<<endl;
}

void Remove_Edge(Graph<int> & simpleGraph){
int node1;
int node2;
cout << "Inserisci nodo sorgente :" <<endl;
while(!(cin >> node1)){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Per favore inserisci un opzione valida \n ";
}
cout << "inserisci nodo destinazione : " << endl;
while(!(cin >> node2)){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Per favore inserisci un opzione valida\n ";
}
simpleGraph.RemoveEdge(node1,node2);
}

void Find_edge(Graph<int> &simpleGraph){
int node1;
int node2;
cout << "Inserisci nodo sorgente :" <<endl;
while(!(cin >> node1)){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Per favore inserisci un opzione valida \n ";
}
cout << "inserisci nodo destinazione : " << endl;
while(!(cin >> node2)){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Per favore inserisci un opzione valida\n ";
}
simpleGraph.FindEdge(node1,node2);  
}

void Add_Edge(Graph<int> &simpleGraph){
int node1;
int node2;
cout << "Inserisci nodo sorgente :" <<endl;
while(!(cin >> node1)){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Per favore inserisci un opzione valida \n ";
}
cout << "inserisci nodo destinazione : " << endl;
while(!(cin >> node2)){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Per favore inserisci un opzione valida\n ";
}
simpleGraph.AddEdge(node1,node2);  
}