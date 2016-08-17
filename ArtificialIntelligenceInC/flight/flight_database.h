/*
 * flight_database.h
 *
 *  Created on: 21 de jul de 2016
 *      Author: Marcelo
 */

#ifndef FLIGHT_FLIGHT_DATABASE_H_
#define FLIGHT_FLIGHT_DATABASE_H_

#include <string.h>
#include <stdio.h>
#include "constants.h"

/* estrutura do banco de dados do voo (db) */
struct FL {
	char from[20];
	char to[20];
	int distance;
	char skip; /* usado para restaurar */
};

struct FL flight[MAX]; /* matriz da estrutura db */

/* coloca os dados no db de voo */
void assert_fligth(char *from, char *to, int dist);

/* se conexao entre origem e destino, entao retorna a distancia do voo;
 * senão, retorna 0 */
int match(char *from, char *to);

/* da origem, acha algum lugar */
int find(char *from, char *anywhere, char method);
int find_down_hill(char *from, char *anywhere);
int find_hill_climbing(char *from, char *anywhere);
int find_small_cost(char *from, char *anywhere);

void setup_database();

void reset_database();

void clearmarkers();

int hasmarkers();

void retract(char *from, char *to);

#endif /* FLIGHT_FLIGHT_DATABASE_H_ */
