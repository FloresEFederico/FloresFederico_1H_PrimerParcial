#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "informes.h"

#define CANTIDAD_IDCLIENTES 1000
#define CANTIDAD_RUBROS 1000

static int cargarIdsClientes(Publicacion* pArray,int limite,int* pArrayIds,int* indiceIds);
static int cargarArrayRubros(Publicacion* pArray,int limite,int* pArrayRubros,int sizeArrayRubros,int* indiceRubros);
static int contadorDeAvisosPausados(Publicacion* pArray,int limite,int* pArrayIds,int indicePArray);
static int isPublicacionAllEmpty(Publicacion* pArray,int limite);

/**
 * \brief: Informa clientes con mayor cantidad de avisos
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param pArrayCliente: Array de Cliente
 * \param limiteCliente: limite del array de Clientes
 * \nreturn Retorna 0 (EXITO) y -1 (ERROR)
 */
int informar_ClienteConMasAvisos(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente)
{
	int retorno = -1;
	int i;
	int j;
	int listaDeClientes[CANTIDAD_IDCLIENTES];
	int indiceDeIdClientes = 0;
	int contadorDeIdsClientes = 0;
	int maximoIds;
	int indiceConMasAvisos;
	int buscarIndice;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0 &&
	   !isPublicacionAllEmpty(pArray,limite) &&
	   !cargarIdsClientes(pArray,limite,listaDeClientes,&indiceDeIdClientes))
	{

		for(i=0;i<indiceDeIdClientes;i++)
		{
			printf("\nID CLIENTE N°: %d ",listaDeClientes[i]);
			printf("\n-----------------------------------------------------------------------------------");
			publicacion_mostrarPoridCliente(pArray,limite,pArrayCliente,limiteCliente,listaDeClientes[i]);
			printf("\n-----------------------------------------------------------------------------------\n\n");
		}
		for(i=0;i<indiceDeIdClientes;i++)
		{
			for(j=0;j<limite;j++)
			{
				if(listaDeClientes[i] == pArray[j].idCliente)
				{
					contadorDeIdsClientes++;
				}
			}
			if(i == 0 || maximoIds < contadorDeIdsClientes)
			{
				maximoIds = contadorDeIdsClientes;
				contadorDeIdsClientes = 0;
				indiceConMasAvisos = i;
			}
		}
		buscarIndice = cliente_buscarId(pArrayCliente,limiteCliente,pArray[indiceConMasAvisos].idCliente);
		if(buscarIndice != -1)
		{
			printf("\nEl Cliente con mas avisos es:\n"
					"ID: %d\n"
					"Apellido,Nombre: %s,%s\n"
					"Cuit: %s\n"
					"Cantidad de avisos: %d\n",pArrayCliente[buscarIndice].id,pArrayCliente[buscarIndice].apellido,pArrayCliente[buscarIndice].nombre,pArrayCliente[buscarIndice].cuit,maximoIds);
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief: Informa la cantidad de avisos pausados
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param pArrayCliente: Array de Cliente
 * \param limiteCliente: limite del array de Clientes
 * \nreturn Retorna 0 (EXITO) y -1 (ERROR)
 */
int informar_CantDeAvisosPausados(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente)
{
	int retorno = -1;
	int arrayIdDeClientes[CANTIDAD_IDCLIENTES];
	int indiceDeIdClientes;
	int cantidadDeAvisosPausados;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0 &&
	   !cargarIdsClientes(pArray,limite,arrayIdDeClientes,&indiceDeIdClientes))
	{
		cantidadDeAvisosPausados = contadorDeAvisosPausados(pArray,limite,arrayIdDeClientes,indiceDeIdClientes);
		if(cantidadDeAvisosPausados != -1)
		{
			printf("\nCantidad de avisos pausados: %d\n",cantidadDeAvisosPausados);
		}else
		{
			printf("\nNo se ha encontrado ningun aviso pausado!\n");
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief: Informa El N° de rubro con mas avisos
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param pArrayCliente: Array de Cliente
 * \param limiteCliente: limite del array de Clientes
 * \nreturn Retorna 0 (EXITO) y -1 (ERROR)
 */
int informar_RubroConMasAvisos(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente)
{
	int retorno = -1;
	int listaDeRubros[CANTIDAD_RUBROS];
	int indiceDeRubros;
	int i;
	int j;
	int contadorDeAvisos = 0;
	int maximoAvisos;
	int RubroConMasAvisos = -1;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0 &&
	   !isPublicacionAllEmpty(pArray,limite) &&
	   !cargarArrayRubros(pArray,limite,listaDeRubros,CANTIDAD_RUBROS,&indiceDeRubros))
	{
		for(i=0;i<indiceDeRubros;i++)
		{
			printf("\nRUBRO N°: %d ",listaDeRubros[i]);
			printf("\n-----------------------------------------------------------------------------------");
			publicacion_mostrarPorRubro(pArray,limite,pArrayCliente,limiteCliente,listaDeRubros[i]);
			printf("\n-----------------------------------------------------------------------------------\n\n");
		}
		for(i=0;i<indiceDeRubros;i++)
		{
			for(j=0;j<limite;j++)
			{
				if(listaDeRubros[i] == pArray[j].numeroDeRubro)
				{
					contadorDeAvisos++;
				}
			}
			if(i == 0 || maximoAvisos < contadorDeAvisos)
			{
				maximoAvisos = contadorDeAvisos;
				contadorDeAvisos = 0;
				RubroConMasAvisos = listaDeRubros[i];
			}
		}
		if(RubroConMasAvisos != -1)
		{
			printf("\nEl rubro con mas avisos es el N° de Rubro: %d\n"
					"\nCantidad de avisos: %d\n",RubroConMasAvisos,maximoAvisos);
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief: SubMenu de informes
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param pArrayCliente: Array de Cliente
 * \param limiteCliente: limite del array de Clientes
 * \nreturn Retorna 0 (EXITO) y -1 (ERROR)
 */
int informar_subMenu(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente)
{
	int retorno = -1;
	int opcionSubMenu;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		if(!utn_getNumero(&opcionSubMenu,"\n-Menu Informes-\n"
										 "1-Cliente con mas avisos.\n"
										 "2-Cantidad de avisos pausados.\n"
										 "3-Rubro con mas avisos.\n"
										 "4-salir.\nElija opcion(1-4): ","\nOpcion invalida!\n",1,4,3))

		{
			switch(opcionSubMenu)
			{
			case 1:
				if(!informar_ClienteConMasAvisos(pArray,limite,pArrayCliente,limiteCliente))
				{
					printf("\nVolviendo al menu principal.");
				}else
				{
					printf("\nNo se cargo ninguna Publicacion!\n");
				}
				break;
			case 2:
				if(!informar_CantDeAvisosPausados(pArray,limite,pArrayCliente,limiteCliente))
				{
					printf("\nVolviendo al menu principal.");
				}else
				{
					printf("\nHubo un error en el informe.\n");
				}
				break;
			case 3:
				if(!informar_RubroConMasAvisos(pArray,limite,pArrayCliente,limiteCliente))
				{
					printf("\nVolviendo al menu principal.");
				}else
				{
					printf("\nNo se cargo ninguna Publicacion!\n");
				}
				break;
			default:
				printf("\nVolviendo al menu principal.");
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief: Carga los idsClientes de una publicacion en un array de IdsClientes
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param pArrayIds: Array de idCLientes a ser cargado
 * \param indiceIds: indice del Array de idClientes.
 * \nreturn Retorna 0 (EXITO) y -1 (ERROR)
 */
static int cargarIdsClientes(Publicacion* pArray,int limite,int* pArrayIds,int* indiceIds)
{
	int retorno = -1;
	int i;
	int j;
	int flagExisteId;
	int auxIndex = 0;
	if(pArray != NULL && limite > 0 && pArrayIds != NULL && indiceIds != NULL)
	{
		for(i=0;i<limite;i++)
		{
			flagExisteId = 0;
			if(pArray[i].isEmpty == FALSE)
			{
				for(j=0;j<auxIndex;j++)
				{
					if(pArray[i].idCliente == pArrayIds[j])
					{
						flagExisteId = 1;
						break;
					}
				}
				if(!flagExisteId)
				{
					pArrayIds[auxIndex] = pArray[i].idCliente;
					auxIndex++;
				}
			}
		}
		*indiceIds = auxIndex;
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief: Carga los Rubros de una Publicaicon en un array de Rubros
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param pArrayCliente: Array de Cliente
 * \param limiteCliente: limite del array de Clientes
 * \param sizeArrayRubros: tamaño del array de Rubros
 * \param indiceRubros: indice del array de Rubros
 * \nreturn Retorna 0 (EXITO) y -1 (ERROR)
 */
static int cargarArrayRubros(Publicacion* pArray,int limite,int* pArrayRubros,int sizeArrayRubros,int* indiceRubros)
{
	int retorno = -1;
	int i;
	int j;
	int flagExisteId;
	int auxIndex = 0;
	if(pArray != NULL && limite > 0 && pArrayRubros != NULL && sizeArrayRubros > 0 && indiceRubros != NULL)
	{
		for(i=0;i<limite;i++)
		{
			flagExisteId = 0;
			if(pArray[i].isEmpty == FALSE)
			{
				for(j=0;j<auxIndex;j++)
				{
					if(pArray[i].numeroDeRubro == pArrayRubros[j])
					{
						flagExisteId = 1;
						break;
					}
				}
				if(!flagExisteId)
				{
					pArrayRubros[auxIndex] = pArray[i].numeroDeRubro;
					auxIndex++;
				}
			}
		}
		*indiceRubros = auxIndex;
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief: cuenta cantidad de avisos pausados
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param pArrayCliente: Array de Cliente
 * \param pArrayIds: array de idClientes.
 * \param indicePArray: idClientes a ser cargados
 * \nreturn Retorna cantidad de avisos contados (EXITO) y -1 (ERROR)
 */
static int contadorDeAvisosPausados(Publicacion* pArray,int limite,int* pArrayIds,int indicePArray)
{
	int retorno = -1;
	int i;
	int j;
	int contadorDeAvisosPausados = 0;
	int flagAvisosPausados = 0;
	if(pArray != NULL && limite > 0 && pArrayIds != NULL && indicePArray > 0)
	{
		for(i=0;i<indicePArray;i++)
		{
			for(j=0;j<limite;j++)
			{
				if(pArrayIds[i] == pArray[j].idCliente && pArray[j].estado == PAUSADO)
				{
					contadorDeAvisosPausados++;
					flagAvisosPausados = 1;
				}
			}
		}
		if(flagAvisosPausados)
		{
			retorno = contadorDeAvisosPausados;
		}
	}
	return retorno;
}

/**
 * \brief: Pregunta si hay publicaciones subidas.
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \nreturn Retorna TRUE si el array esta vacio y FALSE si no lo esta
 */
static int isPublicacionAllEmpty(Publicacion* pArray,int limite)
{
	int respuesta = TRUE;
	int i;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				respuesta = FALSE;
				break;
			}
		}
	}
	return respuesta;
}
