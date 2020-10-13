#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Publicacion.h"


static int generadorIdPublicacion(void); //utilizado en la funcion publicacion_altaArray

/**
 * brief: Imprime los datos de la variable Publicacion
 * \param: auxProducto: variable de Publicaciona ser imprimida
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int publicacion_imprimir(Publicacion* auxPublicacion)
{
	int retorno= -1;
	char estadoDePublicacion[10];
	if(auxPublicacion != NULL)
	{
		if(auxPublicacion->estado == ACTIVO)
		{
			snprintf(estadoDePublicacion,sizeof(estadoDePublicacion),"ACTIVO");
		}else
		{
			snprintf(estadoDePublicacion,sizeof(estadoDePublicacion),"PAUSADA");
		}
		printf("\nID: %d\nN° DE RUBRO: %d  - IDCLIENTE: %d  - ESTADO: %s\nNOMBRE DE ARCHIVO: %s\n",auxPublicacion->id,auxPublicacion->numeroDeRubro,auxPublicacion->idCliente,estadoDePublicacion,auxPublicacion->textoDelArchivo);
		retorno = 0;
	}
	return retorno;
}
/**
 * brief: Imprime el array de Publicaciones
 * \param: pArray: Array de Publicaciones a ser actualizado
 * \param limite: limite del array de Publicaciones
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int publicacion_imprimirArray(Publicacion* pArray,int limite)
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
				publicacion_imprimir(&pArray[i]);
				flag = 1;
			}
		}
		if(flag)
		{
			retorno = 0;
		}else
		{
			printf("\nNo se ha cargado ninguna Publicacion!\n");
		}
	}
	return retorno;
}

/**
 * brief: Imprime el array de Publicaciones Activas
 * \param: pArray: Array de Publicaciones a ser actualizado
 * \param limite: limite del array de Publicaciones
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int publicacion_imprimirPublicacionesActivas(Publicacion* pArray,int limite)
{
	int retorno = -1;
	int i;
	int flag = 0;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].estado == ACTIVO)
			{
				publicacion_imprimir(&pArray[i]);
				flag = 1;
			}
		}
		if(flag)
		{
			retorno = 0;
		}else
		{
			printf("\nNo hay ninguna publicacion activa!\n");
		}
	}
	return retorno;
}

/**
 * brief: Imprime el array de Publicaciones Pausadas
 * \param: pArray: Array de Publicaciones a ser actualizado
 * \param limite: limite del array de Publicaciones
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int publicacion_imprimirPublicacionesPausadas(Publicacion* pArray,int limite)
{
	int retorno = -1;
	int i;
	int flag = 0;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].estado == PAUSADO)
			{
				publicacion_imprimir(&pArray[i]);
				flag = 1;
			}
		}
		if(flag)
		{
			retorno = 0;
		}else
		{
			printf("\nNo hay ninguna publicacion pausada!\n");
		}
	}
	return retorno;
}

/**
 * brief: Inicializa el array
 * \param: pArray: Array de Publicaciones a ser actualizado
 * \param limite: limite del array de Publicaciones
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int publicacion_inicializarArray(Publicacion* pArray,int limite)
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
 * \param: pArray: Array de Publicaciones a ser actualizado
 * \param limite: limite del array de Publicaciones
 * \return Retorna i (EXITO) y -1(ERROR)
 */
int publicacion_getEmptyIndex(Publicacion* pArray,int limite)
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
 * brief: Da de alta una Publicacion en una posicion del array
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param pArrayCliente: Array de Cliente
 * \param limiteCliente: limite del array de CLientes.
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int publicacion_altaArray(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente)
{
	int retorno = -1;
	Publicacion auxPublicacion;
	int indiceLibre;
	int auxIdCliente;
	int existeIdCliente;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		indiceLibre = publicacion_getEmptyIndex(pArray,limite);
		if(indiceLibre != -1 &&
		   !cliente_imprimirArray(pArrayCliente,limiteCliente) &&
		   !utn_getNumero(&auxIdCliente,"Elija ID de Cliente donde desea publicar: ","\nId invalido!\n",MIN_IDCLIENTE,MAX_IDCLIENTE,3))
		{
			existeIdCliente = cliente_buscarId(pArrayCliente,limiteCliente,auxIdCliente);
			if(existeIdCliente != -1 &&
			   !utn_getNumero(&auxPublicacion.numeroDeRubro,"\nIngrese N° de Rubro(1-100): ","\nNumero invalida!\n",MIN_NUMRUBRO,MAX_NUMRUBRO,3) &&
			   !utn_getDireccion(auxPublicacion.textoDelArchivo,TXTARCHIVO_LEN,"\nIngrese Texto del Archivo: ","\nTexto invalido!\n",3))
			{
				auxPublicacion.idCliente = auxIdCliente;
				auxPublicacion.id = generadorIdPublicacion();
				auxPublicacion.estado = ACTIVO;
				auxPublicacion.isEmpty = FALSE;
				pArray[indiceLibre] = auxPublicacion;
				publicacion_imprimir(&pArray[indiceLibre]);
				printf("\nSe ha publico un nuevo aviso exitosamente!\n");
				retorno = 0;
			}
		}
		if(indiceLibre == -1)
		{
			printf("\nNo hay espacios libres para hacer una Publicacion.\n");
		}
		if(existeIdCliente == -1)
		{
			printf("\nNo se encontro ningun Cliente con ese Id.\n");
		}
	}
	return retorno;
}



