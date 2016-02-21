#include "biblioteca.h"

/*-----------------------------------------------------------------------------------------------*/
//Retorna TRUE se a lista estÃ¡ vazia
/*-----------------------------------------------------------------------------------------------*/
int Vazia(TipoLista Lista) {
    return (Lista.Primeiro == Lista.Ultimo);
}
/*-----------------------------------------------------------------------------------------------*/
 
/*-----------------------------------------------------------------------------------------------*/
//Faz uma Lista Ficar Vazia
/*-----------------------------------------------------------------------------------------------*/
void FLVazia(TipoLista *Lista) {
    Lista->Primeiro = malloc(sizeof *(Lista->Primeiro));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
    Lista->tamanho = 0;
}
/*-----------------------------------------------------------------------------------------------*/
   
/*-----------------------------------------------------------------------------------------------*/
//Faz uma MLista Ficar Vazia
/*-----------------------------------------------------------------------------------------------*/
void FMLVazia(TipoMLista *MLista) {
    MLista->First = malloc(sizeof *(MLista->First));
    MLista->Last = MLista->First;
    MLista->First->Next = NULL;
}
/*-----------------------------------------------------------------------------------------------*/
   
/*-----------------------------------------------------------------------------------------------*/
//Insere um item x em uma lista
/*-----------------------------------------------------------------------------------------------*/
void Insere(TipoItem x, TipoLista *Lista) {
    Lista->Ultimo->Prox = malloc(sizeof *(Lista->Ultimo->Prox));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = x;
    Lista->Ultimo->Prox = NULL;
    Lista->tamanho++;
}
/*-----------------------------------------------------------------------------------------------*/
   
/*-----------------------------------------------------------------------------------------------*/
//cria nova lista em uma MLista
/*-----------------------------------------------------------------------------------------------*/
void Cria_lista (TipoMLista *MLista) {
    MLista->Last->Next = malloc(sizeof *(MLista->Last->Next));
    MLista->Last = MLista->Last->Next;
    FLVazia (MLista->Last);
    MLista->Last->Next = NULL;
}
/*-----------------------------------------------------------------------------------------------*/
  
