#ifndef EXPRESSION_TREE_H_INCLUDED
#define EXPRESSION_TREE_H_INCLUDED
#include <iostream>
#include "pilha.h"
#include "fila.h"
#include<math.h>
#include<string>
#include<stdlib.h>
#include<cstring>
using namespace std;

struct No{
    ///nó da arvore, contem um valor e um char para operação, sendo assim, pode ser usado para numeros e operações
	char op;
    int val;
	No* esq;
	No* dir;
};

int prioridade(char op){
    ///retorna a prioridade das operações
	if ((op =='+') || (op =='-')){
        return 1;
	}
	if ((op =='/') || (op =='*')){
        return 2;
	}
}

No* criaNo(char op, int val){
    ///função para criar um nó
	No* node;
	node = new No;
	node->op = op;
	node->val = val;
	node->esq = NULL;
	node->dir = NULL;
	return node;
}

void inclui_operador(TPilha<No*>& operadores, TPilha<No*>& Nos){
    ///inclui o operador na lista de nós, e coloca os nós existentes como filhos, assim, criando a arvore
    No* operador_no = pop_pilha(operadores);
    operador_no->esq = pop_pilha(Nos);
    operador_no->dir = pop_pilha(Nos);
    push_pilha(Nos, operador_no);
}

///função que executa a arvore e retorna um valor float.
float executa_arvore(No* tree){
	float x,y,z;
	if ((tree->op) == '+'||(tree->op) == '-'||(tree->op) == '*'||(tree->op) == '/') {
            ///recursividade, para chegar ao final e somar os valores até o topo
		x = executa_arvore(tree->esq);
		y = executa_arvore(tree->dir);
		///executa as operações aritméticas
		if (tree->op=='+')
			z=x+y;
		else if (tree->op=='-')
			z=x-y;
		else if (tree->op=='*')
			z=x*y;
		else if (tree->op=='/')
			z=x/y;
		return z;
	}
	else return tree->val;
}




///gera uma quantidade de espaços para imprimir a lista
void espaco(int n){
	for (int i=0;i<n;i++){
		cout<<" ";
	}
}
///calculando o tamanho da arvore
int height_tree(No * p){
	if (p==NULL){
		return 0;
	}
	else{
		int eprof=height_tree(p->esq);
		int dprof=height_tree(p->dir);
		if (eprof>dprof){
			return(eprof+1);
		}
		else{
			return(dprof+1);
		}
	}
}


void imprimir_vertical(No *root){///impressão vertical da arvore
	No* ptr;
	ptr = NULL;
	///se a arvore estiver vazia, o programa imprime NULL e sai
	if (root==NULL){
		cout<<"NULL\n";
		return;
	}

	TFilaF<No*> q;
	inicializa_fila(q);
	///introduzindo a raiz na fila, para depois transformar em um vetor
	fila_queue(q, root);
	No ar[10000];
	int i=0;
	memset(ar,-1,sizeof ar);
	int cont=0;
	int height=height_tree(root);
	///convertendo a arvore em um vetor
	while (fila_qtd(q) > 0){
		ptr = fila_unqueue(q);
		cont++;

		if (ptr!=NULL){
			ar[i]=*ptr;
			i++;
			///se tiver alguma posição que esteja nula, o programa não salva na fila
			if(ptr->esq!=NULL){
                fila_queue(q, ptr->esq);
			}
			if(ptr->dir!=NULL){
                fila_queue(q, ptr->dir);
			}
		}
		else{
            ///se chegar em algum lugar q esteja nulo, ele insere nulo na fila
			i++;
			No* nulo = NULL;
			nulo->dir = NULL;
			nulo->esq = NULL;
			fila_queue(q, nulo);
			fila_queue(q, nulo);
		}
		if (log2(cont+1)==height){
			break;
		}
	}
	///impressão da arvore
	cout<<"\nImprimindo arvore na vertical: \n";
	int x=height;
	for (int i=1;i<=pow(2,height-1);i*=2){
		int z=pow(2,x-1)-1;
		espaco(z*2);
		for (int j=i-1;j<(i*2)-1;j++){  ///equações para a lógica de impressão da arvore (para saber a quantidade de espaços e onde colocar cada nó e cada espaço)
			if (ar[j].val != -1){
				if (ar[j].val/10==0){
                    if(ar[j].op==NULL){
                        cout<<"0";
                    }
				}
				if(ar[j].op==NULL){  ///teste para imprimir ou a operação, ou o valor contido no nó
                    cout<<ar[j].val;
				} else{
                    cout<<ar[j].op;
				}
				espaco((pow(2,x)-1)*2);
			}
			else{
				cout<<"  ";
				espaco((pow(2,x)-1)*2);
			}
		}
		cout<<endl;
		espaco((z*2)-1);
		if (i!=pow(2,height-1)){
			for (int j=i-1;j<(i*2)-1;j++){
				if (ar[j].val!=-1){
					if (ar[2*(j+1)-1].val!=-1){
						cout<<"/";
					}
					else{
						cout<<" ";
					}
					cout<<"  ";
					if (ar[2*(j+1)].val!=-1){
						cout<<"\\";
					}
					else{
						cout<<" ";
					}
					espaco(((pow(2,x)-1)*2)-2);
				}
				else{
					espaco(4);
					espaco(((pow(2,x)-1)*2)-2);
				}
			}
		}
		cout<<endl;
		x--;
	}
}


