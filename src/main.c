#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define MAX_WORKERS 4
int primo = 0, quantidade =0,  vetor_numeros[15];
pthread_mutex_t chave;

int isPrimo(int n){
    if (n==0) return 0;
    if (n==1) return 0;
    int i, divisores=0;
    for (i=2;i<=n;i++){
        if (n%i==0){
            divisores++;
            //printf("%d divide %d", i, n);
        }
        if (divisores==2) return 0;
    }
    //printf("%d Primo\n", n);
    return 1;
}
void* prime_thread(){
    int aux;
    while(1){
        //Pega o proximo numero livre
        pthread_mutex_lock(&chave);
        if (quantidade==-1){//caso nao haja encerra o programa
            pthread_mutex_unlock(&chave);
            break;
        }
        aux = quantidade;
        quantidade--;
        pthread_mutex_unlock(&chave);
        //calcula se e primo
        if (isPrimo(vetor_numeros[aux])){
            pthread_mutex_lock(&chave);
            primo++;
            pthread_mutex_unlock(&chave);
        }
        
    }
    return NULL;
}

int main() {
    int i;
    char aux;
    pthread_t threads[4];
    
    //Captar entrada
    while (1){
        scanf("%d", &vetor_numeros[quantidade]);
        scanf("%c", &aux);
        //printf("%d, %d\n", memoria[memoria[14]], memoria[14]);
        if (aux == '\n') break;
        quantidade++;
    }
    i=0;
    //comeca o programa
    for (i=0; i<3; i++) pthread_create(&(threads[i]), NULL, prime_thread, NULL);
    for (i=0; i<3; i++) pthread_join(threads[i], NULL);
    printf("%d\n", primo);
    return 0;
}