/*-----------------------------------------------------------------------------------------------*/
//Função para ler um arquivo e salvar na lista
/*-----------------------------------------------------------------------------------------------*/
void le_arquivo(TipoMLista *MLista) {
    FILE *fp;
    char c;
    int j;
    TipoItem aux;
    fp = fopen("derrotas.txt", "r");
    Cria_lista (MLista);
    if (fp == NULL)
        printf("Houve um erro ao abrir o arquivo.\n");
    else {
        do {
            c = fgetc (fp);
            if ( c == '\n') {
                c = fgetc (fp);
                if (c != EOF)
                    Cria_lista (MLista);
            }
        
            if ( (c != '\n') && (c != ' ') && (c != EOF)) {
                aux.jogada = (int) c - 48;
                Insere (aux, MLista->Last);
            }
          } while (c != EOF);
    }
    fclose(fp);
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//Desaloca uma MLista
/*-----------------------------------------------------------------------------------------------*/
void desaloca (TipoMLista MLista) {
    TipoApontador Aux;
    TipoApontaLista auxL;
    auxL = MLista.First->Next;
    while (auxL != NULL) {
        Aux = auxL->Primeiro->Prox;
        while (Aux != NULL) {
	    free (Aux);
            Aux = Aux->Prox;
        }
        free (auxL);
        auxL = auxL->Next;
    }
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
// devolve um int pseudo-aleatório entre min e max, inclusives    
/*-----------------------------------------------------------------------------------------------*/
int sorteia(int min, int max) {
    srand(time(NULL));
    return min + (rand() % (max - min + 1));
}
/*-----------------------------------------------------------------------------------------------*/
   
/*-----------------------------------------------------------------------------------------------*/
//Maquina joga O (aleatoriamente)
/*-----------------------------------------------------------------------------------------------*/
int maquinaO (char *str){
    int i;
    do {
        i = sorteia(0, 8);
    } while (str[i] != '_');
    str[i] = 'O';
    printf ("%s\n", str);
    return i;
}
/*-----------------------------------------------------------------------------------------------*/
   
/*-----------------------------------------------------------------------------------------------*/
//Maquina joga X (aleatoriamente)
/*-----------------------------------------------------------------------------------------------*/
int maquinaX_aleatorio (char *str){
    int i;
    do {
        i = sorteia(0, 8);
    } while (str[i] != '_');
    str[i] = 'X';
    printf ("%s\n", str);
    return i;
}
/*-----------------------------------------------------------------------------------------------*/
   
/*-----------------------------------------------------------------------------------------------*/
//Verifica se alguem venceu e retorna o simbolo do jogador vencedor (X ou O)
/*-----------------------------------------------------------------------------------------------*/
char ganhou (char *str){
    if ( ((str[0] == str[1]) && (str[1] == str[2])) && (str [0] != '_') ) { //Linha 0
        return str[0];
    }
    else if ( ((str[3] == str[4]) && (str[4] == str[5])) && (str [3] != '_') ) { //Linha 1
        return str[3];
    }
    else if ( ((str[6] == str[7]) && (str[7] == str[8])) && (str [6] != '_') ) { //Linha 2
        return str[6];
    }
     
    else if ( ((str[0] == str[3]) && (str[3] == str[6])) && (str [0] != '_') ) { //Coluna 0
        return str[0];
    }
    else if ( ((str[1] == str[4]) && (str[4] == str[7])) && (str [1] != '_') ) { //Coluna 1
        return str[1];
    }
    else if ( ((str[2] == str[5]) && (str[5] == str[8])) && (str [2] != '_') ) { //Coluna 2
        return str[2];
    }
    
    else if ( ((str[0] == str[4]) && (str[4] == str[8])) && (str [0] != '_') ) { //DP
        return str[0];
    }
    else if ( ((str[2] == str[4]) && (str[4] == str[6])) && (str [2] != '_') ) { // DS
        return str[2];
    }
     
    return 'n';
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//Inicializa o vetor tabuleiro com '_________'
/*-----------------------------------------------------------------------------------------------*/
void zera_tab (char *str) {
    int i;
    for (i = 0; i <= 8; i++) {
        str[i] = '_';
    }
    str[i] = '\0';
     
}
/*-----------------------------------------------------------------------------------------------*/
  
/*-----------------------------------------------------------------------------------------------*/
//maquina joga com 'O' não aleatoreamente
/*-----------------------------------------------------------------------------------------------*/
void maqO(TipoLista *Lista, TipoMLista MLista) { //Lista é a lista de jogadas corrente
    TipoApontador Aux, aux2;
    TipoApontaLista auxL;
    TipoLista derrotas;
    TipoItem item;
    int igual, i;
 
    FLVazia (&derrotas);
  
    auxL = MLista.First->Next;
 
    while (auxL->Next != NULL) {
        Aux = auxL->Primeiro->Prox;
        aux2 = Lista->Primeiro->Prox;
        igual = 1;
        while (((igual == 1) && (Aux != NULL)) && (aux2 != NULL)) {
            igual = 0;
            if (aux2->Item.jogada == Aux->Item.jogada)
                igual = 1;
            aux2 = aux2->Prox;
            Aux = Aux->Prox;
        }
        if (
        	( ((igual == 1) && (Aux != NULL)) && (existe (Aux->Item, derrotas) == 0) )
        	&&
        	( ((*Lista).tamanho <= 4) && ( (auxL->tamanho <= 5) && (auxL->tamanho % 2 != 0) ) )
           )
    	{
            Insere (Aux->Item, &derrotas);
        }
        else if (
            	    ( ((igual == 1) && (Aux != NULL)) && (existe (Aux->Item, derrotas) == 0) ) 
            	    &&
            	    ( ((*Lista).tamanho == 5) && ( (auxL->tamanho <= 7 ) && (auxL->tamanho % 2 != 0) ) )
                )
   	{
            Insere (Aux->Item, &derrotas);
    	}
        else if (
        	    ( ((igual == 1) && (Aux != NULL)) && (existe (Aux->Item, derrotas) == 0) )
        	    &&
        	    ( ((*Lista).tamanho == 6) && ( (auxL->tamanho <= 7) && (auxL->tamanho % 2 != 0) ) )
                )
    	{
            Insere (Aux->Item, &derrotas);
    	}
        else if (
        	    ( ((igual == 1) && (Aux != NULL)) && (existe (Aux->Item, derrotas) == 0) )
        	    &&
        	    ( ((*Lista).tamanho == 7) && ( (auxL->tamanho <= 9) && (auxL->tamanho % 2 != 0) ) )
                )
    	{
            Insere (Aux->Item, &derrotas);
    	}
        else if (
        	    ( ((igual == 1) && (Aux != NULL)) && (existe (Aux->Item, derrotas) == 0) )
            	    &&
            	    ( ((*Lista).tamanho == 8) && ( (auxL->tamanho <= 9) && (auxL->tamanho % 2 != 0) ) )
                )
    	{
            Insere (Aux->Item, &derrotas);
    	}
 
        auxL = auxL->Next;
    }

//derrotas tem as jogadas q levaram à derrota para a jogada atual

    if (Vazia (derrotas)){
        igual = 1;
    } else{
        for (i = 0; i <= 8; i++) {
            igual = 0;
            aux2 = derrotas.Primeiro->Prox;
            while ( (igual == 0) && (aux2 != NULL) ) { //encontra uma jogada q nunca levou a derrota
                if (aux2->Item.jogada == i) {
                    igual = 1;
                }
                aux2 = aux2->Prox;
            }
          
            if ( (igual == 0) && (Lista->Ultimo->Item.tabuleiro[i] == '_') ){
                strcpy (item.tabuleiro, Lista->Ultimo->Item.tabuleiro);
                item.tabuleiro[i] = 'O';
                item.jogada = i;
                printf ("%s\n", item.tabuleiro);
                Insere (item, Lista);
                i = 9;
            }
            else if ( (igual == 0) && (Lista->Ultimo->Item.tabuleiro[i] != '_') )
                igual = 1;
        }
    }
    if ( igual == 1 ) {//se todas levam a derrota, joga aleatorio
        strcpy (item.tabuleiro, Lista->Ultimo->Item.tabuleiro);
        item.jogada = maquinaO(item.tabuleiro);
        Insere (item, Lista);
    }
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//maquina joga com 'X' não aleatoreamente
/*-----------------------------------------------------------------------------------------------*/
void maqX(TipoLista *Lista, TipoMLista MLista) {
    TipoApontador Aux, aux2;
    TipoApontaLista auxL;
    TipoLista derrotas;
    TipoItem item;
    int igual, i    ;
    FLVazia (&derrotas);
    if (Vazia(*Lista)) {
        zera_tab(item.tabuleiro);
        item.jogada = maquinaX_aleatorio (item.tabuleiro);
        Insere (item, Lista);
    } else {
        auxL = MLista.First->Next;
        while (auxL->Next != NULL) {
            Aux = auxL->Primeiro->Prox;
            aux2 = Lista->Primeiro->Prox;
            igual = 1;
 
            while (((igual == 1) && (Aux != NULL)) && (aux2 != NULL)) {
                igual = 0;
                if (aux2->Item.jogada == Aux->Item.jogada)
                    igual = 1;
                aux2 = aux2->Prox;
                Aux = Aux->Prox;
            }    
            if (
            	    ( ((igual == 1) && (Aux != NULL)) && (existe (Aux->Item, derrotas) == 0) )
            	    &&
            	    ( ((*Lista).tamanho <= 5) && ( (auxL->tamanho <= 6) && (auxL->tamanho % 2 == 0) ) )
               )
        	{
                    Insere (Aux->Item, &derrotas);
        	}
            else if (
            		( ((igual == 1) && (Aux != NULL)) && (existe (Aux->Item, derrotas) == 0) )
            		&&
            		( ((*Lista).tamanho == 6) && ( (auxL->tamanho <= 8 ) && (auxL->tamanho % 2 == 0) ) )
                    )
            {
                Insere (Aux->Item, &derrotas);
            }
            else if (
            		( ((igual == 1) && (Aux != NULL)) && (existe (Aux->Item, derrotas) == 0) )
            		&&
            		( ((*Lista).tamanho == 7) && ( (auxL->tamanho <= 8) && (auxL->tamanho % 2 == 0) ) )
                    )
            {
                Insere (Aux->Item, &derrotas);
            }
 
            auxL = auxL->Next;
        }
    

        if (Vazia (derrotas)){
            igual = 1;
        } else{
            for (i = 0; i <= 8; i++) {
                igual = 0;
                aux2 = derrotas.Primeiro->Prox;
                while ( (igual == 0) && (aux2 != NULL) ) {
                    if (aux2->Item.jogada == i) {
                        igual = 1;
                    }
                    aux2 = aux2->Prox;
                }
          
                if ( (igual == 0) && (Lista->Ultimo->Item.tabuleiro[i] == '_') ){
                    strcpy (item.tabuleiro, Lista->Ultimo->Item.tabuleiro);
                    item.tabuleiro[i] = 'X';
                    item.jogada = i;
                    printf ("%s\n", item.tabuleiro);
                    Insere (item, Lista);
                    i = 9;
                }
                else if ( (igual == 0) && (Lista->Ultimo->Item.tabuleiro[i] != '_') )
                    igual = 1;
            }
        }
        if ( igual == 1 ) {
            strcpy (item.tabuleiro, Lista->Ultimo->Item.tabuleiro);
            item.jogada = maquinaX_aleatorio(item.tabuleiro);
            Insere (item, Lista);
        }
    }
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//Verifica se um item existe dentro de uma lista
/*-----------------------------------------------------------------------------------------------*/
int existe (TipoItem Item, TipoLista Lista) {
    TipoApontador aux;
    aux = Lista.Primeiro->Prox;
    while (aux != NULL) {
        if (aux->Item.jogada == Item.jogada)
            return 1;
        aux = aux->Prox;
    }
    return 0;
}
/*-----------------------------------------------------------------------------------------------*/
