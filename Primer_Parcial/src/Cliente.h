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




//-------------------------ACTUALIZADOS CON PUNTEROS--------------------------------------
int cliente_altaArray(Cliente** pArray,int limite);
int cliente_modificarArray(Cliente** pArray,int limite);
int cliente_getEmptyIndex(Cliente** pArray,int limite);
int cliente_bajaArray(Cliente** pArray,int limite,Publicacion** pArrayPublicacion,int limitePublicacion);
int cliente_buscarId(Cliente** pArray,int limite,int idABuscar);
int cliente_imprimir(Cliente* pCliente);
int cliente_imprimirArray(Cliente** pArray,int limite);

Cliente* cli_newConParametros(int id, char* nombre,char* apellido,char* cuit);
int cli_initArray(Cliente** pArray,int limite);
void cli_delete(Cliente* pc);


//-------------------------GETTERS--------------------------------------
int cli_getId(Cliente* pArray, int* pValor);
int cli_getNombre(Cliente* pArray, char* name);
int cli_getApellido(Cliente* pArray, char* lastName);
int cli_getCuit(Cliente* pArray, char* cuit);
//-------------------------sETTERS--------------------------------------
int cli_setId(Cliente* pArray,int pValor);
int cli_setNombre(Cliente* pArray, char* name);
int cli_setApellido(Cliente* pArray, char* lastName);
int cli_setCuit(Cliente* pArray, char* cuit);

#endif /* CLIENTE_H_ */
