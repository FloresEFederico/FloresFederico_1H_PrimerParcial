#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "informes.h"

#define CANTIDAD_IDCLIENTES 1000
#define CANTIDAD_RUBROS 1000

static int cargarIdsClientes(Publicacion* pArray,int limite,int* pArrayIds,int* indiceIds); // utilizada en informar_ClienteConMasAvisos
static int cargarArrayRubros(Publicacion* pArray,int limite,int* pArrayRubros,int sizeArrayRubros,int* indiceRubros); // utilizada en informar_RubroConMasAvisos
static int contadorDeAvisosPausados(Publicacion* pArray,int limite,int* pArrayIds,int indicePArray); //utilizada en informar_CantDeAvisosPausados
static int calcularRubroConMasAvisos(Publicacion* pArray,int limite,int* pArrayRubros,int indiceRubros,int* cantMaxAvisos);
static int calcularClienteConMasAvisos(Publicacion* pArray,int limite,int* pArrayIdClientes,int indiceIdClientes,int* cantMaxAvisos);

//--SEGUNDA PARTE DEL PARCIAL--
static int calcularClienteConMasAvisosPorEstado(Publicacion* pArray,int limite,int* pArrayIdClientes,int indiceIdClientes,int estado,int* cantMaxAvisos);

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
	int listaDeIdClientes[CANTIDAD_IDCLIENTES];
	int indiceDeIdClientes = 0;
	int cantidadMaximaDeAvisos;
	int idClienteConMasAvisos;
	int buscarIndice;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0 &&
	   !cargarIdsClientes(pArray,limite,listaDeIdClientes,&indiceDeIdClientes))
	{

		for(i=0;i<indiceDeIdClientes;i++)
		{
			printf("\nID CLIENTE N°: %d ",listaDeIdClientes[i]);
			printf("\n-----------------------------------------------------------------------------------");
			publicacion_mostrarPoridCliente(pArray,limite,pArrayCliente,limiteCliente,listaDeIdClientes[i]);
			printf("\n-----------------------------------------------------------------------------------\n\n");
		}

		idClienteConMasAvisos = calcularClienteConMasAvisos(pArray,limite,listaDeIdClientes,indiceDeIdClientes,&cantidadMaximaDeAvisos);
		buscarIndice = cliente_buscarId(pArrayCliente,limiteCliente,idClienteConMasAvisos);
		if(idClienteConMasAvisos != -1 && buscarIndice != -1)
		{
			printf("\nEl Cliente con mas avisos es:\n"
					"ID: %d\n"
					"Apellido,Nombre: %s,%s\n"
					"Cuit: %s\n"
					"Cantidad de avisos: %d\n",pArrayCliente[buscarIndice].id,pArrayCliente[buscarIndice].apellido,pArrayCliente[buscarIndice].nombre,pArrayCliente[buscarIndice].cuit,cantidadMaximaDeAvisos);
		}else
		{
			printf("\nNo se ha registrado ninguna Publicacion.\n");
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
		printf("\nPUBLICACIONES PAUSADAS: \n");
		publicacion_mostrarPorEstado(pArray,limite,pArrayCliente,limiteCliente,PAUSADO);
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
	int cantidadMaximaDeAvisos;
	int rubroConMasAvisos;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0 &&
	   !cargarArrayRubros(pArray,limite,listaDeRubros,CANTIDAD_RUBROS,&indiceDeRubros))
	{
		for(i=0;i<indiceDeRubros;i++)
		{
			printf("\nRUBRO N°: %d ",listaDeRubros[i]);
			printf("\n-----------------------------------------------------------------------------------");
			publicacion_mostrarPorRubro(pArray,limite,pArrayCliente,limiteCliente,listaDeRubros[i]);
			printf("\n-----------------------------------------------------------------------------------\n\n");
		}
		rubroConMasAvisos = calcularRubroConMasAvisos(pArray,limite,listaDeRubros,indiceDeRubros,&cantidadMaximaDeAvisos);
		if(rubroConMasAvisos != -1)
		{
			printf("\nEl rubro con mas avisos es el N° de Rubro: %d\n"
					"\nCantidad de avisos: %d\n",rubroConMasAvisos,cantidadMaximaDeAvisos);
		}else
		{
			printf("\nNo se ha registrado ninguna Publicacion.\n");
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
										 "4-Cliente con mas avisos activos\n"
										 "5-Cliente con mas avisos pausados\n"
										 "6-salir.\nElija opcion(1-4): ","\nOpcion invalida!\n",1,6,3))

		{
			switch(opcionSubMenu)
			{
			case 1:
				if(!informar_ClienteConMasAvisos(pArray,limite,pArrayCliente,limiteCliente))
				{
					printf("\nVolviendo al menu principal.");
				}else
				{
					printf("\nHubo un error en el Informe.\n");
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
					printf("\nHubo un error en el Informe.\n");
				}
				break;
			case 4:
				if(!informar_ClienteConMasAvisosActivos(pArray,limite,pArrayCliente,limiteCliente))
				{
					printf("\nVolviendo al menu principal.");
				}else
				{
					printf("\nHubo un error en el Informe.\n");
				}
				break;
			case 5:
				if(!informar_ClienteConMasAvisosPausados(pArray,limite,pArrayCliente,limiteCliente))
				{
					printf("\nVolviendo al menu principal.");
				}else
				{
					printf("\nHubo un error en el Informe.\n");
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
 * \brief: calcula el Cliente con mas avisos segun su id y retorna por referencia la cantidad mayor de avisos y por valor el Id del Cliente.
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param: pArrayIdClientes: Array de IdClientes.
 * \param: indiceIdClientes: limite del array de IdClientes.
 * \param: *cantMaxAvisos: puntero donde se guarda la cantidad maxima de avisos
 * \nreturn Retorna auxIdCliente si salio bien o -1 (ERROR).
 */
static int calcularClienteConMasAvisos(Publicacion* pArray,int limite,int* pArrayIdClientes,int indiceIdClientes,int* cantMaxAvisos)
{
	int retorno = -1;
	int i;
	int j;
	int contadorDeAvisos;
	int auxMaxAvisos;
	int flagMaximo = 0;
	int auxIdCliente;
	if(pArray != NULL && limite > 0 && pArrayIdClientes != NULL && indiceIdClientes > 0)
	{
		for(i=0;i<indiceIdClientes;i++)
		{
			contadorDeAvisos = 0;
			for(j=0;j<limite;j++)
			{
				if(pArrayIdClientes[i] == pArray[j].idCliente)
				{
					contadorDeAvisos++;
				}
			}
			if(i == 0 || auxMaxAvisos < contadorDeAvisos)
			{
				auxMaxAvisos = contadorDeAvisos;
				auxIdCliente = pArrayIdClientes[i];
				flagMaximo = 1;
			}
		}
		if(flagMaximo)
		{
			*cantMaxAvisos = auxMaxAvisos;
			retorno = auxIdCliente;
		}
	}
	return retorno;
}

/**
 * \brief: calcula el N°de Rubro con mas avisos segun su id y retorna por referencia la cantidad mayor de avisos y por valor el N° de Rubro con mas avisos.
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param: pArrayRubros: Array de Rubros.
 * \param: indiceRubros: tamaño del array de Rubros
 * \param: *cantMaxAvisos: puntero donde se guarda la cantidad maxima de avisos
 * \nreturn Retorna Retorna auxRubro si salio bien o -1 (ERROR).
 */
static int calcularRubroConMasAvisos(Publicacion* pArray,int limite,int* pArrayRubros,int indiceRubros,int* cantMaxAvisos)
{
	int retorno = -1;
	int i;
	int j;
	int contadorDeAvisos = 0;
	int auxMaxAvisos;
	int flagMaximo = 0;
	int auxRubro;
	if(pArray != NULL && limite > 0 && pArrayRubros != NULL && indiceRubros > 0)
	{
		for(i=0;i<indiceRubros;i++)
		{
			contadorDeAvisos = 0;
			for(j=0;j<limite;j++)
			{
				if(pArrayRubros[i] == pArray[j].numeroDeRubro)
				{
					contadorDeAvisos++;
				}
			}
			if(i == 0 || auxMaxAvisos < contadorDeAvisos)
			{
				auxMaxAvisos = contadorDeAvisos;
				auxRubro = pArrayRubros[i];
				flagMaximo = 1;
			}
		}
		if(flagMaximo)
		{
			*cantMaxAvisos = auxMaxAvisos;
			retorno = auxRubro;
		}
	}
	return retorno;
}


//----SEGUNDA PARTE DEL PARCIAL----

/**
 * \brief: Informa clientes con mayor cantidad de avisos Activos
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param pArrayCliente: Array de Cliente
 * \param limiteCliente: limite del array de Clientes
 * \nreturn Retorna 0 (EXITO) y -1 (ERROR)
 */
int informar_ClienteConMasAvisosActivos(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente)
{
	int retorno = -1;
	int listaDeIdClientes[CANTIDAD_IDCLIENTES];
	int indiceDeIdClientes = 0;
	int cantidadMaximaDeAvisosActivos;
	int idClienteConMasAvisosActivos;
	int buscarIndice;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0 &&
	   !cargarIdsClientes(pArray,limite,listaDeIdClientes,&indiceDeIdClientes))
	{

		printf("\nPUBLICACIONES ACTIVAS: \n");
		publicacion_mostrarPorEstado(pArray,limite,pArrayCliente,limiteCliente,ACTIVO);
		idClienteConMasAvisosActivos = calcularClienteConMasAvisosPorEstado(pArray,limite,listaDeIdClientes,indiceDeIdClientes,ACTIVO,&cantidadMaximaDeAvisosActivos);
		buscarIndice = cliente_buscarId(pArrayCliente,limiteCliente,idClienteConMasAvisosActivos);
		if(idClienteConMasAvisosActivos != -1 && buscarIndice != -1)
		{
			printf("\nEl Cliente con mas avisos Activos es:\n"
					"ID: %d\n"
					"Apellido,Nombre: %s,%s\n"
					"Cuit: %s\n"
					"Cantidad de avisos Activos: %d\n",pArrayCliente[buscarIndice].id,pArrayCliente[buscarIndice].apellido,pArrayCliente[buscarIndice].nombre,pArrayCliente[buscarIndice].cuit,cantidadMaximaDeAvisosActivos);
		}else
		{
			printf("\nNo se ha registrado ninguna Publicacion.\n");
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief: Informa clientes con mayor cantidad de avisos Pausados
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param pArrayCliente: Array de Cliente
 * \param limiteCliente: limite del array de Clientes
 * \nreturn Retorna 0 (EXITO) y -1 (ERROR)
 */
int informar_ClienteConMasAvisosPausados(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente)
{
	int retorno = -1;
	int listaDeIdClientes[CANTIDAD_IDCLIENTES];
	int indiceDeIdClientes = 0;
	int cantidadMaximaDeAvisosPausados;
	int idClienteConMasAvisosPausados;
	int buscarIndice;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0 &&
	   !cargarIdsClientes(pArray,limite,listaDeIdClientes,&indiceDeIdClientes))
	{

		printf("\nPUBLICACIONES PAUSADAS: \n");
		publicacion_mostrarPorEstado(pArray,limite,pArrayCliente,limiteCliente,PAUSADO);
		idClienteConMasAvisosPausados = calcularClienteConMasAvisosPorEstado(pArray,limite,listaDeIdClientes,indiceDeIdClientes,PAUSADO,&cantidadMaximaDeAvisosPausados);
		buscarIndice = cliente_buscarId(pArrayCliente,limiteCliente,idClienteConMasAvisosPausados);
		if(idClienteConMasAvisosPausados != -1 && buscarIndice != -1)
		{
			printf("\nEl Cliente con mas avisos Pausados es:\n"
					"ID: %d\n"
					"Apellido,Nombre: %s,%s\n"
					"Cuit: %s\n"
					"Cantidad de avisos Pausados: %d\n",pArrayCliente[buscarIndice].id,pArrayCliente[buscarIndice].apellido,pArrayCliente[buscarIndice].nombre,pArrayCliente[buscarIndice].cuit,cantidadMaximaDeAvisosPausados);
		}else
		{
			printf("\nNo se ha registrado ninguna Publicacion.\n");
		}
		retorno = 0;
	}
	return retorno;
}


/**
 * \brief: calcula el Cliente con mas avisos segun su estado y retorna por referencia la cantidad mayor de avisos y por valor el Id del Cliente.
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param: pArrayIdClientes: Array de IdClientes.
 * \param: indiceIdClientes: limite del array de IdClientes.
 * \param estado: estado de publicacion: ACTIVO(1) / PAUSADO(0)
 * \param: *cantMaxAvisos: puntero donde se guarda la cantidad maxima de avisos
 * \nreturn Retorna auxIdCliente si salio bien o -1 (ERROR).
 */
static int calcularClienteConMasAvisosPorEstado(Publicacion* pArray,int limite,int* pArrayIdClientes,int indiceIdClientes,int estado,int* cantMaxAvisos)
{
	int retorno = -1;
	int i;
	int j;
	int contadorDeAvisos;
	int auxMaxAvisos;
	int flagMaximo = 0;
	int auxIdCliente;
	if(pArray != NULL && limite > 0 && pArrayIdClientes != NULL && indiceIdClientes > 0)
	{
		for(i=0;i<indiceIdClientes;i++)
		{
			contadorDeAvisos = 0;
			for(j=0;j<limite;j++)
			{
				if(pArray[j].estado == estado && pArrayIdClientes[i] == pArray[j].idCliente)
				{
					contadorDeAvisos++;
				}
			}
			if(i == 0 || auxMaxAvisos < contadorDeAvisos)
			{
				auxMaxAvisos = contadorDeAvisos;
				auxIdCliente = pArrayIdClientes[i];
				flagMaximo = 1;
			}
		}
		if(flagMaximo)
		{
			*cantMaxAvisos = auxMaxAvisos;
			retorno = auxIdCliente;
		}
	}
	return retorno;
}


