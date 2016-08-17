/*
 * stack.h
 *
 *  Created on: 21 de jul de 2016
 *      Author: Marcelo
 */

#ifndef FLIGHT_STACK_FLIGTH_H_
#define FLIGHT_STACK_FLIGTH_H_

#include "constants.h"

struct stack {
	char from[20];
	char to[20];
	int dist;
};

struct stack bt_stack[MAX];

void push(char *from, char *to, int dist);

void pop(char *from, char *to, int *dist);

int tos();

void reset_tos();

#endif /* FLIGHT_STACK_FLIGTH_H_ */
