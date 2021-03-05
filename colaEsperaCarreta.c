#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct colaEspCarreta{
	int idClienteEC;
	struct colaEspCarreta* siguiente;
} colaEspCarreta;

typedef struct PilaCarreta{
	int idCarreta;
	struct PilaCarreta* siguientePilaCarreta;
	
} PilaCarreta;

typedef struct PilaCarreta2{
	int idCarreta2;
	struct PilaCarreta2* siguientePilaCarreta2;
	
} PilaCarreta2;

///COMPRAS/////////
typedef struct Compra{
	int IDCarretaCompra;
	int IDClienCompra;
	
	struct Compra* siguienteCliCompra;
} Compra;
//LISTA DE PAGOS
typedef struct ListaPago{
	int IDCarretaPago;
	int IDClienPago;
	struct ListaPago* siguienteListaPago;
} ListaPago;

//LISTA DE CAJAS
typedef struct Caja{
	int IDCaja;
	int turno;
	int tiempo;
	bool estado;
	int idClienteEnCaja;
	int idCarretaEnCaja;
	struct Caja* siguienteCaja;
	struct Caja* atrasCaja;
} Caja;


//Cola de Espera de Carretas
colaEspCarreta* primero = NULL;
colaEspCarreta* ultimo = NULL;
void insertarcolaEspCarreta();
void mostarColaEspCarreta();
bool HayClientesEsperando();
void eliminarcolaEspCarreta();
void iniciarSimulacion();
int cantEsperaCarreta;

//Pila de Carretas
PilaCarreta* primeroPilCar = NULL;
PilaCarreta* ultimoPilaCar = NULL;
PilaCarreta2* primeroPilCar2 = NULL;
PilaCarreta2* ultimoPilaCar2 = NULL;
void insertarPilaCarreta();
void insertarPilaCarreta2();
void mostarPilaCarreta1();
void mostarPilaCarreta2();
void eliminarPilaCarreta();
void eliminarPilaCarreta2();
void abrirEscrituraArchivo();
void cerrarEscrituraArchivo();
int cantPilCarreta1;
int cantPilCarreta2;

////CLIENTES COMPRANDO
Compra* primeroCliCompra = NULL;
Compra* ultimoCliCompra = NULL;
void insertarCompra();
void insertarCompraS();
void desplegarListaCompra();
void eliminarCompra();
int cantCliCompra;
int numeroRandom1;
int numeroRandom2;

