#include "leitura.hpp"

void readPrincipal() {
    string filename("dataset/Semana_Machado_Assis.txt");
    ifstream input_file(filename, ios::in);

    string line;
    string palavraLinha;
    bool decisao = false;

    int count = 0, contExpressoes = 0, paragrafoQuantidade = 1, NumStopWords = 0, Num_StopWords = 0;
    int cont = 0, linhai = 1, supremeCont = 0, distancia = 0, contSentecas = 1, tamanhoPalavra = 0;
    int aux = 0, contPalavras = 0;;

    unordered_map<string, Sword> mapPrintGeral;
    map<string, Sword> mapPrintPorParagrafo;
    unordered_map<string, Sword> porSentenca;
    unordered_map<string, bool>stopWords;
    unordered_map<string, vector<int>>expressoes;
    unordered_map<char, bool>pontos;
    vector<map<string, Sword>>printDoParagrafo;
    preencheMapPontos(pontos);

    Sword word;
    Sword wordParagrados;

    bool mudou = false;

    vector<Senteca> sentecas;
    vector<Paragrafo> paragrafos;

    readStopWords(stopWords);
    readExpressoes(expressoes);

    if (!input_file.is_open()) {
        cout << "Nao foi possivel abrir o arquivo" << filename << " " << endl;
    }

    while (!input_file.eof()) {
        while (getline(input_file, line, '\n')) {
            cont++;
            for (auto &c : line) {
                c = tolower(c);
            }

            //cout<<cont<<line<<endl;
            checaExpressao(expressoes, cont, line);
            line = converterAcentuadasParaMinusculas(line);
            line = tiraReticencia(line);
            istringstream ln(line);

            if (line.size() > 1) {
                decisao = false;

                while (ln >> palavraLinha) {
                    if (!temNumero(palavraLinha)) {
                        
                        NumStopWords++;            //contador com stop words pega//
                        supremeCont++;

                        if (Pontuacao(&palavraLinha, &contExpressoes, Num_StopWords)) {
                            mudou = true;
                            sentecas.push_back({ NumStopWords,Num_StopWords });
                            NumStopWords = 0;
                            Num_StopWords = 0;
                        }

                        palavraLinha = removePontuacao(palavraLinha, pontos);

                        auto it2 = stopWords.find(palavraLinha);
                        if (it2 == stopWords.end()) {
                            
                            Num_StopWords++;      //contador sem stop words//
                            //adiciona palavra no map//
                            if (palavraLinha != "") {

                                inserePrintPorParagrafo(mapPrintPorParagrafo, palavraLinha, wordParagrados, cont, supremeCont, paragrafoQuantidade, contSentecas);
                                inserePrintGeral(mapPrintGeral, palavraLinha, word, cont, supremeCont, paragrafoQuantidade, contSentecas, contPalavras);

                            }
                        }

                        if (mudou) {
                            contSentecas++;
                            mudou = false;
                        }
                    }
                }

                line.clear();
            } else {
                contExpressoes = contExpressoes + 1;
                sentecas.push_back({ NumStopWords,Num_StopWords - 1 });
                paragrafos.push_back({ cont - 1,linhai,contExpressoes,sentecas });
                NumStopWords = 0;
                Num_StopWords = 0;
                contExpressoes = 0;
                contSentecas = 1;
                decisao = true;
                supremeCont = 0;
                DistanciaParagrafo(mapPrintPorParagrafo);
                //mapPrintPorParagrafo.clear();
                printDoParagrafo.push_back(mapPrintPorParagrafo);
                mapPrintPorParagrafo.clear();
                paragrafoQuantidade++;
                linhai = cont + 1;
                //mapPrintPorParagrafo.clear();
            }
        }
    }
    if (!(decisao)) {
        contExpressoes = contExpressoes + 1;
        sentecas.push_back({ NumStopWords,Num_StopWords });
        paragrafos.push_back({ cont,linhai,contExpressoes,sentecas });
        contExpressoes = 0;
        decisao = true;
        DistanciaParagrafo(mapPrintPorParagrafo);
        printDoParagrafo.push_back(mapPrintPorParagrafo);
        paragrafoQuantidade++;
        mapPrintPorParagrafo.clear();
        linhai = cont + 1;
        supremeCont = 0;
    }

    outputParagrafos(sentecas, paragrafos, paragrafoQuantidade, printDoParagrafo, expressoes, &aux);

    DistanciaGeral(mapPrintGeral);
    outputGeral(sentecas, paragrafos, paragrafoQuantidade, mapPrintGeral, expressoes);
    cout << "Cont Palavras:" << contPalavras << endl;
}

