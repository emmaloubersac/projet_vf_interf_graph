#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "aqrtopo.h"
#include "liste.h"
#include <math.h>
#define SEUIL 0.0001
#define LIMITE_N 49
#define LIMITE_E 2.45
#define LIMITE_S 48.7
#define LIMITE_O 2.13

void inserer_aqr(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se, Un_truc *truc){
	if (aqr->no==NULL && aqr->ne==NULL && aqr->so==NULL && aqr->se==NULL && aqr->truc==NULL){
		aqr->truc=truc;
		aqr->limite_no=limite_no;
		aqr->limite_se=limite_se;
	}
	else{
		/*if (pow(truc->coord.lat-aqr->truc->coord.lat,2)+pow(truc->coord.lon-aqr->truc->coord.lon,2)<SEUIL){
			truc->coord.lat=truc->coord.lat+SEUIL/2;
			truc->coord.lon=truc->coord.lon+SEUIL/2;
		}*/
		Une_coord moitie;
    	moitie.lat = limite_se.lat + (limite_no.lat - limite_se.lat)/2.0;
    	moitie.lon = limite_no.lon + (limite_se.lon - limite_no.lon)/2.0;
    	if (aqr->truc!=NULL){
    		if (aqr->truc->coord.lat < moitie.lat && aqr->truc->coord.lon > moitie.lon){
    			if (aqr->no==NULL){
    				aqr->no=malloc(sizeof(Un_noeud));
    			}
    			inserer_aqr(aqr->no,limite_no,moitie,aqr->truc);
    		}
    		else if (aqr->truc->coord.lat < moitie.lat && aqr->truc->coord.lon < moitie.lon){
    			if (aqr->so==NULL){
    				aqr->so=malloc(sizeof(Un_noeud));
    			}
    			Une_coord new_no;
    			new_no.lat=limite_no.lat;
    			new_no.lon=moitie.lon;
    			Une_coord new_se;
    			new_se.lat=moitie.lat;
    			new_se.lon=limite_se.lon;
    			inserer_aqr(aqr->so, new_no, new_se, aqr->truc);
    		}
    		else if (aqr->truc->coord.lon > moitie.lon && aqr->truc->coord.lat > moitie.lat){
    			if (aqr->ne==NULL){
    				aqr->ne=malloc(sizeof(Un_noeud));
    			}
    			Une_coord new_no;
    			new_no.lat=moitie.lat;
    			new_no.lon=limite_no.lon;
    			Une_coord new_se;
    			new_se.lat=limite_se.lat;
    			new_se.lon=moitie.lon;
    			inserer_aqr(aqr->ne, new_no, new_se, aqr->truc);
    		}
    		else{
    			if (aqr->se==NULL){
    				aqr->se=malloc(sizeof(Un_noeud));
    			}
    			inserer_aqr(aqr->se,moitie,limite_se,aqr->truc);
    		}
    		aqr->truc=NULL;
    	}
    	if (truc->coord.lat < moitie.lat && truc->coord.lon > moitie.lon){
    		if (aqr->no==NULL){
    			aqr->no=malloc(sizeof(Un_noeud));
    		}
    		inserer_aqr(aqr->no,limite_no,moitie,truc);
    	}
    	else if (truc->coord.lat < moitie.lat && truc->coord.lon < moitie.lon){
    		if (aqr->so==NULL){
    			aqr->so=malloc(sizeof(Un_noeud));
    		}
    		Une_coord new_no;
    		new_no.lat=limite_no.lat;
    		new_no.lon=moitie.lon;
    		Une_coord new_se;
    		new_se.lat=moitie.lat;
    		new_se.lon=limite_se.lon;
    		inserer_aqr(aqr->so, new_no, new_se, truc);
    	}
    	else if (truc->coord.lon > moitie.lon && truc->coord.lat > moitie.lat){
    		if (aqr->ne==NULL){
    			aqr->ne=malloc(sizeof(Un_noeud));
    		}
    		Une_coord new_no;
    		new_no.lat=moitie.lat;
    		new_no.lon=limite_no.lon;
    		Une_coord new_se;
    		new_se.lat=limite_se.lat;
    		new_se.lon=moitie.lon;
    		inserer_aqr(aqr->ne, new_no, new_se, truc);
    	}
    	else{
    		if (aqr->se==NULL){
    			aqr->se=malloc(sizeof(Un_noeud));
    		}
    		inserer_aqr(aqr->se,moitie,limite_se,truc);
    	}
    }
}
    
    
Un_noeud *construire_aqr(Un_elem *liste){
	Un_noeud *aqr=NULL;
	aqr=malloc(sizeof(Un_noeud));
	Une_coord limite_no;
	Une_coord limite_se;
	limite_no.lon=LIMITE_N;
	limite_no.lat=LIMITE_O;
	limite_se.lon=LIMITE_S;
	limite_se.lat=LIMITE_E;
	while (liste->suiv!=NULL){
		inserer_aqr(aqr, limite_no, limite_se, liste->truc);
		liste=liste->suiv;
	}
	return aqr;
}
	
	
void detruire_aqr(Un_noeud *aqr){
    if (aqr->ne != NULL)
        detruire_aqr(aqr->ne);
    if (aqr->no != NULL)
        detruire_aqr(aqr->no);
    if (aqr->se != NULL)
        detruire_aqr(aqr->se);
    if (aqr->so != NULL)
        detruire_aqr(aqr->so);
    free(aqr);
}

