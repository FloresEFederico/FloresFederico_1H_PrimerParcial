#include "Cliente.h"
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
	int isEmpty;
}Publicacion;

int publicacion_inicializarArray(Publicacion* pArray,int limite);
int publicacion_imprimir(Publicacion* auxPublicacion);
int publicacion_imprimirArray(Publicacion* pArray,int limite);
int publicacion_imprimirPublicacionesActivas(Publicacion* pArray,int limite);
int publicacion_imprimirPublicacionesPausadas(Publicacion* pArray,int limite);
int publicacion_getEmptyIndex(Publicacion* pArray,int limite);
int publicacion_altaArray(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente);
int publicacion_pausarPublicacion(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente);
int publicacion_reanudarPublicacion(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente);
int publicacion_buscarId(Publicacion* pArray,int limite,int idABuscar);
int publicacion_buscarRubro(Publicacion* pArray,int limite,int rubroABuscar);
int publicacion_buscarIdyEstado(Publicacion* pArray,int limite,int idABuscar,int estado);
int publicacion_mostrarClientesConPublicacion(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente,int idPublicacion);

//--UTILIZADAS EN INFORMES--
int publicacion_mostrarPorRubro(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente,int rubro);
int publicacion_mostrarPoridCliente(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente,int idClientes);

#endif /* CONTRATACION_H_ */
