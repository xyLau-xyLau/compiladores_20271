#include <set>
#include <string>
#include <map>
#include <format>
#include <iostream>

using namespace std;
class Nfa {
    private:
        int inicial = 0;
        set<int> finales = {};
        set<int> estados = {};
        set<char> alfabeto = {};
        map<int, map<char, set<int>>> transiciones;
    public:
        Nfa(int inicial, set<int> estados, set<int> finales, set<char> alfabeto){
            inicial = inicial;
            finales = finales;
            alfabeto = alfabeto;
            estados = estados;
        }

        Nfa(char simbolo, int inicial, int final){
            estados.insert({inicial,final});
            inicial = inicial;
            alfabeto.insert({simbolo});
            finales.insert({final});
            transiciones[inicial][simbolo].insert({final});
        }

        string to_string(){
            string cadena = "Estados: {";
            for (int x : estados){
                cadena += format("{} ", x);
            }
            cadena += "}\n";
            cadena += format("Inicial: {}", inicial);
            cadena += "\n";
            cadena += "Finales: {";
            for (int x: finales){
                cadena += format("{} ", x);
            }
            cadena += "}\n";
            cadena += "Alfabeto: {";
            for (char x: alfabeto){
                cadena += format("{} ", x);
            }
            cadena += "}\nTransiciones: ";
            for (auto transicion: transiciones){
                for (auto destino: transicion.second){
                    set<int> estados_destino = destino.second;
                    string acc = "{";
                    for (int x: estados_destino){
                        acc += format("{} ", x);
                    }
                    acc += "}";
                    cadena += format("d({},{}) = {}", transicion.first, destino.first, acc);
                }
            }
            return cadena;
        }
};  
/**
int main(){
    Nfa a('a', 0, 1);
    cout << a.to_string() << endl;
    return 0;
} */