void inserePrintPorParagrafo(map<string, Sword> &mapPrintPorParagrafo, string palavraLinha, Sword &wordParagrados, int cont, int supremeCont, int paragrafoQuantidade, int contSentencas) {

    auto it3 = mapPrintPorParagrafo.find(palavraLinha);//MAPA AUX

    if (it3 != mapPrintPorParagrafo.end()) {//palavra existe*
        it3->second.quantidade++; //incrementa valor
        it3->second.linha.push_back(cont);
        it3->second.posicao.push_back(supremeCont);
        it3->second.paragrafo.push_back(paragrafoQuantidade);
        it3->second.sentenca.push_back(contSentencas);
    } else {
        wordParagrados.linha.push_back(cont);
        wordParagrados.posicao.push_back(supremeCont);
        wordParagrados.paragrafo.push_back(paragrafoQuantidade);
        wordParagrados.sentenca.push_back(contSentencas);
        mapPrintPorParagrafo.insert({ palavraLinha, wordParagrados }); //insere se não existir
        wordParagrados.linha.clear();
        wordParagrados.posicao.clear();
        wordParagrados.paragrafo.clear();
        wordParagrados.sentenca.clear();
    }
}

void inserePrintGeral(unordered_map<string, Sword> &mapPrintGeral, string palavraLinha, Sword &wordParagrados, int cont, int supremeCont, int paragrafoQuantidade, int contSentencas, int &contPalavras) {
    auto it = mapPrintGeral.find(palavraLinha); //MAPA FINAL

    if (it != mapPrintGeral.end()) {//palavra existe*
        it->second.quantidade++; //incrementa valor
        it->second.linha.push_back(cont);
        it->second.posicao.push_back(supremeCont);
        it->second.paragrafo.push_back(paragrafoQuantidade);
        it->second.sentenca.push_back(contSentencas);
    } else {
        wordParagrados.linha.push_back(cont);
        wordParagrados.posicao.push_back(supremeCont);
        wordParagrados.paragrafo.push_back(paragrafoQuantidade);
        wordParagrados.sentenca.push_back(contSentencas);
        mapPrintGeral.insert({ palavraLinha, wordParagrados }); //insere se não existir
        wordParagrados.linha.clear();
        wordParagrados.posicao.clear();
        wordParagrados.paragrafo.clear();
        wordParagrados.sentenca.clear();
        contPalavras++;
    }
}


void readStopWords(unordered_map<string, bool> &stopWords) {
    string filename("dataset/stopwords.csv");
    ifstream input_file(filename, ios::in);
    string line;

    while (!input_file.eof()) {
        while (getline(input_file, line, '\n')) {
            if (line.size() >= 1) {
                for (auto &c : line) {
                    c = tolower(c);
                }

                stopWords.insert({ line,true });
            }
        }
    }
}

void preencheMapPontos(unordered_map<char, bool> &pontos) {
    pontos.insert({
        {'-', false},
        {'.', false},
        {',', false},
        {';', false},
        {'"', false},
        {'/', false},
        {'(', false},
        {')', false},
        {'[', false},
        {']', false},
        {'+', false},
        {'-', false},
        {'=', false},
        {'$', false},
        {'%', false},
        {'&', false},
        {'*', false},
        {':', false},
        {'^', false},
        {'|', false},
        {'~', false},
        {'_', false},
        {'§', false},
        {'ª', false},
        {'°', false},
        {'º', false},
        });
}

void readExpressoes(unordered_map<string, vector<int>> &expressoes) {
    string filename("dataset/expressoes.txt");
    ifstream input_file(filename, ios::in);
    string line;
    vector<int> n;
    string num;
    int i = 0;
    while (!input_file.eof()) {
        while (getline(input_file, line, '\n')) {
            if (line.size() >= 1) {
                for (auto &c : line) {
                    c = tolower(c);
                }
                expressoes.insert({ line,n });
            }
        }
    }
}

