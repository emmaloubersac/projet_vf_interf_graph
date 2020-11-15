#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liste.h"
#include "ligne.h"
#include "truc.h"
#include "aqrtopo.h"
#include "abr_type.h"
#include "abr.h"



void dijkstra(Un_elem *liste_sta, Un_truc *sta_dep){
	Un_elem *Q=malloc(sizeof(Un_elem));
	while (liste_sta->suiv!=NULL){
		liste_sta->truc->user_val=10000;
		Q=inserer_deb_liste(Q, liste_sta->truc);
		liste_sta=liste_sta->suiv;
	}
	sta_dep->user_val=0;
	extraire_liste(&Q, sta_dep);
	Q=inserer_deb_liste(Q,sta_dep);
	while(Q->suiv!=NULL){
		Un_truc *truc = extraire_deb_liste(&Q);
		for (int i=0; i<truc->data.sta.nb_con; i++){
			float temp_val=truc->user_val;
			temp_val=temp_val+truc->data.sta.tab_con[i]->data.con.ligne->intervalle;
			if (temp_val<truc->data.sta.tab_con[i]->data.con.sta_arr->user_val){
				truc->data.sta.tab_con[i]->data.con.sta_arr->data.sta.con_pcc=truc->data.sta.tab_con[i];
				extraire_liste(&Q,truc->data.sta.tab_con[i]->data.con.sta_arr);
				Q=inserer_liste_trie(Q,truc->data.sta.tab_con[i]->data.con.sta_arr);
				truc->data.sta.tab_con[i]->data.con.sta_arr->user_val=temp_val;
			}
		}
	}
}

Un_elem *cherche_chemin(Un_truc *sta_arr){
	Un_elem *chemin=inserer_deb_liste(NULL, sta_arr);
	while (chemin->truc->user_val!=0){
		chemin=inserer_deb_liste(chemin, chemin->truc->data.sta.con_pcc->data.con.sta_dep);
	}
	return chemin;
}

int plus_court_chemin(char* sta_dep, char* sta_arr){
	//test et affichage des lignes
    Une_ligne *ligne = NULL;
    ligne = lire_lignes("ligne_metro.csv");
    //afficher_lignes(ligne);
    


    //test et affichage de station
    Un_elem *liste_sta=NULL;
    liste_sta = lire_stations("station2.csv");
    //affiche_liste_truc_sta(liste_sta);



    //test et affichage des connexions et abr
    Un_nabr *abr = construire_abr(liste_sta);
    Un_elem *liste_con = lire_connexions("connexion.csv", ligne,abr);
    //affiche_liste_truc_con(liste_con);
    
    dijkstra(liste_sta, chercher_station(abr,sta_dep));
    Un_elem *liste = cherche_chemin(chercher_station(abr,sta_arr));
	
	while (liste->suiv!=NULL){
		printf("%s->",liste->truc->data.sta.nom);
		liste=liste->suiv;
	}
	printf("%s\n",liste->truc->data.sta.nom);
	return liste->truc->user_val;

    //Un_noeud *aqr=construire_aqr(liste_sta);
    //affiche_aqr(aqr);
    
    //detruire_aqr(aqr);
   	//detruire_abr(abr);
    detruire_liste_et_truc(liste_sta);
    detruire_liste_et_truc(liste_con);
    detruire_lignes(ligne);
}	

int main(){
	printf("%d\n",plus_court_chemin("OLYMPIADES","CONVENTION"));

	return 0;
}