# Auxiliar de Redação

<div style="display: inline-block;">    
<img align="center" height="20px" width="60px" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"/> 
<img align="center" height="20px" width="80px" src="https://img.shields.io/badge/Made%20for-VSCode-1f425f.svg"/> 
</a> 
</div>

<p> </p>
<p> </p>

# Introdução
<p align="justify">
A publicação dos resultados de pesquisa é uma etapa crucial do trabalho científico. Geralmente, esses resultados são compartilhados na forma de artigos em congressos e periódicos, após passarem por uma revisão rigorosa quanto à forma e conteúdo. Infelizmente, é comum encontrar artigos na academia que apresentam dificuldades de leitura, além de conter erros de
ortografia e gramática.

<p align="justify">
Para lidar com a questão acima apresentada, existem diversas ferramentas de auxílio disponíveis. Por exemplo, no Unix, o utilitário "ispell" pode ser utilizado para verificar a ortografia de textos em inglês. Já para outras línguas e ambientes, há outras opções de ferramentas específicas. Além disso, existem ferramentas comerciais baseadas em técnicas de inteligência artificial, que buscam detectar erros gramaticais, analisar o estilo literário e fornecer estatísticas sobre parágrafos. O grammarly e o chatgpt são dois exemplos disso.

<p align="justify">
O objetivo deste trabalho é especificar, projetar e implementar um sistema que ajude no processo de redação. Para realizar essa tarefa, foi essencial escolher cuidadosamente as estruturas de dados e os respectivos algoritmos, visando a utilização eficiente do sistema na prática

<p align="justify">
O programa ira ler um arquivo contento um texto sem nenhuma formatação onde cada sentença termina por um sinal de pontuação. Cada parágrafo é separado por pelo menos uma linha em branco. Ao decorrer no texto existem palavras que nao possuem conteudo semantico, como artigos e conjunções denominadas "stop words". A lista de "stop words" foi fornecida atraves de um arquivo criado por nós.

|          Sinais de pontuação  | Stop words                                      |
|-------------------------------|-------------------------------------------------|
| `.`,   `!`,   `?`                   |   `artigos(a, o, as,os) ou conjunções(e, ou) `  |
               

<p align="justify">
A saida do programa contem diversas infomações, sendo elas: 

Para cada paragrafo do texto deve conter o numero da linha do arquivo fonte onde o paragrafo inicia e termina, o numero de sentenças existentes no paragrafo e o número de palavras de cada sentença incluindo e descartando as "stop words". A razão para inclusão dessas informações se deve ao fato de que existem em redações, parágrafos formados por uma única sentença (o que deve ser evitado), sentenças muito longas ou curtas de mais, ou mesmo uma mistura dessas situações.

As palavras que não são stop word listadas em ordem alfabéticas com a requência de sua ocorrência no texto, indicando as linhas do arquivo onde essas surgem. No caso em que a palavra aparece mais de uma vez em um mesmo parágrafo, foi indicado a sua ocorrência e a distância entre elas incluindo as stop words. Isso se deve ao fato de que é comum na escrita, principalmente científica, repetirmos palavras várias vezes ao longo do texto ou em um mesmo parágrafo.

A ocorrência de certas expressões sendo que para cada expressão foi indicado a linha no arquivo fonte onde aparece. O conjunto de expressões a serem analisadas foi lido de um arquivo txt criado por nós. Isso se deve ao fato de que existem certas expressões ou palavras que são frequentemente usadas mas não existem ou deixam o texto confuso ou pobre devido a sua inclusão. O exemplo mais comum é "em nível de" ou "a nível de" como é bem discutido pelo filólogo Vianney Mesquita, professor da Universidade Federal do Ceará em um de seus livros. Também temos exemplos de palavras que não existem ou são usadas com sentidos inadequados como "deletar" no sentido de remover, e "suportar" no sentido de ter uma funcionalidade. 


# Arquivos e Funções                                                       

O projeto é dividido entre três arquivos de códigos própriamente ditos: `leitura.hpp`, `leitura.cpp` e `main.cpp`.

|  Arquivo                        |   Função                                                                                          |
| ------------------------------- | ------------------------------------------------------------------------------------------------- |
|  `main.c`                       | Arquivo principal para iniciar e chamar as funções do código                                                    |
|  `leitura.hpp`                  | Define as funções e as estruturas que foram utilizadas no código |
|  `leitura.cpp`                  | Contém o escopo de todas as funções que foram utilizadas |

Como saída, o programa irá gerar no terminal apenas o tempo gasto para o mesmo ser executado. Os demais resultados da análise serão exibidos em um arquivo de saida *.txt* criado à partir da execução do código.

# Lógica Implementada
  O arquivo principal, `main.cpp`, inicializa o tempo de execução, chama a função `readPrincipal()` e marca o tempo ao fim do programa, respectivamente. A função citada é a responsável por todo o funcionamento do código propriamente dito. Definida no `leitura.hpp` e trabalhada no `leitura.cpp`, ela é a que processa todas as demais funções presentes no projeto.

### Funcionamento da Função readPrincipal()
Em primeiro lugar, é definido o nome do arquivo de texto que será analizado, posteriormente, outras variáveis dos tipos *int, bool e string* são apresentadas para cumprirem funções específicas. São também definidas variáveis do tipo `unordered_map`. Algumas variáveis desse último tipo processam informações de uma struct denominada *Sword*(criada no arquivo *leitura.hpp*), que armazena as informações de cada palavra individualmente:
- Quantidade (int)
- Distância (vector<int>)
- Posição (vector<int>)
- Parágrafo (vector<int>)
- Sentença (vector<int>)
  
A primeira função referenciada chama-se `preencheMapPontos()`, ela elimina certos caracteres que não serão analisados como palavras.
Posteriormente, outras duas funções são executadas: `readExpressoes()` e `readStopWords()`, elas servem para ler os arquivos *expressoes.txt* e *stopwords.txt* respectivamente, identificar cada um de seus elementos e armazená-los em um *unordered_map* para, depois, servir de suporte para análise do arquivo de texto principal.

# Testes Realizados
<p align="justify">
  
<p> </p>

# Análise dos Testes 
<p align="justify">
  
<p> </p>

# Conclusão
<p align="justify">
  
<p> </p>

# Compilação e Execução

Esse pequeno exemplo possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

<p> </p>

# Contatos

#### Felipe Werneck
<div style="display: inline-block;">
<a href="https://t.me/felipewom">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white"/> 
</a>

<a href="https://www.linkedin.com/in/felipe-werneck-93520a209">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white"/>
</a>

</div>

#### Felipe Parreiras
<div style="display: inline-block;">
<a href="https://t.me/fparreiras">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white"/> 
</a>

<a href="https://www.linkedin.com/in/felipe-parreiras-56b075277/">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white"/>
</a>

</div>

#### José Marconi Almeida
<div style="display: inline-block;">
<a href="https://t.me/jmarconia">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white"/> 
</a>

<a href="https://www.linkedin.com/in/jmarconi-almeida/">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white"/>
</a>

</div>

#### Lucas Fernandes
<div style="display: inline-block;">
<a href="https://t.me/lucas_fba">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white"/> 
</a>

<a href="https://www.linkedin.com/in/lucas-fernandes-381091204/">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white"/>
</a>

</div>

<p> </p>
