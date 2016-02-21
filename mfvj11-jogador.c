#include "biblioteca.h"

/*-----------------------------------------------------------------------------------------------*/
//retorna 1 se for a vez do X, 2 se for a vez do O e 3 se for tabuleiro de vitoria ou de derrota
/*-----------------------------------------------------------------------------------------------*/
int quem_joga (char *str, TipoLista *Lista) {
    int i, x, o, cheio;
    TipoItem item;
    x = 0;
    o = 0;
    cheio = 1;
    for (i = 0; i <= 8; i++) {
        if (str[i] == '_')
            cheio = 0;
    }

    if ( (cheio) || (ganhou (str) != 'n') )
        return 3;
    
    for (i = 0; i <= 8; i++) {
        if (i % 2 == 0) {
            while (x <= 8) {
                if (str[x] == 'X') {
		    item.jogada = x;
		    Insere (item, Lista);
		    x++;
		    break;
	        }
		x++;
	    }
	} else {
	    while (o <= 8) {
	        if (str[o] == 'O') {
		    item.jogada = o;
		    Insere (item, Lista);
		    o++;
		    break;
	        }
		o++;
	    }
	}
    }

    strcpy (Lista->Ultimo->Item.tabuleiro, str);
    if (Lista->tamanho % 2 == 0)
	return 1;
    else
	return 2;
}
/*-----------------------------------------------------------------------------------------------*/



void main() {
    int op;
    char str[tam];
    TipoLista Lista;
    TipoMLista MLista;

    scanf ("%s", str);

    FLVazia (&Lista);
    op = quem_joga (str, &Lista);


    FMLVazia(&MLista);
    le_arquivo(&MLista);

    switch (op) {
        case 1: //maquina joga como x
	    maqX(&Lista, MLista); //maquina joga
            desaloca (MLista);
            break;
        case 2: //maquina joga como o
	    maqO (&Lista, MLista);
            desaloca (MLista);
            break;
	case 3:
            desaloca (MLista);
	    break;
    }
}