bool isPonto(char c, unordered_map<char, bool>pontos) {
    auto it = pontos.find(c);
    if (it != pontos.end()) return true;
    return false;
}

string removePontuacao(string num, unordered_map<char, bool>pontos) {
    string palavraSemPonto;
    for (char c : num) {
        if (!isPonto(c, pontos)) {
            palavraSemPonto += c;
        }
    }
    return palavraSemPonto;
}

string tiraReticencia(string linha) {
    string retiBug = ". . .";
    size_t pos = linha.find(retiBug);
    if (pos != std::string::npos)
        linha.erase(pos, retiBug.length());

    string reti = "...";
    size_t pos2 = linha.find(reti);
    if (pos2 != std::string::npos)
        linha.erase(pos2, reti.length());

    string reti2 = "..";
    size_t pos3 = linha.find(reti2);
    if (pos3 != std::string::npos)
        linha.erase(pos3, reti2.length());

    return linha;
}


bool temNumero(string palavra) {
    for (int i = 0;i < palavra.size();i++) {
        if (isdigit(palavra[i])) return true;
    }

    return false;
}


bool Pontuacao(string *num, int *contExpressoes, int &Num_StopWords) {
    bool encontrar = false;

    char ponto = '.', exclamacao = '!', interrogacao = '?';

    size_t pos1 = (*num).find(ponto);
    if (pos1 != std::string::npos) {  // Verifica se o caractere foi encontrado
        if (!ispunct((*num)[pos1 - 1])) {
            *contExpressoes = *contExpressoes + 1;
            (*num).erase(pos1, 1);
            encontrar = true;
        }
    }
    size_t pos2 = (*num).find(exclamacao);
    if (pos2 != std::string::npos) {  // Verifica se o caractere foi encontrado
        *contExpressoes = *contExpressoes + 1;
        (*num).erase(pos2, 1);
        encontrar = true;
    }
    size_t pos3 = (*num).find(interrogacao);
    if (pos3 != std::string::npos) {  // Verifica se o caractere foi encontrado
        *contExpressoes = *contExpressoes + 1;
        (*num).erase(pos3, 1);
        encontrar = true;
    }

    return encontrar;
}

void checaExpressao(unordered_map<string, vector<int>> &map, int cont, string line) {

    for (auto itE = map.begin();itE != map.end();++itE) {
        auto itS = line.find(itE->first);
        if (itS != string::npos) {
            itE->second.push_back(cont);
        }
    }
}

string converterAcentuadasParaMinusculas(string num) {
    string maiuscula = "ÁÀÃÉÈÍÌÓÒÚÙ";
    string minuscula = "áàãéèíìóòúù";

    for (size_t i = 0; i < maiuscula.size(); i++) {
        replace(num.begin(), num.end(), maiuscula[i], minuscula[i]);
    }
    return num;
}

void DistanciaParagrafo(map<string, Sword> &mapPrintGeral) {
    int distancia = 0;

    for (auto it = mapPrintGeral.begin();it != mapPrintGeral.end();++it) {
        for (int i = 0; i < (it->second.posicao.size() - 1); i++) {
            distancia = it->second.posicao[i + 1] - it->second.posicao[0];

            it->second.distancia.push_back(distancia);
        }
    }
}


void DistanciaGeral(unordered_map<string, Sword> &mapPrintGeral) {
    int distancia = 0;

    for (auto it = mapPrintGeral.begin();it != mapPrintGeral.end();++it) {
        for (int i = 0; i < (it->second.posicao.size() - 1); i++) {
            distancia = it->second.posicao[i + 1] - it->second.posicao[0];

            it->second.distancia.push_back(distancia);
        }
    }
}

