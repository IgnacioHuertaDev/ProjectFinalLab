///Librerias:
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

///Constantes colores:
#define RESET   "\033[1m\033[37m"
#define BLACK   "\033[30m"        /* Black */
#define RED     "\033[1;31m"      /* Red */
#define GREEN   "\033[1;32m"      /* Green */
#define YELLOW  "\033[1;33m"      /* Yellow */
#define BLUE    "\033[1;34m"      /* Blue */
#define MAGENTA "\033[1;35m"      /* Magenta */
#define CYAN    "\033[1;36m"      /* Cyan */
#define WHITE   "\033[1;37m"      /* White */

///Letra enie:
const char enie = 164;

///Archivos:
const char direccionClientes[] = "archiClientes.bin";
const char direccionProductos[]="archiProductos.bin";
const char direccionVentas[]="archiVentas.bin";

///Flechas principales:
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

typedef struct{
int id;
int codigo;
char producto[20];
int stock;
float costo;
float pvp;
char baja; //‘s’ o ‘n’
}PRODUCTO;

typedef struct{
int id;
int idCliente;
int idProducto;
int cantidad;
int dia;
int mes;
int anio;
char pagado;
char anular; //‘a’
}VENTA;


///Prototipos:
void menuPrincipal();
void flechasSN(char *control,int sup,int inf);
void menuColoresSINO(int y,int sup,int inf);
void menuColoresPrincipal(int y);
int cuentaRegistro(char archivo[], int dato);
void menuClientes();
void CargarClientes();
void mostrarClientes();
void estructuraMuestraCliente(CLIENTE a);
void quitarClientes();
void bajaClientes(int pos);
CLIENTE eliminarClientes(CLIENTE a);
void menuColoresClientes(int y);
int dniIgual(int dni);
int existeClienteID(int id, CLIENTE *a);
int buscarPosicionIDCliente(int id);
void guardarCliente(CLIENTE a);
void menuModificarCliente();
void modificarClientes(int pos);
CLIENTE modClientes(CLIENTE a);
void menuProductos();
void CargarProductos();
void mostrarProductos();
void estructuraMuestraProducto(PRODUCTO a);
void quitarProductos();
void bajaProductos(int pos);
PRODUCTO eliminarProductos(PRODUCTO a);
void menuColoresProductos(int y);
int codigoIgual(int codigo);
int existeProductoID(int id, PRODUCTO *a);
int buscarPosicionIDProductos(int id);
void guardarProducto(PRODUCTO a);
void menuModificarProducto();
void modificarProductos(int pos);
PRODUCTO modProductos(PRODUCTO a);
void menuVentas();
void menuColoresVentas(int y);
int buscarCliente();
void abrirLeerClientes(CLIENTE a);
void estructuraReducidaCliente(CLIENTE a);
int buscarProducto();
void abrirLeerProductos(PRODUCTO a);
void estructuraReducidaProducto(PRODUCTO a);
int revisarStock(int id);
int ingresarCantidad(VENTA a);
void mostrarProducto(int pos);
int fijarStock(int pos,int cantidad);
int RealizarVenta(VENTA v);
void estructura1(CLIENTE c);
void estructura2(PRODUCTO p);
void estructura3(VENTA v);
void mostrarCliente(int pos);
void mostrarProducto2(int pos);
void restarProductosStock(int pos,int cantidad);
void altaVenta();
void estructuraMuestraVenta(VENTA v);
void estructuraMuestraVentaAnulada(VENTA v);
void anularVenta();
void bajaVentas(int pos);
VENTA eliminarVentas(VENTA a);
void sumarProductosStock(int pos,int cantidad);
int buscarPosicionIDVentas(int id);
int existeVentaID(int id, VENTA *a);
void estructuraFecha();
int pedirAnio();
int pedirMes(int anio);
int pedirDia(int mes,int anio);
void listaPorCliente();
int existeClienteIDVenta(int id, VENTA *v);
char pagadoVenta();
void listaVentasMes();
int existeAnioVenta(int anio, VENTA *v);
int existeMesVenta(int mes, VENTA *v);
void promedioVentasMes();
void mostrarMatriz(int arreglo [7][4]);
float promedioVentasMatriz(int matriz[7][4]);

int main(){

    system("color 3f");
    hidecursor(0);
    //system("MODE 90,25");
    SetConsoleTitle("TRABAJO PRACTICO INTEGRADOR LABORATORIO 1");

    ///Llamado a funciones:
    menuPrincipal();

    return 0;
}

///Funciones GENERALES:
void menuPrincipal(){

    int y = LIMSUP;
    int bandera = 1;
    char c;

    system("cls");
    system("color 3f");
    hidecursor(0);

    gotoxy(7,y);
    printf("-->");

    //MENU

    gotoxy(30,1);
    printf("Gestion de ventas y control de stock");
    gotoxy(14,6);
    printf(GREEN"CLIENTES"RESET);
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

        //Funcion para cambiar de color los titulos.
        menuColoresPrincipal(y);


        if(c == 13)                      //Acciones al presionar Enter.
            {
                bandera = 0;
                switch (y)
                {
                case 6:
                    menuClientes();
                    break;

                case 8:
                    menuProductos();
                    break;

                case 10:
                    menuVentas();
                    break;

                case 12:
                    exit(1);
                    break;
                }

            }

        if(c ==  27)            //Tecla ESC volver al menu.
                    {
                        exit(1);
                    }



    } while(bandera == 1);


}

void flechasSN(char *control,int sup,int inf){

int limsup = sup;
int liminf =inf;
int y = limsup;
int bandera = 1;
char c;

    hidecursor(0);

    gotoxy(6,y);
    printf("-->");

    //Si o No
    gotoxy(10,limsup);
    printf(GREEN"SI"RESET);
    gotoxy(10,liminf);
    printf("NO");


    do {
        c = getch();

        if(c == -32) {         //Numero identificador de la flecha. Apartir de aca se configura el movimiento de la flecha

                        gotoxy(6,y);
                        printf("   ");

                        c = getch();
                        if(c == 72)           /*Arriba*/
                            if(y == limsup) {    //Limite superior
                                y=liminf;      //Limite inferior
                            }  else {
                                y=y-2;
                            }
                        if(c == 80)           /*Abajo*/

                            if(y==liminf) {      //Limite inferior
                                y = limsup;    //Limite superior

                            } else {
                                y=y+2;
                            }
                        gotoxy(6,y);
                        printf("-->");

        }
        //Cambia de color las flechas:
        menuColoresSINO(y,limsup,liminf);


        if(c == 13)                      //Acciones al presionar Enter.
            {
                bandera = 0;
                if(y == limsup){
                    *control = 's';
                }
                if(y == liminf){
                    *control = 'n';
                }
            }

    } while(bandera == 1);

}

void menuColoresSINO(int y,int sup,int inf){

    if(y == sup){
        gotoxy(10,sup);
        printf(GREEN"SI"RESET);
        }
    if(y != sup){
        gotoxy(10,sup);
        printf(WHITE"SI"RESET);
        }

   if(y == inf){
        gotoxy(10,inf);
        printf(GREEN"NO"RESET);
        }
    if(y != inf){
        gotoxy(10,inf);
        printf(WHITE"NO"RESET);
   }

}

void menuColoresPrincipal(int y){

    if(y == 6){
        gotoxy(14,6);
        printf(GREEN"CLIENTES"RESET);
        }
    if(y != 6){
        gotoxy(14,6);
        printf(WHITE"CLIENTES"RESET);
        }

   if(y == 8){
        gotoxy(14,8);
        printf(GREEN"PRODUCTOS"RESET);
        }
    if(y != 8){
        gotoxy(14,8);
        printf(WHITE"PRODUCTOS"RESET);
   }

   if(y == 10){
        gotoxy(14,10);
        printf(GREEN"VENTAS"RESET);
        }
    if(y != 10){
        gotoxy(14,10);
        printf(WHITE"VENTAS"RESET);
   }

    if(y == 12){
        gotoxy(14,12);
        printf(GREEN"SALIR"RESET);
        }
    if(y != 12){
        gotoxy(14,12);
        printf(WHITE"SALIR"RESET);
   }

}

