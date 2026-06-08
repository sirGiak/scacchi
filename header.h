#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>

#define DIM 8
#define N_PEDINE 32
#define LENGTH 30

typedef enum{
    bianco, nero
} Colore; //4 byte

typedef enum{
    re, regina, alfiere, cavallo, torre, pedone
}Personaggio; //4 byte

typedef struct
{
    Colore colore;
    Personaggio personaggio;
    int posizione[2];
}Pedina; //16 byte

typedef struct
{
    Colore colore;
    Pedina *pedina;
}Casella; //20 byte

typedef Casella Scacchiera[8][8]; //1024 byte

typedef enum{
    errore, ok, fine
}Res_azione;

#endif //HEADER_H
