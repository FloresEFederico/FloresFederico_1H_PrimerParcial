#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "Cliente.h"


static int generadorIdCliente(void); //utilizado en la funcion cliente_altaArray
static int cliente_bajaDePublicacionesDelCliente(Cliente** pArray,int limite,Publicacion** pArrayPublicacion,int limitePublicacion,int indiceDeCliente); // utilizada en la funcion cliente_bajaArray.
static int esNombre(char* pResultado,int limite);
static int toNombre(char text[],int len);
static int esCuit(char* pResultado,int limite);
/**
 * brief: Imprime los datos de un Cliente
 * \param: auxProducto: Cliente a ser imprimido
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int cliente_imprimir(Cliente* pCliente)
{
	int retorno= -1;
	int auxId;
	char auxApellido[NOMBRE_LEN];
	char auxNombre[NOMBRE_LEN];
	char auxCuit[CUIT_LEN];
	if(pCliente != NULL && !cli_getId(pCliente,&auxId) && !cli_getApellido(pCliente,auxApellido) && !cli_getNombre(pCliente,auxNombre) && !cli_getCuit(pCliente,auxCuit))
	{
		printf("\nID CLIENTE: %d -  APELLIDO Y NOMBRE: %s,%s -  CUIT: %s\n",auxId,auxApellido,auxNombre,auxCuit);
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
int cliente_imprimirArray(Cliente** pArray,int limite)
{
	int retorno = -1;
	int i;
	int flag = 0;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i] != NULL)
			{
				cliente_imprimir(*(pArray+i));
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
 * brief: Busca un indice libre y lo devuelve
 * \param: pArray: Array de Cliente
 * \param limite: limite del array de Cliente
 * \return Retorna i (EXITO) y -1(ERROR)
 */
