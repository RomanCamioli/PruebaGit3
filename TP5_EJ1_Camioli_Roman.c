#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//pasar por valor=pasar una copia del valor en bytes que ocupa una variable
//pasar por referencia= pasamos la direccion de memoria de una variable para no pasar la copia y modificar solo la copia, modificamos la variable original

struct Imagenes{
	char nombre[20], codigo[10], tipo_archivo[6];
	float precio;
	int tamano_bytes;
	struct Imagenes *siguiente;
}primera={"Img1\n","001\n","png\n",100.50, 64};

struct Imagenes *agregar_nodo(struct Imagenes *nodo);
struct Imagenes *eliminar_nodo(struct Imagenes *pimagen, int cant);
void mostrar_lista(struct Imagenes *nodoactual);
void guardar_archivo(struct Imagenes *pimagen, int cant, FILE *archivo);
void mostrar_archivo(struct Imagenes *pimagen, int cant, FILE *archivo);
void modificar_datos(struct Imagenes *pimagen, int cant, int selec_img);
void busqueda(struct Imagenes *pimagen, int cant);


int main() {
	int menu=0, total=0;
	struct Imagenes *inicio, *ultimo;
	FILE *Archivo_imagnes;
	inicio = &primera;
	ultimo = inicio;
	
	do {
		printf("\nINFO: \n [1]: Agregar nodo\n [2]: Eliminar nodo\n [3]: Mostrar Lista\n [4]: Grabar Archivo\n [5]: Ver Archivo\n [6]: Busqueda\n [7]:Salir	");
		scanf("%d", &menu);
		fflush(stdin);
	switch(menu)
	{

case 1:
	ultimo = agregar_nodo(ultimo);
	total++;
	break;
	
case 2:
	inicio = eliminar_nodo(inicio, total);
	total--;
	break;
	
case 3:
	mostrar_lista(inicio);
	break;

case 4:
	guardar_archivo(inicio, total, Archivo_imagnes);
	break;
	
case 5:
	mostrar_archivo(inicio, total, Archivo_imagnes);
	break;
	
case 6:
	busqueda(inicio, total);
	break;

}//LLAVE switch
	} while ((menu >= 1) && (menu <7));
	
	return 0;
}

struct Imagenes *agregar_nodo(struct Imagenes *nodo){
	
	struct Imagenes *nuevonodo = (struct Imagenes *) malloc(sizeof(struct Imagenes));
	
	printf("\nIngrese el NOMBRE de la imagen ");
	fgets((nuevonodo)->nombre,19,stdin);
	
	printf("Ingrese el CODIGO de la imagen ");
	fgets((nuevonodo)->codigo,9,stdin);
	
	printf("Ingrese la EXTENSION de la imagen (tipo de archivo 'png, jpg, tiff') ");
	fgets((nuevonodo)->tipo_archivo,6,stdin);
	
	printf("Ingrese el TAMANO en BYTES de la imagen ");
	scanf("%d",&(nuevonodo)->tamano_bytes);
	fflush(stdin);
	
	printf("Ingrese el PRECIO de la imagen ");
	scanf("%f",&(nuevonodo)->precio);
	fflush(stdin);
	
	nodo->siguiente = nuevonodo;
	nuevonodo->siguiente = NULL;
	
	return nuevonodo;
}
	
struct Imagenes *eliminar_nodo(struct Imagenes *nodo, int cant){
	
	int selec, i;
	struct Imagenes *temp, *aux = nodo;
	
	do {
		printf("Que nodo desea elminiar? (de 0 a %d) ", cant);
		scanf("%d",&selec);
		fflush(stdin);
	} while (selec > cant);
	
	for(i=0; i<(selec-1) ; i++){//posicionamos el nodo anterior al que queremos eliminar
		nodo = nodo->siguiente;
	}
	if(selec == 0){//si queremos borrar el primer nodo...
		temp = nodo;//apuntamos al primer nodo
		nodo = nodo->siguiente;//desplazamos el nodo al segundo
		free(temp);
		return nodo;//devolvemos el nuevo inicio
	}
	temp = nodo->siguiente;//temporal apunta al que queremos eliminar
	
	nodo->siguiente = temp->siguiente;
	//el nodo anterior al que queremos eliminar apunta al nodo siguiente del que queremos eliminar
	
