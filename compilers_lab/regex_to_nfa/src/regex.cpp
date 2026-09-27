#include <string>
#include <list>
#include <stack>
#include <queue>
#include <iostream>

int precedencia(char x){
    int value;
    switch (x)
    {
    case '*':
    case '+':
        value = 3;
        break;
    case '.':
        value = 2;
        break;
    case '|':
    case '?':
        value = 1;
        break;
    default:
        value = 0;
        break;
    }
    return value;
}

/// Función para hacer explícita la concatenación en una expresión regular
/**
 * \param[in] regex La expresión regular
 * \return una expresión regular con concatenación explícita
 */
std::string explicita(std::string regex){
    std::list<char> explicita;
    bool caracter = false;
    for (char x: regex){
        switch (x)
        {
        case '(':
            if (caracter){
                explicita.push_back('.');
            }
            caracter = false;
            break;
        case '|':
            caracter = false;
            break;
        case '*':
        case '?':
        case '+':
        case ')':
            caracter = true;
            break;
        default:
            if (caracter){
                explicita.push_back('.');
            } else {
                caracter = true;
            }
            break;
        }
        explicita.push_back(x);
    }
    std::string cadena(explicita.begin(), explicita.end());
    return cadena;
}
    
std::string sufija(std::string regex_explicita){
    std::string sufija;
    std::stack<char> operadores;
    char caracter = false;
    for (char x : regex_explicita){
        switch (x)
        {
        case '(':
            operadores.push(x);
            break;
        case ')':
            while (!operadores.empty() && operadores.top() != '(') {
                char operador = operadores.top();
                if (operador != '(' && operador != ')'){
                    sufija += operador;
                }
                operadores.pop();
            }
            if (!operadores.empty()){
                operadores.pop();
            }
            break;
        case '*':
        case '+':
        case '?':
            if (caracter){
                sufija += x;
                break;
            }
        case '|':
        case '.':
            while(!operadores.empty() && precedencia(operadores.top()) >= precedencia(x)){
                sufija += operadores.top();
                operadores.pop();
            }
            operadores.push(x);
            break;
        default:
            sufija += x;
            caracter = true;
            break;
        }
    }

    while (!operadores.empty()){
        sufija += operadores.top();
        operadores.pop();
    }
    return sufija;

}

std::string sufija_validador(std::string regex_sufija){
    std:: string resultado = "";
    for (char x : regex_sufija){
        if (x == '.'){
            continue;
        }
        resultado += x;
    }
    return resultado;
}
