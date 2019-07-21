#include <stdio.h>
#include <stdlib.h>

struct registro
{
  short numeroLegajo;
  short horasTrabajadas;
  int sueldo;
  struct  registro *siguiente;
};
 typedef struct registro  nodo;

 short evaluarLegajo(short);
 short evaluarHorasTrabajadas(short);
 void insertarLegajoEnOrdenEnLista(nodo ** , short , short);
 void mostrarLista(nodo *);
 FILE* escribirFicheroBinario(nodo *);
 void mostrarFicheroBinario(FILE*);

int main()
{
    short legajo = 0;
    short  numeroHoras = 0;
    nodo *apuntador = NULL;
    FILE *apuntadorFichero = NULL;


      printf("Enter record number [1 - 500]:  ");
      scanf("%hd" , &legajo);

     while(legajo)
    {
      legajo = evaluarLegajo(legajo);

      printf("Enter hours worked:  ");
      scanf("%hd" , &numeroHoras);
      numeroHoras = evaluarHorasTrabajadas(numeroHoras);

      insertarLegajoEnOrdenEnLista(&apuntador , legajo , numeroHoras);

      printf("Enter record number [1 - 500]:  ");
      scanf("%hd" , &legajo);
    }

    printf("\n\n\t\t\t-----------List Information(Orderned by record)------------\n");
    printf("\t\t  Record number  \t\tTotal hours worked\n");
    mostrarLista(apuntador);

    printf("\n\n\t\t\t---------------Binary file Information-------------------\n");
    printf("\t\t  Record number  \t\t\t\tSalary\n");
    apuntadorFichero = escribirFicheroBinario(apuntador);
    mostrarFicheroBinario(apuntadorFichero);
    eliminarLista(&apuntador);

    return 0;
}
////////////////////////////////////////////////////////////////////////////////////
short evaluarLegajo(short legajo)
{
        if(legajo < 0)
        {
            do
           {
              printf("Enter record number [1 - 500]:  ");
              scanf("%hd" , &legajo);

           } while(legajo <= 500 && legajo >= 1);
        }

        else
        {
            if(legajo > 500)
            {
              do
              {
                printf("Enter record number [1 - 500]:  ");
                scanf("%hd" , &legajo);

               } while(legajo > 500);
            }
        }

       return legajo;

}
/////////////////////////////////////////////////////////////////////////////
short evaluarHorasTrabajadas(short numeroHoras)
{
    if(numeroHoras <= 0)
    {
        do
        {
          printf("Enter hours worked:  ");
          scanf("%hd" , &numeroHoras);

        }while(numeroHoras <= 0);
    }

     return numeroHoras;

}
/////////////////////////////////////////////////////////////////////////////
void insertarLegajoEnOrdenEnLista(nodo **apuntador , short legajo ,
                                 short numeroHoras)
{
   if(*apuntador == NULL)
   {
        *apuntador = (nodo*) malloc(sizeof(nodo));
        (*apuntador)->numeroLegajo = legajo;
        (*apuntador)->horasTrabajadas = numeroHoras;
        (*apuntador)->siguiente = NULL;
   }

   else
    {
       if (legajo < (*apuntador)->numeroLegajo)
       {
          nodo *apuntadorAuxiliar = (nodo*) malloc(sizeof(nodo));
          apuntadorAuxiliar->numeroLegajo = legajo;
          apuntadorAuxiliar->horasTrabajadas = numeroHoras;
          apuntadorAuxiliar->siguiente = *apuntador;
          *apuntador = apuntadorAuxiliar;
       }

       else if(legajo == (*apuntador)->numeroLegajo)
       {
         (*apuntador)->horasTrabajadas += numeroHoras;
       }

       else
       {
        insertarLegajoEnOrdenEnLista(&(*apuntador)->siguiente , legajo , numeroHoras);
       }

    }
}
////////////////////////////////////////////////////////////////////////////////////
void mostrarLista(nodo *apuntador)
{
    if(apuntador)
    {
        printf("\t\t\t%hd  \t\t\t\t %hd\n" , apuntador->numeroLegajo , apuntador->horasTrabajadas);
        mostrarLista(&(*apuntador->siguiente));
    }
}
/////////////////////////////////////////////////////////////////////////////
FILE* escribirFicheroBinario(nodo *apuntador)
{
   FILE *apuntadorFichero = NULL;
   nodo n;

   apuntadorFichero = fopen("empleados.dat" , "wb+");

   if((apuntadorFichero = fopen("empleados.dat" ,"wb+")) == NULL)
   {
     printf("\n El archivo empleados.dat no pudo abrirse\n");
   }
   else
   {
       while(apuntador)
       {
         n = *apuntador;

         if(n.numeroLegajo >=1 && n.numeroLegajo <=199)
         {
           n.sueldo = n.horasTrabajadas *500;
           fwrite(&n , sizeof(n) , 1 , apuntadorFichero);
           apuntador = apuntador->siguiente;
         }

         else if(n.numeroLegajo >=200 && n.numeroLegajo <=500)
         {
           n.sueldo = n.horasTrabajadas *750;
           fwrite(&n , sizeof(n) , 1 , apuntadorFichero);
           apuntador = apuntador->siguiente;
         }

       }
   }

   return apuntadorFichero;

}
//////////////////////////////////////////////////////////////////////////
void mostrarFicheroBinario(FILE *apuntadorFichero)
{
   rewind(apuntadorFichero);
   nodo n;

   fread(&n , sizeof(n) , 1 , apuntadorFichero);
   while(!feof(apuntadorFichero))
   {
     printf("\t\t\t%hd   \t\t\t\t\t$ %d\n" , n.numeroLegajo , n.sueldo);
     fread(&n , sizeof(n) , 1 , apuntadorFichero);
   }

   fclose(apuntadorFichero);
}
///////////////////////////////////////////////////////////////////////
void eliminarLista(nodo **apuntador)
{
    nodo *apuntadorAuxiliar = NULL;

   if(*apuntador)
   {
      apuntadorAuxiliar = *apuntador;
      *apuntador = apuntadorAuxiliar->siguiente;
      free(apuntadorAuxiliar);
      eliminarLista(apuntador);

      printf("* ");
   }
}