void affiche_aqr(Un_noeud *aqr){
	if (aqr->truc!=NULL)
		printf("%f  %f\n",aqr->truc->coord.lat,aqr->truc->coord.lon);
	else{
		if (aqr->no!=NULL)
			affiche_aqr(aqr->no);
		if (aqr->ne!=NULL)
			affiche_aqr(aqr->ne);
		if (aqr->so!=NULL)
			affiche_aqr(aqr->so);
		if (aqr->se!=NULL)
			affiche_aqr(aqr->se);
	}
}

Un_truc *chercher_aqr(Un_noeud *aqr, Une_coord coord){
	Une_coord moitie;
    moitie.lat = aqr->limite_se.lat + (aqr->limite_no.lat - aqr->limite_se.lat)/2.0;
    moitie.lon = aqr->limite_no.lon + (aqr->limite_se.lon - aqr->limite_no.lon)/2.0;
    if (coord.lat < moitie.lat && coord.lon < moitie.lon){
    	if (aqr->so!=NULL)
    		chercher_aqr(aqr->so,coord);
    	else 
    		return aqr->truc;
    }
    else if (coord.lat > moitie.lat && coord.lon < moitie.lon){
    	if (aqr->se!=NULL)
    		chercher_aqr(aqr->se,coord);
    	else 
    		return aqr->truc;
    }
    else if (coord.lat > moitie.lat && coord.lon > moitie.lon){
    	if (aqr->ne!=NULL)
    		chercher_aqr(aqr->ne,coord);
    	else 
    		return aqr->truc;
    }

    else{
    	if (aqr->no!=NULL)
    		chercher_aqr(aqr->no,coord);
    	else 
    		return aqr->truc;
    }

}

Un_elem *chercher_zone(Un_noeud *aqr, Un_elem *liste, Une_coord limite_no, Une_coord limite_se){
	if (aqr->truc!=NULL){
		if (aqr->truc->coord.lat>limite_no.lat && aqr->truc->coord.lat<limite_se.lat && aqr->truc->coord.lon<limite_no.lon && aqr->truc->coord.lon>limite_se.lon)
			liste=inserer_deb_liste(liste,aqr->truc);
	}
	else{
		if (aqr->se!=NULL && limite_no.lat<aqr->se->limite_se.lat && limite_no.lon>aqr->se->limite_se.lon && limite_se.lat>aqr->se->limite_no.lat && limite_se.lon<aqr->se->limite_no.lon)
			liste=chercher_zone(aqr->se, liste, limite_no, limite_se);
		if (aqr->ne!=NULL && limite_no.lat<aqr->ne->limite_se.lat && limite_no.lon>aqr->ne->limite_se.lon && limite_se.lat>aqr->ne->limite_no.lat && limite_se.lon<aqr->ne->limite_no.lon)
			liste=chercher_zone(aqr->ne, liste, limite_no, limite_se);
		if (aqr->so!=NULL && limite_no.lat<aqr->so->limite_se.lat && limite_no.lon>aqr->so->limite_se.lon && limite_se.lat>aqr->so->limite_no.lat && limite_se.lon<aqr->so->limite_no.lon)
			liste=chercher_zone(aqr->so, liste, limite_no, limite_se);
		if (aqr->no!=NULL && limite_no.lat<aqr->no->limite_se.lat && limite_no.lon>aqr->no->limite_se.lon && limite_se.lat>aqr->no->limite_no.lat && limite_se.lon<aqr->no->limite_no.lon)
			liste=chercher_zone(aqr->no, liste, limite_no, limite_se);
	}
	return liste;
}

    
    
    
