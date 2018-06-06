#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <conio.h>
#include <windows.h>
#include <string.h>


//Constantes:
#define RESET   "\033[0m"
#define BLACK   "\033[30m"        /* Black */
#define RED     "\033[1;31m"      /* Red */
#define GREEN   "\033[1;32m"      /* Green */
#define YELLOW  "\033[1;33m"      /* Yellow */
#define BLUE    "\033[1;34m"      /* Blue */
#define MAGENTA "\033[1;35m"      /* Magenta */
#define CYAN    "\033[1;36m"      /* Cyan */
#define WHITE   "\033[1;37m"      /* White */
//Archivos:
const char direccion[] = "archiClientes";

//Flechas
#define LIMSUP 6
#define LIMINF 12
#define X 7


///Estructuras:

typedef struct{
int id;
int dni;
char nombre[20];
char apellido[20];
char telefono[20];
char domicilio[30];
char baja; //‘s’ o ‘n’
} CLIENTE;









///Prototipos:





int main()
{

    system("color 3f");
    SetConsoleTitle("TRABAJO PRACTICO INTEGRADOR LABORATORIO 1");

    // Para controlar la consola
    HWND wh = GetConsoleWindow();
    // Definir el tamaño de la consola
    MoveWindow(wh, 100, 100, 950, 600, TRUE);

    ///Llamado a funciones:
    menuPrincipal();

    return 0;
}


void menuPrincipal(){

    int y = LIMSUP;
    char c;

    system("cls");
    hidecursor(0);

    gotoxy(7,y);
    printf("-->");

    //MENU
    gotoxy(30,1);
    printf("Gestion de ventas y control de stock");
    gotoxy(14,6);
    printf("CLIENTES");
    gotoxy(14,8);
    printf("PRODUCTOS");
    gotoxy(14,10);
    printf("VENTAS");
    gotoxy(14,12);
    printf("SALIR");


    do {
        c = getch();

        if(c == -32) {         //Numero identificador de la flecha. Apartir de aca se configura el movimiento de la flecha

                        gotoxy(X,y);
                        printf("   ");

                        c = getch();
                        if(c == 72)           /*Arriba*/
                            if(y == LIMSUP) {    //Limite superior

                                y=LIMINF;      //Limite inferior

                            } else {

                                y=y-2;

                            }
                        if(c == 80)           /*Abajo*/

                            if(y==LIMINF) {      //Limite inferior
                                y = LIMSUP;    //Limite superior
                            } else {

                                y=y+2;

                            }

                        gotoxy(X,y);
                        printf("-->");

        }

        if(c == 13)                      //Acciones al presionar Enter.
            {
                switch (y)
                {
                case 6:
                    menuClientes();
                    return menuPrincipal();
                    break;

                case 8:
                    system("cls");
                    printf("Esta seguro que desea continuar?\nEsta opcion borrara la lista existente en caso de haberla.\n\n");
                    printf("Para continuar presione ENTER o en caso de querer volver \nal menu principal presione ESC.");
                    do{
                    c  = getch();
                    if(c ==  27)            //Tecla ESC volver al menu.
                        {
                            return menuPrincipal();
                        }
                        if(c == 13){
                            //Ingresar a funcion
                            return menuPrincipal();
                        }
                    }while(1);
                    break;

                case 10:
                    system("cls");

                    break;

                case 12:
                    exit(1);
                    break;
                }

            }

        if(c ==  27)            //Tecla ESC volver al menu.
                    {
                        return 0;
                    }



    } while(1);


}

