#include "header.h"
#include <string.h>

void stampa_regole(){
    printf("*REGOLE*\n");
}

void free_pedine(Scacchiera s){
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++){
            if(s[i][j].pedina!=NULL)
                free(s[i][j].pedina);
        }
}

void info_colore(Colore c, char *str){

    switch(c){
        case bianco: strcpy(str, "Bianco"); break;
        case nero: strcpy(str, "Nero"); break;
        default: strcpy(str, "Altro");
    }
}


void info_pedina(Pedina *p){
    char nome[10], colore[7];

    switch(p->personaggio){
        case re: strcpy(nome, "Re"); break;
        case regina: strcpy(nome, "Regina"); break;
        case torre: strcpy(nome, "Torre"); break;
        case cavallo: strcpy(nome, "Cavallo"); break;
        case alfiere: strcpy(nome, "Alfiere"); break;
        case pedone: strcpy(nome, "Pedone"); break;
        default: strcpy(nome, "Altro");
    }
    info_colore(p->colore, colore);
    printf("%s, colore: %s posizione: %d %d\n", nome, colore, p->posizione[0], p->posizione[1]);
}


void inizializza_s(Scacchiera s){
    int i, j;
    for(i=0; i<8; i++){
        for(j=0; j<8; j++){
            if ((i+j)%2)
                s[i][j].colore=nero;
            else
                s[i][j].colore=bianco;

            s[i][j].pedina=NULL;
        }
    }
}

void inizializza_p(Personaggio pers,Colore c,int a,int b,Scacchiera s){ //inizializzazione pedina
        Pedina *p=s[a][b].pedina;

        p->personaggio=pers;
        p->colore=c;
        p->posizione[0]=a;
        p->posizione[1]=b;
}

void inizializza_pedine(Scacchiera s){
    int i, a=7,b=-1;
    Personaggio pers=re;
    Colore colore=bianco;
    for(i=0;i<N_PEDINE;i++){

        if(i%4==0) b++;

        if(i%2==0)
            pers=pedone;
        else{
        switch(b){
            case 0: pers=torre; break;
            case 1: pers=cavallo; break;
            case 2: pers=alfiere; break;
            case 3: pers=regina; break;
            case 4: pers=re; break;
            case 5: pers=alfiere; break;
            case 6: pers=cavallo; break;
            case 7: pers=torre; break;
        }
        }

        if(pers==pedone){
            if(colore==bianco) a=6;
            else a=1;
        }
        s[a][b].pedina=malloc(sizeof(Pedina));
        if(s[a][b].pedina==NULL){
            printf("Memoria non sufficente per le pedine riprova tra un po'. Num pedina: %d\n", i);
            exit(1);
        }

        inizializza_p(pers,colore,a,b,s);

        if(i%2==0)
            colore=!colore;

        if(colore==nero) a=0;
        else a=7;
    }

}

int spostamento_in_diagonale(int x, int y, int a, int b){
    int tempx=a-x;
    int tempy=b-y;

    if(tempx<0) tempx=-tempx;
    if(tempy<0) tempy=-tempy;

    if(tempx==tempy) return 1;
    else return 0;
}

int spostamento_cavallo(int x, int y, int a, int b){
    int tempx=a-x;
    int tempy=b-y;

    if(tempx<0) tempx=-tempx;
    if(tempy<0) tempy=-tempy;

    if((tempx==2 && tempy==1) || (tempx==1 && tempy==2))
        return 1;
    else
        return 0;
}

int spostamento_pedone(int x, int y, int a, int b, Scacchiera s){
    int verso = 1;    // nero avanza aumentando la riga
    int partenza = 1; // riga di partenza del nero
    Colore temp_c = s[x][y].pedina->colore;

    if(temp_c == bianco){
        verso = -1;   // bianco avanza diminuendo la riga
        partenza = 6; // riga di partenza del bianco
    }

    // Caso 1: avanzata di una casella (stessa colonna, casella libera)
    if(a == x + verso && b == y && s[a][b].pedina == NULL)
        return 1;

    // Caso 2: avanzata doppia dalla riga di partenza (entrambe le caselle libere)
    if(x == partenza && a == x + (2*verso) && b == y
       && s[a][b].pedina == NULL
       && s[x+verso][y].pedina == NULL)  // casella intermedia libera
        return 1;

    // Caso 3: cattura diagonale (riga avanza di verso, colonna ±1, pedina avversaria)
    if(a == x + verso && (b == y+1 || b == y-1)
       && s[a][b].pedina != NULL
       && s[a][b].pedina->colore != temp_c)
        return 1;

    return 0;

}