	free(temp);//liberamos memoria
	
	printf("\nNodo [%d] se borró correctamente",selec);
	return aux;
}
	

void mostrar_lista(struct Imagenes *nodoactual){
	do {
		printf("\nNombre imagen:%s", nodoactual->nombre);
		printf("Codigo imagen:%s", nodoactual->codigo);
		printf("Tipo de imagen:%s",nodoactual->tipo_archivo);
		printf("Tamano de imagen:%d\n",nodoactual->tamano_bytes);
		printf("Precio Imagen=%f\n", nodoactual->precio);
		nodoactual = nodoactual->siguiente; 
	} while (nodoactual != NULL);
}
	
void modificar_datos(struct Imagenes *pimagen, int cant, int selec_img){
	
	int seleccion,aux;
	
	do {
		printf("\nINFO: \n [1]: Modificar NOMBRE\n [2]: Modificar CODIGO\n [3]: Modificar TIPO\n [4]: Modificar TAMANO\n [5]: Modificar PRECIO	");
		scanf("%d", &aux);
		fflush(stdin);
	} while (aux < 1 || aux > 5 );
	
	do {
		printf("\nQue imagen desea modificar? (del 0 a %d) ",cant-1);
		scanf("%d",&seleccion);
		fflush(stdin);
	} while (seleccion > cant || seleccion < 0);
	
	switch(aux){
	case 1:
		printf("Ingrese el nuevo nombre para la imagen[%d] ",seleccion+1);
		fgets((pimagen+seleccion)->nombre,19,stdin);
		break;
		
	case 2:
		printf("Ingrese el nuevo codigo para la imagen[%d] ",seleccion+1);
		fgets((pimagen+seleccion)->codigo,9,stdin);
		break;
		
	case 3:
		printf("Ingrese el nuevo tipo archivo para la imagen[%d] ",seleccion+1);
		fgets((pimagen+seleccion)->tipo_archivo,6,stdin);
		break;
		
	case 4:
		printf("Ingrese el nuevo tamaño para la imagen[%d] ",seleccion+1);
		scanf("%d",&(pimagen+seleccion)->tamano_bytes);
		fflush(stdin);
		break;
		
	case 5:
		printf("Ingrese el nuevo precio para la imagen[%d] ",seleccion+1);
		scanf("%f",&(pimagen+seleccion)->precio);
		fflush(stdin);
		break;
	}
	
}
	