void menuClientes(){

    int y = LIMSUP;
    char c;

    system("cls");
    hidecursor(0);

    gotoxy(7,y);
    printf("-->");

    //MENU
    gotoxy(30,1);
    printf("\t\t    Clientes");
    gotoxy(14,6);
    printf("AGREGAR CLIENTES");
    gotoxy(14,8);
    printf("QUITAR CLIENTES");
    gotoxy(14,10);
    printf("MODIFICAR CLIENTES");
    gotoxy(14,12);
    printf("LISTA DE CLIENTES");
    gotoxy(14,14);
    printf("SALIR");

    do {
        c = getch();

        if(c == -32) {         //Numero identificador de la flecha. Apartir de aca se configura el movimiento de la flecha

                        gotoxy(X,y);
                        printf("   ");

                        c = getch();
                        if(c == 72){           /*Arriba*/
                            if(y == LIMSUP) {    //Limite superior

                                y=14;      //Limite inferior

                            } else {

                                y=y-2;

                            }
                        }
                        if(c == 80)           /*Abajo*/

                            if(y==14) {      //Limite inferior
                                y = LIMSUP;    //Limite superior
                            } else {

                                y=y+2;


                            }

                        gotoxy(X,y);
                        printf("-->");

        }

        if(c == 13)                      //Acciones al presionar Enter.
            {
                switch (y)
                {
                case 6:
                    system("cls");
                    CargarClientes();
                    return menuClientes();
                    break;

                case 8:
                    system("cls");
                    printf("Esta seguro que desea continuar?\nEsta opcion borrara la lista existente en caso de haberla.\n\n");
                    printf("Para continuar presione ENTER o en caso de querer volver \nal menu principal presione ESC.");
                    do{
                    c  = getch();
                    if(c ==  27)            //Tecla ESC volver al menu.
                        {
                            return menuClientes();
                        }
                        if(c == 13){
                            //Ingresar a funcion
                            return menuPrincipal();
                        }
                    }while(1);
                    break;

                case 10:
                    system("cls");
                    break;

                case 12:
                    system("cls");
                    mostrarClientes();
                    menuClientes();
                    break;

                case 14:
                    exit(1);
                    break;
                }

            }

        if(c ==  27)            //Tecla ESC volver al menu.
                    {
                        return 0;
                    }



    } while(1);



}

void CargarClientes(){

char control='s';
char ene=164;
int dni = 0;

CLIENTE a;
FILE *archi= fopen(direccion,"ab");

    if(archi==NULL){

        printf("El archivo no existe\n");
    }
    else {

        do{
            puts("\n----------------------------------");
            printf("\nIngrese su DNI: ");
            fflush(stdin);
            scanf("%i", &a.dni);

            dni = a.dni;

            while(dniIgual(dni) == 1){
                system("cls");
                puts("\aDNI ya ingresado, ingrese uno nuevo por favor.");
                printf("\nIngrese su DNI: ");
                fflush(stdin);
                scanf("%i", &a.dni);
                dni = a.dni;
            }

            printf("\nIngrese su nombre/s: ");
            fflush(stdin);
            gets(a.nombre);

            printf("\nIngrese su apellido/s: ");
            fflush(stdin);
            gets(a.apellido);

            printf("\nIngrese su telefono: ");
            fflush(stdin);
            gets(a.telefono);

            printf("\nIngrese su domicilio: ");
            fflush(stdin);
            gets(a.domicilio);
            puts("\n----------------------------------");

            a.baja = 's';

            fwrite(&a,sizeof(CLIENTE),1,archi);

            printf("\nDesea agregar otro registro?");
            fflush(stdin);
            scanf("%c",&control);
            system("cls");

        }while(control=='s');

        fclose(archi);
    }


}

int dniIgual(int dni){

CLIENTE a;
int bandera = 0;

FILE *archi = fopen(direccion,"rb");

    if(archi==NULL){
        printf("El archivo no existe\n");
    }else if(archi!=NULL){
        while(fread(&a,sizeof(CLIENTE),1,archi)>0 && bandera == 0){

                if(a.dni == dni){
                    bandera = 1;
                }
        }
    fclose(archi);
    }
 return bandera;
}

void mostrarClientes(){

int i = 1;
char ene = 164;
CLIENTE a;
FILE *archi = fopen(direccion,"rb");


    if(archi == NULL){
        printf("No se pudo mostrar los datos.");
    }

    if(archi != NULL){
        while(fread(&a,sizeof(CLIENTE),1,archi)>0){

                printf("Registro nro %i:\n", i);
                puts("--------------------------------------------");
                printf("   DNI nro: %i\n", a.dni);
                printf("  Nombre/s: %s\n", a.nombre);
                printf("Apellido/s: %s\n", a.apellido);
                printf("  Telefono: %s\n",a.telefono);
                printf(" Domicilio: %s\n",a.domicilio);
                puts("--------------------------------------------\n");
                i++;

        }
    }

    system("pause");

    fclose(archi);

}

void quitarClientes(){








}











