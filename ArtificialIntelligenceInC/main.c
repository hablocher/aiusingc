/*
 * Main.c
 *
 *  Created on: 21 de jul de 2016
 *      Author: Marcelo
 */
#include "flight/flight_database.h"
#include "flight/flight_operations.h"
#include "flight/stack_fligth.h"

void reset() {
	// Reseta o banco de dados
	clearroutes();
	reset_database();
}

void depth_search_using_down_hill(char from[20], char to[20]) {
	reset();
	// Faz uma busca em profundidade usando o método "descendo o morro"
	isflight_depth_first_search(from, to, 'd', 0);
	// Mostra as rotas
	route(to);
}

void breadth_search_using_down_hill(char from[20], char to[20]) {
	reset();
	// Faz uma busca em nivel, usando o método "descendo o morro"
	isflight_breadth_first_search(from, to, 'd', 0);
	// Mostra as rotas
	route(to);
}

void depth_search_using_hill_climbing(char from[20], char to[20]) {
	reset();
	// Faz uma busca em profundidade, usando o método "subindo o morro"
	isflight_depth_first_search(from, to, 'u', 0);
	// Mostra as rotas
	route(to);
}

void depth_search_using_small_cost(char from[20], char to[20]) {
	reset();
	// Faz uma busca em profundidade, usando e método "menor custo"
	isflight_depth_first_search(from, to, 's', 0);
	// Mostra as rotas
	route(to);
}

void multiple_solutions_using_depth_first_and_down_hill(char from[20],
		char to[20]) {
	printf("Procurando múltiplas soluções\n");
	reset();
	do {
		isflight_depth_first_search(from, to, 'd', 0);
		if (tos() == 0) {
			break;
		} else {
			route(to);
			reset_tos(); /* inicia a pilha de restauracao */
		}
	} while (1);
}

int main() {

	char from[20] = "New York";
	char to[20] = "Los Angeles";

	setup_database();

	depth_search_using_down_hill(from, to);

	breadth_search_using_down_hill(from, to);

	depth_search_using_hill_climbing(from, to);

	depth_search_using_small_cost(from, to);

	multiple_solutions_using_depth_first_and_down_hill(from, to);

	reset();
	char c1[20], c2[20];
	int d;
	do {
		isflight_depth_first_search(from, to, 'd', 0);
		route(to);
		clearmarkers(); /* inicia o banco de dados */
		if (tos()>0) {
			pop(c1, c2, &d);
			retract(c1, c2); /* retira o ultimo no banco de dados */
			reset_tos();
		} else {
			break;
		}
	} while (1);
}

