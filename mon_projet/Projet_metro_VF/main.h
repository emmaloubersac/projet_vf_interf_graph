#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liste.h"
#include "ligne.h"
#include "truc.h"
#include "aqrtopo.h"
#include "abr_type.h"
#include "abr.h"

void dijkstra(Un_elem *liste_sta, Un_truc *sta_dep);
Un_elem *cherche_chemin(Un_truc *sta_arr);
int plus_court_chemin(char* sta_dep, char* sta_arr);


#endif