///CONTADORES
int idCompraTot=0;
char *enter;
int idClienTot=0;
int cantTotCarreta=0;
int cantTotCaja=0;
////LISTA PAGOOO
ListaPago* primeroListaPago = NULL;
ListaPago* ultimoListaPago = NULL;
void insertarListaPago();
void insertarListaPagoS();
void desplegarListaPago();
void eliminarListaPago();
int cantListaPago=0;
bool HayCarretasenpila1();
bool HayCarretasenpila2();
bool HayCajaDisponible();
///caja
Caja* primeroCaja = NULL;
Caja* ultimoCaja = NULL;
void insertarCaja();
void buscarCaja();
void MostrarListaCaja();
void modificarCaja();
void modificarCajaS();
int cantCaja;
int apt=0;
int cDispo;
int bandera=0;
int pasos=1;
//crear un archivo 
FILE *archivo;
//crear un archivo
int main(){
	printf("****************MINI MARKET MANAGER******************\n");
	iniciarSimulacion();
	return 0;
}
//inicia la simulacion
void iniciarSimulacion(){
	colaEspCarreta *esperanCarreta;
	PilaCarreta *pilaCarreta1;
	PilaCarreta2 *pilaCarreta2;
	Compra *compras;
	ListaPago *listaPay;
	Caja* cajeras;
	abrirEscrituraArchivo(0);
	int salir=0,tec=0;


	printf("\n******Ingrese la cantidad de clientes en la cola de espera de carretas:******\n");
	scanf(" %d", &cantEsperaCarreta);	
	insertarcolaEspCarreta(esperanCarreta,cantEsperaCarreta+1);
	mostarColaEspCarreta(esperanCarreta);
	//SOLICITANDO INFORMACION DE PILAS DE CARRETAS
	printf("\n******Ingrese la cantidad de CARRETAS EN LA PILA1******\n");
	scanf(" %d", &cantPilCarreta1);
	insertarPilaCarreta(pilaCarreta1, cantPilCarreta1,1,1);
	mostarPilaCarreta1(pilaCarreta1,1);
	
	printf("\n******Ingrese la cantidad de CARRETAS EN LA PILA2******\n");
	scanf(" %d", &cantPilCarreta2);	
	insertarPilaCarreta2(pilaCarreta2, cantPilCarreta2,cantPilCarreta1+1,2);
	mostarPilaCarreta2(pilaCarreta2,2);
	//SOLICITANDO INFORMACION DE CLIENTES COMPRANDO
	printf("\n******Ingrese la cantidad de CLIENTES COMPRANDO****** \n");
	scanf(" %d", &cantCliCompra);	
	insertarCompra(compras, cantCliCompra,idClienTot);
	desplegarListaCompra();

	printf("\n******Ingrese la cantidad de CLIENTES en la COLA DE PAGOS****** \n");
	scanf(" %d", &cantListaPago);	
	insertarListaPago(listaPay, cantListaPago, idClienTot);
	desplegarListaPago();
	
	printf("\n******Ingrese la cantidad de Cajas****** \n");
	scanf(" %d", &cantCaja);	
	insertarCaja(cajeras,cantCaja);
	MostrarListaCaja(cajeras);
	cerrarEscrituraArchivo();
	printf("\nSe ha graficado con los datos iniciales \n");
	while(bandera == 0 || bandera ==1){
	printf("\n***-*-*-*-*-*-*-*-*- PASO %d*-*-*-*-*-*-*-*-***\n",pasos);
	pasos++;
	printf("Ingrese el numero: 0 para CONTINUAR \n 1 para GRAFICAR Y CONTINUAR \n 9 para SALIR :  ");
	scanf(" %d", &bandera);
	HayCarretasenpila1(pilaCarreta1);
	
	if( HayClientesEsperando(esperanCarreta)&&HayCarretasenpila1(pilaCarreta1)){
	
		eliminarPilaCarreta(pilaCarreta1);
		eliminarcolaEspCarreta(esperanCarreta,compras);
		
	} 
	else {
		if(HayClientesEsperando(esperanCarreta) && HayCarretasenpila2(pilaCarreta2)){
			eliminarPilaCarreta2(pilaCarreta2);
			eliminarcolaEspCarreta(esperanCarreta,compras);
		}
	}
	
	
		numeroRandom1 = rand () % ((idClienTot+15)-1+1) + 1;   // Este está entre M y N
		numeroRandom2 = rand () % ((idClienTot+15)-1+1) + 1;   // Este está entre M y N
		eliminarCompra(compras,numeroRandom1,listaPay);
		eliminarCompra(compras,numeroRandom2,listaPay);
		
	if(HayCajaDisponible(cajeras) ){
		eliminarListaPago(listaPay,cajeras);
		
	}
	int numRandomSalidaCaja;
	numRandomSalidaCaja = rand () % ((cantTotCaja+10)-1+1) + 1;   // Este está entre M y N
	modificarCajaS(cajeras, numRandomSalidaCaja);
	
	if(bandera==1){ 
	abrirEscrituraArchivo(pasos);
	mostarColaEspCarreta(esperanCarreta);
	mostarPilaCarreta1(pilaCarreta1,1);
	mostarPilaCarreta2(pilaCarreta2,2);
	desplegarListaCompra();
	desplegarListaPago();
	MostrarListaCaja(cajeras);
	cerrarEscrituraArchivo();
	}
	
	}
	
	printf("\n");

}
bool HayClientesEsperando(colaEspCarreta* actual){
	actual = (colaEspCarreta*) malloc(sizeof(colaEspCarreta));
	actual = primero;
	colaEspCarreta* anterior = (colaEspCarreta*) malloc(sizeof(colaEspCarreta));
	anterior = NULL;
	if(primero != NULL){
	return true;
	} else{
	return false;
	}
}

bool HayCarretasenpila1(PilaCarreta* actual){
	actual = (PilaCarreta*) malloc(sizeof(PilaCarreta));
	actual = primeroPilCar;
	PilaCarreta* anterior = (PilaCarreta*) malloc(sizeof(PilaCarreta));
	anterior = NULL;
	if(primeroPilCar != NULL){
	return true;
	}else{
	return false;
	}
}
bool HayCarretasenpila2(PilaCarreta2* actual){
	actual = (PilaCarreta2*) malloc(sizeof(PilaCarreta2));
	actual = primeroPilCar2;
	PilaCarreta2* anterior = (PilaCarreta2*) malloc(sizeof(PilaCarreta2));
	anterior = NULL;
	int encontrado=0;
	//int PilaCarretaBuscado = 0, encontrado = 0;
	//printf(" Ingrese el valor del PilaCarreta a Buscar para Eliminar: ");
	//scanf("%d", &PilaCarretaBuscado);
	if(primeroPilCar2 != NULL){
	return true;
	}
	else{
	return false;
	}
}
bool HayCajaDisponible(Caja* actual){
	actual = (Caja*) malloc(sizeof(Caja));
	actual = primeroCaja;
	int encontrado = 0;

	if(primeroCaja!=NULL){
		do{
			if(actual->estado){
			cDispo=actual->IDCaja;
				//printf("\n Caja con el ID:  %d  Encontrado\n", cajaBuscada);
				encontrado = 1;
			}
			actual = actual->siguienteCaja;
		}while(actual != primeroCaja && encontrado != 1);
		if(encontrado == 0){
			return true;
		}
	}else{
		return false;
	}
}



