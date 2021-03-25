/*
    Arcabou�o para desenvolvimento do trabalho da disciplina de AEDSII 2020-1, utilizando os exemplos dos livros
    de Schildt, H. C Completo e Total. Ed. McGraw-Hill e de Ferraz, I. N. Programa��o com Arquivos. Editora Manole Ltda
      sobre o problema de funcion�rios e algoritmos.
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "ordenacao_busca.h"
#include "lista.h"
#include "particoes.h"
#include "intercalacao.h"
#include "arvore_binaria.h"


int menu(){
    setlocale(LC_ALL,"");
    int op;

    printf("\n\n**************MENU************** \n\nBASE DE DADOS\n");

    printf("\nDigite 1 para utilizar a base de dados funcionario de teste.");
    printf("\nDigite 2 se desejar imprimir a base de dados funcionario.");
    printf("\nDigite 3 se desejar imprimir o �ndice prim�rio da base de funcionarios.");


    printf("\n\nINTERPOLA��O\n");
    printf("\nDigite 4 para utilizar a estrutura de interpola��o teste.");
    printf("\nDigite 5, 6  para gerar partic�es ordenadas utilizando, respectivamente, os m�todos: classifica��o interna ou sele��o natural.");
    printf("\nDigite 7 para criar uma pilha com o conte�do das parti��es geradas.");
    printf("\nDigite 8, 9 para gerar intercalar as parti��es ordenadas utilizando, respectivamente, os m�todos: intercala��o basico, intercalacao arvore de vencedores.");

    printf("\n\nINSERTION SORT E �RVORE BIN�RIA, ARVORE B\n");
    printf("\nDigite 10 para criar �rvores bin�rias em mem�ria interna e externa.");
    printf("\nDigite 11 para ordenar a base de dados utilizando o m�todo insertion sort em disco. ");
    printf("\nDigite 12 para criar �rvore B+ de prefixo simples. ");


    printf("\nDigite -1 para sair: ");
    scanf("%d", &op);

    return op;

}

int main(){



    /*criando um arquivo l�gico para abir para leitura e escrita o arquivo bin�rio*/
    FILE* arq = fopen("base_funcionarios.dat", "wb+");
    if(arq == NULL) {
        printf("Arquivo base_funcionarios.dat n�o encontrado.\n");
        return 1;
    }

    /*criando um arquivo l�gico para abir para leitura e escrita do arquivo de indice primario ordenado*/
    FILE* arqIndicePrimario = fopen("IndicePrimarioFunc.dat", "wb+");
    if(arqIndicePrimario == NULL) {
        printf("Arquivo IndicePrimarioFunc.dat n�o encontrado.\n");
        return 1;
    }

    /*criando um arquivo l�gico para abir para leitura e escrita do arquivo de indice primario n�o ordenado*/
    FILE* arqIndicePrimarioNaoOrdenado = fopen("IndicePrimarioFuncNaoOrdenado.dat", "wb+");
    if(arqIndicePrimarioNaoOrdenado == NULL) {
        printf("Arquivo IndicePrimarioFuncNaoOrdenado.dat n�o encontrado.\n");
        return 1;
    }

    /*criando um arquivo l�gico para abir para leitura e escrita da �rvore bin�ria externa*/
    FILE* arqArvoreBinariaExterna = fopen("ArvoreBinariaExternaFunc.dat", "wb+");
    if(arqArvoreBinariaExterna == NULL) {
        printf("Arquivo ArvoreBinariaExternaFunc.dat n�o encontrado.\n");
        return 1;
    }


    int op = menu();
    int nFunc;

    int nParticoes, nElementos;
    Lista  * nomes = NULL;

    TPilha **vetPilhas;
    int crioubase = 0, crioulistadenomes = 0, criouparticoes = 0, crioupilhas = 0;

    //ponteiro para salvar o in�cio da lista de nomes
    Lista *prox;
    int *vetTopo;

    while(op!=-1){
        switch (op){
            case (1):
                //criando a base de dados de funcion�rios teste e o arquivo de �ndice prim�rio
                nFunc = 20;
                cria_base_dados_funcionarios_teste(arq, arqIndicePrimario, arqIndicePrimarioNaoOrdenado, nFunc);
                crioubase = 1;
                printf("\n\n\n**FOI CRIADOOOOOOOOOOOO**\n\n\n");
                break;
            case (2):
                //imprime a base de dados dos funcion�rios
                if(crioubase==1)
                    imprime_base_dados_funcionarios(arq, nFunc);
                else  printf("Base de dados inexistente para ser impressa, crie utilizando a op��o 1 do menu!!!\n");
                break;
            case (3):
                //imprime o arquivo de �ndices prim�rios
                if(crioubase==1){
                    printf("\nArquivo ordenado\n ch:rrn\n");
                    imprime_indice_primario_funcionarios(arqIndicePrimario,nFunc);
                    printf("\nArquivo n�o ordenado\n ch:rrn\n");
                    imprime_indice_primario_funcionarios(arqIndicePrimarioNaoOrdenado,nFunc);
                }else  printf("Indice primario inexistente para ser impresso, ser� criado ap�s a defini��o da base de dados utilizando a op��o 1 do menu!!!\n");
                break;
            case (4):
                nParticoes = 10;
                nElementos = 2;
                printf("\n\nA estrutura de interpola��o ser� composta por 10 arquivos de no m�ximo 2 elementos.\n");
                nomes = cria("p1.dat", cria("p2.dat", cria("p3.dat", cria("p4.dat", cria("p5.dat",  cria("p6.dat",  cria("p7.dat",  cria("p8.dat",  cria("p9.dat",  cria("p10.dat", NULL))))))))));
                crioulistadenomes = 1;
                imprime(nomes);
                break;
            case (5):
                if(crioulistadenomes){
                    //cria as partic�es que cont�m a base de dados de funcion�rios usando o m�todo classifica��o interna
                    printf("\n\nGerando parti��es, utilizando o m�todo de classifica��o interna.\n");
                    classificacao_interna(arq, nomes, nElementos, nFunc);
                    //salvando o ponteiro para o in�cio da lista de nomes
                    prox = nomes;
                    criouparticoes=1;
                }else printf("Lista de nomes de arquivos inexistente para gerar parti��es, crie a estrutura de interpola��o utilizando a op��o 4 do menu!!!\n");
                break;
            case (6):
                if(crioulistadenomes){
                    printf("\n\nGerando parti��es, utilizando o m�todo selecao natural.\n");
                    selecao_natural(arq, nomes, nElementos, nFunc,1);

                    //salvando o ponteiro para o in�cio da lista de nomes
                    prox = nomes;
                    criouparticoes=1;
                }else printf("Lista de nomes de arquivos inexistente para gerar parti��es, crie a estrutura de interpola��o utilizando a op��o  4 do menu!!!\n");
                break;
           case (7):
                if(criouparticoes){
                    //criando pilha com o conte�do das parti��es geradas
                    vetPilhas = (TPilha **) malloc(sizeof(TPilha *) * (nParticoes));
                    vetTopo = (int *) malloc(sizeof(int) * (nParticoes));
                    for(int p = 0 ; p < nParticoes ; p++){
                        //alocando a mem�ria para salvar uma pilha para cada particao
                        vetPilhas[p] = (TPilha *) malloc(sizeof(TPilha) * (nElementos));
                        //abrindo primeira parti��o para leitura
                        FILE *part = fopen(nomes->nome, "rb+");
                        printf("Parti��o %s \n", nomes->nome);
                        nomes = nomes->prox;
                        //imprimindo os funcion�rios gravados nas parti��es
                        imprime_base_dados_funcionarios(part, nElementos);
                        //inicializando os topos das pilhas
                        vetTopo[p] = -1;
                        //criando pilha atrav�s da leitura da parti��o
                        cria_pilha_particao(vetPilhas[p], part, nElementos, &vetTopo[p]);
                        //fechando a parti��o
                        fclose(part);
                    }
                    crioupilhas = 1;
                    nomes = prox;
                }else printf("Parti��es n�o foram criadas, crie as parti��es utilizando as op��es 5 ou 6  do menu!!!\n");
                break;
            case (8):
                if(criouparticoes){
                    printf("\n\nIntercalando as parti��es, utilizando o m�todo de intercala��o basico.\n");
                    intercalacao_basico("arquivo_intercalado.dat", nParticoes, nomes);
                    //imprimindo o arquivo intercalado
                    FILE *fi = fopen("arquivo_intercalado.dat","rb+");
                    imprime_base_dados_funcionarios(fi,nFunc);
                    fclose(fi);
                }else printf("Parti��es n�o foram criadas, crie as parti��es utilizando as op��es 5 ou 6 do menu!!!\n");
                break;
            case (9):
                printf("M�todo a ser implementado na parte I do trabalho.\n");
                if(criouparticoes){
                    if(crioupilhas){
                        intercalacao_arvore_de_vencedores(vetPilhas, vetTopo, "arquivo_intercalado.dat", nParticoes);
                    }else printf("As pilhas das parti��es geradas n�o foram criadas, crie as pilhas utilizando as op��es 7!!!\n");
                }else printf("Parti��es n�o foram criadas, crie as parti��es utilizando as op��es 5 ou 6  do menu!!!\n");


                //imprimindo o arquivo intercalado
                FILE *fi = fopen("arquivo_intercalado.dat","rb+");
                imprime_base_dados_funcionarios(fi,nFunc);
                fclose(fi);
                break;
            case (10):
                //cria �rvore bin�ria em mem�ria utilizando o arquivo de �ndice prim�rio ordenado
                if(crioubase==1){
                    printf("\nArvore bin�ria em mem�ria pelo arquivo de  �ndice prim�rio ordenado\n <nopai <noesq><nodireita> >\n");
                    cria_arvore_binaria_indice_primario(arqIndicePrimario,nFunc);
                    printf("\nArvore bin�ria em mem�ria pelo arquivo de �ndice prim�rio n�o ordenado\n <nopai <noesq><nodireita> >\n");
                    cria_arvore_binaria_indice_primario(arqIndicePrimarioNaoOrdenado,nFunc);
                    printf("\nArvore bin�ria externa pelo arquivo de base de dados do funcion�rio\n <nopai <noesq><nodireita> >\n");
                    criar_arvore_binaria_externa(arq,arqArvoreBinariaExterna);
                }else  printf("Arquivo de �ndice primario inexistente para a cria��o da arvore binaria, crie utilizando a op��o 1 do menu!!!\n");
                break;
            case (11):
                 //ordenando a base de dados utilizando ordena��o direta no arquivo com o m�todo inseriton sort
                if(crioubase==1){
                    insertion_sort_disco(arq, nFunc);
                    imprime_base_dados_funcionarios(arq, nFunc);
                    //procurando por um funcion�rio na base de dados usando o m�todo de busca bin�ria
                    int busca_codigo;
                    printf("\n\nInforme o codigo do funcion�rio procurado (digite -1 caso n�o queira procurar um funcion�rio): ");
                    scanf("%d", &busca_codigo);
                    if(busca_codigo!= -1){
                        TFunc* func = busca_binaria(busca_codigo, arq, nFunc);
                        imprime_funcionario(func);
                        free(func);
                    }
                }else printf("Base de dados inexistente para ser ordenada, crie utilizando a op��o 1 do menu!!!\n");
                break;
            case (12):
                printf("M�todo a ser implementado na parte II do trabalho.\n");
                if(crioubase==1){
                    ;//criar_arvore_B();
                }else printf("Base de dados inexistente para ser ordenada, crie utilizando a op��o 1 do menu!!!\n");
                break;
            default:
                printf("\nOp��o inv�lida!");
        }
        op = menu();
    }

	while(nomes) {
		prox = nomes->prox;
		free(nomes);
		nomes = prox;
	}

    for(int p = 0; p <nParticoes; p++){
        free(vetPilhas[p]);
	}
	free(vetPilhas);

    fclose(arqIndicePrimario);
    fclose(arqIndicePrimarioNaoOrdenado);
    fclose(arqArvoreBinariaExterna);
    fclose(arq);

    return 0;
}
