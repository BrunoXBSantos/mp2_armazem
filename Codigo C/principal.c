// FICHEIRO COM A FUNCAO MAIN

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include "declaracaoDadosPrototiposFuncoes.h"
#include "definicaoFuncoesArmazem.c"
#include "definicaoFuncoesAuxiliares.c"
#include "definicaoFuncoesEncomendas.c"

#define N_ARTIGO 50

int main(){
	// Inicializacao das listas ligadas
	LLista l = NULL;
	LEncomendas en = NULL;
    LLista pt = NULL;
	int r,q, quantiEncomendar, nOpcao, x, y;
	int numArtigosEncomenda, numReferenciasEncomenda, numeroEncomenda;
	float p;
	float precoTotalEncomenda;
	char n[100];
    char nomeFich[20]="listaArtigos.txt";
	char nomeFichE[20]="listaEncomendas.txt";


	// Se for a primeira vez a utilizar o programa
	// tem que se criar os ficheiros que nos quais se armazem a lista de encomentas e a lista dos artigos
	creditos();
	printf("\nPrimeira vez que utiliza o programa, deve inicializa-lo (instalar).\n");
	printf("Prima 1 para ir para o Menu Inicial ou 2 para inicializar o programa: ");
	scanf("%d",&nOpcao);
	if(nOpcao==2){
		x = criarFicheiro(nomeFich);
		if(x=0){
			printf("Erro ao criar o ficheiro dos artigos do armazem.\n");
			nOpcao=esperar();
			exit(1);
		}
		x = criarFicheiro(nomeFichE);
		if(x=0){
			printf("Erro ao criar o ficheiro da lista de encomendas ja efetuadas.\n");
			nOpcao=esperar();
			exit(2);
		}
	}
	else{
	    // carregar os dados para as listas ligadas
		lerFicheiro(&l, nomeFich);
		lerFicheiroEncomendas(&en, nomeFichE);
	}
	inic_random();
	while(nOpcao!=0){
		system("cls");
		nOpcao=menu();
		//Inserir um artigo
		if(nOpcao==1){
			system("cls");
			printf("Menu Inicial\n");
            printf("\t1. Inserir artigo\n\n");
			if(inserirInformacaoArtigo(l,&r,n,&p,&q) == 1)		// ll 313
				;
			else
				inserirArtigo(&l,r,n,p,q);
			printf("\nARTIGO ADICIONADO COM SUCESSO.\n\n");
		}
		if(nOpcao==2){
			system("cls");
			printf("Menu Inicial\n");
            printf("\t2. Ver informacoes de um artigo\n\n");
			verDadosArtigo(l);			// 191
			printf("\n\n");
		}
		if(nOpcao==3){
			system("cls");
			printf("Menu Inicial\n");
            printf("\t3. Remover um artigo\n\n");
			r = inserirReferencia();
			if(procurarNomePrecoQuantidade_porReferencia(l,r,n,&p,&q) == 0){
				printf("\n\nArtigo nao existe no armazem.\n\n\n");
			}
			else{
				system("cls");
				printf("Artigo a remover:\n");   	//131
				printf("\tNome: %s\n",n);
				printf("\tReferencia: %d\n",r);
				printf("\tPreco: %.2f euros\n",p);
				printf("\tQuantidade: %d\n",q);
				removerArtigo(&l,r);
				printf("\nARTIGO REMOVIDO COM SUCESSO.\n\n\n");
			}
		}
		if(nOpcao==4){
			system("cls");
			printf("Menu Inicial\n");
            printf("\t4. Alterar informacoes de um artigo\n\n");
			r=inserirReferencia();
			if(procurarNomePrecoQuantidade_porReferencia(l,r,n,&p,&q) == 0){
                    printf("\nReferencia do artigo nao existe no armazem\nInsira opcao 1 do menu inicial para o adicionar\n\n");
			}
			else{
                pt=procurarArtigo(l,r);
				printf("\nArtigo a alterar:\n\n");
				printf("\t1. Referencia:  %d\n",(pt->artigo).referencia);
				printf("\t2. Nome:        %s\n",(pt->artigo).nomeArtigo);
				printf("\t3. Preco:       %.2f euros\n",(pt->artigo).preco);
				printf("\t4. Quantidade:  %d\n\n",(pt->artigo).quantidade);
				printf("Insira a opcao do artigo que pretende alterar: ");
				scanf("%d",&nOpcao);
				y = alterarInformacoesArtigo(&l,pt,nOpcao,r,n,p,q);
				if(y == 1){
					printf("\nArtigo alterado com sucesso:\n\n");
					printf("\tReferencia:  %d\n",(pt->artigo).referencia);
					printf("\tNome:        %s\n",(pt->artigo).nomeArtigo);
					printf("\tPreco:       %.2f euros\n",(pt->artigo).preco);
					printf("\tQuantidade:  %d\n\n",(pt->artigo).quantidade);
				}
				if(y == 2){
					printf("\nArtigo removido com sucesso.\n\n");
				}
			}
		}
		if(nOpcao==5){
			system("cls");
			printf("Menu Inicial\n");
            printf("\t5. Ver lista de todos os artigos\n\n");
			imprimeLista(l);				//400
        }
		if(nOpcao==6){
			system("cls");
			printf("Menu Inicial\n");
            printf("\t5. Numero total de artigos e referencias\n\n");
			printf("\n\t Numero de referencias: %d\n",numeroTotalReferencias(l));
			printf("\t Numero de artigos: %d\n",numeroTotalArtigos(l));
			printf("\n\t Valor de todos os artigos do armazem: %.2f euros\n\n\n\n",valorTotalArtigosArmazem(l));
		}
		if(nOpcao==7){
			system("cls");
			printf("Menu Inicial\n");
			printf("\t6. Fazer uma encomenda\n\n");
			precoTotalEncomenda=0;
			numArtigosEncomenda=0;
			numReferenciasEncomenda=0;
			do{
				numeroEncomenda = 1 + (rand()%100);
			}
			while(existeNumeroEncomenda(en,numeroEncomenda));
			while(nOpcao!=0){
				if(fazerEncomendas(l,&r,n,&p,&q,&quantiEncomendar) != 0){				// 260
					system("cls");
					printf("\n\nARTIGO REGISTADO\n");
					printf("\tNome: %s\n",n);
					printf("\tReferencia: %d\n",r);
					printf("\tQuantidade do artigo a encomendar: %d\n",quantiEncomendar);
					printf("\tPreco Total dos artigos: %.2f euros\n\n",p*quantiEncomendar);
					precoTotalEncomenda=precoTotalEncomenda+(p*quantiEncomendar);
					numArtigosEncomenda=numArtigosEncomenda+quantiEncomendar;
					numReferenciasEncomenda++;
					atualizarStock(&l,r,quantiEncomendar);
				}
				printf("Prima 1 para inserir novo artigo na encomenda. 0 para Terminar encomenda: ");
				scanf("%d",&nOpcao);
				system("cls");
			}
			if(numReferenciasEncomenda == 0){
				printf("\n\nNenhum artigo selecionado na encomenda.\n");
				printf("Encomenda Cancelada\n\n");
                nOpcao=1;
			}
			else{
				printf("\n\nEncomenda Final:\n");
				printf("\tNumero da Encomenda: %d\n", numeroEncomenda);
				printf("\tNumero de Referencias encomendadas: %d\n",numReferenciasEncomenda);
				printf("\tNumero de Artigos encomendados: %d\n",numArtigosEncomenda);
				printf("\tPreco Total: %.2f euros\n\n",precoTotalEncomenda);
				printf("\nSTOCK NO ARMAZEM ATUALIZADO COM SUCCESSO.\n\n\n");
				inserirListaEncomendas(&en, numeroEncomenda, numReferenciasEncomenda, numArtigosEncomenda, precoTotalEncomenda);
				getchar();
				nOpcao=1;
			}
		}
		if(nOpcao==8){
			system("cls");
			printf("Menu Inicial\n");
			printf("\t8. Ver lista de encomendas realizadas\n\n\n");
			imprimeEncomendas(en);					// 354
			printf("\n\n");
		}
		if(nOpcao==9){
			system("cls");
			printf("Menu Inicial\n");
			printf("\t9. Numero Total de encomendas realizadas\n\n\n");
			printf("Total de encomendas Realizadas: %d\n\n",numeroTotalEncomendas(en));
		}
		if(nOpcao==10){
			system("cls");
			printf("Menu Inicial\n");
			printf("\t10. Numero total de referencias e artigos encomendados\n\n\n");
			printf("\n\tTotal de referencias encomendadas: %5d\n",numeroTotalReferenciasEncomendadas(en));
			printf("\n\tTotal de artigos encomendados:     %5d\n\n\n",numeroTotalArtigosEncomendados(en));
		}
		if(nOpcao==11){
            system("cls");
			printf("Menu Inicial\n");
			printf("\t11. Valor total faturado\n\n\n");
			printf("\n\tValor total faturado atraves das encomendas: %.2f euros.\n\n\n",(float) valorTotalEfetuadoEncomendas(en));
		}
		if(nOpcao==12){
			system("cls");
			nOpcao = subMenuDefenicoes();
			if(nOpcao==2){
				x = criarFicheiro(nomeFich);
				if(x=0){
					printf("Erro ao criar o ficheiro dos artigos do armazem.\n");
					exit(3);
				}
				x = criarFicheiro(nomeFichE);
				if(x=0){
					printf("Erro ao criar o ficheiro da lista de encomendas ja efetuadas.\n");
					exit(4);
				}
				printf("PROGRAMA RESTAURADO COM SUCESSO.\n\n");
			}
			if(nOpcao==5)
				;
		}
		// guardar os dados das listas ligadas nos respetivos ficheiros
		escreverFicheiro(l,nomeFich);
		escreverFicheiroEncomendas(en,nomeFichE);

		if(nOpcao==0){
			system("cls");
            puts("Programa terminado com sucesso!");
            puts("Obrigado\n");
            creditos();
            exit(10);
		}
		nOpcao=esperar();
		if(nOpcao==0){
			system("cls");
            puts("Programa terminado com sucesso!");
            puts("Obrigado\n");
            creditos();
            exit(10);
        }
    }
}
