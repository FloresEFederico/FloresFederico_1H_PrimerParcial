/*
 ============================================================================
 Name        : Primer_Parcial.c
 Author      : Flores Federico 1-H
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Cliente.h"
#include "Publicacion.h"
#include "Informes.h"

int main(void) {
	setbuf(stdout,NULL);
	Cliente listaDeClientes[QTY_CLIENTES];
	Publicacion listaDePublicaciones[QTY_PUBLICACIONES];
	int opcion;

	cliente_inicializarArray(listaDeClientes,QTY_CLIENTES);
	publicacion_inicializarArray(listaDePublicaciones,QTY_PUBLICACIONES);
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
				if(!cliente_altaArray(listaDeClientes,QTY_CLIENTES))
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
				if(!cliente_modificarArray(listaDeClientes,QTY_CLIENTES))
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
				if(!cliente_bajaArray(listaDeClientes,QTY_CLIENTES))
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
				if(!publicacion_altaArray(listaDePublicaciones,QTY_PUBLICACIONES,listaDeClientes,QTY_CLIENTES))
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
				if(!publicacion_pausarPublicacion(listaDePublicaciones,QTY_PUBLICACIONES,listaDeClientes,QTY_CLIENTES))
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
				if(!publicacion_reanudarPublicacion(listaDePublicaciones,QTY_PUBLICACIONES,listaDeClientes,QTY_CLIENTES))
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
				if(!cliente_imprimirArray(listaDeClientes,QTY_CLIENTES))
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
				if(!informar_subMenu(listaDePublicaciones,QTY_PUBLICACIONES,listaDeClientes,QTY_CLIENTES))
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

	return EXIT_SUCCESS;
}
