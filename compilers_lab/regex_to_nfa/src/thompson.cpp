#include "Nfa.cpp"
#include <set>
#include <stack>
#include <string>
#include <iostream>

using namespace std;

Nfa thompson(string postfix_regex){
    stack<Nfa> pila;
    Nfa temp('z',0, 1);
    int num_estados = 0;
    for (char x : postfix_regex){
        switch (x)
        {
        case '.':
        case '*':
        case '?':
        case '|':
        case '+':
            //Nfa temp('z',0, 1);
            break;
        default:
            int estado_inicial = num_estados;
            int estado_final = num_estados + 1;
            temp = Nfa(x, estado_inicial, estado_final);
            //return temp;
            break;
        }
    }
    return temp;
}

int main(){
    Nfa x = thompson("a");
    cout << x.to_string() << endl;
    return 0;
}