/**
 * brief: busca un Id existente en el array de Publicaciones y devuelve su indice si se encontro
 * \param: pArray: Array de Publicaciones a ser actualizado
 * \param limite: limite del array de Publicaciones
 * \param: idABuscar: id a ser buscado
 * \return Retorna i (ID ENCONTRADO) y -1(ID NO ENCONTRADO)
 */
int publicacion_buscarId(Publicacion* pArray,int limite,int idABuscar)
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
 * brief: Pausa una Publicacion elegida por el usuario.
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param pArrayCliente: Array de Cliente
 * \param limiteCliente: limite del array de Clientes
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int publicacion_pausarPublicacion(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente)
{
	int retorno = -1;
	int auxIdPublicacion;
	int indicePublicacion;
	char confirmarPausa;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0 && !publicacion_imprimirPublicacionesActivas(pArray,limite))
	{
		utn_getNumero(&auxIdPublicacion,"\nIngrese el Id de la publicacion que desea pausar: ","\nId Invalido!\n",1000,1100,3);
		indicePublicacion = publicacion_buscarIdyEstado(pArray,limite,auxIdPublicacion,ACTIVO);
		if(indicePublicacion != -1 &&
		  !publicacion_mostrarClientesConPublicacion(pArray,limite,pArrayCliente,limiteCliente,auxIdPublicacion) &&
		  !utn_getResponse(&confirmarPausa,"\nEsta seguro que desea pausar la publicacion?(s-n): ","\nLetra invalida!\n",3))
		{
			 if(confirmarPausa == 's')
			 {
				pArray[indicePublicacion].estado = PAUSADO;
				printf("\nSe ha pausado la publicacion!\n");
			 }else
			 {
					printf("\nSe ha cancelado la accion!\n");
			 }
			 fflush(stdin);
			 retorno = 0;
		}
		if(indicePublicacion == -1)
		{
			printf("\nNo se encontro ninguna publicacion con ese ID.\n");
		}
	}
	return retorno;
}

/**
 * brief: Reanuda una Publicacion del Array elegida por el usuario.
 * \param: pArray: Array de Publicaciones a ser dado de baja
 * \param limite: limite del array de Publicaciones
 * \param pArrayCliente: Array de Cliente
 * \param limiteCliente: limite del array de Clientes
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int publicacion_reanudarPublicacion(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente)
{
	int retorno = -1;
	int auxIdPublicacion;
	int indicePublicacion;
	char confirmarReanudacion;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0 && !publicacion_imprimirPublicacionesPausadas(pArray,limite))
	{
		utn_getNumero(&auxIdPublicacion,"\nIngrese el Id de la publicacion que desea reanudar: ","\nId Invalido!\n",1000,1100,3);
		indicePublicacion = publicacion_buscarIdyEstado(pArray,limite,auxIdPublicacion,PAUSADO);
		if(indicePublicacion != -1 &&
		  !publicacion_mostrarClientesConPublicacion(pArray,limite,pArrayCliente,limiteCliente,auxIdPublicacion) &&
		  !utn_getResponse(&confirmarReanudacion,"\nEsta seguro que desea reanudar la publicacion?(s-n): ","\nLetra invalida!\n",3))
		{
			 if(confirmarReanudacion == 's')
			 {
				pArray[indicePublicacion].estado = ACTIVO;
				printf("\nSe ha reanudaado la publicacion!\n");
			 }else
			 {
					printf("\nSe ha cancelado la accion!\n");
			 }
			 fflush(stdin);
			 retorno = 0;
		}
		if(indicePublicacion == -1)
		{
			printf("\nNo se encontro ninguna publicacion con ese ID.\n");
		}
	}
	return retorno;
}


/**
 * \brief: lista los Clientes con Publicaciones a partir del idPublicacion, mostrando sus campos
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param pArrayCliente: Array de Cliente
 * \param limiteCliente: limite del array de Clientes
 * \param idPublicacion: idPublicacion.
 * \nreturn Retorna 0 (EXITO) y -1 (ERROR)
 */
