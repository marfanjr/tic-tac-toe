#include "biblioteca.h"

/*-----------------------------------------------------------------------------------------------*/
//Função para salvar a lista em um arquivo
/*-----------------------------------------------------------------------------------------------*/
void salva_arquivo(TipoMLista MLista) {
    FILE *fp;
    TipoApontador Aux;
    TipoApontaLista auxL;
    int i;
    fp = fopen("derrotas.txt", "a+");
    for ( i = 5; i <= 9; i++) {
        auxL = MLista.First->Next;
        while (auxL != NULL) {
            Aux = auxL->Primeiro->Prox;
            if ((*auxL).tamanho == i){
                while (Aux != NULL) {
                    fprintf (fp, "%d ", Aux->Item.jogada);
		    free (Aux);
                    Aux = Aux->Prox;
                }
                fprintf (fp, "\n");
            }
	    free (auxL);
            auxL = auxL->Next;
        }
    }
    fclose(fp);
}
/*-----------------------------------------------------------------------------------------------*/

   
/*-----------------------------------------------------------------------------------------------*/
//Verifica se ainda há espaços vazios no tabuleiro
/*-----------------------------------------------------------------------------------------------*/
int tem_espaco (char *str) {
    int i;
    for (i = 0; i <= 9; i++){
        if (str[i] == '_')
            return 0;
    }
    return 1;
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//Verifica a jogada comparando duas strings
/*-----------------------------------------------------------------------------------------------*/
int verifica_jogada (char *str1, char *str2){
    int i;
    for (i = 0; i < 9; i++) {
        if (str1[i] != str2[i])
            return i;
    }
}
/*-----------------------------------------------------------------------------------------------*/
   
/*-----------------------------------------------------------------------------------------------*/
//Verifica se uma lista ja existe dentro da lista de listas
/*-----------------------------------------------------------------------------------------------*/
int ja_existe(TipoLista Lista, TipoMLista MLista) {
    TipoApontador Aux, aux2;
    TipoApontaLista auxL;
    int igual;
    auxL = MLista.First->Next;
    while (auxL->Next!= NULL) {
        Aux = auxL->Primeiro->Prox;
        aux2 = Lista.Primeiro->Prox;
        igual = 1;
        while ( ((igual == 1) && (Aux != NULL)) && (aux2 != NULL) ) {
            igual = 0;
            if (aux2->Item.jogada == Aux->Item.jogada)
                igual = 1;
            aux2 = aux2->Prox;
            Aux = Aux->Prox;
        }
        if (igual == 1)
            return 1;
        auxL = auxL->Next;
    }
    return 0;
}
/*-----------------------------------------------------------------------------------------------*/
  
void main() {
    int op, i;
    char copia[tam];
    TipoItem aux;
    TipoMLista MLista;

   
    printf("Quem joga primeiro? (digite 1 para humano ou 2 para maquina): ");
    scanf("%d", &op);
    FMLVazia(&MLista);
    le_arquivo(&MLista);
    Cria_lista(&MLista);
  
    zera_tab(aux.tabuleiro);
    zera_tab(MLista.Last->Ultimo->Item.tabuleiro);

    i = 0;
    switch (op) {
        case 1: //humano joga primeiro
            do {
                strcpy(copia,  MLista.Last->Ultimo->Item.tabuleiro); //faz uma copia do tab pré-jogada para comparar com o tab pós-jogada e verificar qual jogada foi feita
                scanf("%s", aux.tabuleiro); //humano joga
                aux.jogada = verifica_jogada(copia, aux.tabuleiro);
                Insere(aux, MLista.Last); //insere um item na ultima lista da lista de listas
		i++;
                if ( (ganhou(MLista.Last->Ultimo->Item.tabuleiro) == 'n') && (i <= 8) ) {
		    maqO (MLista.Last, MLista);
		    i++;
                }
            } while ( (ganhou(MLista.Last->Ultimo->Item.tabuleiro) == 'n') && (i <= 8) );
  
            if ( (ganhou(MLista.Last->Ultimo->Item.tabuleiro) != 'n') && (ja_existe((*MLista.Last), MLista) == 0) )
                salva_arquivo(MLista);
            desaloca (MLista);

            break;
        case 2: //maquina joga primeiro
            do {
                maqX(MLista.Last, MLista); //maquina joga
		i++;
                if ( (ganhou(MLista.Last->Ultimo->Item.tabuleiro) == 'n') && (i <= 8) ) {
                    strcpy(copia,  MLista.Last->Ultimo->Item.tabuleiro); //faz uma copia do tab pré-jogada para comparar com o tab pós-jogada e verificar qual jogada foi feita
                    scanf("%s", aux.tabuleiro); //humano joga
                    aux.jogada = verifica_jogada(copia, aux.tabuleiro);
                    Insere(aux, MLista.Last); //insere um item na ultima lista da lista de listas
		    i++;
                }
            } while ( (ganhou(MLista.Last->Ultimo->Item.tabuleiro) == 'n') && (i <= 8) );
  
            if ( (ganhou(MLista.Last->Ultimo->Item.tabuleiro) != 'n') && (ja_existe((*MLista.Last), MLista) == 0) )
                salva_arquivo(MLista);

            desaloca (MLista);

            break;
    }
}
