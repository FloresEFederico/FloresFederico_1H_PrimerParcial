/*
 ============================================================================
FALTA HACER CON MEMORIA DINAMICA TODOS LAS FUNCIONES QUE ESTAN COMENTADAS!!!!
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Cliente.h"
#include "Publicacion.h"
#include "Informes.h"

int cli_hardCodeo(Cliente** pArray);
int pub_hardCodeo(Publicacion** pArray);


int main(void) {
	setbuf(stdout,NULL);
	//Cliente listaDeClientes[QTY_CLIENTES]; // NO SIRVE MAS
	//Publicacion listaDePublicaciones[QTY_PUBLICACIONES]; // NO SIRVE MAS
	//cliente_inicializarArray(listaDeClientes,QTY_CLIENTES); // NO SIRVE MAS
	//publicacion_inicializarArray(listaDePublicaciones,QTY_PUBLICACIONES);

	Cliente* listOfClients[QTY_CLIENTES];
	Publicacion* listOfPublications[QTY_PUBLICACIONES];
	int opcion;

	cli_initArray(listOfClients,QTY_CLIENTES);
	pub_initArray(listOfPublications,QTY_PUBLICACIONES);
	cli_hardCodeo(listOfClients);
	pub_hardCodeo(listOfPublications);
	do
	{
		if(!utn_getNumero(&opcion,"\n--MENU PRINCIPAL--\n"
								  "1-Alta de Cliente.\n"
								  "2-Modificar datos de Cliente.\n"
								  "3-Baja de Cliente.\n"
								  "4-Publicar.\n"
								  "5-Pausar Publicacion.\n"
								  "6-Reanudar Publicacion.\n"
								  "7-Imprimir Clientes.\n"
								  "8-Informar.\n"
								  "9-Salir.\nElija una opcion(1-9): ","\nOpcion invalida!\n",1,9,3))
		{
			switch(opcion)
			{
			case 1:
				if(!cliente_altaArray(listOfClients,QTY_CLIENTES))
				{
					printf("\n-----------------------------\n");
				}else
				{
					printf("\nHubo un error al hacer el alta\n");
				}
				printf("\nPresione enter para continuar...\n");
				getchar();
				break;
			case 2:
				if(!cliente_modificarArray(listOfClients,QTY_CLIENTES))
				{
					printf("\n-----------------------------\n");
				}else
				{
					printf("\nHubo un error al modificar al Cliente\n");
				}
				printf("\nPresione enter para continuar...\n");
				getchar();
				break;
			case 3:
				if(!cliente_bajaArray(listOfClients,QTY_CLIENTES,listOfPublications,QTY_PUBLICACIONES))
				{
					printf("\n-----------------------------\n");
				}else
				{
					printf("\nHubo un error al dar de baja al Cliente\n");
				}
				printf("\nPresione enter para continuar...\n");
				getchar();
				break;

			case 4:
				if(!publicacion_altaArray(listOfPublications,QTY_PUBLICACIONES,listOfClients,QTY_CLIENTES))
				{
					printf("\n-----------------------------\n");
				}else
				{
					printf("\nHubo un error al hacer la publicacion\n");
				}
				printf("\nPresione enter para continuar...\n");
				getchar();
				break;
				case 5:
				if(!publicacion_pausarPublicacion(listOfPublications,QTY_PUBLICACIONES,listOfClients,QTY_CLIENTES))
				{
					printf("\n-----------------------------\n");
				}else
				{
					printf("\nHubo un error al pausar la publicacion\n");
				}
				printf("\nPresione enter para continuar...\n");
				getchar();
				break;
			case 6:
				if(!publicacion_reanudarPublicacion(listOfPublications,QTY_PUBLICACIONES,listOfClients,QTY_CLIENTES))
				{
					printf("\n-----------------------------\n");
				}else
				{
					printf("\nHubo un error al reanudar la publicacion\n");
				}
				printf("\nPresione enter para continuar...\n");
				getchar();
				break;
			case 7:
				if(!cliente_imprimirArray(listOfClients,QTY_CLIENTES))
				{
					printf("\n-----------------------------\n");
				}else
				{
					printf("\nHubo un error al imprimir los Clientes\n");
				}
				printf("\nPresione enter para continuar...\n");
				getchar();
				break;
			case 8:
				if(!informar_subMenu(listOfPublications,QTY_PUBLICACIONES,listOfClients,QTY_CLIENTES))
				{
					printf("\n-----------------------------\n");
				}else
				{
					printf("\nHubo un error en el menu de Informes\n");
				}
				printf("\nPresione enter para continuar...\n");
				getchar();
				break;
			}
		}else
		{
			printf("\nSe acabo el numero de reintentos para ingresar una opcion valida!\n"
					"Saliendo del programa.\n");
			break;
		}
	}while(opcion != 9);
	printf("\nHasta luego!\n");
	//free(listOfClients);
	//free(listOfPublications);
	return EXIT_SUCCESS;
}

int cli_hardCodeo(Cliente** pArray)
{
	int retorno = -1;
	int bufferId[5] = {100,101,102,103,104};
	char bufferName[5][NOMBRE_LEN] ={"Federico","Cecilia","Jardin","Santiago","Viviana"};
	char bufferLastName[5][NOMBRE_LEN] = {"Flores","Perez","Maria","Rivera","Natulio"};
	char bufferCuit[5][CUIT_LEN] = {"20045169384","20378374644","1234567890","273737647","27140385455"};
	Cliente* pc;
	if(pArray != NULL)
	{
		for(int i=0;i<5;i++)
		{
			//1)Construyo el cliente
			pc = cli_newConParametros(bufferId[i],
									bufferName[i],
									bufferLastName[i],
									bufferCuit[i]);
			//2)Agrego el cliente al array
			*(pArray+i) = pc;
		}
		retorno = 0;
	}
	return retorno;
}

int pub_hardCodeo(Publicacion** pArray)
{
	int retorno = -1;
	int bufferId[5] = {1000,1001,1002,1003,1004};
	int bufferRubro[5] ={99,99,56,23,55};
	char bufferTxtArchivo [5][TXTARCHIVO_LEN] = {"Texto1","Texto2","Texto3","Texto4","Texto5"};
	char bufferidCliente[5] = {100,100,102,100,102};
	int bufferEstado[5] = {0,0,1,0,1};
	Publicacion* pc;
	if(pArray != NULL)
	{
		for(int i=0;i<5;i++)
		{
			//1)Construyo el cliente
			pc = pub_newConParametros(bufferId[i],bufferRubro[i],bufferTxtArchivo[i],bufferidCliente[i],bufferEstado[i]);
			//2)Agrego el cliente al array
			*(pArray+i) = pc;
		}
		retorno = 0;
	}
	return retorno;
}