void printTable(vector<vector<string>> &tabela, int &columnWidths) {
    for (auto &linha : tabela) {
        int maxLines = 1;
        vector<vector<string>> cellLines(linha.size());

        for (size_t i = 0; i < linha.size(); ++i) {
            string cellValue = linha[i];
            int numLines = static_cast<int>(cellValue.length() / columnWidths) + 1;
            maxLines = max(maxLines, numLines);

            for (int line = 0; line < numLines; ++line) {
                int startPos = line * columnWidths;
                int endPos = min(static_cast<int>(cellValue.length()) - startPos, columnWidths);
                string lineValue = cellValue.substr(startPos, endPos);
                cellLines[i].push_back(lineValue);
            }
        }

        for (int line = 0; line < maxLines; ++line) {
            for (size_t i = 0; i < linha.size(); ++i) {
                string cellValue = (line < cellLines[i].size()) ? cellLines[i][line] : "";
                cout << setw(columnWidths) << left << setw(columnWidths) << left << cellValue << " ";
            }
            cout << endl;
        }
    }
}

void outputGeral(vector<Senteca> sentecas, vector<Paragrafo> paragrafos, int quantParagrafos, unordered_map<string, Sword> &mapPrintGeral, unordered_map<string, vector<int>>expressoes) {
    string arq = "outputt.txt";
    string loc = "dataset/" + arq;
    string paragrafosS, sentencasS, linhasS, posicaoS, distanciaS, qtd, expressoesS;

    int aux = 0, contadorDeParagrafo = 0, tam1, contcarac = 0;
    int j = 0;

    vector<vector<string>>table;
    vector<pair<string, Sword>> vetor(mapPrintGeral.begin(), mapPrintGeral.end());

    // Ordena o vetor com base nas chaves
    sort(vetor.begin(), vetor.end(), [](const auto &a, const auto &b) {
        return a.first < b.first;
    });

    fstream f(loc, fstream::out | fstream::app);
    //ofstream f(loc);

    table.push_back({ "WORD", "PARAGRAPH", "SENTENCE", "LINE","APPERANCES","POSITIONS","DISTANCE" });

    if (f.is_open()) {
        for (auto it : vetor) {

            for (auto i : it.second.paragrafo) {
                paragrafosS += std::to_string(i);
                paragrafosS += " ";
            }

            for (int i = 0; i < (int)it.second.sentenca.size(); i++) {
                sentencasS += std::to_string(it.second.sentenca[i]);
                sentencasS += " ";
            }

            for (int i = 0; i < (int)it.second.linha.size(); i++) {
                linhasS += std::to_string(it.second.linha[i]);
                linhasS += " ";
            }

            for (int i = 0; i < (int)it.second.posicao.size(); i++) {
                posicaoS += std::to_string(it.second.posicao[i]);
                posicaoS += " ";
            }

            qtd = std::to_string(it.second.quantidade);


            for (int i = 0; i < (int)it.second.distancia.size(); i++) {

                if (it.second.distancia[i] > 0) {
                    distanciaS += std::to_string(it.second.distancia[i]);
                    distanciaS += " ";
                }
            }

            table.push_back({ it.first, paragrafosS, sentencasS, linhasS, qtd, posicaoS, distanciaS });

            paragrafosS.clear(); sentencasS.clear(); linhasS.clear(); posicaoS.clear(); distanciaS.clear(); qtd.clear();

        }

        for (auto &linha : table) {
            int maxLines = 1;
            vector<vector<string>> cellLines(linha.size());

            for (size_t i = 0; i < linha.size(); ++i) {
                string cellValue = linha[i];
                int numLines = static_cast<int>(cellValue.length() / 15) + 1;
                maxLines = max(maxLines, numLines);

                for (int line = 0; line < numLines; ++line) {
                    int startPos = line * 15;
                    int endPos = min(static_cast<int>(cellValue.length()) - startPos, 15);
                    string lineValue = cellValue.substr(startPos, endPos);
                    cellLines[i].push_back(lineValue);
                }
            }

            for (int line = 0; line < maxLines; ++line) {
                for (size_t i = 0; i < linha.size(); ++i) {
                    string cellValue = (line < cellLines[i].size()) ? cellLines[i][line] : " ";
                    f << setw(15) << left << setw(15) << left << cellValue << " ";
                }
                f << '|' << endl;
            }
            f << "+-------------+---------------+---------------+---------------+---------------+---------------+---------------+ " << endl;
        }

        f << endl << endl;

        table.clear();

        for (auto i = paragrafos.begin(); i != paragrafos.end(); ++i) {
            contadorDeParagrafo++;

            table.push_back({ "Paragrafo: " + std::to_string(contadorDeParagrafo), "Linha Inicial: " + std::to_string(i->linhaI), "Linha Final: " + std::to_string(i->linhaF) });

            table.push_back({ "Sentenca", "Número de palavras com StopWords", "Numero de palavras sem Stop Words" });

            for (int j = 0; j < i->numSetencas; j++) {
                if (i->vetorSentencas[aux].numeroPalavrasComStopWord != 0) {
                    table.push_back({ std::to_string(j + 1), std::to_string(i->vetorSentencas[aux].numeroPalavrasComStopWord), std::to_string(i->vetorSentencas[aux].numeroPalavraSemStopWord + 1) });
                }
                aux++;
            }
        }

        for (auto &linha : table) {
            int maxLines = 1;
            vector<vector<string>> cellLines(linha.size());

            for (size_t i = 0; i < linha.size(); ++i) {
                string cellValue = linha[i];
                int numLines = static_cast<int>(cellValue.length() / 35) + 1;
                maxLines = max(maxLines, numLines);

                for (int line = 0; line < numLines; ++line) {
                    int startPos = line * 35;
                    int endPos = min(static_cast<int>(cellValue.length()) - startPos, 35);
                    string lineValue = cellValue.substr(startPos, endPos);
                    cellLines[i].push_back(lineValue);
                }
            }

            for (int line = 0; line < maxLines; ++line) {
                for (size_t i = 0; i < linha.size(); ++i) {
                    string cellValue = (line < cellLines[i].size()) ? cellLines[i][line] : " ";
                    f << setw(35) << left << setw(35) << left << cellValue << " ";
                }
                f << '|' << endl;
            }
            f << "+---------------------------------+----------------------------------+----------------------------------+" << endl;
        }

        f << endl << endl;
        table.clear();


        for (auto it = expressoes.begin();it != expressoes.end();++it) {
            table.push_back({ "Expressão", "Linha" });

            for (int k = 0; k < (int)it->second.size(); k++) {
                expressoesS += std::to_string(it->second[k]);
                expressoesS += " ";
            }

            table.push_back({ it->first, expressoesS });
            expressoesS.clear();

        }

        for (auto &linha : table) {
            int maxLines = 1;
            vector<vector<string>> cellLines(linha.size());

            for (size_t i = 0; i < linha.size(); ++i) {
                string cellValue = linha[i];
                int numLines = static_cast<int>(cellValue.length() / 35) + 1;
                maxLines = max(maxLines, numLines);

                for (int line = 0; line < numLines; ++line) {
                    int startPos = line * 35;
                    int endPos = min(static_cast<int>(cellValue.length()) - startPos, 35);
                    string lineValue = cellValue.substr(startPos, endPos);
                    cellLines[i].push_back(lineValue);
                }
            }

            for (int line = 0; line < maxLines; ++line) {
                for (size_t i = 0; i < linha.size(); ++i) {
                    string cellValue = (line < cellLines[i].size()) ? cellLines[i][line] : " ";
                    f << setw(35) << left << setw(35) << left << cellValue << " ";
                }
                f << '|' << endl;
            }
            f << "+---------------------------------+----------------------------------+" << endl;
        }
        f.close();

    } else {
        cout << "Erro ao abrir o arquivo." << endl;
    }

}


