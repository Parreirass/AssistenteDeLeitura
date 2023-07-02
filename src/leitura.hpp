#ifndef LER_HPP
#define LER_HPP

#include <bits/stdc++.h>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <locale>
#define endl '\n'

//#define tolowerStr(str) loopStr(str) str[d_inc] = tolower(str[d_inc]);

using namespace std;

typedef struct palavra {
    int quantidade = 1;
    vector<int> linha;
    vector<int> distancia;
    vector<int> posicao;
    vector<int> paragrafo;
    vector<int> sentenca;
}Sword;

typedef struct sentecas {
    int numeroPalavrasComStopWord = 0, numeroPalavraSemStopWord = 0;

}Senteca;

typedef struct conjunto {
    int linhaF, linhaI, numSetencas;
    vector<Senteca> vetorSentencas;

}Paragrafo;

void inserePrintPorParagrafo(map<string, Sword> &mapPrintPorParagrafo, string palavraLinha, Sword &wordParagrados, int cont, int supremeConte, int paragrafoQuantidade, int contSentencas);
void inserePrintGeral(unordered_map<string, Sword> &mapPrintGeral, string palavraLinha, Sword &wordParagrados, int cont, int supremeConte, int paragrafoQuantidade, int contSentencas, int &contPalavras);
void readPrincipal();
void preencheMapPontos(unordered_map<char, bool> &pontos);
void readStopWords(unordered_map<string, bool> &stopWords);
void readExpressoes(unordered_map<string, vector<int>> &expressoes);
void imprimir(vector<int> m);
void checaExpressao(unordered_map<string, vector<int>> &map, int cont, string line);
void insertPontos(unordered_map<char, bool>pontos);
string tiraReticencia(string linha);
string removePontuacao(string num, unordered_map<char, bool>pontos);
string removePontuacaoQueDelimitaSentenca(string num, int *contExpressoes, int &Num_StopWords);
string converterAcentuadasParaMinusculas(string num);
bool checaSetenca(string linha);
bool temNumero(string palavra);
bool Pontuacao(string *num, int *contExpressoes, int &Num_StopWord);
void DistanciaParagrafo(map<string, Sword> &m1);
void DistanciaGeral(unordered_map<string, Sword> &m1);
void printTable(vector<vector<string>> &tabela, int &columnWidths);
void outputGeral(vector<Senteca> sentecas, vector<Paragrafo> paragrafos, int quantParagrafos, unordered_map<string, Sword> &m1, unordered_map<string, vector<int>>expressoes);
void outputSentencas(map<string, vector<int>>expressoes);
map<pair<string, int>, Sword>::iterator find_if_map(map<pair<string, int>, Sword> &mapPrintGeral, int paragrafoProcurado);
void outputParagrafos(vector<Senteca> sentecas, vector<Paragrafo> paragrafos, int quantParagrafos, vector< map<string, Sword> > &m1, unordered_map<string, vector<int>>expressoes, int *aux);
bool isPonto(char c, unordered_map<char, bool>pontos);
#endif