
#include "funcionarios.h"
#include <stdlib.h>
#include <limits.h>
#include "particoes.h"

void classificacao_interna(FILE *arq, Lista *nome_arquivos_saida, int M, int nFunc) {
    rewind(arq); //posiciona cursor no inicio do arquivo


    int reg = 0;

    while (reg != nFunc) {
        //le o arquivo e coloca no vetor
        TFunc *v[M];
        int i = 0;
        while (!feof(arq)) {
            fseek(arq, (reg) * tamanho_registro(), SEEK_SET);
            v[i] = le_funcionario(arq);
       //     imprime_funcionario(v[i]);
            i++;
            reg++;
            if(i>=M) break;
        }

        //ajusta tamanho M caso arquivo de entrada tenha terminado antes do vetor
        if (i != M) {
            M = i;
        }

        //faz ordenacao
        for (int j = 1; j < M; j++) {
            TFunc *f = v[j];
            i = j - 1;
            while ((i >= 0) && (v[i]->cod > f->cod)) {
                v[i + 1] = v[i];
                i = i - 1;
            }
            v[i + 1] = f;
        }

        //cria arquivo de particao e faz gravacao
        char *nome_particao = nome_arquivos_saida->nome;
        nome_arquivos_saida = nome_arquivos_saida->prox;
        printf("\n%s\n", nome_particao);
        FILE *p;
        if ((p = fopen(nome_particao, "wb+")) == NULL) {
            printf("Erro criar arquivo de saida\n");
        } else {
            for (int i = 0; i < M; i++) {
                fseek(p, (i) * tamanho_registro(), SEEK_SET);
                salva_funcionario(v[i], p);
                imprime_funcionario(v[i]);
            }
            fclose(p);
        }
        for(int jj = 0; jj<M; jj++)
            free(v[jj]);
    }
}

void selecao_natural(FILE *arq, Lista *nome_arquivos_saida, int M, int nFunc, int n){
    /*PARTE 1 TRABALHO*/

    //posiciona cursor no inicio do arquivo
    rewind(arq);

    int reg = 0;
    int i=0;
    int controle = 0;
    TFunc *v[M];

    //Passo 1: (POSSIVEL ALTERAÇÃO NECESSÁRIA
    //le o arquivo e colocar os dados em um vetor
    //se controle == 0 é pra ler o arquivo inicial (arq)
    if(controle==0){
        while (reg != nFunc) {
            while (!feof(arq)) {
                fseek(arq, (reg) * tamanho_registro(), SEEK_SET);
                v[i] = le_funcionario(arq);
                i++;
                reg++;
                if(i>=M) break;
                }
            }
        }

        //APARTIR DA SEGUNDA ITERAÇÃO
        /*else {
             //verificar o tamanho do reservatório (tam)
             //criar um vetor TFunc *v[tam];
             reg=0;
             i=0;

             while (reg != tam) {
                    while (!feof(reservatorio)) {
                        fseek(resevatorio, (reservatorio) * tamanho_registro(), SEEK_SET);
                        v[i] = le_funcionario(reservatorio);
                        i++;
                        reg++;
                        if(i>=tam) break;
                        }
            }

        }*/

    //Passo 2:
    // Escolher o menor registro R
    //verifica os códigos
    int r=v[0]->cod;
    //recebe a posição
    int pos;

        for(i=0;i<M;i++){
                if(r>v[i]->cod){
                    r=v[i]->cod;
                    pos=i;
                }
                //imprime_funcionario(v[i]);
                 //free(v[i]);
                }


    //Passo 3:
    //Gravar o registro r na partição de saida


     //cria arquivo de particao e faz gravacao
        char *nome_particao = nome_arquivos_saida->nome;
        nome_arquivos_saida = nome_arquivos_saida->prox;
        printf("\n%s\n", nome_particao);
        FILE *p;
        if ((p = fopen(nome_particao, "wb+")) == NULL) {
            printf("Erro criar arquivo de saida\n");
        }

        //coloca o registro de menor valor [R] na partição criada
        salva_funcionario(v[pos], p);
        else {
            //não pode ser M e sim o tamanho do vetor, vai dar pau na segunda iteração
            //PASSO 4:
            for (int i = 0; i < M; i++) {

                    //quando o i chegar na posição do elemento já adicionado pular
                    if(i==pos){
                        continue;
                    }

                    fseek(p, (i) * tamanho_registro(), SEEK_SET);
                    //PASSO 5
                    if(v[i]->cod <v[i-1]->cod){
                      //colocar v[i] no reservatorio
                      //salva_funcionario(v[i], p);
                    } else {
                        //colocar v[i] na partição de saida
                        fseek(p, (i) * tamanho_registro(), SEEK_SET);
                        salva_funcionario(v[i], p);
                    }

               /* fseek(p, (i) * tamanho_registro(), SEEK_SET);
                salva_funcionario(v[i], p);
                imprime_funcionario(v[i]);*/
            }
            fclose(p);
        }

        //PASSO 7: PENSAR CONDIÇÕES
        //PEGAR O RESERVATÓRIO LER SEUS DADOS NO VETOR V[] E REPETIR
        //PRECISA-SE SABER O TAMANHO DO VETOR



return 0;
}
