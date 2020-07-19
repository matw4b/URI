#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int habitantes;
	int mediaPHab;
}moradia;

typedef struct node{
	moradia habitacao;
	struct node* proximo;
}no;

no** criaLista(){
	no** lista;
	lista = (no**) malloc(sizeof(no*));
	*lista = NULL;
	return lista;
}

no* alocaNo(){
	no* ponteiro = (no*) malloc(sizeof(no));
	ponteiro->proximo = NULL;
	return ponteiro;
}

void insereNo(no** lista, int habitantes, int consumo){
	
	no* aux;
	no* novo_No;
	no* antecessor;
	int divisao;
	divisao = consumo/habitantes;
	
	if(*lista == NULL){
		*lista = alocaNo();
		(*lista)->habitacao.habitantes = habitantes;
		(*lista)->habitacao.mediaPHab = divisao;
	}
	else{
		if(divisao == ((*lista)->habitacao.mediaPHab)){
			(*lista)->habitacao.habitantes += habitantes;
		}
		else if(divisao < ((*lista)->habitacao.mediaPHab)){
			aux = alocaNo();
			aux->habitacao.habitantes = habitantes;
			aux->habitacao.mediaPHab = divisao;
			aux->proximo = *lista;
			*lista = aux;
		}
		else if(divisao > ((*lista)->habitacao.mediaPHab)){
			if((*lista)->proximo == NULL){
				(*lista)->proximo = alocaNo();
				(*lista)->proximo->habitacao.habitantes = habitantes;
				(*lista)->proximo->habitacao.mediaPHab = divisao;
			}
			else{
				aux = *lista;
				antecessor = aux;
				while( (aux->proximo != NULL) && (divisao > aux->habitacao.mediaPHab)){
					if(aux != antecessor)
						antecessor = antecessor->proximo;
					aux = aux->proximo;
				}
				if( divisao == aux->habitacao.mediaPHab)
					aux->habitacao.habitantes += habitantes;
				else if( divisao < aux->habitacao.mediaPHab ){
					novo_No = alocaNo();
					novo_No->habitacao.habitantes = habitantes;
					novo_No->habitacao.mediaPHab = divisao;
					novo_No->proximo = aux;
					antecessor->proximo = novo_No;
				}
				else if(divisao > aux->habitacao.mediaPHab){
					novo_No = alocaNo();
					novo_No->habitacao.habitantes = habitantes;
					novo_No->habitacao.mediaPHab = divisao;
					novo_No->proximo = aux->proximo;
					aux->proximo = novo_No;
				}
			}
		}
	}
}

void liberaLista(no** lista){
	
	no* aux;
	
	if(lista != NULL){
		aux = *lista;
		if(*lista != NULL){
			while(aux->proximo != NULL){
				*lista = (*lista)->proximo;
				free(aux);
				aux = *lista;
			}
			free(*lista);
			*lista = NULL;
		}
	}
}

void imprimeLista(no** lista){
	no* aux;
	aux = *lista;
	while(aux != NULL){
		printf("%d-%d", aux->habitacao.habitantes, aux->habitacao.mediaPHab);
		if(aux->proximo != NULL)
			printf(" ");
		aux = aux->proximo;
	}
	printf("\n");
}

int main(){
	
	unsigned long int n; /*numero de casos*/
	unsigned long int i, j = 0; /*iteracoes*/
	int x; /*imoveis/habitacoes*/
	int y; /*consumo*/
	unsigned long int tHab = 0, tCon = 0; /*total de habitantes e total consumido*/
	double resultado;
	/*FILE* fd;
	char arquivo[] = "teste.txt";
	fd = fopen(arquivo, "r");*/
	
	no** lista = criaLista();
	
	/*while(fscanf(fd,"%ld", &n) && n){*/
	while(scanf("%ld", &n) && n){
		j++;
		for(i = 0; i<n; i++){
			/*if(fscanf(fd,"%d %d", &x, &y)){*/
			if(scanf("%d %d", &x, &y)){
				insereNo(lista, x, y);
				tHab += x;
				tCon += y;
			}
		}
		if(j>1)
			printf("\n");
		printf("Cidade# %ld:\n", j);
		imprimeLista(lista);
		resultado = (tCon*100)/tHab;
		resultado = resultado/100;
		printf("Consumo medio: %.2lf m3.\n", resultado);
		liberaLista(lista);
		tHab = 0;
		tCon = 0;
	}
	free(lista);
	lista = NULL;
	/*fclose(fd);*/
	
	return 0;
}