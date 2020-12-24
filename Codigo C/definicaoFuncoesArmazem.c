// FICHEIRO COM AS DEFENICOES DAS FUNCOES QUE MANIPULAM OS ARTIGOS DO ARMAZEM

#define N_ARTIGO 50

// criar um novo elemento da lista ligada, que no contexto do problema e um artigo
// Devolve o endereco do elemento criado em caso de sucesso, em caso de insucesso, devolve NULL
LLista criarArtigo(int refe, char *nome, float p, int q){
	LLista novo = (LLista) malloc(sizeof(struct lligada));
	if(novo!=NULL){
		(novo->artigo).referencia = refe;
		strcpy((novo->artigo).nomeArtigo,nome);
		(novo->artigo).preco=p;
		(novo->artigo).quantidade = q;
		novo->prox = NULL;
	}
	return novo;
}

// Procura se existe um artigo pela sua referencia na lista
//A funcao rece a cabeca da lista e a referencia a procurar
// Devolve o endereco do artigo se encontrar a sua referencia. Devolve NULL caso a referencia nao existe na lista
LLista procurarArtigo(LLista l, int refe){
	while(l!=NULL && (l->artigo).referencia != refe)
		l=l->prox;
	return l;
}

// Procura o nome e o preco de uma artigo no armazem pela referencia
// devolve 0 caso nao o encontra. 1 se o artigo existe.
int procurarNomePrecoQuantidade_porReferencia(LLista l, int refe, char *nome, float *pre, int *quanti){
	LLista p=NULL;
	if((p=procurarArtigo(l,refe))==NULL)
		return 0;
	strcpy(nome,(p->artigo).nomeArtigo);
	(*pre)=(p->artigo).preco;
	(*quanti)=(p->artigo).quantidade;
	return 1;
}

// Insere um artigo na lista.
// A lista esta ordenada por ordem crescente do numero da referencia do artigo
// Tem como parametro um apontador para apontador. Recebe o endereco da cabeca da lista
// Devolve, -1 se nao conseguir criar o artigo. 0 se o artigo ja exitir em stock(atualiza o stock). 1 se for criado um novo artigo.
int inserirArtigo(LLista *l, int r, char *n, float preco, int q){
	int nOpcao;
	LLista p = NULL, novo=criarArtigo(r,n,preco,q);
	if(novo==NULL){
		printf("Erro ao criar o artigo. Tente novamente.\n");
		return -1;
	}
	if((p=procurarArtigo((*l),(novo->artigo).referencia))!=NULL){
		printf("A referencia introduzida existe no armazem. Prima 1 para atualizar o stock ou 0 para sair: ");
		scanf("%d",&nOpcao);
		if(nOpcao==0)
			return 0;
		(p->artigo).quantidade = (p->artigo).quantidade + (novo->artigo).quantidade;
		printf("Stock Atualizado Com Sucesso.\n");
		return 1;
	}
	if((*l)==NULL){
        (*l)=novo;
        return 1;
	}
	if((novo->artigo).referencia < ((*l)->artigo).referencia){
		novo->prox=(*l);
		(*l)=novo;
		return 1;
	}
	p=(*l)->prox;
	while(p!=NULL && (novo->artigo).referencia > (p->artigo).referencia){
		l=&((*l)->prox);
		p=p->prox;
	}
	novo->prox=p;
	(*l)->prox=novo;
	return 1;
}



// Funcao que remova um artigo da lista ligada
// Recebe o o endereco da cabeca da lista e e colocada numa variavel do tipo apontador
// Devolve 0 se o artigo nao existir na lista. 1 se a remocao foi feira com sucesso
int removerArtigo(LLista *l, int refe){
	LLista p=(*l), q=NULL;
	if(*l==NULL)
		return 0;
	if(((*l)->artigo).referencia == refe){
		(*l)=(*l)->prox;
		free(p);
		return 1;
	}
	q=(*l)->prox;
	while(q!=NULL &&  refe > (q->artigo).referencia){
		p=q;
		q=q->prox;
	}
	if(q!=NULL){
		p->prox=q->prox;
		free(q);
		return 1;
	}
	return 0;
}




int alterarInformacoesArtigo(LLista *l, LLista pt, int nOpcao, int r, char *n, float p, int q){
	int novaReferencia;
	int quanti;
	float pre;
	if(nOpcao==1){
		printf("\nInsira a nova referencia: ");
		scanf("%d",&novaReferencia);
		if(procurarArtigo((*l),novaReferencia)!=NULL){
			printf("Referencia ja existe no armazem\n");
			return 0;
		}
		(pt->artigo).referencia=novaReferencia;
		return 1;
	}
	if(nOpcao==2){
		printf("\nInsira o novo nome: ");
		fflush(stdin);
		gets((pt->artigo).nomeArtigo);
		return 1;
	}
	if(nOpcao==3){
		printf("\nInsira o novo preco: ");
		scanf("%f",&pre);
		if(pre<=0){
            printf("\nPreco nao pode nulo ou negativo. \n\n");
            return 0;
		}
		(pt->artigo).preco = pre;
		return 1;
	}
	if(nOpcao==4){
		printf("\nInsira a nova quantidade: ");
		scanf("%d",&quanti);
		if(quanti == 0){
            printf("Tem a certeza que pretende remover o artigo (1 - confirmar ou 0 - anular operacao): ");
            scanf("%d",&nOpcao);
            if(nOpcao == 1){
                removerArtigo(l,r);
                return 2;
            }
            else
                printf("\nOperacao anulada com sucesso.\n\n");
		}
		else{
			(pt->artigo).quantidade = quanti;
			return 1;
		}
	}
}