void busqueda(struct Imagenes *nodo, int cant){
	
	char nombre_aux[20],codigo_aux[10],extension_aux[6];
	int busqueda=0, tamano_aux, precio_aux, i=0, validador = 0, seleccion;
	struct Imagenes *aux = nodo;
	
	do {
		printf("\nINFO: \n [1]: Buscar por NOMBRE\n [2]: Buscar CODIGO\n [3]: Buscar TIPO\n [4]: Buscar TAMANO\n [5]: Buscar PRECIO	");
		scanf("%d", &busqueda);
		fflush(stdin);
	} while (busqueda < 1 || busqueda > 5 );
	
	switch(busqueda){
	case 1:
		printf("Ingrese el nombre para la busqueda ");
		fgets(nombre_aux,19,stdin);
		validador = 0;
		
		while(validador == 0 && nodo != NULL) {
			if(strcmp(nombre_aux,(nodo)->nombre) == 0){
				printf("\nLa imagen fue encontrada en la imagen [%d]",i+1);
				validador = 1;
				break;
			}
			else{
				printf("\nNo se encontro la imagen.");
				nodo = nodo->siguiente;
				i++;
			}
			}
		break;

	case 2:
		printf("Ingrese el codigo para la busqueda ");
		fgets(codigo_aux,9,stdin);
		
		validador = 0;
		
		while(validador == 0 && nodo != NULL) {
		if(strcmp(codigo_aux,(nodo)->codigo) == 0){
		printf("\nLa imagen fue encontrada en la imagen [%d]",i+1);
		validador = 1;
		break;
		}
		else{
			printf("\nNo se encontro la imagen.");
			nodo = nodo->siguiente;
			i++;
		}
		}
		break;
		
	case 3:
		printf("Ingrese la extension para la busqueda ");
		fgets(extension_aux,19,stdin);
		validador = 0;
		
		while(validador == 0 && nodo != NULL) {
		if(strcmp(extension_aux,(nodo)->tipo_archivo) == 0){
		printf("\nLa imagen fue encontrada en la imagen [%d]",i+1);
		break;
		}
		else{
			printf("\nNo se encontro la imagen.");
			nodo = nodo->siguiente;
			i++;
		}
		}
		break;
		
	case 4://tamano cambiar a v2
		printf("\nINFO: \n [1]: Buscar MAYOR A X(tamano)\n [2]: Buscar MENOR a X(tamano) ");
		scanf("%d", &seleccion);
		fflush(stdin);
		switch(seleccion){
			
		case 1:
			printf("Ingrese el parametro a definir ");
			scanf("%d", &tamano_aux);
			while( nodo != NULL){
				if( nodo->tamano_bytes > tamano_aux){
					printf("\nLa imagen fue encontrada en la imagen [%d]",i+1);
					nodo = nodo->siguiente;
				}
				else{
					i++;
					nodo = nodo->siguiente;
				}
			}
			break;
		case 2:
			printf("Ingrese el parametro a definir ");
			scanf("%d", &tamano_aux);
			while( nodo != NULL){
				if( nodo->tamano_bytes < tamano_aux){
					printf("\nLa imagen fue encontrada en la imagen [%d]",i+1);
					nodo = nodo->siguiente;
				}
				else{
					i++;
					nodo = nodo->siguiente;
				}
			}
			break;	  
		}
		break;
		
	case 5:
		printf("Ingrese el precio para la busqueda ");
		scanf("%d" ,&precio_aux);
		fflush(stdin);
		validador = 0;
		
		while(validador == 0 && nodo != NULL) {
		if( precio_aux == (nodo)->precio){
		printf("\nLa imagen fue encontrada en la imagen [%d]",i+1);
		validador = 1;
		break;
		}
		else{
			printf("\nNo se encontro la imagen.");
			nodo = nodo->siguiente;
			i++;
		}
		
		}
		break;
	}	
}/*realizar búsquedas: por cualquiera de los miembros de la estructura imagen (tipo
	archivo, nombre, etc). En el caso del tamaño del archivo, especificar si se busca
	mayor a X tamaño (ingresado por teclado) o menor a X o un valor exacto de
	tamaño*/



void guardar_archivo(struct Imagenes *nodo, int cant, FILE *archivo){
	
	archivo = fopen("Imagenes.bin","ab");
	if(archivo != NULL){
		printf("\nApertura exitosa\n");
	}
	else{
		printf("\nError al abrir o crear archivo");
		exit(1);
	}
	while(nodo != NULL) {
		fwrite(nodo, sizeof(struct Imagenes), 1, archivo);
		/** se escriben en el archivo los datos ingresados en el menu**/
		nodo = nodo->siguiente;
	}
	printf("Archivo guardado con exito!!\n");
	fclose(archivo);
}

void mostrar_archivo(struct Imagenes *nodo, int cant, FILE *archivo){
	
	int i=0;
	const int leer = 1;
	struct Imagenes stock_Binario;
	/** se declaran las imagenes binarias con la cant equivalente al tamano del archivo**/
	
	archivo= fopen("Imagenes.bin", "rb");
	
	if(archivo == NULL){
		printf("\nError al abrir archivo");
		return;
	}
	
	else{
		rewind(archivo);
		while( (fread(&stock_Binario, sizeof(struct Imagenes), leer, archivo)) == leer){
		/*fread devuelve la cantidad de elementos leidos con exito, si el numero devuelto es 
			distinto al numero entero ingresado en la funcion fread significa que hay un error
			para encontrar el feof (size_t fread...)  */
		printf("\nNombre imagen [%d]: %s",i+1, stock_Binario.nombre);
		printf("Codigo imagen [%d]: %s",i+1, stock_Binario.codigo);
		printf("Tipo de imagen [%d]: %s",i+1, stock_Binario.tipo_archivo);
		printf("Tamano imagen [%d]: %d\n",i+1, stock_Binario.tamano_bytes);
		printf("Precio imagen [%d]: %f\n",i+1, stock_Binario.precio);
		i++;
		}
	}
	fclose(archivo);
}
