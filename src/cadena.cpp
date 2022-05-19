/* 5088530 */ 

#include "../include/cadena.h"

struct _rep_cadena {
	TInfo info;
	TCadena siguiente;
	TCadena anterior;
}; 

TCadena crearCadena() {
	TCadena cad = NULL;
	return cad;
}


void liberarCadena(TCadena cad) {
	if (cad != NULL) {
		cad = removerDeCadena(natInfo(primeroEnCadena(cad)),cad);
		liberarCadena(cad);
	}
}

nat cantidadEnCadena(TCadena cad) {
	nat cont = 0;
	TCadena aux = cad;
	if (aux != NULL) {
		do {
			aux = aux-> siguiente;
			cont++;
		} while (aux != cad);
	}
	return cont;
} 

bool estaEnCadena(nat natural, TCadena cad) {
	if (cad != NULL) {
		TCadena aux = cad;
		do {
			aux = aux->siguiente;
		} while (natInfo(aux->info) != natural && aux != cad);
		return (natInfo(aux->info) == natural);
	}
	else {return false;}
}

TCadena insertarAlInicio(nat natural, double real, TCadena cad) {
	if (cad == NULL) {
		TCadena nuevo = new _rep_cadena;
		nuevo->info = crearInfo(natural,real);
		nuevo->siguiente = nuevo;
		nuevo->anterior = nuevo;
		return nuevo;
	}
	else {
		TCadena nuevo = new _rep_cadena;
		nuevo->info = crearInfo(natural,real);
		nuevo->siguiente = cad;
		nuevo->anterior = cad->anterior;
		cad->anterior->siguiente = nuevo;
		cad->anterior = nuevo;
		return nuevo;	
	}
}

TInfo infoCadena(nat natural, TCadena cad) {
	TCadena aux = cad;
	while (natInfo(aux->info) != natural){
		aux = aux-> siguiente;
	}
	return aux->info;
}

TInfo primeroEnCadena(TCadena cad) {
  return cad->info;
} 

TCadena cadenaSiguiente(TCadena cad) {
	if (cad == NULL || cad->siguiente == NULL) {
		return cad;
	}
	else {
		return cad->siguiente;
	}
}

TCadena removerDeCadena(nat natural, TCadena cad) {
	if (cad->siguiente == cad) {
		liberarInfo(cad->info);
		delete cad;
		return NULL;
	}
	else {
		TCadena borrar = cad;
		bool primero = true;
		while (natInfo(borrar->info) != natural) {
			borrar = borrar->siguiente;
			primero = false;
		}
		TCadena siguiente = borrar->siguiente;
		borrar->anterior->siguiente = borrar->siguiente;
		siguiente->anterior = borrar->anterior;
		liberarInfo(borrar->info);
		delete borrar;
		if (primero) {return siguiente;}
		else {return cad;}	
	}
}

void imprimirCadena(TCadena cad) {
	TCadena aux = cad;
	if (aux != NULL) {
		do {
			printf("(%u,%0.2f)", natInfo(aux->info), realInfo(aux->info));
			aux = aux-> siguiente;
		} while (aux != cad);
	}
	printf("\n");
}