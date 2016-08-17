/*
 * flight.h
 *
 *  Created on: 21 de jul de 2016
 *      Author: Marcelo
 */

#ifndef FLIGHT_FLIGHT_OPERATIONS_H_
#define FLIGHT_FLIGHT_OPERATIONS_H_

void isflight_depth_first_search(char *from, char *to, char find_method, int dist);
void isflight_breadth_first_search(char *from, char *to, char find_method, int dist);
void route(char *to);
void clearroutes();

#endif /* FLIGHT_FLIGHT_OPERATIONS_H_ */
