#ifndef CONTRATACION_H_
#define CONTRATACION_H_

#define TXTARCHIVO_LEN 64
#define QTY_PUBLICACIONES 1000
#define TRUE 1
#define FALSE 0
#define MIN_IDCLIENTE 100
#define MAX_IDCLIENTE 999
#define MIN_NUMRUBRO 1
#define MAX_NUMRUBRO 100
#define ACTIVO 1
#define PAUSADO 0


typedef struct
{
	int id;
	int numeroDeRubro;
	char textoDelArchivo[TXTARCHIVO_LEN];
	int idCliente;
	int estado;

}Publicacion;


#include "Cliente.h"







//-------------------------ACTUALIZADOS CON PUNTEROS--------------------------------------

int publicacion_imprimirPublicacionesActivas(Publicacion** pArray,int limite);
int publicacion_imprimirPublicacionesPausadas(Publicacion** pArray,int limite);
int publicacion_pausarPublicacion(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente);
int publicacion_reanudarPublicacion(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente);
int publicacion_buscarId(Publicacion** pArray,int limite,int idABuscar);
int publicacion_buscarRubro(Publicacion** pArray,int limite,int rubroABuscar);
int publicacion_mostrarPorEstado(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente,int estado);
int publicacion_buscarIdyEstado(Publicacion** pArray,int limite,int idABuscar,int estado);
int publicacion_mostrarClientesConPublicacion(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente,int idPublicacion);
int publicacion_altaArray(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente);
int publicacion_getEmptyIndex(Publicacion** pArray,int limite);
int publicacion_imprimir(Publicacion* pPublicacion);

//--UTILIZADAS EN INFORMES--
int publicacion_imprimirArray(Publicacion** pArray,int limite);
int publicacion_mostrarPorRubro(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente,int rubro);
int publicacion_mostrarPoridCliente(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente,int idClientes);

Publicacion* pub_newConParametros(int id, int numeroDeRubro,char* textoDelArchivo,int idCliente,int estado);
int pub_initArray(Publicacion** pArray,int limite);
void pub_delete(Publicacion* pc);


//-------------------------GETTERS--------------------------------------
int pub_getId(Publicacion* pArray, int* pValor);
int pub_getRubro(Publicacion* pArray, int* numRubro);
int pub_getTxtArchivo(Publicacion* pArray, char* txtArchivo);
int pub_getidCliente(Publicacion* pArray, int* idCliente);
int pub_getEstado(Publicacion* pArray, int* estado);
//-------------------------sETTERS--------------------------------------
int pub_setId(Publicacion* pArray, int pValor);
int pub_setRubro(Publicacion* pArray, int numRubro);
int pub_setTxtArchivo(Publicacion* pArray, char* txtArchivo);
int pub_setidCliente(Publicacion* pArray, int idCliente);
int pub_setEstado(Publicacion* pArray, int estado);

#endif /* CONTRATACION_H_ */
