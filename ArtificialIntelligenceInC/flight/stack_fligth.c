/*
 * stack.c
 *
 *  Created on: 21 de jul de 2016
 *      Author: Marcelo
 */
#include "stack_fligth.h"
#include <string.h>
#include <stdio.h>
#include "constants.h"

int tos_=0; /* topo da pilha */

void push(from, to, dist)
char *from, * to;
int dist;
{
	if (tos_<MAX) {
		strcpy(bt_stack[tos_].from, from);
		strcpy(bt_stack[tos_].to, to);
		bt_stack[tos_].dist = dist;
		tos_++;
	}
	else printf("pilha cheia.\n");
}

void pop(from, to, dist)
char *from, *to;
int *dist;
{
	if (tos_>0) {
		tos_--;
		strcpy(from, bt_stack[tos_].from);
		strcpy(to, bt_stack[tos_].to);
		*dist = bt_stack[tos_].dist;
	} else printf("underflow de pilha.\n");
}

int tos() {
	return tos_;
}

void reset_tos() {
	tos_ = 0;
}
