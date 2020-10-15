#ifndef CLIENTE_H_
#define CLIENTE_H_


#define NOMBRE_LEN 51
#define CUIT_LEN 21
#define QTY_CLIENTES 100
#define TRUE 1
#define FALSE 0

typedef struct
{
	int id;
	char nombre[NOMBRE_LEN];
	char apellido[NOMBRE_LEN];
	char cuit[CUIT_LEN];
	int isEmpty;
}Cliente;

#include "Publicacion.h"




int cliente_inicializarArray(Cliente* pArray,int limite);
int cliente_imprimir(Cliente* auxCliente);
int cliente_imprimirArray(Cliente* pArray,int limite);
int cliente_altaArray(Cliente* pArray,int limite);
int cliente_modificarArray(Cliente* pArray,int limite);
int cliente_bajaArray(Cliente* pArray,int limite,Publicacion* pArrayPublicacion,int limitePublicacion);
int cliente_getEmptyIndex(Cliente* pArray,int limite);
int cliente_buscarId(Cliente* pArray,int limite,int idABuscar);

#endif /* CLIENTE_H_ */