void outputParagrafos(vector<Senteca> sentecas, vector<Paragrafo> paragrafos, int quantParagrafos, vector<map<string, Sword>> &printParagrafo, unordered_map<string, vector<int>>expressoes, int *aux) {
    int i = 0, cont = 1;
    int j = 0;
    string arq = "outputt.txt";
    string paragrafosS, sentencasS, linhasS, posicaoS, distanciaS, qtd;
    string loc = "dataset/" + arq;

    vector<vector<string>>table;

    ofstream f(loc,ios::out|ios::trunc);
    //ofstream f(loc);


    if (f.is_open()) {
        for (auto map : printParagrafo) {
            table.push_back({ "\n\nWORD", "PARAGRAPH", "SENTENCE", "LINE","APPERANCES","POSITIONS","DISTANCE" });

            for (auto pos : map) {
                paragrafosS += std::to_string(cont);

                for (int i = 0; i < (int)pos.second.sentenca.size(); i++) {
                    sentencasS += std::to_string(pos.second.sentenca[i]);
                    sentencasS += " ";
                }

                for (int i = 0; i < (int)pos.second.linha.size(); i++) {
                    linhasS += std::to_string(pos.second.linha[i]);
                    linhasS += " ";
                }

                for (int i = 0; i < (int)pos.second.posicao.size(); i++) {
                    posicaoS += std::to_string(pos.second.posicao[i]);
                    posicaoS += " ";
                }

                qtd = std::to_string(pos.second.quantidade);


                for (int i = 0; i < (int)pos.second.distancia.size(); i++) {
                    distanciaS += std::to_string(pos.second.distancia[i]);
                    distanciaS += " ";
                }
                table.push_back({ pos.first, paragrafosS, sentencasS, linhasS, qtd, posicaoS, distanciaS });
                paragrafosS.clear(); sentencasS.clear(); linhasS.clear(); posicaoS.clear(); distanciaS.clear(); qtd.clear();
            }

            table.push_back({ "\n\nParagrafo: " + std::to_string(cont), "Linha Inicial: " + std::to_string(paragrafos[cont - 1].linhaI), "Linha Final: " + std::to_string(paragrafos[cont - 1].linhaF) });
            table.push_back({ "Sentenca", "StopWords", "Sem Stop Words" });

            for (int j = 0; j < paragrafos[cont-1].numSetencas; j++) {
                if (paragrafos[cont - 1].vetorSentencas[*aux].numeroPalavrasComStopWord != 0) {
                    table.push_back({ std::to_string(j + 1), std::to_string(paragrafos[cont - 1].vetorSentencas[*aux].numeroPalavrasComStopWord), std::to_string(paragrafos[cont - 1].vetorSentencas[*aux].numeroPalavraSemStopWord + 1) });
                }
                *aux = *aux + 1;
            }
            cont++;
        }

        for (auto &linha : table) {
            int maxLines = 1;
            vector<vector<string>> cellLines(linha.size());

            for (size_t i = 0; i < linha.size(); ++i) {
                string cellValue = linha[i];
                int numLines = static_cast<int>(cellValue.length() / 15) + 1;
                maxLines = max(maxLines, numLines);

                for (int line = 0; line < numLines; ++line) {
                    int startPos = line * 15;
                    int endPos = min(static_cast<int>(cellValue.length()) - startPos, 15);
                    string lineValue = cellValue.substr(startPos, endPos);
                    cellLines[i].push_back(lineValue);
                }
            }

            for (int line = 0; line < maxLines; ++line) {
                for (size_t i = 0; i < linha.size(); ++i) {
                    string cellValue = (line < cellLines[i].size()) ? cellLines[i][line] : " ";
                    f << setw(15) << left << setw(15) << left << cellValue << " ";
                }
                f << " " << endl;
            }
            f << "+-------------+---------------+---------------+---------------+---------------+---------------+---------------+ " << endl;
        }

        f << endl << endl;
        table.clear();



        // i = quantParagrafos - 1;

        // table2.add_row({ "Paragrafo: " + std::to_string(quantParagrafos), "Linha Inicial: " + std::to_string(paragrafos[i].linhaI), "Linha Final: " + std::to_string(paragrafos[i].linhaF) });

        // table2.add_row({ "Sentenca", "Número de palavras com StopWords", "Numero de palavras sem Stop Words" });

        // for (int j = 0; j < paragrafos[i].numSetencas; j++) {
        //     if (paragrafos[i].vetorSentencas[*aux].numeroPalavrasComStopWord != 0) {
        //         table2.add_row({ std::to_string(j + 1), std::to_string(paragrafos[i].vetorSentencas[*aux].numeroPalavrasComStopWord), std::to_string(paragrafos[i].vetorSentencas[*aux].numeroPalavraSemStopWord + 1) });
        //     }
        //     *aux = *aux + 1;
        // }

        // f << table2;
        // f << endl << endl;
        cout<<paragrafos[paragrafos.size()-1].vetorSentencas[paragrafos[paragrafos.size()-1].vetorSentencas.size()-1].numeroPalavrasComStopWord<<endl;
        f.close();
    } else {
        cout << "Erro ao abrir o arquivo." << endl;
    }

}