// FICHEIRO COM A DEFINICAO DO NOVOS TIPOS DE DADOS E DECLARACOES (PROTOTIPOS) DAS FUNCOES UTILIZADAS

#define N_ARTIGO 50

typedef struct IDartigo{
	char nomeArtigo[N_ARTIGO];
	int referencia;
	float preco;
	int quantidade;
} ID_ARTIGO;


typedef struct lligada{
	ID_ARTIGO artigo;
	struct lligada *prox;
}*LLista;

typedef struct encomendas{
	int numeroEncomenda;
	float precoTotal;
	int numArtigos;
	int numReferencias;
    struct encomendas *prox;
}*LEncomendas;

// DECLARACAO DAS FUNCOES. PROTOTIPO DAS FUNCOES
void inic_random();
int inserirReferencia();
float inserirPreco();
void inserirNome(char *);
int inserirQuantidade();
int verDadosArtigo(LLista); 		// 191
int inserirInformacaoArtigo(LLista,int *,char *,float *,int *);  //ll 313
void imprimeLista(LLista);							//400
void imprimeEncomendas(LEncomendas);					//354
int numeroTotalReferencias(LLista);
int numeroTotalArtigos(LLista);
int procurarNomePrecoQuantidade_porReferencia(LLista,int,char *,float *,int *);  // 118
LLista procurarArtigo(LLista,int);
LLista criarArtigo(int,char *,float,int);
int inserirArtigo(LLista *,int,char *,float,int);
int removerArtigo(LLista *,int);                      // 131
int existeNumeroEncomenda(LEncomendas,int);
LEncomendas alocarEncomenda(int,int,int,float);
int inserirListaEncomendas(LEncomendas *,int,int,int,int);
int fazerEncomendas(LLista,int *,char *,float *,int *,int *);   //260
int atualizarStock(LLista *,int,int);
int escreverFicheiro(LLista,char *);
int lerFicheiro(LLista *,char *);							//281
int escreverFicheiroEncomendas(LEncomendas,char *);		//224
int lerFicheiroEncomendas(LEncomendas *,char *);			//301
int criarFicheiro(char *);
int menu();
int esperar();
void creditos();
int subMenuDefenicoes();
int alterarInformacoesArtigo(LLista *,LLista,int,int,char *,float,int);
int numeroTotalEncomendas(LEncomendas l);
int numeroTotalReferenciasEncomendadas(LEncomendas);
int valorTotalEfetuadoEncomendas(LEncomendas);
int numeroTotalArtigosEncomendados(LEncomendas);
float valorTotalArtigosArmazem(LLista);
