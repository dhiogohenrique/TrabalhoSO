//Dhiogo Henrique Rodrigues das Neves, 215004
//Julia Yumi Nakamura, 219372
//Rodrigo Fronza, 224192

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#define NUM_THREADS
int a[101];

typedef struct node {
    int j;
    int f;
} NODE;

void * MergeSort(void *a);
void Merge(int i, int j);

int main (int argc, char *argv[ ]){
    FILE* fp;
    FILE* fw;
    clock_t tempo;
    tempo = clock();
    int contador=0, argcNOVO, contnovo, ret;
    char charvet[102];
    int num = atoi(argv[1]); //numero de threads
    NUM_THREADS num;
    char t[2] = ",";
    char *token;
    NODE m;
    pthread_t tid;
    
    for(int cont=2; cont<(argc-1); cont++){
    	fp = fopen(argv[cont], "r");
	//pega o que tem nos arquivos e joga numa vetor
	    
    	fscanf(fp,"%s",charvet);
	token = strtok(charvet,t);
	    
   	while(token != NULL){
    		a[contador]=atoi(token);
		contador++;
		token = strtok(NULL,t);
    	}
       fclose(fp);
    }
    
    contnovo = contador-1;
    m.j = 0;
    m.f = contnovo;
    
    ret=pthread_create(&tid, NULL, MergeSort, &m);
        if (ret) {    
            exit(1);
        }

    pthread_join(tid, NULL);
    /*fopen(argv[argc-1], "w"); 
    escreve no ultimo indice dos argumentos, no caso o arquivo de saida*/
    argcNOVO=argc-1;
    fw = fopen(argv[argcNOVO], "w");
    for(int h=0; h <= contnovo;h++){
        fprintf(fw,"%d ",a[h]);
    }
    
    printf("Tempo de execução: %f\n",(clock()-tempo)/(double)CLOCKS_PER_SEC);
    
    return 0;
}

void * MergeSort(void *a){
    
        NODE *p = (NODE *)a;
        NODE num1, num2;
        int meio = (p->j+p->f)/2;
        pthread_t tid1, tid2;
        int ret;

        num1.j = p->j;
        num1.f = meio;

        num2.j = meio+1;
        num2.f = p->f;

        if (p->j >= p->f){
            return 0;
        }
        ret = pthread_create(&tid1, NULL, MergeSort, &num1);
        if (ret) {
            exit(1);
        }


        ret = pthread_create(&tid2, NULL, MergeSort, &num2);
        if (ret) {  
            exit(1);
        }

        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        Merge(p->j, p->f);
        pthread_exit(NULL);
}

void Merge(int i, int j){
    
        int meio = (i+j)/2; 
        int ai = i;
        int bi = meio+1;

        int newa[j-i+1], newai = 0;

        while(ai <= meio && bi <= j){
                if (a[ai] > a[bi])
                        newa[newai++] = a[bi++];
                else                    
                        newa[newai++] = a[ai++];
        }

        while(ai <= meio){
                newa[newai++] = a[ai++];
        }

        while(bi <= j){
                newa[newai++] = a[bi++];
        }

        for (ai = 0; ai < (j-i+1) ; ai++)
                a[i+ai] = newa[ai];

}