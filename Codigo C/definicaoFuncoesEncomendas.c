// FICHEIRO COM AS DEFINICOES DAS FUNCOES QUE MANIPULAM AS ENCOMENDAS

#define N_ARTIGO 50

LEncomendas alocarEncomenda(int numeroEncomenda, int numReferenciasEncomenda, int numArtigosEncomenda, float precoTotalEncomenda){
	LEncomendas novo = (LEncomendas) malloc (sizeof(struct encomendas));
	if(novo!=NULL){
		novo->numeroEncomenda = numeroEncomenda;
		novo->numReferencias = numReferenciasEncomenda;
		novo->numArtigos = numArtigosEncomenda;
		novo->precoTotal = precoTotalEncomenda;
		novo->prox = NULL;
	}
	return novo;
}

int inserirListaEncomendas(LEncomendas *en, int numeroEncomenda, int numReferenciasEncomenda, int numArtigosEncomenda, int precoTotalEncomenda){
	LEncomendas novo = alocarEncomenda(numeroEncomenda, numReferenciasEncomenda, numArtigosEncomenda, precoTotalEncomenda);
	LEncomendas q = NULL;
	if(novo==NULL)
		return 0;
	if(*en==NULL){
		(*en)=novo;
		return 1;
	}
	if((novo->numeroEncomenda) < (*en)->numeroEncomenda){
		novo->prox = (*en);
		(*en)=novo;
		return 1;
	}
	q=(*en)->prox;
	while(q!=NULL && (novo->numeroEncomenda) < (q->numeroEncomenda)){
		en=&((*en)->prox);
		q=q->prox;
	}
	novo->prox = q;
	(*en)->prox = novo;
	return 1;
}

int escreverFicheiroEncomendas(LEncomendas l, char *nomeFichE){
	FILE *fp = NULL;
	if((fp=fopen(nomeFichE,"w"))==NULL){
		printf("Erro ao abrir ficheiro\n");
		return 0;
	}
	while(l!=NULL){
		fprintf(fp,"\t%d\t\t%d\t\t%d \t\t%.2f\n",l->numeroEncomenda, l->numReferencias, l->numArtigos, l->precoTotal);
		l=l->prox;
	}
	fclose(fp);
}


int fazerEncomendas(LLista l, int *refe, char *n, float *pre, int *quanti, int *quantiEncomendar){
	printf("\n\n");
	(*refe)=inserirReferencia();
	if((procurarNomePrecoQuantidade_porReferencia(l,*refe,n,pre,quanti))==0){
		printf("Nao e possivel encomendar o artigo. Artigo nao existe no armazem.\n\n");
		return 0;
	}
	printf("\nArtigo a encomendar:\n");
	printf("\tNome: %s\n",n);
	printf("\tReferencia: %d\n",(*refe));
	printf("\tPreco: %.2f euros\n",(*pre));
	printf("\tStock disponivel: %d\n\n",(*quanti));
	printf("Quantidade a encomendar: ");
	scanf("%d",quantiEncomendar);
	if((*quantiEncomendar) > (*quanti)){
		printf("Nao e possivel efetuar a encomenda. Quantidade pretendida superior ao stock em armazem\n\n");
		return 0;
	}
	return 1;
}

int atualizarStock(LLista *l, int refe, int quantiEncomendar){
	LLista p = procurarArtigo((*l),refe);
	LLista q = NULL;
	if((p->artigo).quantidade > quantiEncomendar){
		(p->artigo).quantidade -= quantiEncomendar;
		return 1;
	}
	if(*l==p){
		(*l)=(*l)->prox;
		free(p);
		return 1;
	}
	p=(*l);
	q=p->prox;
	while(q!=NULL && (q->artigo).referencia != refe){
		p=q;
		q=q->prox;
	}
	p->prox=q->prox;
	free(q);
	return 1;
}

int lerFicheiroEncomendas(LEncomendas *en, char *nomeFichE){
	FILE *fp = NULL;
	int numeroEncomenda, numeroReferencias, numeroArtigos;
	float precoTotal;
	if((fp=fopen(nomeFichE,"r"))==NULL)
		return 0;
	while((fscanf(fp,"%d %d %d %f",&numeroEncomenda, &numeroReferencias, &numeroArtigos, &precoTotal)) != EOF){
		inserirListaEncomendas(en, numeroEncomenda, numeroReferencias, numeroArtigos, precoTotal);
	}
	fclose(fp);
	return 1;
}

void imprimeEncomendas(LEncomendas l){
	printf(" Numero Encomenda    Numero de Referencias  Numero de Artigos   Preco Total\n\n");
	while(l!=NULL){
		printf("\t %d \t \t \t %d \t \t %2d \t \t %.2f euros\n",l->numeroEncomenda, l->numReferencias, l->numArtigos, l->precoTotal);
		l=l->prox;
	}
}

// Definicao recursiva que calcula o numero total de encomendas
int numeroTotalEncomendas(LEncomendas l){
	if(l==NULL)
		return 0;
	return 1+numeroTotalEncomendas(l->prox);
}

// Definicao que calcula o numero total de referencias encomendadas
int numeroTotalReferenciasEncomendadas(LEncomendas l){
	int conta = 0;
	while(l!=NULL){
		conta += l->numReferencias;
		l=l->prox;
	}
	return conta;
}

// Definicao que calcula o numero total de artigos encomendadas
int numeroTotalArtigosEncomendados(LEncomendas l){
	int conta = 0;
	while(l!=NULL){
		conta += l->numArtigos;
		l=l->prox;
	}
	return conta;
}

int valorTotalEfetuadoEncomendas(LEncomendas l){
	float total = 0.0;
	while(l!=NULL){
		total += l->precoTotal;
		l=l->prox;
	}
	return total;
}