void insertarcolaEspCarreta(colaEspCarreta* nuevo1,int n){

for(int i=1;i<n;i++){

	nuevo1 = (colaEspCarreta*) malloc(sizeof(colaEspCarreta));
	//printf(" Ingrese el idClienteEC que contendra el nuevo colaEspCarreta: ");
	//scanf("%d", &nuevo->idClienteEC);
	idClienTot++;
	nuevo1->idClienteEC=i;
	if(primero == NULL){
		primero = nuevo1;
		primero->siguiente = NULL;
		ultimo = nuevo1;
	}else{
		ultimo->siguiente = nuevo1;
		nuevo1->siguiente = NULL;
		ultimo = nuevo1;
	}
	printf("\n Se ha ingresado el cliente: %d a la cola de espera de carretas",i);
	
	cantEsperaCarreta=i;
}

}


//elimina el primero de la cola
void eliminarcolaEspCarreta(colaEspCarreta* actual,Compra* compra){
	actual = (colaEspCarreta*) malloc(sizeof(colaEspCarreta));
	actual = primero;
	colaEspCarreta* anterior = (colaEspCarreta*) malloc(sizeof(colaEspCarreta));
	anterior = NULL;
	int encontrado=0;
	//int colaEspCarretaBuscado = 0, encontrado = 0;
	//printf(" Ingrese el valor del colaEspCarreta a Buscar para Eliminar: ");
	//scanf("%d", &colaEspCarretaBuscado);
	if(primero != NULL){
		
		while(actual != NULL && encontrado != 1){
			
			if(actual->idClienteEC == ultimo->idClienteEC){		
				if(actual == primero){
					primero = primero->siguiente;
				}else if(actual == ultimo){
					anterior->siguiente = NULL;
					ultimo = anterior;
				}else{
					anterior->siguiente = actual->siguiente;
				}
				//printf("\n El colaEspCarreta eliminado con exito\n\n");
				insertarCompraS(compra,actual->idClienteEC, apt);
				encontrado = 1;
			}
			anterior = actual;	
			actual = actual->siguiente;
		}
		if(encontrado==0){
			printf("\n colaEspCarreta no Encontrado\n\n");
		}else{
			free(anterior);
		}
	}else{
		printf("\n La COLA DE ESPERA DE CARRETAS ESTA VACIA\n\n");
	}
}


void mostarColaEspCarreta(colaEspCarreta* actual1){
	actual1 = (colaEspCarreta*) malloc(sizeof(colaEspCarreta));
	actual1 = primero;
	if(primero != NULL){
		fprintf(archivo," Cola_de_espera_de_Carreta-> Cliente%d; \n",actual1->idClienteEC);
		while(actual1 != NULL){
			//printf("\n %d", actual1->idClienteEC);
			if(actual1->siguiente != NULL){
			fprintf(archivo,"\n Cliente%d -> Cliente%d;",actual1->idClienteEC,(actual1->siguiente)->idClienteEC);
			
			}
			actual1 = actual1->siguiente;
			//int a=actual1->idClienteEC;
			//(actual1->siguiente)->idClienteEC;	

		}
		//system("dot -Tpng miarchivo.txt -o miarchivo.png");
		printf("\n");
	}else{
		printf("\n La cola no existe\n\n");
	}
}



