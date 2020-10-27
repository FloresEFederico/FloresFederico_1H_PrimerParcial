#include "Cliente.h"
#include "Publicacion.h"
#ifndef INFORMES_H_
#define INFORMES_H_

int informar_ClienteConMasAvisos(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente);
int informar_CantDeAvisosPausados(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente);
int informar_RubroConMasAvisos(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente);
int informar_subMenu(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente);

//-----SEGUNDA PARTE DEL PARCIAL-----
int informar_ClienteConMasAvisosActivos(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente);
int informar_ClienteConMasAvisosPausados(Publicacion** pArray,int limite,Cliente** pArrayCliente,int limiteCliente);
#endif /* INFORMES_H_ */