int verDadosArtigo(LLista l){
	int refe;
	LLista p=NULL;
	printf("Insira a referecia do artigo: ");
	scanf("%d",&refe);
	p=procurarArtigo(l,refe);
	if(p==NULL){
		printf("\nNao existe nenhum artigo com essa referencia.\n");
		return 0;
	}
	printf("\nInformacao do artigo:\n\n");
	printf("\t Referencia:  %d\n",(p->artigo).referencia);
	printf("\t Nome:        %s\n",(p->artigo).nomeArtigo);
	printf("\t Preco:       %.2f euros\n",(p->artigo).preco);
	printf("\t Quantidade:  %d\n",(p->artigo).quantidade);
}



int escreverFicheiro(LLista l, char *nomeFich){
	FILE *fp = NULL;
	if((fp=fopen(nomeFich,"w+"))==NULL){
			printf("Erro ao abrir ficheiro\n");
			return 0;
	}
	while(l!=NULL){
		fprintf(fp,"%s\n",(l->artigo).nomeArtigo);
		fprintf(fp,"\t %d \t%.2f \t%d\n",(l->artigo).referencia, (l->artigo).preco, (l->artigo).quantidade);
		l=l->prox;
	}
	fclose(fp);
	return 1;
}

int lerFicheiro(LLista *l, char *nomeFich){
	FILE *fp=NULL;
	int r,q,comprimento;
	float p;
	char frase[50];
	if((fp=fopen(nomeFich,"r"))==NULL){
		return 0;
	}
	while(fgets(frase,50,fp) != NULL){
			comprimento=strlen(frase);
			if(frase[comprimento-1]=='\n'){
				frase[comprimento-1]=0;
			}
			fscanf(fp,"%d %f %d\n",&r, &p, &q);
			inserirArtigo(l,r,frase,p,q);
	}
	fclose(fp);
}


// Insere as informacoes de um artigo
// devolve 1 se o artigo ja existe. 2 caso contrario
int inserirInformacaoArtigo(LLista l,int *r, char *n, float *p, int *q){
	LLista pt_l = NULL;
	int d;
	(*r)=inserirReferencia();
	pt_l = procurarArtigo(l,(*r));
	if(pt_l!=NULL){
			printf("\nReferencia ja existe no armazem.\n");
			strcpy(n,(pt_l->artigo).nomeArtigo);
			(*p)=(pt_l->artigo).preco;
			(*q)=(pt_l->artigo).quantidade;
			printf("\tReferencia: %d\n",(*r));
			printf("\tNome %s\n",n);
			printf("\tPreco: %.2f euros\n",(*p));
			printf("\tQuantidade: %d\n\n",(*q));
			printf("Insira quantidade a adicionar: ");
			scanf("%d",&d);
			(l->artigo).quantidade += d;
			return 1;
	}
	fflush(stdin);
	inserirNome(n);
	(*p)=inserirPreco();
	(*q)=inserirQuantidade();
	return 2;
}


// Funcao que cria um ficheiro com o nome enviado como argumento
// Devolve 1 em caso de sucesso. 0 se nao foi possivel criar
int criarFicheiro(char *nomeFich){
	FILE *fp=NULL;
	if((fp=fopen(nomeFich,"w"))==NULL)
		return 0;
	fclose(fp);
	return 1;
}

// imprime no standard input/output a lista total de todos os artigos existentes no armazem
// Recebe o endereco do primeiro membro da lista
void imprimeLista(LLista l){
    printf("\n\t\t\tLISTA DE TODOS OS ARTIGOS NO ARMAZEM\n\n");
    while(l!=NULL){
        printf("%s\n",(l->artigo).nomeArtigo);
        printf("%4d\t %.2f euros \t %d\n\n",(l->artigo).referencia, (l->artigo).preco, (l->artigo).quantidade);
		l=l->prox;
    }
}


// Funcao recursiva que calcula o numero total de referencias existentes no armazem
int numeroTotalReferencias(LLista l){
	if(l==NULL)
		return 0;
	return 1+numeroTotalReferencias(l->prox);
}

// Funcao recursiva que calcula o numero total de artigos
int numeroTotalArtigos(LLista l){
	if(l==NULL)
		return 0;
	return (l->artigo).quantidade + numeroTotalArtigos(l->prox);
}

// Calcula o valor total de artigos no armazem
float valorTotalArtigosArmazem(LLista l){
	float total = 0.0;
	while(l!=NULL){
		total += (l->artigo).quantidade * (l->artigo).preco;
		l=l->prox;
	}
	return total;
}