void inizializza_ped_non_in_gioco(Pedina **array){
    int i;
    for(i=0; i<N_PEDINE; i++)
        array[i]=NULL;
}

int controllo_percorso(int x, int y, int a, int b, Scacchiera s){
    int varx=1, vary=1, trovato=0, i=1;
    int n_p_da_saltare=a-x;

    if(a-x<0){ varx=-1; n_p_da_saltare=n_p_da_saltare*-1; }
    if(b-y<0){ vary=-1; if((b-y)*-1>n_p_da_saltare) n_p_da_saltare=(b-y)*-1; }
    else{ if(b-y>n_p_da_saltare) n_p_da_saltare=b-y; }


    while(i<n_p_da_saltare && !trovato){
        if(x!=a && y!=b){
            if(s[x+i*varx][y+i*vary].pedina!=NULL)
                trovato=1;
        }else{
            if(x==a){
                if(s[x][y+i*vary].pedina!=NULL)
                    trovato=1;
             }else
                if(s[x+i*varx][y].pedina!=NULL)
                    trovato=1;
         }
        i++;
    }

    if (trovato) return 0;
    else return 1;
}

void controllo_scacco_matto(Scacchiera s){
    ;
}

Res_azione muovi(Colore turno,int x,int y,int a,int b,Scacchiera s){

    unsigned short int sposta=0;
    Pedina *p=s[x][y].pedina, *p2=s[a][b].pedina; //p2 ha l'indirizzo della pedina in posizione a b ovvero dove dobbiamo spostare la pedina puntata da p
    char colore[7];

    info_pedina(p);

    info_colore(turno, colore);
    //printf("Colore %d - personaggio: %d - posizione: %d %d\n", p->colore, p->personaggio, p->posizione[0], p->posizione[1]);

    if(p2!=NULL && p2->colore==p->colore)
        printf("Posizione già occupata da una pedina dello stesso colore\n");
    else if(a>7 || b>7 || a<0 || b<0 || x>7 || y>7 || x<0 || y<0)
        printf("Le coordinate devono essere incluse nell'intervallo [0;7]\n");
        else if(a==x && b==y)
            printf("Coordinate iniziali e finali devono essere diverse\n");
            else if(turno!=p->colore)
                printf("Deve giocare il %s\n", colore);
    else{
        switch (p->personaggio)
        {
            case re:
                if((x-1<=a && a<=x+1) && (y-1<=b && b<=y+1))
                    sposta=1;
            break;

            case regina:
                if(a!=x && b!=y){//spostamento obliquo
                    sposta=spostamento_in_diagonale(x,y,a,b);
                    if(sposta)
                        sposta=controllo_percorso(x,y,a,b,s);
                }
                else //spostamento orizzontale o verticale
                    sposta=controllo_percorso(x,y,a,b,s);

            break;

            case alfiere:
                if(a!=x && b!=y){
                    sposta=spostamento_in_diagonale(x,y,a,b);
                    if(sposta)
                        sposta=controllo_percorso(x,y,a,b,s);
                }
            break;

            case cavallo:
                sposta=spostamento_cavallo(x,y,a,b);
            break;

            case torre:
                if(a==x || b==y)
                    sposta=controllo_percorso(x,y,a,b,s);
            break;

            case pedone:
                    sposta=spostamento_pedone(x,y,a,b,s);

            break;

            default:
                printf("Pedina non riconosciuta.\n");
            break;
        }
    }

    if(sposta){
        p->posizione[0]=a;
        p->posizione[1]=b;
        s[a][b].pedina=p;
        s[x][y].pedina=NULL;

        //TODO
        controllo_scacco_matto(s);

        if(p2!=NULL){

            //togliere
            if(p2->personaggio==re){
                printf("Ha vinto il %s!", colore);
                return fine;
            }else{
                free(p2);
                return ok;
            }
        }else
            return ok;
    }
    else{
        printf("Spostamento non effettuato. Ripetere\n");
        return errore;
    }
}


