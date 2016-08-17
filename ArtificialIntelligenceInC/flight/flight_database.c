/*
 * flight_database.c
 *
 *  Created on: 21 de jul de 2016
 *      Author: Marcelo
 */
#include "flight_database.h"
#include "constants.h"

int f_pos=0; 		/* numero de entradas no db do voo */
int find_pos=0;		/* indice para procura no db de voo */

/* coloca os dados no db de voo */
void assert_fligth(from,to,dist)
char *from,*to;
int dist;
{
	if(f_pos<MAX) {
		strcpy(flight[f_pos].from, from);
		strcpy(flight[f_pos].to, to);
		flight[f_pos].distance=dist;
		flight[f_pos].skip=0;
		printf("From: %s\t To:%s\t Distance:%i\n", flight[f_pos].from, flight[f_pos].to, flight[f_pos].distance);
		f_pos++;
	}
	else printf("O banco de dados de vooa esta cheio.\n");
}

/* se conexao entre origem e destino, entao retorna a distancia do voo;
 * senão, retorna 0 */
int match(from, to)
char *from, *to;
{
	register int t;
	for (t=f_pos-1; t>-1; t--)
		if ( !strcmp(flight[t].from, from) && !strcmp(flight[t].to, to) )
			return flight[t].distance;
	return 0; /* nao achou */
}

int find(from, anywhere, method)
char *from, *anywhere, method;
{
	switch (method) {
		case 'd':
			return find_down_hill(from, anywhere);
			break;
		case 'u':
			return find_hill_climbing(from, anywhere);
			break;
		case 's':
			return find_small_cost(from, anywhere);
			break;
		default:
			return 0;
	}
}

int find_down_hill(from, anywhere)
char *from, *anywhere;
{
	find_pos=0;
	while (find_pos<f_pos) {
		if (!strcmp(flight[find_pos].from, from) &&
			!flight[find_pos].skip) {
			strcpy(anywhere, flight[find_pos].to);
			flight[find_pos].skip=1; /* mantem ativo */
			return flight[find_pos].distance;
		}
		find_pos++;
	}
	return 0;
}

int find_hill_climbing(from, anywhere)
char *from, *anywhere;
{
	int pos, dist;

	pos=dist=find_pos=0;

	while (find_pos < f_pos) {
		if (!strcmp(flight[find_pos].from, from) && !flight[find_pos].skip) {
			if(flight[find_pos].distance > dist) {
				pos = find_pos;
				dist=flight[find_pos].distance;
			}
		}
		find_pos++;
	}
	if (pos) {
		strcpy(anywhere, flight[pos].to);
		flight[pos].skip=1;
		return flight[pos].distance;
	}
	return 0;
}

int find_small_cost(from, anywhere)
char *from, *anywhere;
{
	int pos, dist;

	pos=find_pos=0;
	dist=32000;
	while (find_pos < f_pos) {
		if (!strcmp(flight[find_pos].from, from) && !flight[find_pos].skip) {
			if(flight[find_pos].distance < dist) {
				pos = find_pos;
				dist=flight[find_pos].distance;
			}
		}
		find_pos++;
	}
	if (pos) {
		strcpy(anywhere, flight[pos].to);
		flight[pos].skip=1;
		return flight[pos].distance;
	}
	return 0;
}

void reset_database() {
	for (int i = 0; i < MAX; ++i) {
		flight[i].skip = 0;
	}
}

void clearmarkers() {
	for (int i = 0; i < f_pos; ++i) {
		flight[i].skip = 0;
	}
}

int hasmarkers() {
	for (int var = 0; var < MAX; ++var) {
		if (flight[var].skip) {
			return flight[var].skip;
		}
	}
	return 0;
}

void retract(from, to)
char *from, *to;
{
	int t;
	for (t = 0; t < f_pos; ++t) {
		if (!strcmp(flight[t].from, from) && !strcmp(flight[t].to, to)) {
			strcpy(flight[t].from, "");
		}
	}
}

void setup_database() {
	// Cria e popula o banco de dados
	assert_fligth("New York"	, "Chicago"		,1000);
	assert_fligth("Chicago"		, "Denver"		,1000);
	assert_fligth("New York"	, "Toronto"		,800);
	assert_fligth("New York"	, "Denver"		,1900);
	assert_fligth("Toronto"		, "Calgary"		,1500);
	assert_fligth("Toronto"		, "Los Angeles"	,1800);
	assert_fligth("Toronto"		, "Chicago"		,500);
	assert_fligth("Denver"		, "Urbana"		,1000);
	assert_fligth("Denver"		, "Houston"		,1500);
	assert_fligth("Houston"		, "Los Angeles"	,1500);
	assert_fligth("Denver"		, "Los Angeles"	,1000);
}
