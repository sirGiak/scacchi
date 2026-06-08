#include "header.h"

void inizializza_s(Scacchiera s);//inizializzazione scacchiera
void inizializza_pedine(Scacchiera s);
Res_azione muovi(Colore turno,int x,int y,int a,int b,Scacchiera s); //x e y parametri posizione iniziale. a e b parametri posizione finale
void stampa_s(Scacchiera s);
void stampa_regole();
void free_pedine(Scacchiera s);
void info_colore(Colore c, char *str);
//TUTTE LE VARIABILI LOCALI 'a' e 'x' SI RIFERIRANNO AL NUMERO DI RIGA
//TUTTE LE VARIABILI LOCALI 'b' e 'y' SI RIFERIRANNO AL NUMERO DI COLONNA


int main(){
    Scacchiera s; //s è la scacchiera che andremo a inizializzare
    Colore turno;
    int giocare=2,n_riga,n_colonna, n_riga_new,n_colonna_new;
    char colore[7];
    Res_azione res_azione=ok;

    printf("\033[40m"); // sfondo nero per tutto il terminale
    printf("\033[37m"); // testo bianco
    printf("Scacchi\n");
    while(giocare){
        if(giocare==1)
            stampa_regole();
        else{

            inizializza_s(s);

            inizializza_pedine(s);

            turno=nero;
            while(res_azione!=fine){
                turno=!turno;
                stampa_s(s);
                do{
                    info_colore(turno, colore);
                    printf("Turno del %s:\nPedina da spostare (<num. riga> <num. colonna>): ", colore);
                    scanf("%d %d", &n_riga, &n_colonna);

                    printf("Inserisci nuova posizione (<num. riga> <num. colonna>): ");
                    scanf("%d %d", &n_riga_new, &n_colonna_new);

                    res_azione=muovi(turno,n_riga,n_colonna, n_riga_new,n_colonna_new,s);

                }while(res_azione==errore);

            }

            free_pedine(s);

        }

        printf("Premi:\n0 - Se vuoi chiudere;\n 1 - Regole;\n 2 - Avvia un'altra partita.\n>");
        scanf("%d",&giocare);
    }
}
