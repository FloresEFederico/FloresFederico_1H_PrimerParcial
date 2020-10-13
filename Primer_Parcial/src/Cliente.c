#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Cliente.h"


static int generadorIdCliente(void); //utilizado en la funcion cliente_altaArray
static int cliente_bajaDePublicacionesDelCliente(Cliente* pArray,int limite,Publicacion* pArrayPublicacion,int limitePublicacion,int indiceDeCliente); // utilizada en la funcion cliente_bajaArray.
/**
 * brief: Imprime los datos de un Cliente
 * \param: auxProducto: Cliente a ser imprimido
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int cliente_imprimir(Cliente* auxCliente)
{
	int retorno= -1;
	if(auxCliente != NULL)
	{
		printf("\nID CLIENTE: %d -  APELLIDO Y NOMBRE: %s,%s -  CUIT: %s\n",auxCliente->id,auxCliente->apellido,auxCliente->nombre,auxCliente->cuit);
		retorno = 0;
	}
	return retorno;
}
/**
 * brief: Imprime el array de Clientes
 * \param: pArray: Array de Clientes a ser imprimido
 * \param limite: limite del array de clientes
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int cliente_imprimirArray(Cliente* pArray,int limite)
{
	int retorno = -1;
	int i;
	int flag = 0;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				cliente_imprimir(&pArray[i]);
				flag = 1;
			}
		}
		if(flag)
		{
			retorno = 0;
		}else
		{
			printf("\nNo se ha cargado ningun Cliente!\n");
		}
	}
	return retorno;
}

/**
 * brief: Inicializa el array de CLientes
 * \param: pArray: Array de Clientes
 * \param limite: limite del array de Clientes
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int cliente_inicializarArray(Cliente* pArray,int limite)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			pArray[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * brief: Busca un indice libre y lo devuelve
 * \param: pArray: Array de Cliente
 * \param limite: limite del array de Cliente
 * \return Retorna i (EXITO) y -1(ERROR)
 */
int cliente_getEmptyIndex(Cliente* pArray,int limite)
{
	int indiceEncontrado = -1;
	int i;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i].isEmpty == TRUE)
			{
				indiceEncontrado = i;
				break;
			}
		}
	}
	return indiceEncontrado;
}

/**
 * brief: Da de alta un Cliente en una posicion del array. Y si el alta fue exitosa, imprimira por pantalla al Cliente
 * \param: pArray: Array de Cliente
 * \param limite: limite del array de Cliente
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int cliente_altaArray(Cliente* pArray,int limite)
{
	int retorno = -1;
	Cliente auxCliente;
	int indiceLibre;
	if(pArray != NULL && limite > 0)
	{
		indiceLibre = cliente_getEmptyIndex(pArray,limite);
		if(indiceLibre != -1 &&
		   !utn_getNombre(auxCliente.nombre,NOMBRE_LEN,"\nIngrese Nombre del Cliente: ","\nNombre invalido!\n",3) &&
		   !utn_getNombre(auxCliente.apellido,NOMBRE_LEN,"Ingrese Apellido del Cliente: ","\nApellido invalida!\n",3) &&
		   !utn_getDni(auxCliente.cuit,CUIT_LEN,"Ingrese Cuit del Cliente: ","\nCuit invalida!\n",3)
		   )
		{
			auxCliente.id = generadorIdCliente();
			auxCliente.isEmpty = FALSE;
			pArray[indiceLibre] = auxCliente;
			printf("\nSe ha realizado el alta exitosamente!\n");
			cliente_imprimir(&pArray[indiceLibre]);
			retorno = 0;
		}
		if(indiceLibre == -1)
		{
			printf("\nYa no hay espacio para seguir cargando Clientes.\n");
		}
	}
	return retorno;
}


/**
 * brief: busca un Id existente en el array de Clientes y devuelve su indice si se encontro
 * \param: pArray: Array de Cliente
 * \param limite: limite del array de Cliente
 * \param: idABuscar: id a ser buscado
 * \return Retorna i (ID ENCONTRADO) y -1(ID NO ENCONTRADO)
 */
int cliente_buscarId(Cliente* pArray,int limite,int idABuscar)
{
	int indiceEncontrado = -1;
	int i;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].id == idABuscar)
			{
				indiceEncontrado = i;
				break;
			}
		}
	}
	return indiceEncontrado;
}

