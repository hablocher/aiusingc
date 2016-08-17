/*
 * flight.c
 *
 *  Created on: 21 de jul de 2016
 *      Author: Marcelo
 */
#include "flight_operations.h"
#include "flight_database.h"
#include "stack_fligth.h"
#include "constants.h"

/* determina se ha uma rota entre a origem e o destino */
void isflight_depth_first_search(from, to,  find_method, dist)
char *from, *to, find_method;
int dist;
{
	int dmatch, dfind;
	char anywhere[20];

	/* ve se o destino é alcançado */
	if ( (dmatch=match(from, to)) ) {
		push(from, to, dmatch);
		return;
	}

	/* tenta outra conexão */
	if ( (dfind=find(from, anywhere, find_method)) ) {
		push(from, anywhere, dfind);
		isflight_depth_first_search(anywhere, to, find_method, dfind);
	} else if (tos()>0) {
		/* restauração */
		pop(from, to, &dist);
		isflight_depth_first_search(from, to, find_method, dist);
	}
}


void isflight_breadth_first_search(from, to, find_method, dist)
char *from, *to, find_method;
int dist;
{
	int d, dfind;
	char anywhere[20];

	while ( (dist=find(from, anywhere, find_method)) ) {
		/* modificação para busca em largura */
		if ( (d=match(anywhere, to)) ) {
			push(from, to, dist);
			push(anywhere, to, d);
			return;
		}
	}

	/* procura outra conexão */
	if ( (dfind=find(from, anywhere, find_method)) ) {
		push(from, to, dfind);
		isflight_breadth_first_search(anywhere, to, find_method, dfind);
	} else if (tos()>0) {
		pop(from, to, &dist);
		isflight_breadth_first_search(from, to, find_method, dist);
	}
}

/* mostra a rota e a distancia */
void route(to)
char *to;
{
	int dist = 0, t = 0;
	while (t<tos()) {
		printf("%s", bt_stack[t].from);
		dist += bt_stack[t].dist;
		t++;
		printf(" para ");
	}
	printf("%s", to);
	printf(" - distancia %d\n", dist);
}

void clearroutes() {
	for (int i = 0; i < MAX; ++i) {
		bt_stack[i].dist = 0;
	}
	reset_tos();
}