//*********PILA DE CARRETA************
void insertarPilaCarreta(PilaCarreta* nuevo, int n, int initial, int NoPila){

	
	for(int i=initial;i<(n+initial);i++){
	cantTotCarreta++;
	//printf(" Ingrese el idCarreta que contendra el nuevo PilaCarreta: ");
	//scanf("%d", &nuevo->idCarreta);
	nuevo = (PilaCarreta*) malloc(sizeof(PilaCarreta));
	nuevo->idCarreta=i;
	if(primeroPilCar == NULL){
		primeroPilCar = nuevo;
		primeroPilCar->siguientePilaCarreta = NULL;
		ultimoPilaCar = nuevo;
	}else{
		ultimoPilaCar->siguientePilaCarreta = nuevo;
		nuevo->siguientePilaCarreta = NULL;
		ultimoPilaCar = nuevo;
	}
	printf("\n Se ha agregado la Carreta %d en la PILA %d\n",i,NoPila);
	}
}
void insertarPilaCarreta2(PilaCarreta2* nuevo, int n, int initial, int NoPila){
	
	for(int i=initial;i<(n+initial);i++){
	cantTotCarreta++;
	//printf(" Ingrese el idCarreta que contendra el nuevo PilaCarreta: ");
	//scanf("%d", &nuevo->idCarreta);
	nuevo = (PilaCarreta2*) malloc(sizeof(PilaCarreta2));
	nuevo->idCarreta2=i;
	if(primeroPilCar2 == NULL){
		primeroPilCar2 = nuevo;
		primeroPilCar2->siguientePilaCarreta2 = NULL;
		ultimoPilaCar2 = nuevo;
	}else{
		ultimoPilaCar2->siguientePilaCarreta2 = nuevo;
		nuevo->siguientePilaCarreta2 = NULL;
		ultimoPilaCar2 = nuevo;
	}
	printf("\n Se ha agregado la Carreta %d en la PILA %d\n",i,NoPila);
	}
}
//elimina el primeroPilCar de la cola
void eliminarPilaCarreta(PilaCarreta* actual){
	actual = (PilaCarreta*) malloc(sizeof(PilaCarreta));
	actual = primeroPilCar;
	PilaCarreta* anterior = (PilaCarreta*) malloc(sizeof(PilaCarreta));
	anterior = NULL;
	int encontrado=0;
	//int PilaCarretaBuscado = 0, encontrado = 0;
	//printf(" Ingrese el valor del PilaCarreta a Buscar para Eliminar: ");
	//scanf("%d", &PilaCarretaBuscado);
	if(primeroPilCar != NULL){
		
		while(actual != NULL && encontrado != 1){
			
			if(actual->idCarreta == ultimoPilaCar->idCarreta){		
				if(actual == primeroPilCar){
					primeroPilCar = primeroPilCar->siguientePilaCarreta;
				}else if(actual == ultimoPilaCar){
					anterior->siguientePilaCarreta = NULL;
					ultimoPilaCar = anterior;
				}else{
					anterior->siguientePilaCarreta = actual->siguientePilaCarreta;
				}
				apt=actual->idCarreta;
				//printf("\n El PilaCarreta eliminado con exito\n");
				encontrado = 1;
			}
			anterior = actual;	
			actual = actual->siguientePilaCarreta;
		}
		if(encontrado==0){
			printf("\n No se ha encontrado la carreta para eliminarla\n");
		}else{
			free(anterior);
		}
	}else{
		printf("\n No Hay carretas disponibles\n");
	}
}
void eliminarPilaCarreta2(PilaCarreta2* actual){
	actual = (PilaCarreta2*) malloc(sizeof(PilaCarreta2));
	actual = primeroPilCar2;
	PilaCarreta2* anterior = (PilaCarreta2*) malloc(sizeof(PilaCarreta2));
	anterior = NULL;
	int encontrado=0;
	//int PilaCarretaBuscado = 0, encontrado = 0;
	//printf(" Ingrese el valor del PilaCarreta a Buscar para Eliminar: ");
	//scanf("%d", &PilaCarretaBuscado);
	if(primeroPilCar2 != NULL){
		
		while(actual != NULL && encontrado != 1){
			
			if(actual->idCarreta2 == ultimoPilaCar2->idCarreta2){		
				if(actual == primeroPilCar2){
					primeroPilCar2 = primeroPilCar2->siguientePilaCarreta2;
				}else if(actual == ultimoPilaCar2){
					anterior->siguientePilaCarreta2 = NULL;
					ultimoPilaCar2 = anterior;
				}else{
					anterior->siguientePilaCarreta2 = actual->siguientePilaCarreta2;
				}
				//printf("\n El PilaCarreta eliminado con exito\n");
				encontrado = 1;
			}
			anterior = actual;	
			actual = actual->siguientePilaCarreta2;
		}
		if(encontrado==0){
			printf("\n No se ha encontrado la carreta para eliminarla\n");
		}else{
			free(anterior);
		}
	}else{
		printf("\n No Hay carretas disponibles\n");
	}
}