/**
 * brief: Actualiza los datos de un Cliente en una posicion del array
 * \param: pArray: Array de Clientes a ser actualizado
 * \param limite: limite del array de Cliente
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int cliente_modificarArray(Cliente* pArray,int limite)
{
	int retorno = -1;
	int idModificacion;
	int indiceAModificar;
	char auxNombre[NOMBRE_LEN];
	char auxApellido[NOMBRE_LEN];
	char auxCuit[CUIT_LEN];
	int opcionModificar;
	if(pArray != NULL && limite > 0 && !cliente_imprimirArray(pArray,limite))
	{
		utn_getNumero(&idModificacion,"Ingrese el ID del Cliente que desea modificar(100-999): ","\nID invalido!\n",100,999,3);
		indiceAModificar = cliente_buscarId(pArray,limite,idModificacion);
		if(indiceAModificar != - 1 &&
		   !utn_getNumero(&opcionModificar,"\n¿Que desea modificar?\n"
										   "1-Nombre.\n"
										   "2-Apellido.\n"
										   "3-Cuit.\n"
										   "4-Salir.\nElija una opcion(1-4): ","\nOpcion invalida!\n",1,4,3)
			)
		{
			switch(opcionModificar)
			{
			case 1:
				if(!utn_getNombre(auxNombre,NOMBRE_LEN,"\nIngrese nuevo Nombre: ","\nNombre invalido!\n",3))
				{
					strncpy(pArray[indiceAModificar].nombre,auxNombre,NOMBRE_LEN);
					printf("\nSe ha modificado el Nombre!\n");
					retorno = 0;
				}else
				{
					printf("\nSe acabo el numero de reintentos para ingresar un Nombre valido\n");
				}
				break;
			case 2:
				if(!utn_getNombre(auxApellido,NOMBRE_LEN,"\nIngrese nuevo Apellido: ","\nApellido invalido!\n",3))
				{
					strncpy(pArray[indiceAModificar].apellido,auxApellido,NOMBRE_LEN);
					printf("\nSe ha modificado el Apellido!\n");
					retorno = 0;
				}else
				{
					printf("\nSe acabo el numero de reintentos para ingresar un Apellido valido\n");
				}
				break;
			case 3:
				if(!utn_getDni(auxCuit,CUIT_LEN,"\nIngrese nuevo Cuit: ","\nCuit invalido!\n",3))
				{
					strncpy(pArray[indiceAModificar].cuit,auxCuit,CUIT_LEN);
					printf("\nSe ha modificado el Cuit!\n");
					retorno = 0;
				}else
				{
					printf("\nSe acabo el numero de reintentos para ingresar un Cuit valido\n");
				}
				break;
			case 4:
				retorno = 0;
				printf("\nModificacion Cancelada\n");
				break;
			}
		}
		if(indiceAModificar == -1)
		{
			printf("\nNo se encontro a un Cliente con el ID ingresado.\n");
		}
	}
	return retorno;
}

/**
 * brief: Da de baja un Cliente del Array mas todas sus publicaciones.
 * \param: pArray: Array de Clientes
 * \param limite: limite del array de Cliente
 * \param pArrayPublicaciones: Array de Publicaciones
 * \param limitePublicacion: limite del array de Publicacion
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int cliente_bajaArray(Cliente* pArray,int limite,Publicacion* pArrayPublicacion,int limitePublicacion)
{
	int retorno = -1;
	int idBaja;
	int indiceADarDeBaja;
	char confirmarBaja;

	if(pArray != NULL && limite > 0 && cliente_imprimirArray(pArray,limite) == 0)
		{
			utn_getNumero(&idBaja,"Ingrese el ID del Cliente que desea dar de baja(100-999): ","\nID invalido!\n",100,999,3);
			indiceADarDeBaja = cliente_buscarId(pArray,limite,idBaja);
			if(indiceADarDeBaja != - 1 && !utn_getResponse(&confirmarBaja,"\nDesea confirmar la baja?(s-n): ","\nLetra invalida!\n",3))
			{
				if(confirmarBaja == 's')
				{
					pArray[indiceADarDeBaja].isEmpty = TRUE;
					cliente_bajaDePublicacionesDelCliente(pArray,limite,pArrayPublicacion,limitePublicacion,indiceADarDeBaja);
					printf("\nSe ha dado de baja al Cliente con todas sus publicaciones exitosamente\n");
				}else
				{
					printf("\nSe ha cancelado la baja!\n");
				}
				fflush(stdin);
				retorno = 0;
			}
			if(indiceADarDeBaja == -1)
			{
				printf("\nNo se encontro a una Cliente con ese ID.\n");
			}
		}
	return retorno;
}

/**
 * brief: Da de baja Las Publicaciones en un Cliente determinado.
 * \param: pArray: Array de Clientes
 * \param limite: limite del array de Cliente
 * \param pArrayPublicaciones: Array de Publicaciones
 * \param limitePublicacion: limite del array de Publicacion
 * \param indiceDeCliente: indice del cliente al cual se le dara de baja las publicaciones.
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
static int cliente_bajaDePublicacionesDelCliente(Cliente* pArray,int limite,Publicacion* pArrayPublicacion,int limitePublicacion,int indiceDeCliente)
{
	int retorno= -1;
	int i;
	for(i=0;i<limitePublicacion;i++)
	{
		if(pArray[indiceDeCliente].id == pArrayPublicacion[i].idCliente)
		{
			pArrayPublicacion[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief: genera un valor de ID para array de Clientes.Id
 * \return id
 */
static int generadorIdCliente(void)
{
	static int id = 99;
	id++;
	return id;
}
