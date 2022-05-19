/* 5088530 */ 

#include "../include/abb.h"

struct _rep_abb {
    TInfo info;
    _rep_abb *izq, *der;
};

TAbb crearAbb() {
    TAbb abb = NULL;
    return abb; 
}

void liberarAbb(TAbb abb) {
    if (!esVacioAbb(abb)) {
        TAbb aux = abb;
        liberarInfo(abb->info);
        liberarAbb(derecho(abb));
        liberarAbb(izquierdo(abb));
        delete aux;
    }
}

bool esVacioAbb(TAbb abb) {
    return (abb == NULL);
}

TAbb buscarSubarbol(nat clave, TAbb abb) {
    if (!esVacioAbb(abb)) {
        if (natInfo(abb->info) == clave) {
            return abb;
        } else {
            TAbb izq = buscarSubarbol(clave,izquierdo(abb));
            TAbb der = buscarSubarbol(clave,derecho(abb));
            if (izq != NULL) {return izq;}
            else if (der != NULL) {return der;}            
            else {return NULL;}
        }
    } else {
        return NULL;
    }
}

TInfo raiz(TAbb abb) {
    return abb->info;
}

TAbb izquierdo(TAbb abb) {
    return abb->izq;
}

TAbb derecho(TAbb abb) {
    return abb->der;
}

TInfo menorEnAbb(TAbb abb) {
    if (izquierdo(abb) != NULL) {
        return menorEnAbb(izquierdo(abb));
    } else {
        return abb->info;
    }
}

TInfo mayorEnAbb(TAbb abb) {
    if (derecho(abb) != NULL) {
        return mayorEnAbb(derecho(abb));
    } else {
        return abb->info;
    }
}

TAbb consAbb(TInfo dato, TAbb izq, TAbb der) {
    TAbb nuevo = new _rep_abb;
    nuevo->info = dato;
    nuevo->izq = izq;
    nuevo->der = der;
    return nuevo;
}

static void insertarEnAbbAux(TInfo dato, TAbb &abb) {
    if (esVacioAbb(abb)) {
        abb = new _rep_abb;
        abb->info = dato;
        abb->izq = abb->der = NULL;
    } else {
        if (natInfo(dato) < natInfo(abb->info)) {
            insertarEnAbbAux(dato,abb->izq);
        } else {
            insertarEnAbbAux(dato,abb->der);
        }
    }
}

TAbb insertarEnAbb(TInfo dato, TAbb abb) { 
    insertarEnAbbAux(dato,abb);
    return abb;
}

static void removerDeAbbAux(nat clave, TAbb &abb) {
    if (!esVacioAbb(abb)) {
        if (clave == natInfo(abb->info) && izquierdo(abb) == NULL && derecho(abb) == NULL) {
            TAbb borrar = abb;
            abb = NULL;
            liberarInfo(borrar->info);
            delete borrar;
        } else if (clave == natInfo(abb->info) && izquierdo(abb) != NULL && derecho(abb) == NULL) {
            TAbb borrar = abb;
            abb = izquierdo(abb);
            liberarInfo(borrar->info);
            delete borrar;
        } else if (clave == natInfo(abb->info) && izquierdo(abb) == NULL && derecho(abb) != NULL) {
            TAbb borrar = abb;
            abb = derecho(abb);
            liberarInfo(borrar->info);
            delete borrar;
        } else if (clave == natInfo(abb->info) && izquierdo(abb) != NULL && derecho(abb) != NULL) {
            liberarInfo(abb->info);
            TInfo infoMayorIzq = crearInfo(natInfo(mayorEnAbb(izquierdo(abb))),realInfo(mayorEnAbb(izquierdo(abb))));
            abb->info = infoMayorIzq;
            removerDeAbbAux(natInfo(abb->info),abb->izq);
        } else {
            removerDeAbbAux(clave,abb->izq);
            removerDeAbbAux(clave,abb->der);
        }
    }
}

TAbb removerDeAbb(nat clave, TAbb abb) {
    removerDeAbbAux(clave,abb);
    return abb;
}

TAbb copiaAbb(TAbb abb) {
    if (!esVacioAbb(abb)) {
        TAbb abbNuevo = new _rep_abb;
        abbNuevo->info = crearInfo(natInfo(abb->info),realInfo(abb->info));
        abbNuevo->izq = copiaAbb(izquierdo(abb));
        abbNuevo->der = copiaAbb(derecho(abb));
        return abbNuevo;
    } else {
        return NULL;
    }
}