int cliente_getEmptyIndex(Cliente** pArray,int limite)
{
	int indiceEncontrado = -1;
	int i;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i] == NULL)
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
int cliente_altaArray(Cliente** pArray,int limite)
{
	int retorno = -1;
	int auxId;
	char auxNombre[NOMBRE_LEN];
	char auxApellido[NOMBRE_LEN];
	char auxCuit[CUIT_LEN];
	Cliente* auxCliente;
	int indiceLibre;

	if(pArray != NULL && limite > 0)
	{
		indiceLibre = cliente_getEmptyIndex(pArray,limite);
		if(indiceLibre != -1 &&
		   !utn_getNombre(auxNombre,NOMBRE_LEN,"\nIngrese Nombre del Cliente: ","\nNombre invalido!\n",3) &&
		   !utn_getNombre(auxApellido,NOMBRE_LEN,"Ingrese Apellido del Cliente: ","\nApellido invalida!\n",3) &&
		   !utn_getDni(auxCuit,CUIT_LEN,"Ingrese Cuit del Cliente: ","\nCuit invalida!\n",3)
		   )
		{
			auxId = generadorIdCliente();
			auxCliente = cli_newConParametros(auxId,auxNombre,auxApellido,auxCuit);
			*(pArray+indiceLibre) = auxCliente;
			printf("\nSe ha realizado el alta exitosamente!\n");
			cliente_imprimir(*(pArray+indiceLibre));
			retorno = 0;
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
int cliente_buscarId(Cliente** pArray,int limite,int idABuscar)
{
	int indiceEncontrado = -1;
	int i;
	int auxId;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i] != NULL && !cli_getId(*(pArray+i),&auxId) && auxId == idABuscar)
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
int cliente_modificarArray(Cliente** pArray,int limite)
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
				if(!utn_getNombre(auxNombre,NOMBRE_LEN,"\nIngrese nuevo Nombre: ","\nNombre invalido!\n",3) && !cli_setNombre(*(pArray+indiceAModificar),auxNombre))
				{
					printf("\nSe ha modificado el Nombre!\n");
					retorno = 0;
				}else
				{
					printf("\nHubo Un error al modificar el nombre\n");
				}
				break;
			case 2:
				if(!utn_getNombre(auxApellido,NOMBRE_LEN,"\nIngrese nuevo Apellido: ","\nApellido invalido!\n",3) && !cli_setApellido(*(pArray+indiceAModificar),auxApellido))
				{
					printf("\nSe ha modificado el Apellido!\n");
					retorno = 0;
				}else
				{
					printf("\nSe acabo el numero de reintentos para ingresar un Apellido valido\n");
				}
				break;
			case 3:
				if(!utn_getDni(auxCuit,CUIT_LEN,"\nIngrese nuevo Cuit: ","\nCuit invalido!\n",3) && !cli_setCuit(*(pArray+indiceAModificar),auxCuit))
				{
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
int cliente_bajaArray(Cliente** pArray,int limite,Publicacion** pArrayPublicacion,int limitePublicacion)
{
	int retorno = -1;
	int idBaja;
	int indiceADarDeBaja;
	char confirmarBaja;

	if(pArray != NULL && limite > 0 && !cliente_imprimirArray(pArray,limite))
	{
		utn_getNumero(&idBaja,"Ingrese el ID del Cliente que desea dar de baja(100-999): ","\nID invalido!\n",100,999,3);
		indiceADarDeBaja = cliente_buscarId(pArray,limite,idBaja);
		if(indiceADarDeBaja != - 1 && !utn_getResponse(&confirmarBaja,"\nDesea confirmar la baja?(s-n): ","\nLetra invalida!\n",3))
		{
			if(confirmarBaja == 's' &&
			  !cliente_bajaDePublicacionesDelCliente(pArray,limite,pArrayPublicacion,limitePublicacion,indiceADarDeBaja))
			{
				cli_delete(*(pArray+indiceADarDeBaja));
				*(pArray+indiceADarDeBaja) = NULL;
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
static int cliente_bajaDePublicacionesDelCliente(Cliente** pArray,int limite,Publicacion** pArrayPublicacion,int limitePublicacion,int indiceDeCliente)
{
	int retorno= -1;
	int i;
	int auxIdCliente;
	int auxPublicacionIdCliente;
	if(pArray != NULL && limite > 0 && pArrayPublicacion != NULL && limitePublicacion > 0 && indiceDeCliente >= 0 && !cli_getId(*(pArray+indiceDeCliente),&auxIdCliente))
	{
		for(i=0;i<limitePublicacion;i++)
		{
			if(*(pArrayPublicacion+i) != NULL && !pub_getidCliente(*(pArrayPublicacion+i),&auxPublicacionIdCliente) && auxIdCliente == auxPublicacionIdCliente)
			{
				pub_delete(*(pArrayPublicacion+i));
				*(pArrayPublicacion+i) = NULL;
			}
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

Cliente* cli_newConParametros(int id, char* nombre,char* apellido,char* cuit)
{
	Cliente* pc;
	if(id >= 0 &&  nombre != NULL)
	{
		pc = (Cliente*)malloc(sizeof(Cliente));
		if(pc != NULL)
		{
			cli_setId(pc,id);
			cli_setNombre(pc,nombre);
			cli_setApellido(pc,apellido);
			cli_setCuit(pc,cuit);
		}
	}
	return pc;
}

void cli_delete(Cliente* pc)
{
	if(pc!= NULL)
	{
		free(pc);
	}
}

int cli_initArray(Cliente** pArray,int limite)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			*(pArray+i) = NULL;
		}
		retorno = 0;
	}
	return retorno;
}

//-------------------------GETTERS--------------------------------------
int cli_getId(Cliente* pArray, int* pValor)
{
	int ret = -1;
	if(pArray != NULL && pValor != NULL)
	{
		*pValor = pArray->id;
		ret = 0;
	}
	return ret;
}

int cli_getNombre(Cliente* pArray, char* name)
{
	int ret = -1;
	if(pArray != NULL && name != NULL)
	{
		strncpy(name,pArray->nombre,NOMBRE_LEN);
		ret = 0;
	}
	return ret;
}

int cli_getApellido(Cliente* pArray, char* lastName)
{
	int ret = -1;
	if(pArray != NULL && lastName != NULL)
	{
		strncpy(lastName,pArray->apellido,NOMBRE_LEN);
		ret = 0;
	}
	return ret;
}

int cli_getCuit(Cliente* pArray, char* cuit)
{
	int ret = -1;
	if(pArray != NULL && cuit != NULL)
	{
		strncpy(cuit,pArray->cuit,CUIT_LEN);
		ret = 0;
	}
	return ret;
}
//-------------------------SETTERS--------------------------------------
int cli_setId(Cliente* pArray,int pValor)
{
	int ret = -1;
	if(pArray != NULL && pValor >= 100 && pValor <= 999)
	{
		pArray->id = pValor;
		ret = 0;
	}
	return ret;
}

int cli_setNombre(Cliente* pArray, char* name)
{
	int ret = -1;
	if(pArray != NULL && name != NULL)
	{
		if(esNombre(name,NOMBRE_LEN) && toNombre(name,NOMBRE_LEN))
		{
			strncpy(pArray->nombre,name,NOMBRE_LEN);
			ret = 0;
		}
	}
	return ret;
}

int cli_setApellido(Cliente* pArray, char* lastName)
{
	int ret = -1;
	if(pArray != NULL && lastName != NULL)
	{
		if(esNombre(lastName,NOMBRE_LEN) && toNombre(lastName,NOMBRE_LEN))
		{
			strncpy(pArray->apellido,lastName,NOMBRE_LEN);
			ret = 0;
		}
	}
	return ret;
}

int cli_setCuit(Cliente* pArray, char* cuit)
{
	int ret = -1;
	if(pArray != NULL && cuit != NULL)
	{
		if(esCuit(cuit,CUIT_LEN))
		{
			strncpy(pArray->cuit,cuit,CUIT_LEN);
			ret = 0;
		}
	}
	return ret;
}


static int esNombre(char* pResultado,int limite)
{
	int respuesta = 1;
	int i;
	if(pResultado != NULL && limite > 0){
		for(i=0; i <= limite && pResultado[i] != '\0';i++){
			if((pResultado[i] < 'a' || pResultado[i] > 'z') &&
			   (pResultado[i] < 'A' || pResultado[i] > 'Z'))
			{
				respuesta = 0;
				break;
			}
		}
	}
	return respuesta;
}

static int toNombre(char text[],int len)
{
	int retorno = 0;
	int i;
	if(text != NULL && len > 0)
	{
		for(i=0;i<len && text[i] != '\0';i++)
		{
			if(i!=0)
			{
				text[i] = tolower(text[i]);
			}else
			{
				text[i] = toupper(text[i]);
			}
		}
		retorno = 1;
	}
	return retorno;
}

static int esCuit(char* pResultado,int limite)
{
	int respuesta = 1;
	int i;
	int contadorDeGuion = 0;
	int longitudDeDni = strlen(pResultado);
	if(pResultado != NULL && limite > 0){
		for(i=0; i <= limite && pResultado[i] != '\0';i++){
			if((pResultado[i] < '0' || pResultado[i] > '9') || (longitudDeDni < 8))
			{
				if(pResultado[i] == '-' && contadorDeGuion < 3)
				{
					contadorDeGuion++;
				}else
				{
					respuesta = 0;
					break;
				}
			}
		}
	}
	return respuesta;
}
