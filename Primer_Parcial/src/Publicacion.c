#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Publicacion.h"


static int generadorIdPublicacion(void); //utilizado en la funcion publicacion_altaArray
static int esTxtArchivo(char* pResultado);

/**
 * brief: Imprime los datos de la variable Publicacion
 * \param: auxProducto: variable de Publicaciona ser imprimida
 * \return Retorna 0 (EXITO) y -1(ERROR)
 */
int publicacion_imprimir(Publicacion* pPublicacion)
{
	int retorno= -1;
	int auxId;
	int auxRubro;
	char auxTxtArchivo[TXTARCHIVO_LEN];
	int auxIdCliente;
	int auxEstado;
	char estadoDePublicacion[10];
	if(pPublicacion != NULL &&
	   !pub_getId(pPublicacion,&auxId) &&
	   !pub_getRubro(pPublicacion,&auxRubro) &&
	   !pub_getTxtArchivo(pPublicacion,auxTxtArchivo) &&
	   !pub_getidCliente(pPublicacion,&auxIdCliente) &&
	   !pub_getEstado(pPublicacion,&auxEstado))
	{
		if(auxEstado == ACTIVO)
		{
			snprintf(estadoDePublicacion,sizeof(estadoDePublicacion),"ACTIVO");
		}else
		{
			snprintf(estadoDePublicacion,sizeof(estadoDePublicacion),"PAUSADA");
		}
		printf("\nID: %d\nN° DE RUBRO: %d  - IDCLIENTE: %d  - ESTADO: %s\nNOMBRE DE ARCHIVO: %s\n",auxId,auxRubro,auxIdCliente,estadoDePublicacion,auxTxtArchivo);
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
int publicacion_imprimirArray(Publicacion** pArray,int limite)
{
	int retorno = -1;
	int i;
	int flag = 0;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i] == NULL)
			{
				publicacion_imprimir(*(pArray+i));
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
int publicacion_imprimirPublicacionesActivas(Publicacion** pArray,int limite)
{
	int retorno = -1;
	int i;
	int flag = 0;
	int auxEstado;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i] != NULL && !pub_getEstado(*(pArray+i),&auxEstado)  && auxEstado == ACTIVO)
			{
				publicacion_imprimir(*(pArray+i));
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
int publicacion_imprimirPublicacionesPausadas(Publicacion** pArray,int limite)
{
	int retorno = -1;
	int i;
	int flag = 0;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(pArray[i] != NULL && (*(pArray+i))->estado == PAUSADO)
			{
				publicacion_imprimir(*(pArray+i));
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
 * brief: Busca un indice libre y lo devuelve
 * \param: pArray: Array de Publicaciones a ser actualizado
 * \param limite: limite del array de Publicaciones
 * \return Retorna i (EXITO) y -1(ERROR)
 */
int publicacion_getEmptyIndex(Publicacion** pArray,int limite)
{
	int indiceEncontrado = -1;
	int i;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(*(pArray+i) == NULL)
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
int publicacion_altaArray(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente)
{
	int retorno = -1;
	int auxId;
	int auxNumDeRubro;
	char auxTxtDelArchivo[TXTARCHIVO_LEN];
	int auxEstado;
	Publicacion* auxPublicacion;
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
			   !utn_getNumero(&auxNumDeRubro,"\nIngrese N° de Rubro(1-100): ","\nNumero invalida!\n",MIN_NUMRUBRO,MAX_NUMRUBRO,3) &&
			   !utn_getDireccion(auxTxtDelArchivo,TXTARCHIVO_LEN,"\nIngrese Texto del Archivo: ","\nTexto invalido!\n",3))
			{
				auxId = generadorIdPublicacion();
				auxEstado = ACTIVO;
				auxPublicacion = pub_newConParametros(auxId,auxNumDeRubro,auxTxtDelArchivo,auxIdCliente,auxEstado);
				*(pArray+indiceLibre) = auxPublicacion;
				publicacion_imprimir(*(pArray+indiceLibre));
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
int publicacion_buscarId(Publicacion** pArray,int limite,int idABuscar)
{
	int indiceEncontrado = -1;
	int i;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(*(pArray+i) != NULL && (*(pArray+i))->id == idABuscar)
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
int publicacion_pausarPublicacion(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente)
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
				pub_setEstado(*(pArray+indicePublicacion),PAUSADO);
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
int publicacion_reanudarPublicacion(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente)
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
				pub_setEstado(*(pArray+indicePublicacion),ACTIVO);
				printf("\nSe ha reanudado la publicacion!\n");
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
int publicacion_mostrarClientesConPublicacion(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente,int idPublicacion)
{
	int retorno = -1;
	int i;
	int buscarIndiceCliente;
	int auxIdPublicacion;
	int auxIdCliente;
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(*(pArray+i) != NULL && !pub_getId(*(pArray+i),&auxIdPublicacion) && auxIdPublicacion == idPublicacion && !pub_getidCliente(*(pArray+i),&auxIdCliente))
			{
				buscarIndiceCliente = cliente_buscarId(pArrayCliente,limiteCliente,auxIdCliente);
				if(buscarIndiceCliente != -1)
				{
					publicacion_imprimir(*(pArray+i));
					cliente_imprimir(*(pArrayCliente+buscarIndiceCliente));
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
int publicacion_mostrarPoridCliente(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente,int idClientes)
{
	int retorno = -1;
	int i;
	int buscarIndiceCliente;
	int auxIdCliente;
	char auxApellido[NOMBRE_LEN];
	char auxNombre[NOMBRE_LEN];
	char auxCuit[CUIT_LEN];
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(*(pArray+i) != NULL && !pub_getidCliente(*(pArray+i),&auxIdCliente) && auxIdCliente == idClientes)
			{
				buscarIndiceCliente = cliente_buscarId(pArrayCliente,limiteCliente,auxIdCliente);
				if(buscarIndiceCliente != -1 &&
				   !cli_getApellido(*(pArrayCliente+buscarIndiceCliente),auxApellido) &&
				   !cli_getNombre(*(pArrayCliente+buscarIndiceCliente),auxNombre) &&
				   !cli_getCuit(*(pArrayCliente+buscarIndiceCliente),auxCuit))
				{
					publicacion_imprimir(*(pArray+i));
					printf("APELLIDO,NOMBRE: %s,%s   - CUIT: %s\n",auxApellido,auxNombre,auxCuit);
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
int publicacion_mostrarPorRubro(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente,int rubro)
{
	int retorno = -1;
	int i;
	int buscarIndiceCliente;
	int auxRubro;
	int auxIdCliente;
	char auxApellido[NOMBRE_LEN];
	char auxNombre[NOMBRE_LEN];
	char auxCuit[CUIT_LEN];
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(*(pArray+i) != NULL && !pub_getRubro(*(pArray+i),&auxRubro) && auxRubro == rubro && !pub_getidCliente(*(pArray+i),&auxIdCliente))
			{
				buscarIndiceCliente = cliente_buscarId(pArrayCliente,limiteCliente,auxIdCliente);
				if(buscarIndiceCliente != -1 &&
				   !cli_getApellido(*(pArrayCliente+buscarIndiceCliente),auxApellido) &&
				   !cli_getNombre(*(pArrayCliente+buscarIndiceCliente),auxNombre) &&
				   !cli_getCuit(*(pArrayCliente+buscarIndiceCliente),auxCuit))
				{
					publicacion_imprimir(*(pArray+i));
					printf("APELLIDO,NOMBRE: %s,%s   - CUIT: %s\n",auxApellido,auxNombre,auxCuit);
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
int publicacion_mostrarPorEstado(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente,int estado)
{
	int retorno = -1;
	int i;
	int buscarIndiceCliente;
	int auxEstado;
	int auxIdCliente;
	char auxApellido[NOMBRE_LEN];
	char auxNombre[NOMBRE_LEN];
	char auxCuit[CUIT_LEN];
	if(pArray != NULL && limite > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(*(pArray+i) != NULL && !pub_getEstado(*(pArray+i),&auxEstado) && auxEstado == estado && !pub_getidCliente(*(pArray+i),&auxIdCliente))
			{
				buscarIndiceCliente = cliente_buscarId(pArrayCliente,limiteCliente,auxIdCliente);
				if(buscarIndiceCliente != -1 &&
				   !cli_getApellido(*(pArrayCliente+buscarIndiceCliente),auxApellido) &&
				   !cli_getNombre(*(pArrayCliente+buscarIndiceCliente),auxNombre) &&
				   !cli_getCuit(*(pArrayCliente+buscarIndiceCliente),auxCuit))
				{
					publicacion_imprimir(*(pArray+i));
					printf("APELLIDO,NOMBRE: %s,%s   - CUIT: %s\n",auxApellido,auxNombre,auxCuit);
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
int publicacion_buscarIdyEstado(Publicacion** pArray,int limite,int idABuscar,int estado)
{
	int indiceEncontrado = -1;
	int i;
	int auxIdPublicacion;
	int auxEstado;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(*(pArray+i) != NULL && !pub_getId(*(pArray+i),&auxIdPublicacion) && auxIdPublicacion == idABuscar && !pub_getEstado(*(pArray+i),&auxEstado) && auxEstado == estado)
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
int publicacion_buscarRubro(Publicacion** pArray,int limite,int rubroABuscar)
{
	int indiceEncontrado = -1;
	int i;
	int auxRubro;
	if(pArray != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(*(pArray+i) != NULL && !pub_getRubro(*(pArray+i),&auxRubro) && auxRubro == rubroABuscar)
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


Publicacion* pub_newConParametros(int id, int numeroDeRubro,char* textoDelArchivo,int idCliente,int estado)
{
	Publicacion* pc;
	if(id >= 0 &&  textoDelArchivo != NULL)
	{
		pc = (Publicacion*)malloc(sizeof(Publicacion));
		if(pc != NULL)
		{
			pub_setId(pc,id);
			pub_setRubro(pc,numeroDeRubro);
			pub_setTxtArchivo(pc,textoDelArchivo);
			pub_setidCliente(pc,idCliente);
			pub_setEstado(pc,estado);
		}
	}
	return pc;
}

int pub_initArray(Publicacion** pArray,int limite)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && limite)
	{
		for(i=0;i<limite;i++)
		{
			*(pArray+i) = NULL;
		}
		retorno = 0;
	}
	return retorno;
}
void pub_delete(Publicacion* pc)
{
	if(pc!= NULL)
	{
		free(pc);
	}
}

//-------------------------GETTERS--------------------------------------
int pub_getId(Publicacion* pArray, int* pValor)
{
	int ret = -1;
	if(pArray != NULL && pValor != NULL)
	{
		*pValor = pArray->id;
		ret = 0;
	}
	return ret;
}
int pub_getRubro(Publicacion* pArray, int* numRubro)
{
	int ret = -1;
	if(pArray != NULL && numRubro != NULL)
	{
		*numRubro = pArray->numeroDeRubro;
		ret = 0;
	}
	return ret;

}
int pub_getTxtArchivo(Publicacion* pArray, char* txtArchivo)
{
	int ret = -1;
	if(pArray != NULL && txtArchivo != NULL)
	{
		strncpy(txtArchivo,pArray->textoDelArchivo,TXTARCHIVO_LEN);
		ret = 0;
	}
	return ret;
}
int pub_getidCliente(Publicacion* pArray, int* idCliente)
{
	int ret = -1;
	if(pArray != NULL && idCliente != NULL)
	{
		*idCliente = pArray->idCliente;
		ret = 0;
	}
	return ret;

}
int pub_getEstado(Publicacion* pArray, int* estado)
{
	int ret = -1;
	if(pArray != NULL && estado != NULL)
	{
		*estado = pArray->estado;
		ret = 0;
	}
	return ret;
}
//-------------------------sETTERS--------------------------------------
int pub_setId(Publicacion* pArray, int pValor)
{
	int ret = -1;
	if(pArray != NULL && pValor > 0 && pValor >= 1000 && pValor <= 1999)
	{
		pArray->id = pValor;
		ret = 0;
	}
	return ret;
}
int pub_setRubro(Publicacion* pArray, int numRubro)
{
	int ret = -1;
	if(pArray != NULL && numRubro > 0 && numRubro >= MIN_NUMRUBRO && numRubro <= MAX_NUMRUBRO)
	{
		pArray->numeroDeRubro = numRubro;
		ret = 0;
	}
	return ret;

}
int pub_setTxtArchivo(Publicacion* pArray, char* txtArchivo)
{
	int ret = -1;
	if(pArray != NULL && txtArchivo != NULL)
	{
		if(esTxtArchivo(txtArchivo))
		{
			strncpy(pArray->textoDelArchivo,txtArchivo,TXTARCHIVO_LEN);
			ret = 0;
		}
	}
	return ret;

}
int pub_setidCliente(Publicacion* pArray, int idCliente)
{
	int ret = -1;
	if(pArray != NULL && idCliente > 0)
	{
		if(idCliente >= MIN_IDCLIENTE && idCliente <= MAX_IDCLIENTE)
		{
			pArray->idCliente = idCliente;
			ret = 0;
		}
	}
	return ret;

}
int pub_setEstado(Publicacion* pArray, int estado)
{
	int ret = -1;
	if(pArray != NULL && (estado == ACTIVO || estado == PAUSADO))
	{
		pArray->estado = estado;
		ret = 0;
	}
	return ret;

}

static int esTxtArchivo(char* pResultado)
{
	int retorno = 1;
	int i;
	if(pResultado != NULL){
		for(i=0;pResultado[i] != '\0';i++){
			if((pResultado[i] != ' ') &&
			   (pResultado[i] != '.') &&
			   (pResultado[i] != '¡') && (pResultado[i] != '!') &&
			   (pResultado[i] != '¿') && (pResultado[i] != '?') &&
			   (pResultado[i] < 'a' || pResultado[i] > 'z') &&
			   (pResultado[i] < 'A' || pResultado[i] > 'Z') &&
			   (pResultado[i] < '0' || pResultado[i] > '9')){
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