void componi_numeri_verticali(int riga_interna, int i){
    switch (riga_interna)
    {
        case 1:
            switch (i)
                {
                case 0:
                    printf(" |\"\"\"| |");
                    break;
                case 1:
                    printf("  /|   |");
                    break;
                case 4:
                    printf("  / |  |");
                    break;
                case 5:
                    printf(" |\"\"\"\" |");
                    break;
                case 6:
                    printf(" |\"\"\"  |");
                    break;
                case 7:
                    printf(" |\"\"\"/ |");
                    break;
                default:
                        printf(" \"\"\"\"| |");
                    break;
                }
            break;

        case 2:
            switch (i)
                {
                case 0:
                    printf(" |   | |");
                    break;
                case 1:
                    printf("   |   |");
                    break;
                case 3:
                    printf(" ----| |");
                    break;
                case 4:
                    printf(" /__|_ |");
                    break;
                case 6:
                    printf(" |---  |");
                    break;
                case 7:
                    printf("    /  |");
                    break;
                default:
                        printf("  ---  |");
                    break;
                }
            break;

        case 3:
            switch (i)
                {
                case 0:
                    printf(" |___| |");
                    break;
                case 1:
                    printf("  _|_  |");
                    break;
                case 2:
                    printf(" |____ |");
                    break;
                case 4:
                    printf("    |  |");
                    break;
                case 6:
                    printf(" |___| |");
                    break;
                case 7:
                    printf("   /   |");
                    break;
                default:
                        printf(" ____| |");
                    break;
                }
            break;
    }
}

void componi_pedine(int riga_interna,Colore casella, Colore c_pedina, Personaggio p){
    char sc=' '; //sc=spazio vuoto della casella
    char sp=' '; //sp=spazio vuoto della pedina


    if(casella==bianco) sc='#';
    if(c_pedina==bianco) sp='#';


    switch (riga_interna)
    {
        case 1:
            switch (p)
            {
                case re:
                    printf("%c<-^->%c|",sc,sc);
                    break;

                case regina:
                    printf("%c(***)%c|",sc,sc);
                    break;

                case alfiere:
                    printf("%c(---)%c|",sc,sc);
                    break;

                case cavallo:
                    printf("%c(^^_\\%c|",sc,sc);
                    break;

                case torre:
                    printf("|_|_|_||");
                    break;

                case pedone:
                    printf("%c%c(%c)%c%c|",sc,sc,sp,sc,sc);
                    break;
            }
            break;

        case 2:
            switch (p)
            {
                case cavallo:
                    printf("%c|%c%c\\%c%c|",sc,sp,sp,sc,sc);
                    break;

                case torre:
                    printf("%c|%c%c%c|%c|",sc,sp,sp,sp,sc);
                    break;

                default:
                    printf("%c%c)%c(%c%c|",sc,sc,sp,sc,sc);
                    break;
            }
            break;

        case 3:
            if(p==re || p==regina)
                printf("%c{%c%c%c}%c|",sc,sp,sp,sp,sc);
            else
                printf("%c[%c%c%c]%c|",sc,sp,sp,sp,sc);
            break;
    }

}

void componi_numeri_orizzontali(int riga_interna){
    switch(riga_interna)
    {
        case 1:
            printf("        | |\"\"\"| |  /|   | \"\"\"\"| | \"\"\"\"| |  / |  | |\"\"\"\" | |\"\"\"  | |\"\"\"/ |");
            break;

        case 2:
            printf("        | |   | |   |   |  ---  | ----| | /__|_ |  ---  | |---  |    /  |");
            break;

        case 3:
            printf("        | |___| |  _|_  | |____ | ____| |    |  | ____| | |___| |   /   |");
            break;

    }
}
void stampa_s(Scacchiera s){
    int i=-1, j, n, riga_interna=1, m;
    //i=riga della matrice, j=colonna della matrice
    //n=numero riga in lavorazione nell'output
    //riga_interna= numero riga partendo da sopra di una casella (valori: 1,2,3)
    //m=serve per facilitare l'inserimento di una nuova riga nell'output
    for(n=0; n<37; n++){
        if(n<33){
            if(n==0)
                printf("\n-");
            else
                printf("\n|");
        }
        else
            printf("\n");

        if(n%4!=0){
            if(i<8){
                componi_numeri_verticali(riga_interna, i);

                for(j=0; j<8; j++){
                    if(s[i][j].pedina==NULL){
                        if(s[i][j].colore==bianco)
                            printf("#######|"); //linea casella vuota bianca
                        else
                            printf("       |"); //linea casella vuota nera
                    }
                    else
                        componi_pedine(riga_interna, s[i][j].colore, s[i][j].pedina->colore, s[i][j].pedina->personaggio);
                }
            }else componi_numeri_orizzontali(riga_interna);

            riga_interna++;
        }else{
            if(n!=36)
                for(m=0; m<72; m++) printf("-");
            else{
                printf("        "); for(m=0; m<65; m++) printf("-");
            }
            i++;
            riga_interna=1;
        }
    }
    printf("\n");
}