int cuentaRegistro(char archivo[], int dato){

int cantRegistros;
FILE *archi = fopen(archivo,"rb");
fseek(archi,0,SEEK_END);
cantRegistros = ftell(archi) / dato;
fclose(archi);
cantRegistros++;
return cantRegistros;
}

///Funciones CLIENTES:

void menuClientes(){

    int y = LIMSUP;
    int bandera = 1;
    char c;

    system("cls");
    system("color 3f");
    hidecursor(0);

    gotoxy(7,y);
    printf("-->");

    //MENU
    gotoxy(30,1);
    printf("\t\t    Clientes");
    gotoxy(14,6);
    printf(GREEN"AGREGAR CLIENTES"RESET);
    gotoxy(14,8);
    printf("QUITAR CLIENTES");
    gotoxy(14,10);
    printf("MODIFICAR CLIENTES");
    gotoxy(14,12);
    printf("LISTA DE CLIENTES");
    gotoxy(14,14);
    printf("VOLVER");

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

        //Funcion para cambiar de color los titulos.
        menuColoresClientes(y);

        if(c == 13)                      //Acciones al presionar Enter.
            {
                switch (y)
                {
                case 6:
                    system("cls");
                    CargarClientes();
                    menuClientes();
                    break;

                case 8:
                    system("cls");
                    quitarClientes();
                    menuClientes();
                    break;

                case 10:
                    system("cls");
                    menuModificarCliente();
                    menuClientes();
                    break;

                case 12:
                    system("cls");
                    mostrarClientes();
                    break;

                case 14:
                    return menuPrincipal();
                    break;
                }

            }

        if(c ==  27)            //Tecla ESC volver al menu.
                    {
                        return menuPrincipal();
                    }



    } while(bandera == 1);



}