void montar_arvore(string infix)
{
    TPilha<char> input;
    TPilha<No*> operadores;
    TPilha<No*> Nos;
    No temp;
    int ant = 0;
    inicializa_pilha(input);
    inicializa_pilha(operadores);
    inicializa_pilha(Nos);
    ///coloca a string recebida em uma pilha.
    for (int i=0;i<infix.length();i++){
			push_pilha(input, infix[i]);
		}

    while(qntd_pilha(input)>0){

            ///teste para saber se é um numero, ou uma operação.
            if (isdigit(Top_pilha(input))){
                temp.val = (int)(pop_pilha(input) - '0');
                temp.op = NULL;
            } else {
                temp.op = pop_pilha(input);
                temp.val = 0;
            }
            ///a variável temp recebe um digito da string.

        if(temp.op==NULL){
            while(isdigit(Top_pilha(input))){
                temp.val = (temp.val*10) + (int)(pop_pilha(input) - '0');
            }
            ///inverte o numero, pois quando colocado na pilha ele é colocado na direção oposta.
            int n = temp.val;
            int remainder;
            int reversedNumber = 0;
               while(n != 0)
            {
                remainder = n%10;
                reversedNumber = reversedNumber*10 + remainder;
                n /= 10;
            }
            push_pilha(Nos, criaNo(temp.op,reversedNumber));
        }
        if (temp.op==')'){ ///teste de parenteses pt.1
                ant=1;     ///flag para caso o parenteses se abra, ele inclua todas as operações dentro dele
            }
        if ((temp.op=='+') || (temp.op=='/') || (temp.op =='-') || (temp.op=='*')){
            bool pushed = false;
            while(pushed == false){
                if(qntd_pilha(operadores)<=0){
                        ///coloca na pilha de operadores o operador contido no temp
                    push_pilha(operadores, criaNo(temp.op,temp.val));
                    pushed = true;
                } else if (Top_pilha(operadores)->op==')'){
                    push_pilha(operadores, criaNo(temp.op,temp.val));
                    pushed = true;
                } else if ((prioridade(temp.op)>prioridade(Top_pilha(operadores)->op)) || (prioridade(temp.op)==prioridade(Top_pilha(operadores)->op))){
                    ///cuida da prioridade das operações onde * e / tem prioridade sobre + e -
                    push_pilha(operadores, criaNo(temp.op,temp.val));
                    pushed = true;
                } else if(ant==0){ ///não inclui enquanto os parenteses estiverem abertos
                    inclui_operador(operadores, Nos);
                }
            }
        }
        if (temp.op=='('){ ///teste de parenteses pt.2
                inclui_operador(operadores, Nos); ///inclui quando os parenteses se fecham
                ant = 0;
        }
    }
    while(qntd_pilha(operadores)>0){
            ///inclui na arvore o resto das operações que não foram inseridas
        inclui_operador(operadores, Nos);
    }
    ///chamada da função de imprimir
    imprimir_vertical(Top_pilha(Nos));
    ///chamada da função de executar a arvore, que calcula a partir dos nós, e retorna um valor float.
    float resposta = executa_arvore(Top_pilha(Nos));
    cout << "resposta: " << resposta << endl;
}





#endif // EXPRESSION_TREE_H_INCLUDED
