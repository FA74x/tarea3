/* 5088530 */

#include "../include/aplicaciones.h"
#include <math.h>
#include <string.h>

typedef unsigned int uint;

TCadena linealizacion(TAbb abb) {
  TCadena cad = crearCadena();
  if (!esVacioAbb(abb)) {
    TCadena cad_izq = linealizacion(izquierdo(abb));
    TCadena cad_der = linealizacion(derecho(abb));
    while (cad_der != NULL) {
      for (uint i = 0; i < cantidadEnCadena(cad_der) - 1; i++) {
        cad_der = cadenaSiguiente(cad_der);
      }
      cad = insertarAlInicio(natInfo(primeroEnCadena(cad_der)),realInfo(primeroEnCadena(cad_der)),cad);
      cad_der = removerDeCadena(natInfo(primeroEnCadena(cad_der)),cad_der);
    }
    cad = insertarAlInicio(natInfo(raiz(abb)),realInfo(raiz(abb)),cad);
    while (cad_izq != NULL) {
      for (uint j = 0; j < cantidadEnCadena(cad_izq) - 1; j++) {
        cad_izq = cadenaSiguiente(cad_izq);
      }
      cad = insertarAlInicio(natInfo(primeroEnCadena(cad_izq)),realInfo(primeroEnCadena(cad_izq)),cad);
      cad_izq = removerDeCadena(natInfo(primeroEnCadena(cad_izq)),cad_izq);
    }
  } return cad;
}

static void imprimirAbbAux(TAbb abb, uint nivel) {
  if (!esVacioAbb(abb)) {
    imprimirAbbAux(derecho(abb),nivel+1);
    for (uint i = 0; i < nivel; i++) {printf("-");}
    imprimirInfo(raiz(abb));
    printf("\n");
    imprimirAbbAux(izquierdo(abb),nivel+1);
  }
}

void imprimirAbb(TAbb abb) {
  uint nivel = 0;
  imprimirAbbAux(abb,nivel);  
}

static uint altura (TAbb abb) {
    if (esVacioAbb(abb)) {
      return 0;
    }
    else {
      return 1 + (fmax(altura(izquierdo(abb)),altura(derecho(abb))));
    }
}

static uint contarHojas (TAbb abb) {
    if ((izquierdo(abb) == NULL) && (derecho(abb) == NULL)) {
      return 1;
    } else if (izquierdo(abb) == NULL) {
      return contarHojas(derecho(abb));
    } else if (derecho(abb) == NULL) {
      return contarHojas(izquierdo(abb));
    } else {
      return (contarHojas(izquierdo(abb)) + contarHojas(derecho(abb)));
    }
}

bool esPerfecto(TAbb abb) {
  return (esVacioAbb(abb) || (pow(2,altura(abb)-1) == contarHojas(abb)));
}

TAbb menores(double limite, TAbb abb) {
  TAbb a_izq, a_der, res;
  TInfo mayor;
  if (esVacioAbb(abb)) {
    res = NULL;
  } else {
    a_izq = menores(limite,izquierdo(abb));
    a_der = menores(limite,derecho(abb));
    if (realInfo(raiz(abb)) < limite) {
      TInfo info = copiaInfo(raiz(abb));
      res = consAbb(info,a_izq,a_der);
    } else if (a_izq == NULL) {
      res = a_der;
    } else if (a_der == NULL) {
      res = a_izq;
    } else {
      mayor = copiaInfo((mayorEnAbb(a_izq)));
      a_izq = removerDeAbb(natInfo(mayorEnAbb(a_izq)),a_izq);
      res = consAbb(mayor,a_izq,a_der);
    }
  }
  return res;
}

static TIterador caminoAscendenteAux(nat clave, nat &k, TAbb abb, TIterador it) {
  if (k != 0 && clave == natInfo(raiz(abb))) {
    agregarAIterador(natInfo(raiz(abb)),it);
    k = k - 1;
  } else if (clave < natInfo(raiz(abb))) {
    caminoAscendenteAux(clave,k,izquierdo(abb),it);
    if (k != 0) {
      agregarAIterador(natInfo(raiz(abb)),it);
      k = k - 1;
    }
  } else if (clave > natInfo(raiz(abb))) {
    caminoAscendenteAux(clave,k,derecho(abb),it);
    if (k != 0) {
      agregarAIterador(natInfo(raiz(abb)),it);
      k = k - 1;
    }
  }
  return it;
}

TIterador caminoAscendente(nat clave, nat k, TAbb abb) {
  TIterador it = crearIterador();
  it = caminoAscendenteAux(clave,k,abb,it);
  return it;
}

static void imprimirPalabrasCortasAux(nat k, nat m, TPalabras palabras, ArregloChars arr) {
  if (m <= k && letra(palabras) == '\0') {
    arr[m] = letra(palabras);
    printf("%s\n",arr);
  } else if (m <= k && letra(palabras) != '\0') {
    arr[m] = letra(palabras);
    imprimirPalabrasCortasAux(k,m+1,subarboles(palabras),arr);
  } if (m <= k && siguientes(palabras) != NULL) {
    imprimirPalabrasCortasAux(k,m,siguientes(palabras),arr);
  }
}

void imprimirPalabrasCortas(nat k, TPalabras palabras) {
  TPalabras aux = subarboles(palabras);
  nat m = 0;
  ArregloChars arr = new char[k+1];
  imprimirPalabrasCortasAux(k,m,aux,arr);
  delete[] arr;
}

static TPalabras buscarFinPrefijoAux(int i, int largo, ArregloChars prefijo, TPalabras palabras) {
  if (i < largo && prefijo[i] == letra(palabras)) {
    return buscarFinPrefijoAux(i+1,largo,prefijo,subarboles(palabras));
  } else if (i <= largo && prefijo[i] != letra(palabras) && siguientes(palabras) == NULL) {
    return NULL;
  } else if (i == largo && prefijo[i] == letra(palabras)) {
    return palabras;
  } else {
    return buscarFinPrefijoAux(i,largo,prefijo,siguientes(palabras));
  }
}

TPalabras buscarFinPrefijo(ArregloChars prefijo, TPalabras palabras) {
  int largo = strlen(prefijo);
  int i = 0;
  TPalabras aux = subarboles(palabras);
  return buscarFinPrefijoAux(i,largo-1,prefijo,aux);
}