void mostarPilaCarreta1(PilaCarreta* actuall, int n){
	actuall = (PilaCarreta*) malloc(sizeof(PilaCarreta));
	actuall = primeroPilCar;
	if(primeroPilCar != NULL){
		fprintf(archivo," Pila_Carreta%d-> Carreta%d; \n",n,actuall->idCarreta);
		while(actuall != NULL){
			
			if(actuall->siguientePilaCarreta != NULL){
			//printf("\n Carreta%d \n",actuall->idCarreta);
			fprintf(archivo,"\n Carreta%d -> Carreta%d; ID=%d",actuall->idCarreta,(actuall->siguientePilaCarreta)->idCarreta,n);
			
			}
			actuall = actuall->siguientePilaCarreta;
		}
	}else{
		printf("\n La cola no existe\n\n");
	}
}
void mostarPilaCarreta2(PilaCarreta2* actuall, int n){
	actuall = (PilaCarreta2*) malloc(sizeof(PilaCarreta2));
	actuall = primeroPilCar2;
	if(primeroPilCar2 != NULL){
		fprintf(archivo," Pila_Carreta%d-> Carreta%d; \n",n,actuall->idCarreta2);
		while(actuall != NULL){
			
			if(actuall->siguientePilaCarreta2 != NULL){
			//sprintf("\n Carreta%d \n",actuall->idCarreta2);
			fprintf(archivo,"\n Carreta%d -> Carreta%d; ID=%d",actuall->idCarreta2,(actuall->siguientePilaCarreta2)->idCarreta2,n);
			
			}
			actuall = actuall->siguientePilaCarreta2;
		}
	}else{
		fprintf(archivo," Pila_Carreta->Vacia ; \n");
		printf("\n La cola no existe\n\n");
	}
}
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
void insertarCompra(Compra* nuevo, int cant, int tam){

for(int i=tam+1;i<(tam+cant)+1;i++){
	nuevo = (Compra*) malloc(sizeof(Compra));
	idClienTot++;
	cantTotCarreta++;
	//defino los atributos de la lista compras con un ID y el cliente que contiene
	nuevo->IDCarretaCompra=cantTotCarreta;
	nuevo->IDClienCompra=i;
	//
	if(primeroCliCompra==NULL){
		primeroCliCompra = nuevo;
		primeroCliCompra->siguienteCliCompra = primeroCliCompra;
		ultimoCliCompra = primeroCliCompra;
	}else{
		ultimoCliCompra->siguienteCliCompra = nuevo;
		nuevo->siguienteCliCompra = primeroCliCompra;
		ultimoCliCompra = nuevo;
	}
	printf("\n El CLIENTE%d con CARRETA%d esta en LISTA DE COMPRAS",nuevo->IDClienCompra,nuevo->IDCarretaCompra);

	}
}

void insertarCompraS(Compra* nuevo,int IDclientee, int IDcarretaa){

	nuevo = (Compra*) malloc(sizeof(Compra));
	
	//defino los atributos de la lista compras con un ID y el cliente que contiene
	nuevo->IDCarretaCompra=IDcarretaa;
	nuevo->IDClienCompra=IDclientee;
	//
	if(primeroCliCompra==NULL){
		primeroCliCompra = nuevo;
		primeroCliCompra->siguienteCliCompra = primeroCliCompra;
		ultimoCliCompra = primeroCliCompra;
	}else{
		ultimoCliCompra->siguienteCliCompra = nuevo;
		nuevo->siguienteCliCompra = primeroCliCompra;
		ultimoCliCompra = nuevo;
	}
	printf("\n El CLIENTE%d toma la CARRETA%d y entra a LISTA DE COMPRAS",nuevo->IDClienCompra,nuevo->IDCarretaCompra);
	
	
}