void CargarClientes(){
int i;
char control ='s';
int dni = 0;

CLIENTE a;
FILE *archi = fopen(direccionClientes,"ab");

    if(archi==NULL){

        printf("El archivo no existe\n");
    }
    else {

        do{
            printf("\t\t\t\t==> AGREGUE UN CLIENTE <==\n");
            puts("\n----------------------------------");
            printf("\nIngrese su DNI: ");
            fflush(stdin);
            scanf("%i", &a.dni);

            dni = a.dni;

            while(dniIgual(dni) == 1){
                system("cls");
                puts("\aDNI ya ingresado/no valido/dado de baja, ingrese uno nuevo por favor.");
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

            a.baja = 's';
            i = cuentaRegistro(direccionClientes, sizeof(CLIENTE));
            a.id = i;

            system("cls");
            guardarCliente(a);
            printf("\nDesea agregar otro registro?");
            flechasSN(&control,4,6);
            system("cls");

        }while(control=='s');

        fclose(archi);
    }


}

void mostrarClientes(){

int bandera = 1;
char c;
CLIENTE a;
FILE *archi = fopen(direccionClientes,"r+b");


    if(archi == NULL){
        printf("No se pudo mostrar los datos.");
    }
    else {
            printf("\t\t\t\t==> LISTA DE CLIENTES <==\n");
            while(fread(&a,sizeof(CLIENTE),1,archi)>0){
                    if(a.baja == 's'){
                        printf("ID nro %i:\n", a.id);
                        estructuraMuestraCliente(a);

                   }
            }
    }

    printf("\nPRESION ESC PARA VOLVER.");

    while(bandera == 1){
            c = getch();

            if(c == 27){

                fclose(archi);
                bandera = 0;
                return menuClientes();
            }
    }



}

void estructuraMuestraCliente(CLIENTE a){
    puts("--------------------------------------------");
    printf("   DNI nro: %i\n", a.dni);
    printf("  Nombre/s: %s\n", a.nombre);
    printf("Apellido/s: %s\n", a.apellido);
    printf("  Telefono: %s\n",a.telefono);
    printf(" Domicilio: %s\n",a.domicilio);
    puts("--------------------------------------------\n");
}

void quitarClientes(){

CLIENTE a;
int id;
char control = 's';

	do {
		system("cls");
		printf("\n\t\t\t==> QUITAR CLIENTE POR ID <==\n");

		/* Se pide el ID del cliente a quitar */
		printf("\n\tID del cliente: ");
        scanf("%i", &id);

		/* Se verifica que el cliente a buscar exista */
		if (existeClienteID(id, &a)) {
                    bajaClientes(buscarPosicionIDCliente(id));
                system("cls");

			} else {
                /* El cliente no existe */
                printf("\n\tEl cliente de ID %i no existe.\n", id);
            }

		printf("\n\tDesea quitar algun otro cliente? [S/N]: ");
		flechasSN(&control,10,12);
		if (control == 'n'){
            break;
		}


	} while (control == 's');
}

void bajaClientes(int pos){
    FILE * archi;
    CLIENTE a;
    archi=fopen(direccionClientes, "r+b");

    if(archi!=NULL)
    {
        fseek(archi, sizeof(CLIENTE)*(pos), SEEK_SET);
        fread(&a,sizeof(CLIENTE),1,archi);

        a = eliminarClientes(a);

        fseek(archi, sizeof(CLIENTE)*(-1), SEEK_CUR);
        fwrite(&a,sizeof(CLIENTE),1,archi);

        fclose(archi);
    }
}

CLIENTE eliminarClientes(CLIENTE a){

char control = 'n';

        system("cls");
        estructuraMuestraCliente(a);

        printf("\n Desea quitar al cliente?\n");
        flechasSN(&control,12,14);
        if (control == 's')
        {
            a.baja = 'n';
        }

        puts("----------------------------------\n");

return a;
}

void menuColoresClientes(int y){

    if(y == 6){
        gotoxy(14,6);
        printf(GREEN"AGREGAR CLIENTES"RESET);
        }
    if(y != 6){
        gotoxy(14,6);
        printf(WHITE"AGREGAR CLIENTES"RESET);
        }

   if(y == 8){
        gotoxy(14,8);
        printf(GREEN"QUITAR CLIENTES"RESET);
        }
    if(y != 8){
        gotoxy(14,8);
        printf(WHITE"QUITAR CLIENTES"RESET);
   }

   if(y == 10){
        gotoxy(14,10);
        printf(GREEN"MODIFICAR CLIENTES"RESET);
        }
    if(y != 10){
        gotoxy(14,10);
        printf(WHITE"MODIFICAR CLIENTES"RESET);
   }

    if(y == 12){
        gotoxy(14,12);
        printf(GREEN"LISTA DE CLIENTES"RESET);
        }
    if(y != 12){
        gotoxy(14,12);
        printf(WHITE"LISTA DE CLIENTES"RESET);
   }

    if(y == 14){
        gotoxy(14,14);
        printf(GREEN"VOLVER"RESET);
        }
    if(y != 14){
        gotoxy(14,14);
        printf(WHITE"VOLVER"RESET);
   }

}

int dniIgual(int dni){

int bandera = 0;

CLIENTE a;
FILE *archi = fopen(direccionClientes,"rb");

    if(archi==NULL){
        printf("El archivo no existe\n");
    }else {
            while(fread(&a,sizeof(CLIENTE),1,archi)>0 && bandera == 0){
                    if(a.dni == dni){
                        bandera = 1;
                    }
            }

    fclose(archi);
    }
 return bandera;
}

int existeClienteID(int id, CLIENTE *a){
	FILE *archi;
	int existe;


	archi = fopen(direccionClientes, "rb");

	if (archi == NULL) {
		existe = 0;

	} else {
		existe = 0;


		fread(&(*a), sizeof(*a), 1, archi);
		while (!feof(archi)) {
			if ((*a).id == id) {
				existe = 1;
				break;
			}
			fread(&(*a), sizeof(*a), 1, archi);
		}

		/* Cierra el archivo */
		fclose(archi);
	}

	return existe;
}

int buscarPosicionIDCliente(int id){
    FILE * archi;
    CLIENTE a;
    int flag = 0;
    int pos = 0;
    archi=fopen(direccionClientes, "rb");
    if(archi != NULL){
        while(!feof(archi) && flag == 0){
            fread(&a, sizeof(CLIENTE),1,archi);
            if (!feof(archi)){
                if(a.id == id)
                {
                        flag = 1;
                }
            }
        }
    }
        pos = (ftell(archi)/sizeof(CLIENTE));
        pos = pos-1;
        fclose(archi);

return pos;
}

void guardarCliente(CLIENTE a){

FILE *archi=fopen(direccionClientes,"ab");
    if(archi != NULL){
        fwrite(&a,sizeof(CLIENTE),1,archi);
        fclose(archi);
    }
}

void menuModificarCliente(){
	CLIENTE a;
	int id;
	char control = 's';

	do {
		system("cls");
		printf("\n\t\t\t==> MODIFICAR CLIENTE POR ID <==\n");

		/* Se pide el ID del cliente a modificar */
		printf("\n\tID del cliente: ");
        scanf("%i", &id);

		/* Se verifica que el cliente a buscar exista */
		if (existeClienteID(id, &a)) {
                    modificarClientes(buscarPosicionIDCliente(id));
                system("cls");

			} else {
                /* El cliente no existe */
                printf("\n\tEl cliente de ID %i no existe.\n", id);
            }

		printf("\n\tDesea modificar algun otro cliente? [S/N]: ");
		flechasSN(&control,10,12);
		if (control == 'n'){
            break;
		}


	} while (control == 's');
}

void modificarClientes(int pos){
    FILE * archi;
    CLIENTE a;
    archi=fopen(direccionClientes, "r+b");

    if(archi!=NULL)
    {
        fseek(archi, sizeof(CLIENTE)*(pos), SEEK_SET);
        fread(&a,sizeof(CLIENTE),1,archi);

        a = modClientes(a);

        fseek(archi, sizeof(CLIENTE)*(-1), SEEK_CUR);
        fwrite(&a,sizeof(CLIENTE),1,archi);

        fclose(archi);
    }
}

CLIENTE modClientes(CLIENTE a){

char control = 'n';

        system("cls");
        estructuraMuestraCliente(a);

        printf("\n Desea modificar el DNI?\n");
        printf("\ DNI actual: %i\n", a.dni);
        flechasSN(&control,12,14);
        if (control == 's')
        {
            printf("\nIngrese el nuevo dni: ");
            fflush(stdin);
            scanf("%i", &a.dni);
        }

        system("cls");
        estructuraMuestraCliente(a);

        printf("\n Desea modificar el nombre?\n");
        printf("\n Nombre actual: %s\n", a.nombre);
        flechasSN(&control,12,14);
        if (control == 's')
        {
            printf("\nIngrese el nuevo nombre: ");
            fflush(stdin);
            gets(a.nombre);
        }

        system("cls");
        estructuraMuestraCliente(a);

        printf("\n Desea modificar el apellido?\n");
        printf("\n Apellido actual: %s\n", a.apellido);
        flechasSN(&control,12,14);
        if (control == 's')
        {
            printf("\nIngrese el nuevo apellido: ");
            fflush(stdin);
            gets(a.apellido);
        }

        system("cls");
        estructuraMuestraCliente(a);

        printf("\n Desea modificar el telefono?\n");
        printf("\n Telefono actual: %s\n", a.telefono);
        flechasSN(&control,12,14);
        if (control == 's')
        {
            printf("\nIngrese el nuevo telefono: ");
            fflush(stdin);
            gets(a.telefono);
        }

        system("cls");
        estructuraMuestraCliente(a);

        printf("\n Desea modificar el domicilio?\n");
        printf("\n Domicilio actual: %s\n", a.domicilio);
        flechasSN(&control,12,14);
        if (control == 's')
        {
            printf("\nIngrese el nuevo domicilio: ");
            fflush(stdin);
            gets(a.domicilio);
        }

       if(a.baja == 'n'){

            system("cls");
            estructuraMuestraCliente(a);

            printf("\n Desea agregar devuelta al cliente?\n");
            flechasSN(&control,12,14);
            if (control == 's')
            {
                a.baja = 's';
            }

    }


return a;
}

///Funciones PRODUCTOS:

void menuProductos(){

   int y = LIMSUP;
   char c;


   system("cls");
   system("color 3f");
   hidecursor(0);

   gotoxy(7,y);
   printf("-->");

   //MENU
   gotoxy(30,1);
   printf("\t\t    Productos");
   gotoxy(14,6);
   printf(GREEN"AGREGAR PRODUCTOS"RESET);
   gotoxy(14,8);
   printf("QUITAR PRODUCTOS");
   gotoxy(14,10);
   printf("MODIFICAR PRODUCTOS");
   gotoxy(14,12);
   printf("LISTA DE PRODUCTOS");
   gotoxy(14,14);
   printf("VOLVER");

   do {
       c = getch();

       if(c == -32) {         //Numero identificador de la flecha. Apartir de aca se configura el movimiento de la flecha

                       gotoxy(X,y);
                       printf("   ");

                       c = getch();
                       if(c == 72)           /*Arriba*/
                           if(y == LIMSUP) {    //Limite superior

                               y=14;      //Limite inferior

                           } else {

                               y=y-2;

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

       //Funcion para cambiar de color los titulos.
       menuColoresProductos(y);

       if(c == 13)                      //Acciones al presionar Enter.
           {
               switch (y)
               {
                case 6:
                    system("cls");
                    CargarProductos();
                    menuProductos();
                   break;

                case 8:
                    system("cls");
                    quitarProductos();
                    menuProductos();
                    break;

                case 10:
                    system("cls");
                    menuModificarProducto();
                    menuProductos();
                    break;

                case 12:
                    system("cls");
                    mostrarProductos();
                    break;

                case 14:
                 return menuPrincipal();
                 break;
               }



           }

       if(c ==  27)            //Tecla ESC volver al menu.
                   {
                       return menuPrincipal();
                   }



   } while(1);



}

void CargarProductos(){

char control='s';
int codigo = 0;
int i;

PRODUCTO a;
FILE *archi= fopen(direccionProductos,"ab");

   if(archi==NULL){

       printf("El archivo no existe\n");
   }
   else {

       do{
            printf("\t\t\t\t==> AGREGUE UN PRODUCTO <==\n");
            puts("\n----------------------------------");
            printf("\nIngrese el codigo de barras del producto: ");
            fflush(stdin);
            scanf("%i", &a.codigo);

            codigo = a.codigo;

            while(codigoIgual(codigo) == 1){
                system("cls");
                puts("\aCodigo ya ingresado/no valido/dado de baja, ingrese uno nuevo por favor.");
                printf("\nIngrese el codigo: ");
                fflush(stdin);
                scanf("%i", &a.codigo);
                codigo = a.codigo;
            }

           printf("\nIngrese el nombre del producto: ");
           fflush(stdin);
           gets(&a.producto);

           printf("\nIngrese el stock del producto: ");
           fflush(stdin);
           scanf("%i", &a.stock);

           printf("\nIngrese el costo por unidad del producto: $");
           fflush(stdin);
           scanf("%f", &a.costo);

           printf("\nIngrese el precio de venta por unidad del producto: $");
           fflush(stdin);
           scanf("%f", &a.pvp);

            a.baja = 's';
            i = cuentaRegistro(direccionProductos, sizeof(PRODUCTO));
            a.id = i;


            system("cls");
            guardarProducto(a);
            printf("\nDesea agregar otro producto?");
            flechasSN(&control,4,6);
            system("cls");


       }while(control=='s');

       fclose(archi);
   }


}

void mostrarProductos(){

int bandera = 1;
char c;
PRODUCTO a;
FILE *archi = fopen(direccionProductos,"r+b");


    if(archi == NULL){
        printf("No se pudo mostrar los datos.");

    }else {

        printf("\t\t\t\t==> LISTA DE PRODUCTOS <==\n");
        while(fread(&a,sizeof(PRODUCTO),1,archi)>0){
            if(a.baja == 's'){
                printf("ID nro %i:\n", a.id);
                estructuraMuestraProducto(a);

           }
        }
    }

    printf("\nPRESION ESC PARA VOLVER.");

    while(bandera == 1){
            c = getch();

            if(c == 27){

                fclose(archi);
                bandera = 0;
                return menuProductos();
            }
    }

}

void estructuraMuestraProducto(PRODUCTO a){

            puts("--------------------------------------------");
            printf("Codigo nro: %i\n", a.codigo);
            printf("  Producto: %s\n", a.producto);
            printf("     Stock: %i\n",a.stock);
            printf("     Costo: %.2f\n",a.costo);
            printf("    Precio: %.2f\n",a.pvp);
            puts("--------------------------------------------\n");

}

void quitarProductos(){

PRODUCTO a;
int id;
char control = 's';

	do {
		system("cls");
		printf("\n\t\t\t==> QUITAR PRODUCTO POR ID <==\n");

		/* Se pide el ID del producto a quitar */
		printf("\n\tID del producto: ");
        scanf("%i", &id);

		/* Se verifica que el producto a buscar exista */
		if (existeProductoID(id, &a)) {
                    bajaProductos(buscarPosicionIDProductos(id));
                system("cls");

			} else {
                /* El cliente no existe */
                printf("\n\tEl producto de ID %i no existe.\n", id);
            }

		printf("\n\tDesea quitar algun otro producto? [S/N]: ");
		flechasSN(&control,10,12);
		if (control == 'n'){
            break;
		}


	} while (control == 's');
}

void bajaProductos(int pos){
    FILE * archi = fopen(direccionProductos, "r+b");
    PRODUCTO a;


    if(archi!=NULL)
    {
        fseek(archi, sizeof(PRODUCTO)*(pos), SEEK_SET);
        fread(&a,sizeof(PRODUCTO),1,archi);

        a = eliminarProductos(a);

        fseek(archi, sizeof(PRODUCTO)*(-1), SEEK_CUR);
        fwrite(&a,sizeof(PRODUCTO),1,archi);

        fclose(archi);
    }
}

PRODUCTO eliminarProductos(PRODUCTO a){

char control = 'n';

        system("cls");
        estructuraMuestraProducto(a);

        printf("\n Desea quitar al producto?\n");
        flechasSN(&control,12,14);
        if (control == 's')
        {
            a.baja = 'n';
        }

        puts("----------------------------------\n");

return a;
}

void menuColoresProductos(int y){

    if(y == 6){
        gotoxy(14,6);
        printf(GREEN"AGREGAR PRODUCTOS"RESET);
        }
    if(y != 6){
        gotoxy(14,6);
        printf(WHITE"AGREGAR PRODUCTOS"RESET);
        }

   if(y == 8){
        gotoxy(14,8);
        printf(GREEN"QUITAR PRODUCTOS"RESET);
        }
    if(y != 8){
        gotoxy(14,8);
        printf(WHITE"QUITAR PRODUCTOS"RESET);
   }

    if(y == 10){
        gotoxy(14,10);
        printf(GREEN"MODIFICAR PRODUCTOS"RESET);
        }
    if(y != 10){
        gotoxy(14,10);
        printf(WHITE"MODIFICAR PRODUCTOS"RESET);
   }

    if(y == 12){
        gotoxy(14,12);
        printf(GREEN"LISTA DE PRODUCTOS"RESET);
        }
    if(y != 12){
        gotoxy(14,12);
        printf(WHITE"LISTA DE PRODUCTOS"RESET);
   }

   if(y == 14){
        gotoxy(14,14);
        printf(GREEN"VOLVER"RESET);
        }
    if(y != 14){
        gotoxy(14,14);
        printf(WHITE"VOLVER"RESET);
   }

}

int codigoIgual(int codigo){

int bandera = 0;

PRODUCTO a;
FILE *archi = fopen(direccionProductos,"rb");

    if(archi==NULL){
        printf("El archivo no existe\n");
    }else {
            while(fread(&a,sizeof(PRODUCTO),1,archi)>0 && bandera == 0){
                    if(a.codigo == codigo){
                        bandera = 1;
                    }
            }

    fclose(archi);
    }
 return bandera;
}

int existeProductoID(int id, PRODUCTO *a){
	FILE *archi;
	int existe;


	archi = fopen(direccionProductos, "rb");

	if (archi == NULL) {
		existe = 0;

	} else {
		existe = 0;


		fread(&(*a), sizeof(*a), 1, archi);
		while (!feof(archi)) {
			if ((*a).id == id) {
				existe = 1;
				break;
			}
			fread(&(*a), sizeof(*a), 1, archi);
		}

		fclose(archi);
	}

	return existe;
}

int buscarPosicionIDProductos(int id){
    FILE * archi;
    PRODUCTO a;
    int flag = 0;
    int pos = 0;
    archi=fopen(direccionProductos, "rb");
    if(archi != NULL){
        while(!feof(archi) && flag == 0){
            fread(&a, sizeof(PRODUCTO),1,archi);
            if (!feof(archi)){
                if(a.id == id)
                {
                        flag = 1;
                }
            }
        }
    }
        pos = (ftell(archi)/sizeof(PRODUCTO));
        pos = pos-1;
        fclose(archi);

return pos;
}

void guardarProducto(PRODUCTO a){

FILE *archi=fopen(direccionProductos,"ab");
    if(archi != NULL){
        fwrite(&a,sizeof(PRODUCTO),1,archi);
        fclose(archi);
    }
}

void menuModificarProducto(){
	PRODUCTO a;
	int id;
	char control = 's';

	do {
		system("cls");
		printf("\n\t\t\t==> MODIFICAR CLIENTE POR ID <==\n");

		/* Se pide el ID del producto a modificar */
		printf("\n\tID del cliente: ");
        scanf("%i", &id);

		/* Se verifica que el producto a buscar exista */
		if (existeProductoID(id, &a)) {
                modificarProductos(buscarPosicionIDProductos(id));
                system("cls");

			} else {
                /* El producto no existe */
                printf("\n\tEl producto de ID %i no existe.\n", id);
            }

		printf("\n\tDesea modificar algun otro producto? [S/N]: ");
		flechasSN(&control,10,12);
		if (control == 'n'){
            break;
		}


	} while (control == 's');
}

void modificarProductos(int pos){
    FILE * archi;
    PRODUCTO a;
    archi=fopen(direccionProductos, "r+b");

    if(archi!=NULL)
    {
        fseek(archi, sizeof(PRODUCTO)*(pos), SEEK_SET);
        fread(&a,sizeof(PRODUCTO),1,archi);

        a = modProductos(a);

        fseek(archi, sizeof(PRODUCTO)*(-1), SEEK_CUR);
        fwrite(&a,sizeof(PRODUCTO),1,archi);

        fclose(archi);
    }
}

PRODUCTO modProductos(PRODUCTO a){

char control = 'n';

        system("cls");
        estructuraMuestraProducto(a);

        printf("\n Desea modificar el codigo de barras?\n");
        printf("\ Codigo de barras actual: %i\n", a.codigo);
        flechasSN(&control,12,14);
        if (control == 's')
        {
            printf("\nIngrese el nuevo codigo: ");
            fflush(stdin);
            scanf("%i", &a.codigo);
        }

        system("cls");
        estructuraMuestraProducto(a);

        printf("\n Desea modificar el nombre del producto?\n");
        printf("\n Nombre actual: %s\n", a.producto);
        flechasSN(&control,12,14);
        if (control == 's')
        {
            printf("\nIngrese el nuevo nombre: ");
            fflush(stdin);
            gets(a.producto);
        }

        system("cls");
        estructuraMuestraProducto(a);

        printf("\n Desea modificar el stock?\n");
        printf("\n Stock actual: %i\n", a.stock);
        flechasSN(&control,12,14);
        if (control == 's')
        {
            printf("\nIngrese el nuevo stock: ");
            fflush(stdin);
            scanf("%i", &a.stock);
        }

        system("cls");
        estructuraMuestraProducto(a);

        printf("\n Desea modificar el costo por unidad del producto?\n");
        printf("\n Costo actual: %.2f\n", a.costo);
        flechasSN(&control,12,14);
        if (control == 's')
        {
            printf("\nIngrese el nuevo costo del producto: ");
            fflush(stdin);
            scanf("%f", &a.costo);
        }

        system("cls");
        estructuraMuestraProducto(a);

        printf("\n Desea modificar el precio de venta por unidad?\n");
        printf("\n Precio de venta actual: %.2f\n", a.pvp);
        flechasSN(&control,12,14);
        if (control == 's')
        {
            printf("\nIngrese el nuevo precio de venta por unidad: ");
            fflush(stdin);
            scanf("%f", &a.pvp);
        }

       if(a.baja == 'n'){

            system("cls");
            estructuraMuestraProducto(a);

            printf("\n Desea agregar devuelta al producto?\n");
            flechasSN(&control,12,14);
            if (control == 's')
            {
                a.baja = 's';
            }

    }


return a;
}

///Funciones VENTAS:

void menuVentas(){

   int y = LIMSUP;
   char c;


   system("cls");
   system("color 3f");
   hidecursor(0);

   gotoxy(7,y);
   printf("-->");

   //MENU
   gotoxy(30,1);
   printf("\t\t  Ventas");
   gotoxy(14,6);
   printf(GREEN"ALTA DE VENTAS"RESET);
   gotoxy(14,8);
   printf("ANULACION DE VENTAS");
   gotoxy(14,10);
   printf("LISTAR VENTAS POR CLIENTE");
   gotoxy(14,12);
   printf("LISTAR VENTAS DEL MES");
   gotoxy(14,14);
   printf("MOSTRAR PROMEDIO DE VENTAS DEL MES");
   gotoxy(14,16);
   printf("VOLVER");

do {
    c = getch();

    if(c == -32) {         //Numero identificador de la flecha. Apartir de aca se configura el movimiento de la flecha

       gotoxy(X,y);
       printf("   ");

       c = getch();
       if(c == 72)
           if(y == LIMSUP) {    //Limite superior

               y=16;      //Limite inferior

           } else {

               y=y-2;

           }
       if(c == 80)

           if(y==16) {      //Limite inferior
               y = LIMSUP;    //Limite superior
           } else {

               y=y+2;

           }

       gotoxy(X,y);
       printf("-->");

    }

                //Funcion para cambiar de color los titulos.
                menuColoresVentas(y);

        if(c == 13)                      //Acciones al presionar Enter.
        {
               switch (y)
               {
               case 6:

                   system("cls");
                   altaVenta();
                   menuVentas();
                   break;

               case 8:

                   system("cls");
                   anularVenta();
                   menuVentas();
                   break;

               case 10:
                   system("cls");
                   listaPorCliente();
                   menuVentas();
                   break;

               case 12:
                   system("cls");
                   listaVentasMes();
                   menuVentas();
                   break;

               case 14:
                    system("cls");
                    promedioVentasMes();
                    menuVentas();
                    break;

               case 16:
                    return menuPrincipal();
                    break;
               }

           }
        if(c ==  27)            //Tecla ESC volver al menu.
                   {
                       return menuPrincipal();
                   }

        } while(1);
}

void menuColoresVentas(int y){

    if(y == 6){
        gotoxy(14,6);
        printf(GREEN"ALTA DE VENTAS"RESET);
        }
    if(y != 6){
        gotoxy(14,6);
        printf(WHITE"ALTA DE VENTAS"RESET);
        }

   if(y == 8){
        gotoxy(14,8);
        printf(GREEN"ANULACION DE VENTAS"RESET);
        }
    if(y != 8){
        gotoxy(14,8);
        printf(WHITE"ANULACION DE VENTAS"RESET);
   }

    if(y == 10){
        gotoxy(14,10);
        printf(GREEN"LISTAR VENTAS POR CLIENTE"RESET);
        }
    if(y != 10){
        gotoxy(14,10);
        printf(WHITE"LISTAR VENTAS POR CLIENTE"RESET);
   }

    if(y == 12){
        gotoxy(14,12);
        printf(GREEN"LISTAR VENTAS DEL MES"RESET);
        }
    if(y != 12){
        gotoxy(14,12);
        printf(WHITE"LISTAR VENTAS DEL MES"RESET);
   }

   if(y == 14){
        gotoxy(14,14);
        printf(GREEN"MOSTRAR PROMEDIO DE VENTAS DEL MES"RESET);
        }
    if(y != 14){
        gotoxy(14,14);
        printf(WHITE"MOSTRAR PROMEDIO DE VENTAS DEL MES"RESET);
   }

     if(y == 16){
        gotoxy(14,16);
        printf(GREEN"VOLVER"RESET);
        }
    if(y != 16){
        gotoxy(14,16);
        printf(WHITE"VOLVER"RESET);
        }

}

int buscarCliente(){

int id;
CLIENTE a;

abrirLeerClientes(a);

printf("\n\nIngrese el ID del cliente: ");
fflush(stdin);
scanf("%i",&id);

    while(existeClienteID(id,&a)== 0 || a.baja == 'n'){

            system("cls");
            abrirLeerClientes(a);

            if(existeClienteID(id,&a)==0) {
                    printf("\aEl cliente no existe, ingrese otro ID: ");
                    fflush(stdin);
                    scanf("%i",&id);
            }

            system("cls");
            abrirLeerClientes(a);

             if(a.baja == 'n') {
                    printf("\aEl cliente esta dado de baja y no es valido para la venta, ingrese otro ID: ");
                    fflush(stdin);
                    scanf("%i",&id);
            }
        }

return id;
}

void abrirLeerClientes(CLIENTE a){

FILE *archi = fopen(direccionClientes,"r+b");


    if(archi == NULL){
        printf("No se pudo mostrar los datos.");
    }
    else {
            printf("\t\t\t\t==> LISTA DE CLIENTES <==\n");
            while(fread(&a,sizeof(CLIENTE),1,archi)>0){
                    if(a.baja == 's'){
                        printf("ID nro %i:\n", a.id);
                        estructuraReducidaCliente(a);

                   }
            }
        fclose(archi);
    }

}

void estructuraReducidaCliente(CLIENTE a){
    puts("--------------------------------------------");
    printf("   DNI nro: %i\n", a.dni);
    printf("  Nombre/s: %s\n", a.nombre);
    printf("Apellido/s: %s\n", a.apellido);
    puts("--------------------------------------------\n");
}

int buscarProducto(){

int id;
PRODUCTO a;

abrirLeerProductos(a);

printf("\n\nIngrese el ID del producto: ");
fflush(stdin);
scanf("%i",&id);

    while(existeProductoID(id,&a)==0 || revisarStock(id)==0){

        system("cls");
        abrirLeerProductos(a);

        if(existeProductoID(id,&a)==0) {
            printf("\aEl producto no existe, ingrese un ID valido: ");
            fflush(stdin);
            scanf("%i",&id);
        }

        system("cls");
        abrirLeerProductos(a);

        if(revisarStock(id)==0 && existeProductoID(id,&a)==1){
            printf("\aEl producto tiene stock 0, ingrese un ID valido:");
            fflush(stdin);
            scanf("%i",&id);
        }
    }

return id;
}

void abrirLeerProductos(PRODUCTO a){


FILE *archi = fopen(direccionProductos,"rb");

    if(archi == NULL){

        printf("No se pudo mostrar los datos.");

    }else {
        printf("\t\t\t\t==> LISTA DE PRODUCTOS <==\n");

        while(fread(&a,sizeof(PRODUCTO),1,archi)>0){

            if(a.baja == 's' && a.stock>0){
                printf("ID nro %i:\n", a.id);
                estructuraReducidaProducto(a);
           }
        }
        fclose(archi);
    }

}

void estructuraReducidaProducto(PRODUCTO a){

puts("-------------------------------------");
printf("Codigo nro: %i\n", a.codigo);
printf("  Producto: %s\n", a.producto);
printf("     Stock: %i\n",a.stock);
puts("-------------------------------------\n");


}

int revisarStock(int id){

FILE * archi;
PRODUCTO a;
int flag = 0;
archi=fopen(direccionProductos, "rb");

    if(archi != NULL){

        while(!feof(archi) && flag == 0){
            fread(&a, sizeof(PRODUCTO),1,archi);

            if (!feof(archi)){
                if(a.id == id && a.stock>0)
                {
                        flag = 1;
                }
            }
        }

        fclose(archi);
    }


return flag;
}

int ingresarCantidad(VENTA a){

int cantidad;

    printf("\t\t\t\t==> ELEGIR CANTIDAD <==\n");

    mostrarProducto(buscarPosicionIDProductos(a.idProducto));
    printf("\n\n");

    printf("Ingrese la cantidad a comprar: ");
    fflush(stdin);
    scanf("%i",&cantidad);

    while(fijarStock(buscarPosicionIDProductos(a.idProducto),cantidad)==1 || cantidad <= 0){

        system("cls");
        printf("\t\t\t\t==> ELEGIR CANTIDAD <==\n");
        mostrarProducto(buscarPosicionIDProductos(a.idProducto));

        if(fijarStock(buscarPosicionIDProductos(a.idProducto),cantidad)==1) {
                printf("\n\aLa cantidad supera el stock, ingrese una cantidad menor: ");
                fflush(stdin);
                scanf("%i",&cantidad);
        }

        system("cls");
        printf("\t\t\t\t==> ELEGIR CANTIDAD <==\n");
        mostrarProducto(buscarPosicionIDProductos(a.idProducto));

        if(cantidad <= 0){
                printf("\n\aLa cantidad tiene que ser mayor a 0, ingrese una cantidad mayor: ");
                fflush(stdin);
                scanf("%i",&cantidad);
        }
    }


return cantidad;
}

void mostrarProducto(int pos){
    FILE * archi = fopen(direccionProductos, "rb");
    PRODUCTO a;


    if(archi!=NULL) {

        fseek(archi, sizeof(PRODUCTO)*(pos), SEEK_SET);
        fread(&a,sizeof(PRODUCTO),1,archi);

        estructuraReducidaProducto(a);

        fclose(archi);
    }
}

int fijarStock(int pos,int cantidad){

    FILE * archi = fopen(direccionProductos, "r+b");
    PRODUCTO a;

    int flag=0;

    if(archi!=NULL) {

        fseek(archi, sizeof(PRODUCTO)*(pos), SEEK_SET);
        fread(&a,sizeof(PRODUCTO),1,archi);

        if(a.stock<cantidad){

            flag=1;
        }

        fclose(archi);
    }

 return flag;
}

int RealizarVenta(VENTA v){

char c;

printf("\t\t\t\t==> REALIZAR VENTA <==\n");

    mostrarCliente(buscarPosicionIDCliente(v.idCliente));
    mostrarProducto2(buscarPosicionIDProductos(v.idProducto));
    estructura3(v);


    gotoxy(0,14);
    printf("\nDesea dar de alta la venta?");

    flechasSN(&c,17,19);

return c;
}

void estructura1(CLIENTE c){

    puts("-------------------------------------");
    printf("   DNI del Cliente: %i\n", c.dni);
    printf("          Nombre/s: %s\n", c.nombre);
    printf("        Apellido/s: %s\n", c.apellido);

}

void estructura2(PRODUCTO p){

    printf("        Codigo nro: %i\n", p.codigo);
    printf("          Producto: %s\n", p.producto);

}

void estructura3(VENTA v){

    printf("Cantidad a comprar: %i\n", v.cantidad);
    printf("               Dia: %i\n", v.dia);
    printf("               Mes: %i\n", v.mes);
    printf("              A%co: %i\n", enie ,v.anio);
    printf("            Pagado: %c\n", v.pagado);
    puts("--------------------------------------\n");

}

void mostrarCliente(int pos){
    FILE * archi=fopen(direccionClientes, "r+b");
    CLIENTE a;

    if(archi!=NULL) {

        fseek(archi, sizeof(CLIENTE)*(pos), SEEK_SET);
        fread(&a,sizeof(CLIENTE),1,archi);

        estructura1(a);

        fclose(archi);
    }
}

void mostrarProducto2(int pos){

    FILE * archi = fopen(direccionProductos, "rb");
    PRODUCTO a;

    if(archi!=NULL) {

        fseek(archi, sizeof(PRODUCTO)*(pos), SEEK_SET);
        fread(&a,sizeof(PRODUCTO),1,archi);

        estructura2(a);

        fclose(archi);

    }
}

void restarProductosStock(int pos,int cantidad){
    FILE * archi;
    PRODUCTO a;
    archi=fopen(direccionProductos, "r+b");

    if(archi!=NULL)
    {
        fseek(archi, sizeof(PRODUCTO)*(pos), SEEK_SET);
        fread(&a,sizeof(PRODUCTO),1,archi);

        a.stock = a.stock - cantidad;

        fseek(archi, sizeof(PRODUCTO)*(-1), SEEK_CUR);
        fwrite(&a,sizeof(PRODUCTO),1,archi);

        fclose(archi);
    }
}

void altaVenta(){

VENTA v;
CLIENTE c;
PRODUCTO p;

int i;
int anio;
int mes;
int dia;

FILE *archi = fopen(direccionVentas,"ab");

    if(archi != NULL){

        v.idCliente=buscarCliente();
        system("cls");

        v.idProducto=buscarProducto();
        system("cls");

        v.cantidad=ingresarCantidad(v);
        system("cls");



        //Se pide el anio
        gotoxy(0,0);
        printf("\t\t\t==> INGRESE LA FECHA DE LA VENTA <==\n");
        anio = pedirAnio();

        //Se pide el mes
        gotoxy(0,0);
        printf("\t\t\t==> INGRESE LA FECHA DE LA VENTA <==\n");
        mes = pedirMes(anio);

        //Se pide el dia
        gotoxy(0,0);
        printf("\t\t\t==> INGRESE LA FECHA DE LA VENTA <==\n");
        dia = pedirDia(mes,anio);

        v.anio = anio;
        v.mes = mes;
        v.dia = dia;

        gotoxy(0,0);
        printf("\t\t\t==> CONFIRMAR PAGO DE LA VENTA <==\n");
        v.pagado = pagadoVenta();

        system("cls");
        i = cuentaRegistro(direccionVentas, sizeof(VENTA));
        v.id = i;

        if(RealizarVenta(v)=='s'){

        restarProductosStock(buscarPosicionIDProductos(v.idProducto),v.cantidad);
        fwrite(&v,sizeof(VENTA),1,archi);
        fclose(archi);

        }else{

        fclose(archi);

        }
    }

}

void estructuraMuestraVenta(VENTA v){
    puts("--------------------------------------------");
    printf("   ID Cliente: %i\n", v.idCliente);
    printf("  ID Producto: %i\n", v.idProducto);
    printf("     Cantidad: %i\n", v.cantidad);
    printf("          Dia: %i\n", v.dia);
    printf("          Mes: %i\n", v.mes);
    printf("         A%co: %i\n", enie , v.anio);
    printf("       Pagado: %c\n", v.pagado);
    puts("--------------------------------------------\n");

}

void estructuraMuestraVentaAnulada(VENTA v){
    puts(RED"--------------------------------------------"RESET);
    printf(RED"   ID Cliente: %i\n"RESET, v.idCliente);
    printf(RED"  ID Producto: %i\n"RESET, v.idProducto);
    printf(RED"     Cantidad: %i\n"RESET, v.cantidad);
    printf(RED"          Dia: %i\n"RESET, v.dia);
    printf(RED"          Mes: %i\n"RESET, v.mes);
    printf(RED"         A%co: %i\n"RESET,enie , v.anio);
    printf(RED"       Pagado: %c\n"RESET, v.pagado);
    puts(RED"--------------------------------------------\n"RESET);

}

void anularVenta(){

VENTA a;
int id;
char control = 's';

	do {
		system("cls");
		printf("\n\t\t\t==> QUITAR VENTA POR ID <==\n");

		/* Se pide el ID de la venta a quitar */
		printf("\n\tID del venta: ");
        scanf("%i", &id);

		/* Se verifica que la venta a buscar exista */
		if (existeVentaID(id, &a)) {
                    bajaVentas(buscarPosicionIDVentas(id));

                    system("cls");

			} else {
                /* El venta no existe */
                printf("\n\tLa venta con ID %i no existe.\n", id);
            }

		printf("\n\tDesea quitar anular otra venta? [S/N]: ");
		flechasSN(&control,10,12);
		if (control == 'n'){
            break;
		}


	} while (control == 's');
}

void bajaVentas(int pos){
    FILE * archi;
    VENTA a;
    archi=fopen(direccionVentas, "r+b");

    if(archi!=NULL)
    {
        fseek(archi, sizeof(VENTA)*(pos), SEEK_SET);
        fread(&a,sizeof(VENTA),1,archi);

        a = eliminarVentas(a);
        sumarProductosStock(buscarPosicionIDProductos(a.idProducto),a.cantidad);

        fseek(archi, sizeof(VENTA)*(-1), SEEK_CUR);
        fwrite(&a,sizeof(VENTA),1,archi);

        fclose(archi);
    }
}

VENTA eliminarVentas(VENTA a){

char control = 'n';

        system("cls");
        estructuraMuestraVenta(a);

        printf("\n Desea quitar anular la venta?\n");
        flechasSN(&control,12,14);
        if (control == 's')
        {
            a.anular = 'a';
        }

        puts("----------------------------------\n");

return a;
}

void sumarProductosStock(int pos,int cantidad){
    FILE * archi;
    PRODUCTO a;
    archi=fopen(direccionProductos, "r+b");

    if(archi!=NULL)
    {
        fseek(archi, sizeof(PRODUCTO)*(pos), SEEK_SET);
        fread(&a,sizeof(PRODUCTO),1,archi);

        a.stock = a.stock + cantidad;

        fseek(archi, sizeof(PRODUCTO)*(-1), SEEK_CUR);
        fwrite(&a,sizeof(PRODUCTO),1,archi);

        fclose(archi);
    }
}

int buscarPosicionIDVentas(int id){
    FILE * archi;
    VENTA a;
    int flag = 0;
    int pos = 0;
    archi=fopen(direccionVentas, "rb");
    if(archi != NULL){
        while(!feof(archi) && flag == 0){
            fread(&a, sizeof(VENTA),1,archi);
            if (!feof(archi)){
                if(a.id == id)
                {
                        flag = 1;
                }
            }
        }
    }
        pos = (ftell(archi)/sizeof(VENTA));
        pos = pos-1;
        fclose(archi);

return pos;
}

int existeVentaID(int id, VENTA *a){

	FILE *archi;
	int existe;


	archi = fopen(direccionVentas, "rb");

	if (archi == NULL) {
		existe = 0;

	} else {
		existe = 0;


		fread(&(*a), sizeof(*a), 1, archi);
		while (!feof(archi)) {
			if ((*a).id == id) {
				existe = 1;
				break;
			}
			fread(&(*a), sizeof(*a), 1, archi);
		}

		/* Cierra el archivo */
		fclose(archi);
	}

	return existe;
}

void estructuraFecha(){

        gotoxy(3,4);
        printf("YYYY");
        gotoxy(8,4);
        printf("MM");
        gotoxy(11,4);
        printf("DD");

        gotoxy(2,5);
        printf("/");
        gotoxy(7,5);
        printf("/");
        gotoxy(10,5);
        printf("/");
        gotoxy(13,5);
        printf("/");

}

int pedirAnio(){

int anio = 0;

    estructuraFecha();

    printf("\nIngrese el a%co: ", enie);
    fflush(stdin);
    scanf("%i",&anio);

    while(anio < 2018 || anio > 2100){
        gotoxy(0,6);
        printf("\n\aEl a%co ingresado no es valido, ingrese uno nuevo por favor: ", enie);
        fflush(stdin);
        gotoxy(61,7);
        printf("               ");
        gotoxy(0,6);
        printf("                         ");
        gotoxy(61,7);
        scanf("%i", &anio);
    }

    system("cls");
    gotoxy(3,5);
    printf("%i", anio);

    return anio;
}

int pedirMes(int anio){

int mes = 0;

    estructuraFecha();

    printf("\nIngrese el mes: ");
    fflush(stdin);
    scanf("%i",&mes);

    while(mes < 1 || mes > 12){
        gotoxy(0,6);
        printf("\n\aEl mes ingresado no es valido, ingrese uno nuevo por favor: ");
        fflush(stdin);
        gotoxy(60,7);
        printf("             ");
        gotoxy(0,6);
        printf("                      ");
        gotoxy(60,7);
        scanf("%i", &mes);
    }

    system("cls");
    gotoxy(3,5);
    printf("%i", anio);

                gotoxy(8,5);
                if(mes < 10){
                    printf("0%i", mes);
                }else {
                    printf("%i", mes);
                    }


    return mes;
}

int pedirDia(int mes,int anio){

int dia = 0;
int dia_maximo = 0;
int diaCorrecto = 0;

    estructuraFecha();

    printf("\nIngrese el dia: ");
    fflush(stdin);
    scanf("%i",&dia);

    do {
        switch(mes)
            {
            case  1 : dia_maximo = 31;
                      break;

            case  2 : if ( anio % 4 == 0 && anio % 100 != 0 || anio % 400 == 0 ){
                          dia_maximo = 29;
                      }else{
                          dia_maximo = 28;
                      }
                      break;

            case  3 : dia_maximo = 31;
                      break;

            case  4 : dia_maximo = 30;
                      break;

            case  5 : dia_maximo = 31;
                      break;

            case  6 : dia_maximo = 30;
                      break;

            case  7 : dia_maximo = 31;
                      break;

            case  8 : dia_maximo = 31;
                      break;

            case  9 : dia_maximo = 30;
                      break;

            case 10 : dia_maximo = 31;
                      break;

            case 11 : dia_maximo = 30;
                      break;

            case 12 : dia_maximo = 31;
                      break;

        }

            if ( dia >= 1 && dia <= dia_maximo ){
                diaCorrecto = 1;
            }else{
                gotoxy(0,6);
                printf("\n\aEl dia ingresado no es valido, ingrese uno nuevo por favor: ");
                fflush(stdin);
                gotoxy(60,7);
                printf("           ");
                gotoxy(0,6);
                printf("                      ");
                gotoxy(60,7);
                scanf("%i",&dia);
            }

    }while(diaCorrecto == 0);

                system("cls");
                estructuraFecha();
                gotoxy(3,5);
                printf("%i", anio);

                gotoxy(8,5);
                if(mes < 10){
                    printf("0%i", mes);
                }else {
                    printf("%i", mes);
                    }

                gotoxy(11,5);
                if(dia < 10){
                    printf("0%i", dia);
                }else {
                        printf("%i", dia);
                    }

    return dia;
}

void listaPorCliente(){

VENTA v;
int id;
int bandera = 1;
char c;

    FILE *archi = fopen(direccionVentas,"rb");

    if(archi == NULL){
        printf("No se pudo mostrar los datos.");
    }else {

        printf("\t\t\t\t==> LISTA DE VENTAS POR ID DE CLIENTE <==\n");

        printf("\n\tID del cliente: ");
        scanf("%i", &id);

        while(existeClienteIDVenta(id,&v)==0){

        system("cls");
        printf("\t\t\t\t==> LISTA DE VENTAS POR ID DE CLIENTE <==\n");
        printf("\n\tEl cliente no existe, ingrese otro: ");
        fflush(stdin);
        scanf("%i",&id);

        }

        system("cls");
        printf("\t\t\t\t==> LISTA DE VENTAS POR ID DE CLIENTE <==\n");

        while(fread(&v,sizeof(VENTA),1,archi)>0){

            if(id == v.idCliente){
                if(v.anular == 'a'){
                printf(RED"ID nro %i:\n"RESET, v.id);
                estructuraMuestraVentaAnulada(v);
                }else{
                printf("ID nro %i:\n", v.id);
                estructuraMuestraVenta(v);
                }
            }
        }
    }

    printf("\nPRESION ESC PARA VOLVER.");

    while(bandera == 1){
            c = getch();

            if(c == 27){

                fclose(archi);
                bandera = 0;
            }
    }

}

int existeClienteIDVenta(int id, VENTA *v){

int existe;

FILE *archi = fopen(direccionVentas, "rb");

    if (archi == NULL) {
        existe = 0;

    } else {
        existe = 0;


        fread(&(*v), sizeof(*v), 1, archi);
        while (!feof(archi)) {
            if ((*v).idCliente == id) {
                existe = 1;
                break;
            }
            fread(&(*v), sizeof(*v), 1, archi);
        }

        /* Cierra el archivo */
        fclose(archi);
    }

    return existe;
}

char pagadoVenta(){

char control;

gotoxy(0,6);
printf("\n\n   Desea pagar ahora?");

flechasSN(&control,10,12);

return control;
}

void listaVentasMes(){

VENTA v;
int anio;
int mes;
int bandera = 1;
char c;

    FILE *archi = fopen(direccionVentas,"rb");

    if(archi == NULL){
        printf("No se pudo mostrar los datos.");
    }else {

        printf("\t\t\t\t==> LISTA DE VENTAS DEL MES <==\n");

        printf("\n\tIngrese el a%co: ", enie);
        scanf("%i", &anio);
        system("cls");

        while(existeAnioVenta(anio,&v)==0){


        printf("\t\t\t\t==> LISTA DE VENTAS DEL MES <==\n");
        printf("\n\tNo hay ningun a%co que concuerde, ingrese otro: ", enie);
        fflush(stdin);
        scanf("%i",&anio);
        system("cls");

        }

        printf("\t\t\t\t==> LISTA DE VENTAS DEL MES <==\n");

        printf("\n\tIngrese el mes: ");
        scanf("%i",&mes);
        system("cls");


        while(existeMesVenta(mes,&v)==0){

        printf("\t\t\t\t==> LISTA DE VENTAS DEL MES <==\n");
        printf("\n\tNo hay ningun mes que concuerde, ingrese otro: ");
        fflush(stdin);
        scanf("%i",&mes);
        system("cls");

        }

        system("cls");
        printf("\t\t\t\t==> LISTA DE VENTAS DEL MES <==\n");

        while(fread(&v,sizeof(VENTA),1,archi)>0){

            if(anio == v.anio && mes == v.mes){

                    if(v.anular == 'a'){
                    printf(RED"ID nro %i:\n"RESET, v.id);
                    estructuraMuestraVentaAnulada(v);
                    }else{
                    printf("ID nro %i:\n", v.id);
                    estructuraMuestraVenta(v);
                    }

            }
        }
    }

    printf("\nPRESION ESC PARA VOLVER.");

    while(bandera == 1){
            c = getch();

            if(c == 27){

                fclose(archi);
                bandera = 0;
            }
    }

}

int existeAnioVenta(int anio, VENTA *v){

int existe;

FILE *archi = fopen(direccionVentas, "rb");

    if (archi == NULL) {
        existe = 0;

    } else {
        existe = 0;


        fread(&(*v), sizeof(*v), 1, archi);
        while (!feof(archi)) {
            if ((*v).anio == anio) {
                existe = 1;
                break;
            }
            fread(&(*v), sizeof(*v), 1, archi);
        }

        /* Cierra el archivo */
        fclose(archi);
    }

    return existe;
}

int existeMesVenta(int mes, VENTA *v){

int existe;

FILE *archi = fopen(direccionVentas, "rb");

    if (archi == NULL) {
        existe = 0;

    } else {
        existe = 0;


        fread(&(*v), sizeof(*v), 1, archi);
        while (!feof(archi)) {
            if ((*v).mes == mes) {
                existe = 1;
                break;
            }
            fread(&(*v), sizeof(*v), 1, archi);
        }

        /* Cierra el archivo */
        fclose(archi);
    }

    return existe;
}

void promedioVentasMes(){

VENTA v;

int anio;
int mes;
int dia=1;
int matriz[7][4];
int bandera = 1;
int contador = 0;
float pvp;
float sumaPvP = 0;
float promedioDia = 0;
float z ;
char c;

    FILE *archi = fopen(direccionVentas,"rb");

    if(archi == NULL){
        printf("No se pudo mostrar los datos.");
    }else {

        printf("\t\t\t==> PROMEDIO DE VENTAS DEL MES <==\n");

        printf("\n\tIngrese el a%co: ", enie);
        scanf("%i", &anio);
        system("cls");

        while(existeAnioVenta(anio,&v)==0){


        printf("\t\t\t==> PROMEDIO DE VENTAS DEL MES <==\n");
        printf("\n\tNo hay ningun a%co que concuerde, ingrese otro: ", enie);
        fflush(stdin);
        scanf("%i",&anio);
        system("cls");

        }

        printf("\t\t\t==> PROMEDIO DE VENTAS DEL MES <==\n");

        printf("\n\tIngrese el mes: ");
        scanf("%i",&mes);
        system("cls");


        while(existeMesVenta(mes,&v)==0){

        printf("\t\t\t==> PROMEDIO DE VENTAS DEL MES <==\n");
        printf("\n\tNo hay ningun mes que concuerde, ingrese otro: ");
        fflush(stdin);
        scanf("%i",&mes);
        system("cls");

        }

        system("cls");
        printf("\t\t\t==> PROMEDIO DE VENTAS DEL MES <==\n");

    for(int i=0;i<7;i++){
        for(int j=0;j<4;j++){

                if(dia<=28){
                    contador = 0;
                    while(fread(&v,sizeof(VENTA),1,archi)>0){

                        if(anio == v.anio && mes == v.mes){

                            if(v.dia==dia){

                                contador++;
                        }

                    }
                }
                rewind(archi);
                matriz[i][j] = contador;
                dia++;
                }

        }
    }

    printf("\n\n");
    mostrarMatriz(matriz);
    z = promedioVentasMatriz(matriz);
    printf("\n\nEl promedio de ventas del mes es %.2f", z);

    }

    printf("\n\nPRESION ESC PARA VOLVER.");

    while(bandera == 1){
            c = getch();

            if(c == 27){

                fclose(archi);
                bandera = 0;
            }
    }



}

void mostrarMatriz(int arreglo [7][4]){
int i,j;

	for (i=0;i<7;i++)
	{
		for (j=0;j<4;j++)
		{
			printf("| %d |",arreglo[i][j]);
		}
	printf("\n");
	}

}

float promedioVentasMatriz(int matriz[7][4]){

int x = 0;
float prom = 0;

            for(int i=0;i<7;i++){
                    for(int j=0;j<4;j++){

                        x = x + matriz[i][j];

                            }
                    }

        prom = (float)x / (float)28;

 return prom;
}















