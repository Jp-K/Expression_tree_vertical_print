#include "pilha.h"
#include "expression_tree.h"
#include <iostream>
using namespace std;


int main()
{

    string equacao;
    cout << "digite a equacao:" << endl;
    cin >> equacao;
    cout << endl;
    montar_arvore(equacao);
}