void eliminarCompra(Compra* actual,int num,ListaPago* lstPago){
	actual = (Compra*)malloc(sizeof(Compra));
	actual = primeroCliCompra;
	Compra* anterior = (Compra*)malloc(sizeof(Compra));
	anterior = NULL;
	int CompraBuscado = 0, encontrado = 0;
	//printf(" Ingrese el valor de Compra a Buscar para Eliminar: ");
	//scanf("%d",&CompraBuscado);
	if(primeroCliCompra!=NULL){
		do{
			if(actual->IDClienCompra == num){
				//printf("\n Compra con el IDCompra ( %d ) Encontrado", CompraBuscado);
				if(actual==primeroCliCompra){
					primeroCliCompra = primeroCliCompra->siguienteCliCompra;
					ultimoCliCompra->siguienteCliCompra = primeroCliCompra;
				}else if(actual==ultimoCliCompra){
					anterior->siguienteCliCompra  = primeroCliCompra;
					ultimoCliCompra = anterior;
				}else{
					anterior->siguienteCliCompra = actual->siguienteCliCompra;
				}
				printf("\n El CLIENTE %d con CARRETA %d HA SALIDO DE LA LISTA COMPRAS",actual->IDClienCompra,actual->IDCarretaCompra );		
				insertarListaPagoS(lstPago,actual->IDClienCompra,actual->IDCarretaCompra);
				encontrado = 1;
			}
			anterior = actual;
			actual = actual->siguienteCliCompra;
		}while(actual!=primeroCliCompra && encontrado!=1);
		
		if(encontrado==0){
			//printf("\n Compra no Encontrado\n\n");
		}else{
			free(anterior);
		}
	}else{
		
		printf("\n La lista se encuentra vaci\n\n");
	}
}
void desplegarListaCompra(){
	Compra* actual = (Compra*)malloc(sizeof(Compra));
	actual = primeroCliCompra;
	if(primeroCliCompra!=NULL){
	char coma ='"';
	fprintf(archivo," Lista_Compras-> %cCliente%d \nCarreta%d%c; \n",coma, actual->IDClienCompra,actual->IDCarretaCompra,coma);
		do{
		
			//printf("\nEl CLIENTE %d esta comprando con la CARRETA %d", actual->IDClienCompra,actual->IDCarretaCompra);
			if(actual->siguienteCliCompra != NULL){
			//printf("\n Cliente%d Carreta%d",actual->IDClienCompra,actual->IDCarretaCompra);
			fprintf(archivo,"\n %cCliente%d \nCarreta%d%c -> %cCliente%d \nCarreta%d%c; ID=3",coma,actual->IDClienCompra,actual->IDCarretaCompra,coma,coma,(actual->siguienteCliCompra)->IDClienCompra,(actual->siguienteCliCompra)->IDCarretaCompra,coma);
			fprintf(archivo,"\n %cCliente%d \nCarreta%d%c -> %cCliente%d \nCarreta%d%c; ID=3",coma,(actual->siguienteCliCompra)->IDClienCompra,(actual->siguienteCliCompra)->IDCarretaCompra,coma,coma,actual->IDClienCompra,actual->IDCarretaCompra,coma);
			
			}
			actual = actual->siguienteCliCompra;
		}while(actual!=primeroCliCompra);
	}else{
	fprintf(archivo," Lista_Compras-> Vacia ; \n");
		printf("\n NO HAY CLIENTES COMPRANDO\n\n");
	}
}
/////////LISTA PAGOOOOOOOOO///////////////
void insertarListaPago(ListaPago* nuevo,int cant, int initClie){
for(int i=initClie+1;i<(initClie+cant);i++){
	idClienTot++;
	cantTotCarreta++;
	nuevo = (ListaPago*) malloc(sizeof(ListaPago));
	//printf(" Ingrese el IDClienPago que contendra el nuevo ListaPago: ");
	//scanf("%d", &nuevo->IDClienPago);
	nuevo->IDClienPago=i;
	nuevo->IDCarretaPago=cantTotCarreta;
	if(primeroListaPago == NULL){
		primeroListaPago = nuevo;
		primeroListaPago->siguienteListaPago = NULL;
		ultimoListaPago = nuevo;
	}else{
		ultimoListaPago->siguienteListaPago = nuevo;
		nuevo->siguienteListaPago = NULL;
		ultimoListaPago = nuevo;
	}
	printf("\nSe ingreso a la lista de Pagos el CLiente%d con CARRETA%d",idClienTot,cantTotCarreta);
	}
}
void insertarListaPagoS(ListaPago* nuevo,int IDclientee, int IDcarretaa){

	nuevo = (ListaPago*) malloc(sizeof(ListaPago));
	nuevo->IDClienPago=IDclientee;
	nuevo->IDCarretaPago=IDcarretaa;
	if(primeroListaPago == NULL){
		primeroListaPago = nuevo;
		primeroListaPago->siguienteListaPago = NULL;
		ultimoListaPago = nuevo;
	}else{
		ultimoListaPago->siguienteListaPago = nuevo;
		nuevo->siguienteListaPago = NULL;
		ultimoListaPago = nuevo;
	}
	printf("\n el Cliente%d con CARRETA%d entra por fin a la lista de pagos",nuevo->IDClienPago,nuevo->IDCarretaPago);
	
}