int publicacion_mostrarClientesConPublicacion(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente,int idPublicacion)
{
	int retorno = -1;
	int i;
	int buscarIndiceCliente;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].id == idPublicacion)
			{
				buscarIndiceCliente = cliente_buscarId(pArrayCliente,limiteCliente,pArray[i].idCliente);
				if(buscarIndiceCliente != -1)
				{
					publicacion_imprimir(&pArray[i]);
					cliente_imprimir(&pArrayCliente[buscarIndiceCliente]);
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}

/**
 * \brief: lista los Clientes con Publicaciones a partir del idCliente, mostrando sus campos
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param pArrayCliente: Array de Cliente
 * \param limiteCliente: limite del array de Clientes
 * \param idClientes: idCliente.
 * \nreturn Retorna 0 (EXITO) y -1 (ERROR)
 */
int publicacion_mostrarPoridCliente(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente,int idClientes)
{
	int retorno = -1;
	int i;
	int buscarIndiceCliente;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].idCliente == idClientes)
			{
				buscarIndiceCliente = cliente_buscarId(pArrayCliente,limiteCliente,pArray[i].idCliente);
				if(buscarIndiceCliente != -1)
				{
					publicacion_imprimir(&pArray[i]);
					printf("APELLIDO,NOMBRE: %s,%s   - CUIT: %s\n",pArrayCliente[buscarIndiceCliente].apellido,pArrayCliente[buscarIndiceCliente].nombre,pArrayCliente[buscarIndiceCliente].cuit);
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}

/**
 * \brief: lista los Clientes con Publicaciones a partir del N° de Rubro, mostrando sus campos
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param pArrayCliente: Array de Cliente
 * \param limiteCliente: limite del array de Clientes
 * \param rubro: N° de rubro.
 * \nreturn Retorna 0 (EXITO) y -1 (ERROR)
 */
int publicacion_mostrarPorRubro(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente,int rubro)
{
	int retorno = -1;
	int i;
	int buscarIndiceCliente;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].numeroDeRubro == rubro)
			{
				buscarIndiceCliente = cliente_buscarId(pArrayCliente,limiteCliente,pArray[i].idCliente);
				if(buscarIndiceCliente != -1)
				{
					publicacion_imprimir(&pArray[i]);
					printf("APELLIDO,NOMBRE: %s,%s   - CUIT: %s\n",pArrayCliente[buscarIndiceCliente].apellido,pArrayCliente[buscarIndiceCliente].nombre,pArrayCliente[buscarIndiceCliente].cuit);
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}

/**
 * \brief: lista los Clientes con Publicaciones a partir del estado, mostrando sus campos
 * \param: pArray: Array de Publicacion
 * \param limite: limite del array de Publicaciones
 * \param pArrayCliente: Array de Cliente
 * \param limiteCliente: limite del array de Clientes
 * \param estado: ACTIVO o PAUSADO.
 * \nreturn Retorna 0 (EXITO) y -1 (ERROR)
 */
int publicacion_mostrarPorEstado(Publicacion* pArray,int limite,Cliente* pArrayCliente,int limiteCliente,int estado)
{
	int retorno = -1;
	int i;
	int buscarIndiceCliente;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].estado == estado)
			{
				buscarIndiceCliente = cliente_buscarId(pArrayCliente,limiteCliente,pArray[i].idCliente);
				if(buscarIndiceCliente != -1)
				{
					publicacion_imprimir(&pArray[i]);
					printf("APELLIDO,NOMBRE: %s,%s   - CUIT: %s\n",pArrayCliente[buscarIndiceCliente].apellido,pArrayCliente[buscarIndiceCliente].nombre,pArrayCliente[buscarIndiceCliente].cuit);
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}



/**
 * brief: busca un Id existente en el array de Publicaciones teniendo en cuenta su estado si se encuentra activo o pausado y devuelve su indice si se encontro
 * \param: pArray: Array de Publicaciones a ser actualizado
 * \param limite: limite del array de Publicaciones
 * \param: idABuscar: id a ser buscado
 * \param: estado: estado a ser buscado
 * \return Retorna i (ID ENCONTRADO) y -1(ID NO ENCONTRADO)
 */
int publicacion_buscarIdyEstado(Publicacion* pArray,int limite,int idABuscar,int estado)
{
	int indiceEncontrado = -1;
	int i;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].id == idABuscar && pArray[i].estado == estado)
			{
				indiceEncontrado = i;
				break;
			}
		}
	}
	return indiceEncontrado;
}

/**
 * brief: busca un N° de Rubro existente en el array de Publicaciones y devuelve su indice si se encontro
 * \param: pArray: Array de Publicaciones a ser actualizado
 * \param limite: limite del array de Publicaciones
 * \param: rubroABuscar: id a ser buscado
 * \return Retorna i (ID ENCONTRADO) y -1(ID NO ENCONTRADO)
 */
int publicacion_buscarRubro(Publicacion* pArray,int limite,int rubroABuscar)
{
	int indiceEncontrado = -1;
	int i;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].numeroDeRubro == rubroABuscar)
			{
				indiceEncontrado = i;
				break;
			}
		}
	}
	return indiceEncontrado;
}

/**
 * \brief: genera un valor de ID para array de Publicacions.Id
 * \return id
 */
static int generadorIdPublicacion(void)
{
	static int id = 999;
	id++;
	return id;
}
