// FICHEIRO COM AS DEFINICOES DE FUNCOES AUXILIARES

#define N_ARTIGO 50

void inic_random(){
	long ultime;
	time(&ultime);
	srand((unsigned) ultime);
}
// Insere uma referencia de uma artigo. Devolve como resultado da funcao o inteiro inserido
int inserirReferencia(){
	int referencia;
    printf("Insira a referencia: ");
    scanf("%d",&referencia);
	return referencia;
}

// Insere o preco de um artigo
// Devolve como resultado da funcao o preco introduzido
float inserirPreco(){
	float preco;
	printf("Insira o preco: ");
	scanf("%f",&preco);
	return preco;
}


// Insere o nome de um artigo
// Recebe uma string
void inserirNome(char *nomeArtigo){
	printf("Insira o nome do artigo: ");
	gets(nomeArtigo);
}

// Insere a quantidade
int inserirQuantidade(){
	int quantidade;
	printf("Insira a quantidade do artigo: ");
	scanf("%d",&quantidade);
	return quantidade;
}


// Funcao recursiva que verifica se existe uma encomenda com o mesmo numero
int existeNumeroEncomenda(LEncomendas l, int n){
	if(l==NULL)
		return 0;
	if(l->numeroEncomenda == n)
		return 1;
	existeNumeroEncomenda(l->prox,n);
}

void creditos(){
	printf("\t**********************************************\n");
	printf("\n");
	printf("\t                  GESTAO  \n");
	printf("\t              DE UM ARMAZEM\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t Copyright c 2018 Todos os direitos reservados\n");
	printf("\t            realizado por : Bruno e Catarina\n");
	printf("\t                        universidade do minho\n");
	printf("\n");
	printf("\n");
	printf("\t***********************************************\n");
}

int subMenuDefenicoes(){
	int n;
    puts("\t******************************** 1.9 DEFINICOES **********************************");
    putchar('\n');
    printf("\n\n");
    printf("\t\t\t 1. Como usar o programa\n");
    printf("\t\t\t 2. Restaurar o programa - Inicializar o armazem\n");
	putchar('\n');
	printf("\t\t\t 5. Ir para o Menu Inicial\n");
	printf("\n\n");
    puts("\t******************************** 1.9 DEFINICOES **********************************");
    putchar('\n');
    do{
        printf("Insira a opcao: ");
        scanf(" %d",&n);
    }
    while((n<1 || n>2) && n!=5);
    return n;
}



// imprime a lista com todas as encomendas efetuadas

int menu(){					// mostra as opcoes do menu
    int n;
    puts("\t******************************** 1 MENU INICIAL **********************************");
    putchar('\n');
    printf("\n\n");
    printf("\t\t\t  1. Inserir artigo\n");
    printf("\t\t\t  2. Ver informacoes de um artigo\n");
    printf("\t\t\t  3. Remover artigo\n");
	printf("\t\t\t  4. Alterar informacoes de um artigo\n");
    printf("\t\t\t  5. Ver lista de stock do armazem\n");
	printf("\t\t\t  6. Numero total de artigos e referencias no armazem\n");
	putchar('\n');
	printf("\t\t\t  7. Fazer uma encomenda\n");
	printf("\t\t\t  8. Ver lista de encomendas realizadas\n");
	printf("\t\t\t  9. Numero Total de encomendas realizadas\n");
	printf("\t\t\t 10. Numero total de referencias e artigos encomendados\n");
	printf("\t\t\t 11. Valor total faturado\n");
	putchar('\n');
	printf("\t\t\t 12. Definicoes\n\n\n");
	printf("\t\t\t 0. Terminar o Programa\n\n");
    puts("\t******************************** 1 MENU INICIAL **********************************");
    putchar('\n');
    do{
        printf("Insira a opcao: ");
        scanf(" %d",&n);
    }
    while((n<1 || n>12) && n!=0);
    return n;
}

int esperar(){
            char c='a';
			do{
				printf("Prima <M> para o Menu Inicial. Prima <0> para sair do programa: ");
                scanf(" %c",&c);
			}
            while(toupper(c)!='M' && c!='0');
            if(c=='0')
				return 0;
            else
                return 1;
}