void eliminarListaPago(ListaPago* actual, Caja* cajerass){
	actual = (ListaPago*) malloc(sizeof(ListaPago));
	actual = primeroListaPago;
	ListaPago* anterior = (ListaPago*) malloc(sizeof(ListaPago));
	anterior = NULL;
	int ListaPagoBuscado = 0, encontrado = 0;
	//printf(" Ingrese el valor del ListaPago a Buscar para Eliminar: ");
	//scanf("%d", &ListaPagoBuscado);
	if(primeroListaPago != NULL){
		
		while(actual != NULL && encontrado != 1){
			
			if(actual->IDClienPago == primeroListaPago->IDClienPago){		
				if(actual == primeroListaPago){
					primeroListaPago = primeroListaPago->siguienteListaPago;
				}else if(actual == ultimoListaPago){
					anterior->siguienteListaPago = NULL;
					ultimoListaPago = anterior;
				}else{
					anterior->siguienteListaPago = actual->siguienteListaPago;
				}
				printf("\n El CLIENTE %d con CARRETA %d HA SALIDO DE LA COLA DE PAGOS",actual->IDClienPago,actual->IDCarretaPago);
				modificarCaja(cajerass, cDispo,actual->IDClienPago,actual->IDCarretaPago);
				encontrado = 1;
			}
			anterior = actual;	
			actual = actual->siguienteListaPago;
		}
		if(encontrado==0){
			//printf("\n *****NO SE HA ENCONTRADO LA LISTA DE PAGOS*****");
		}else{
			free(anterior);
		}
	}else{
		//printf("\n ***** NO HAY CLIENTES ES LA LISTA DE PAGOS*****");
	}
}

void desplegarListaPago(){
	ListaPago* actual = (ListaPago*) malloc(sizeof(ListaPago));
	actual = primeroListaPago;
	if(primeroListaPago != NULL){
		char coma ='"';
		fprintf(archivo," Cola_Pago-> %cCliente%d \nCarreta%d%c ; \n",coma,actual->IDClienPago,actual->IDCarretaPago,coma);
		while(actual != NULL){
			if(actual->siguienteListaPago != NULL){
			fprintf(archivo," %cCliente%d \nCarreta%d%c -> %cCliente%d \nCarreta%d%c; ID=4\n",coma,actual->IDClienPago,actual->IDCarretaPago,coma,coma,(actual->siguienteListaPago)->IDClienPago,(actual->siguienteListaPago)->IDCarretaPago,coma);
			//printf("\nEl CLIENTE %d con CARRETA %d esta EN LISTA DE PAGOS", actual->IDClienPago,actual->IDCarretaPago);
			//printf("\n %d", actual->IDClienPago);
			}
			actual = actual->siguienteListaPago;
		}
	}else{
		fprintf(archivo," Cola_Pago->Vacia");
		printf("\n La cola no existe\n\n");
	}
}
/////////////////CAJA/////////////////////////
void insertarCaja(Caja* nuevo,int cant){
for(int i=1;i<cant+1;i++){
	int estad;
	cantTotCaja=i;
	nuevo = (Caja*) malloc(sizeof(Caja));
	
	printf(" Ingrese el estado de la Caja%d: \n 0) para Disponible\n 1) para OCUPADO ",i);
	
	scanf("%d",&estad);
	printf("\n Ingrese el numero de turnos de la Caja-%d: ",i);
	
	scanf("%d",&nuevo->turno);
	
	if(estad==0){
		nuevo->estado= true;
	} else{
		nuevo->estado= false;
	}
	nuevo->IDCaja= i;
	nuevo->tiempo= 0;
	
	nuevo->idClienteEnCaja=0;
	nuevo->idCarretaEnCaja=0;
	
	if(primeroCaja==NULL){
		primeroCaja = nuevo;
		primeroCaja->siguienteCaja = primeroCaja;
		ultimoCaja = primeroCaja;
		primeroCaja->atrasCaja = ultimoCaja;
	}else{
		ultimoCaja->siguienteCaja = nuevo;
		nuevo->siguienteCaja = primeroCaja;
		nuevo->atrasCaja = ultimoCaja;
		ultimoCaja = nuevo;
		primeroCaja->atrasCaja = ultimoCaja;
	}
	printf("Caja Ingresada\n");
	}
}
//Busca una caja por su ID
void buscarCaja(Caja* actual,int a){
	actual = (Caja*) malloc(sizeof(Caja));
	actual = primeroCaja;
	int cajaBuscada = 0, encontrado = 0;
	//printf(" Ingrese el dato del nodo a Buscar: ");
	//scanf("%d", &cajaBuscada);
	cajaBuscada=a;
	if(primeroCaja!=NULL){
		do{
			if(actual->IDCaja == cajaBuscada){
				printf("\n Caja con el ID:  %d  Encontrado\n", cajaBuscada);
				encontrado = 1;
			}
			actual = actual->siguienteCaja;
		}while(actual != primeroCaja && encontrado != 1);
		if(encontrado == 0){
			printf(" Caja no Encontrada\n");
		}
	}else{
		printf(" La Lista se encuentra vacia\n");
	}	
}


