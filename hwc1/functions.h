//
// Created by Alessandro Iori on 21/11/2017.
//

#ifndef UNTITLED_FUNCTIONS_H
#define UNTITLED_FUNCTIONS_H

#include <stdio.h>
#include <pthread.h>
#include "msg.h"
#include "buffer.h"

#define EXPECTED_MSG_CONTENT "content"
#define BUFFER_PIENO_UNITARIO_MSG_CONTENT "pieno unitario content"
#define BUFFER_PIENO_DIMENSIONE_M_MSG_CONTENT "pieno dimensione m content"
#define BUFFER_MEZZO_PIENO_MSG_CONTENT "mezzo pieno"
#define PRODUTTORE_MSG_CONTENT "produttore"

int* EXIT_FROM_COND_WAIT_WHILE; //consente funzionamento dei fake produttori consumatori
msg_t* INPUT_MSG;
msg_t* OUTPUT_MSG;
msg_t* PRODUTTORE_INPUT_MSG;
msg_t* PRODUTTORE_OUTPUT_MSG;
msg_t* CONSUMATORE_OUTPUT_MSG;

buffer_t* BUFFER;

pthread_t *A_PRODUTTORI, *A_CONSUMATORI;
pthread_t PRODUTTORE, CONSUMATORE;

pthread_mutex_t MUTEX;
pthread_cond_t COND_NOT_FULL;
pthread_cond_t COND_NOT_EMPTY;

/* operazioni sul buffer */
// inserimento bloccante: sospende se pieno, quindi
// effettua l’inserimento non appena si libera dello spazio
// restituisce il messaggio inserito; N.B.: msg!=null
msg_t* put_bloccante(buffer_t* buffer, msg_t* msg);
// inserimento non bloccante: restituisce BUFFER_ERROR se pieno,
// altrimenti effettua l’inserimento e restituisce il messaggio
// inserito; N.B.: msg!=null
msg_t* put_non_bloccante(buffer_t* buffer, msg_t* msg);
// estrazione bloccante: sospende se vuoto, quindi
// restituisce il valore estratto non appena disponibile
msg_t* get_bloccante(buffer_t* buffer);
// estrazione non bloccante: restituisce BUFFER_ERROR se vuoto
// ed il valore estratto in caso contrario
msg_t* get_non_bloccante(buffer_t* buffer);


/*
*
* FUNZIONI DI SUPPORTO
*
*/
void esegui_put_non_bloccante(void);
void esegui_get_non_bloccante(void);
void esegui_put_bloccante(void);
void esegui_get_bloccante(void);

/*
 *
 *  BUFFER e MSG
 *
 */
msg_t* get_msg_input();
msg_t* get_msg_output();
buffer_t* get_buffer();

void init_molteplici_produttori(int n);
void distruggi_molteplici_produttori();
void init_molteplici_consumatori(int n);
void distruggi_molteplici_consumatori();
/* Inizializza il messaggio di input con MSG_CONTENT */
void init_msg_input(void);
/* Distrugge il messaggio aspettato*/
void distruggi_msg_input(void);
/* Inizializza il messaggio di output con NULL */
void init_msg_output(void);
/* Distrugge il messaggio output*/
void distruggi_msg_output(void);

void init_produttore_msg_input(void);
void distruggi_produttore_msg_input(void);
void init_produttore_msg_output(void);
void distruggi_produttore_msg_output(void);
void init_consumatore_msg_output(void);
void distruggi_consumatore_msg_output(void);

/* Distrugge il buffer */
void distruggi_buffer(void);
/* Inizializza il buffer vuoto di dimensione unitaria */
void init_buffer_vuoto_unitario(void);
/* Inizializza il buffer pieno di dimensione unitaria */
void init_buffer_pieno_unitario(void);
void init_buffer_pieno_dimensione_M(int m);
void init_buffer_vuoto_dimensione_M(int m);
void init_buffer_mezzo_pieno_con_M_messaggi(int m);

/*
 *
 * FUNZIONI DI SUPPORTO PER PRODUTTORE CONSUMATORE
 *
 */

void get_fake(void);
void put_fake(void);

/* Inizializza i il mutex e le variabili condizione */
int init_mutex_cond(int ew);
void distruggi_mutex_cond(void);
void* funzione_produttore_bloccante(void* args);
void* funzione_consumatore_bloccante(void* args);

void esegui_consumatore_bloccante(void);
void esegui_produttore_bloccante(void);
void esegui_join_consumatore(void);
void esegui_join_produttore(void);

void esegui_molteplici_produttori_bloccante(int n);
void esegui_molteplici_join_produttore(int n);
void esegui_molteplici_consumatori_bloccanti(int n);
void esegui_molteplici_join_consumatore(int n);

void eseguit_molteplici_fake_consumatori(int n);
void eseguit_molteplici_fake_produttori(int n);

#endif //UNTITLED_PROD_CONS_H
