
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

void selecao_natural(FILE *arq, Lista *nome_arquivos_saida, int M, int nFunc, int numeroNomes){
    int totalLidos = 0;
    Lista* nomes = nome_arquivos_saida;
    TFunc** v = malloc(M * sizeof(TFunc*));
    int noVetor = 0;

    FILE* repositorio = fopen("repository.dat", "w+");
    int noRepositorio = 0;

    Lista* nomeAtual = nomes;
    FILE* particaoAtual = NULL;
    int naParticaoAtual = 0;

    while(possoLerMais(totalLidos, nFunc)) {
        if(noVetor < M) {
            v[noVetor] = recuperaFuncionario(arq, &totalLidos);
            noVetor++;
        }

        if(noVetor < M)
            continue;

        int menor = buscarMenor(v, noVetor);
        if(particaoAtual == NULL) {
            char* nome = nomes->nome;
            particaoAtual = abrirParticao(nome);
            nomeAtual = nomes;

            atualizaNomeNaParticao(nomes, numeroNomes);
            nomes = nomes->prox;
        }
        if(naParticaoAtual >= M) {
            fclose(particaoAtual);
            particaoAtual = NULL;
            naParticaoAtual = 0;
            continue;
        }
        fseek(particaoAtual, naParticaoAtual * tamanho_registro(), SEEK_SET);
        salva_funcionario(v[menor], particaoAtual);

        naParticaoAtual++;

        if(!possoLerMais(totalLidos, nFunc)) {
            for (int i = menor; i < noVetor - 1; i++) {
                v[i] = v[i + 1];
            }
            noVetor--;
            break;
        }

        int code = v[menor]->cod;
        free(v[menor]);
        v[menor] = recuperaFuncionario(arq, &totalLidos);

        menor = buscarMenor(v, noVetor);

        if(v[menor]->cod < code) {
            fseek(repositorio, noRepositorio * tamanho_registro(), SEEK_SET);
            salva_funcionario(v[menor], repositorio);
            noRepositorio++;
            if(!possoLerMais(totalLidos, nFunc)) {
                for (int i = menor; i < noVetor - 1; i++) {
                    v[i] = v[i + 1];
                }
                noVetor--;
                break;
            }
            v[menor] = recuperaFuncionario(arq, &totalLidos);
        }

        if(noRepositorio < numeroNomes) {
            continue;
        }
        fclose(particaoAtual);

        char* nome = nomes->nome;
        particaoAtual = abrirParticao(nome);
        nomeAtual = nomes;
        atualizaNomeNaParticao(nomes, numeroNomes);
        nomes = nomes->prox;

        int* ultimoSalvo = NULL;
        int i = 0;
        while(noVetor > 0)
        {
            fseek(particaoAtual, i * tamanho_registro(), SEEK_SET);
            int lower = buscarMenor(v, noVetor);
            salva_funcionario(v[lower], particaoAtual);
            imprime_funcionario(v[i]);

            for (int i = lower; i < noVetor - 1; i++) {
                v[i] = v[i + 1];
            }
            noVetor--;
            i++;
        }

        for (int i = 0; i < noVetor; i++)
            free(v[i]);
        noVetor = 0;
        for (int i = 0; i < noRepositorio; i++)
        {
            fseek(repositorio, i * tamanho_registro(), SEEK_SET);
            v[i] = le_funcionario(repositorio);
            noVetor++;
        }
        noRepositorio = 0;

        fclose(particaoAtual);
        particaoAtual = NULL;
        naParticaoAtual = 0;


    }

    if(particaoAtual) {
        fclose(particaoAtual);
        particaoAtual = NULL;
        naParticaoAtual = 0;
    }
    int ultimaParticao = 0;
    if(!(noVetor <= 0 && noRepositorio <= 0)) {

        if(noRepositorio > 0) {
            char* nome = nomes->nome;
            particaoAtual = abrirParticao(nome);
            nomeAtual = nomes;
            naParticaoAtual = 0;
            for (int i = 0; i < noRepositorio; i++)
            {
                fseek(repositorio, i * tamanho_registro(), SEEK_SET);
                TFunc* func = le_funcionario(repositorio);
                fseek(particaoAtual, naParticaoAtual * tamanho_registro(), SEEK_SET);
                salva_funcionario(func, particaoAtual);
                imprime_funcionario(v[i]);
                naParticaoAtual++;
            }
            fclose(particaoAtual);
            naParticaoAtual = 0;
        }

        if(noVetor > 0) {
            atualizaNomeNaParticao(nomes, numeroNomes);
            nomes = nomes->prox;
            char* nome = nomes->nome;
            particaoAtual = abrirParticao(nome);
            nomeAtual = nomes;
            naParticaoAtual = 0;
            for (int i = 0; i < noVetor; i++)
            {
                fseek(particaoAtual, i * tamanho_registro(), SEEK_SET);
                salva_funcionario(v[i], particaoAtual);
                imprime_funcionario(v[i]);
                naParticaoAtual++;
            }
            fclose(particaoAtual);
        }
    }
    fclose(repositorio);
    free(v);

}

TFunc* recuperaFuncionario(FILE* arq, int* totalLidos) {
    fseek(arq, *totalLidos * tamanho_registro(), SEEK_SET);
    TFunc* func = le_funcionario(arq);
    (*totalLidos)++;
    return func;
}

void atualizaNomeNaParticao(Lista* nomes, int* numeroNomes) {
    if(nomes->prox == NULL) {
        char* novoNome = malloc(5 * sizeof(char));
        (*numeroNomes)++;
        sprintf(novoNome, "p%d.dat", *numeroNomes);
        nomes->prox = cria(novoNome, NULL);
    }
}

int possoLerMais(int totalLidos, int nFunc) {
    return totalLidos < nFunc;
}

FILE* abrirParticao(char* nome) {
    FILE* file = fopen(nome, "w+");
    return file;
}

int buscarMenor(TFunc* v[], int tam) {
    int menor = 0;
    for (int k = 1; k < tam; k++)
    {
        if(v[menor]->cod > v[k]->cod)
            menor = k;
    }
    return menor;
}