void MostrarListaCaja(Caja* actual){
	actual= (Caja*) malloc(sizeof(Caja));
	actual = primeroCaja;
	if(primeroCaja!=NULL){
	char coma ='"';
	fprintf(archivo," Lista_de_Cajas-> CAJA%d; ID=5",actual->IDCaja);
		do{
		if(actual->siguienteCaja != NULL){
			//fprintf(archivo," CAJA%d\n-> CAJA%d; ID=5\n",actual->IDCaja,(actual->siguienteCaja)->IDCaja);
			//printf("\nEl CLIENTE %d con CARRETA %d esta EN LISTA DE PAGOS", actual->IDClienPago,actual->IDCarretaPago);
			//printf("\n %d", actual->IDClienPago);
			if(actual->idClienteEnCaja==0){
			fprintf(archivo," CAJA%d-> CAJA%d; ID=5\n",actual->IDCaja,(actual->siguienteCaja)->IDCaja);
			} else {
			fprintf(archivo," %cCAJA%d\n Cliente%d con CARRETA%d%c-> %cCAJA%d\n Cliente%d con CARRETA%d%c; ID=5\n",coma,actual->IDCaja,actual->idClienteEnCaja,actual->idCarretaEnCaja,coma,coma,(actual->siguienteCaja)->IDCaja,(actual->siguienteCaja)->idClienteEnCaja,(actual->siguienteCaja)->idCarretaEnCaja,coma);
			
			}
			}
		
		
			printf(" %d %d \n", actual->IDCaja,actual->tiempo);
			actual = actual->siguienteCaja;
		}while(actual != primeroCaja);
	}else{
	fprintf(archivo," Lista_de_Cajas-> VACIA.; ID=5");
		printf(" La Lista se encuentra vacia\n\n");
	}
}
void modificarCaja(Caja* actual, int cDisp,int C,int K){
	actual = (Caja*) malloc(sizeof(Caja));
	actual = primeroCaja;
	int cajaBuscado = 0, encontrado = 0;
	
	if(primeroCaja!=NULL){
		do{
			if(actual->IDCaja == cDisp){

				actual->turno++;
				actual->estado=false;
				actual->idClienteEnCaja=C;
				actual->idCarretaEnCaja=K;
				printf("\nEl CLIENTE %d con CARRETA %d  pasa a la CAJA %d",actual->idClienteEnCaja,actual->idCarretaEnCaja,actual->IDCaja);
				encontrado = 1;
			}
			actual = actual->siguienteCaja;
		}while(actual != primeroCaja && encontrado != 1);
		if(encontrado == 0){
			printf("\n Caja no Encontrado\n\n");
		}
	}else{
		printf("\n La Lista se encuentra vacia\n");
	}		
}
void modificarCajaS(Caja* actual, int cDisp){
	actual = (Caja*) malloc(sizeof(Caja));
	actual = primeroCaja;
	int cajaBuscado = 0, encontrado = 0;
	
	if(primeroCaja!=NULL){
		do{
			if(actual->IDCaja == cDisp){

				
				printf("\nEl CLIENTE %d con CARRETA %d  sale de la CAJA %d",actual->idClienteEnCaja,actual->idCarretaEnCaja,actual->IDCaja);
				actual->estado=true;
				actual->idClienteEnCaja=0;
				actual->idCarretaEnCaja=0;
				encontrado = 1;
			}
			actual = actual->siguienteCaja;
		}while(actual != primeroCaja && encontrado != 1);
		if(encontrado == 0){
			//printf("\n Caja no Encontrado\n\n");
		}
	}else{
		//printf("\n La Lista se encuentra vacia\n");
	}		
}


void abrirEscrituraArchivo(int p){
	archivo=fopen("MiniMarket.txt","w");
	fprintf(archivo,"digraph james{");
	fprintf(archivo," node [shape= record fontsize=11 ] ");
}



void cerrarEscrituraArchivo(){
	fprintf(archivo,"}");
	fclose(archivo);
	system("dot -Tpng MiniMarket.txt -o MiniMarket.png");

}









