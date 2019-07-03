#include <stdio.h>
#include <stdlib.h>

//Estructura de vagon.
typedef struct vagon{
    char CA;    //Conexion Anterior.
    char CS;    //Conexion Siguiente.
    int vacio;  //Saber si existe vagon.

    int EstadoA;    //Estado Conexion Anterior.
    int VAGON;      //Estado Vagon.
    int EstadoS;    //Estado Siguiente.

    struct vagon *next;
}*Vagon;

//Funciones.
void Presentacion();
void Menu();
int SubMenu();
Vagon CopiarVagones(Vagon lista,char *linea);
Vagon copiarPiezas(Vagon lista);
void trenPrincipal();
void actualizarCopia(Vagon lista);
void actualizarCopiaPiezas(Vagon lista);
Vagon agregarVagonEn(Vagon lista, int posicion);

//Funciones de Menu.
/* 1. Creacion de Informe. */
void CrearPresupuesto();

/* 2. Imprimir Plano Actual. */
void ImprimirPlano();

/* 3. Edicion de Vagones. */
void EditarVagones();

/* 4. Calculo de Presupuesto a futuro. */
void PresupuestoFuturo();

/* Main. */

int main(){
    system("color a");

    trenPrincipal();

    Presentacion();
    Menu();
    return 0;
}

//Funciones.

void Presentacion(){    //Lista.
    //Nombre del programa.
    printf("###########                                                                   #####\n");
    printf("     #       #####     ######    #    #     ####     #    #####     ####     #      \n");
    printf("     #       #    #    #         ##   #    #    #    #      #      #    #    #       \n");
    printf("     #       #    #    #####     # #  #    #         #      #      #    #     #####  \n");
    printf("     #       #####     #         #  # #    #         #      #      #    #          # \n");
    printf("     #       #   #     #         #   ##    #    #    #      #      #    #          # \n");
    printf("     #       #    #    ######    #    #     ####     #      #       ####      #####  \n");

    //printf("Nombre de los integrantes");
    printf("\n\n\t\t\t\t\t\tPablo Montoya / Francisco Ojeda.\n");
    printf("\n\n\nPresione para continuar...");  
    getchar();
                                                                                      
}

void Menu(){    //Listo.
    int opcmenu;

    do{
        do{
            system("cls");
	        printf("| 1.GENERAR INFORME | 2.VER PLANO ACTUAL | 3.EDITAR VAGONES | 4.CALCULAR MANTENIMIENTO A FUTURO | 5.SALIR |\n\n");
	        scanf("%d",&opcmenu);
	    }while(opcmenu<1 || opcmenu>5);
    
        switch(opcmenu){
            case 1:
                CrearPresupuesto();
                break;

            case 2:
                ImprimirPlano();
                getchar();getchar();
                break;

            case 3:
                EditarVagones();
                break;

            case 4:
                PresupuestoFuturo();
                break;
        }
    }while(opcmenu!=5);

}

Vagon CopiarVagones(Vagon lista, char *linea){  //Lista.
    Vagon nuevo = (Vagon)malloc(sizeof(struct vagon));  //Se crea nuevo nodo.

    //Se llenan valores de "nuevo".
    if(*(linea+0)!=45){
        nuevo->CA = *(linea+0);
        nuevo->CS = *(linea+2);
        nuevo->vacio = 1;
        nuevo->next = NULL;
    }
    else{
        nuevo->vacio = 0;
        nuevo->next = NULL;
    }

    //Caso que lista sea nula.
    if(lista == NULL){
        return nuevo;
    }

    //Se crea auxiliar.
    Vagon aux = lista;

    while(aux->next!=NULL){ //Se recorre la lista.
        aux = aux->next;
    }

	aux->next = nuevo;

    return lista;
}

Vagon copiarPiezas(Vagon lista){   //Falta arreglar.
    
    FILE *copia_piezas = fopen("copia_piezas.txt","r");
    Vagon aux = lista;

    //Tren tomará el estado de sus piezas.
    while(!feof(copia_piezas)){
        fscanf(copia_piezas,"%d,%d,%d",&aux->EstadoA,&aux->VAGON,&aux->EstadoS);
        aux = aux->next;
    }

    return lista;
}

void trenPrincipal(){   //Lista.

    FILE *estado = fopen("estado_vagones.txt","r");
    FILE *copia = fopen("copia_estado.txt","w");
    
    FILE *piezas = fopen("piezas_estado.txt","r");
    FILE *copia_piezas = fopen("copia_piezas.txt","w");
    
    int modo = 0;
    char *linea = (char*)malloc(sizeof(char));

    while(!feof(estado)){
        if(modo==1){
            fprintf(copia,"\n");
        }

        fscanf(estado,"%s",linea);
        fprintf(copia,"%s",linea);

        modo = 1;
    }

    modo = 0;

    while(!feof(piezas)){
        if(modo==1){
            fprintf(copia_piezas,"\n");
        }

        fscanf(piezas,"%s",linea);
        fprintf(copia_piezas,"%s",linea);

        modo = 1;
    }

    //fprintf("\r");

    fflush(stdin);
    fclose(estado);
    fclose(copia);
    fclose(piezas);
    fclose(copia_piezas);
}

void actualizarCopia(Vagon lista){  //Lista.
    FILE *copia = fopen("copia_estado.txt","w");

    int mod=0;

    while(lista!=NULL){

        if(mod==1){
            fprintf(copia,"\n");
        }

        if(lista->vacio==0){
            fprintf(copia,"-");
        }
        else{
            fprintf(copia,"%c",lista->CA);
            fprintf(copia,"v%c",lista->CS);
        }

        lista = lista->next;
        mod = 1;

    }

    fflush(stdin);
    fclose(copia);
}

void actualizarCopiaPiezas(Vagon lista){
    FILE *copia_piezas = fopen("copia_piezas.txt","w");
    int mod=0;

    mod = 0;

    while(lista!=NULL){
        if(mod==1){
            fprintf(copia_piezas,"\n");
        }

        fprintf(copia_piezas,"%d,%d,%d",lista->EstadoA,lista->VAGON,lista->EstadoS);

        mod = 1;
        lista = lista->next;
    }

    fflush(stdin);
    fclose(copia_piezas);
}

Vagon agregarVagonEn(Vagon lista, int posicion){   //Lista.
	Vagon nuevo = (Vagon)malloc(sizeof(struct vagon));

    nuevo->vacio = 1;
    int opcion;
	int cont=1;
	int modo=0;

	//Se llenan datos.
    system("cls");
    printf("Ingrese Conexion Anterior.\n\n");
    do{
        printf("1) C.\n2) O.\n\n");
        scanf("%d",&opcion);
    }while(opcion<1 || opcion>2);

    if(opcion==1){
        nuevo->CA = 67;
    }
    else{
        nuevo->CA = 79;
    }
	
    system("cls");
    printf("Ingrese Conexion Siguiente.\n\n");
    do{
        printf("1) C.\n2) O.\n\n");
        scanf("%d",&opcion);
    }while(opcion<1 || opcion>2);

    if(opcion==1){
        nuevo->CS = 67;
    }
    else{
        nuevo->CS = 79;
    }

    nuevo->EstadoA = 0;
    nuevo->EstadoS = 0;
    nuevo->VAGON = 0;
    
    nuevo->next = NULL;

	if(lista == NULL){
		return nuevo;
	}
		
	Vagon ant = lista;
	Vagon aux = lista->next;
	
	if(posicion==0){
		nuevo->next = lista;
		lista = nuevo;
		modo = 1;
	}
	else{
		while(ant->next!=NULL){
			if(cont==posicion){
				ant->next = nuevo;
				nuevo->next = aux;
				modo = 1;
				break;
			}
			aux = aux->next;
			ant = ant->next;
			cont = cont+1;
		}
	}
	
	if(modo==0){
		ant->next = nuevo;
		nuevo->next = aux;
	}
	
	return lista;
}

//Funciones del menu.
//Opcion 1.
void CrearPresupuesto(){
    FILE *copia = fopen("copia_estado.txt","r");
    FILE *presupuesto = fopen("presupuesto.txt","w");
    
    FILE *copia_piezas = fopen("copia_piezas.txt","r");

    //Variables.
    int gastosCorrecion = 0,gasto=0;
    int i;
    char *linea = (char*)malloc(sizeof(char));

    //Creamos Lista con los vagones y conexiones.
    Vagon Tren = NULL;

    while(!feof(copia)){
        fscanf(copia,"%s",linea);

        Tren = CopiarVagones(Tren,linea);
    }

    //Se llena el estado de las piezas
    Tren = copiarPiezas(Tren);

    Vagon aux1 = Tren;
    Vagon aux2 = Tren->next;
    i = 0;

    //Correcion puntos de anclaje.
    fprintf(presupuesto,"%s","Correcion de puntos de anclaje:\n");

    while(aux2!=NULL){

        if(aux1->CS == aux2->CA){
            if(aux1->CS==67){   //Se cambia [C] por [O], gasto: 5$
                aux1->CS = 79;
                gasto = 5;
            }
            else{               //Se cambia [O] por [C], gasto: 10$
                aux1->CS = 67;
                gasto = 10;
            }
            
            fprintf(presupuesto,"\n%s","Posicion ");
            fprintf(presupuesto,"%d:\n",i);

            fprintf(presupuesto,"%s","\n\tEliminacion punto de anclaje [");
            fprintf(presupuesto,"%c] por punto de anclaje [",aux2->CA);
            fprintf(presupuesto,"%c].\n",aux1->CS);
            fprintf(presupuesto,"\n\tGasto: %d Dolares.\n",gasto);

            gastosCorrecion = gastosCorrecion+gasto;   
        }
        aux1 = aux1->next;
        aux2 = aux2->next;
        i = i+1;
    }
    fprintf(presupuesto,"\n\nGastos Totales: %d Dolares.\n\n",gastosCorrecion);
    aux1->next = NULL;
    actualizarCopia(Tren);

    //Integración de vagones y sus conexiones.
    fprintf(presupuesto,"%s","****************************************************************************\n\n");
    fprintf(presupuesto,"%s","Integración de vagones y sus conexiones:\n\n");

    aux1 = Tren;
    aux2 = Tren->next;
    i = 0;
    int gastosIntegracion = 0;

    if(aux1->next!=NULL){

        //txt Comienza con "-".
        if(aux1->vacio==0){
            aux1->CA = 79;
            aux1->EstadoA = 0;

            gasto = 5;

            if(aux1->next!=NULL && (aux1->next)->CA==67){ //Ov[O] [C]vO
                aux1->CS = 79;
                gasto = gasto+5;
            }
            if(aux1->next!=NULL && (aux1->next)->CA==79){ //Ov[C] [O]vO
                aux1->CS = 67;
                gasto = gasto+10;
            }
            aux1->vacio = 1;
            aux1->EstadoS = 0;

            aux1->VAGON = 0;    //Se actualiza el tiempo del Vagon.

            aux1 = aux1->next;
            aux2 = aux2->next;
            gasto = gasto+50;

            fprintf(presupuesto,"\nPosicion %d:",i);
            fprintf(presupuesto,"\n\tIntegracion de %cv%c\n",aux1->CA,aux1->CS);
            fprintf(presupuesto,"\tGastos: %d Dolares\n",gasto);

            gastosIntegracion = gastosIntegracion+gasto;
            gasto = 0;
            i = i+1;
        }

        //Se recorre el txt.
        while(aux2->next!=NULL){
            i = i+1;

            if(aux2->vacio==0){
                if(aux1->CS==67){   //Cv[C] [O]vO
                    aux2->CA = 79;
                    gasto = 5;
                }
                else{
                    aux2->CA = 67;
                    gasto = 10;
                }

                if(aux2->next!=NULL && (aux2->next)->CA==67){   //Cv[O] [C]vO
                    aux2->CS = 79;
                    gasto = gasto+5;
                }
                else{
                    aux2->CS = 67;
                    gasto = gasto+10;
                }

                aux2->EstadoA = 0;
                aux2->EstadoS = 0;
                aux2->VAGON = 0;

                aux2->vacio = 1;
                gasto = gasto+50;

                fprintf(presupuesto,"\nPosicion %d:",i);
                fprintf(presupuesto,"\n\tIntegracion de %cv%c\n",aux2->CA,aux2->CS);
                fprintf(presupuesto,"\tGastos: %d Dolares\n",gasto);

                gastosIntegracion = gastosIntegracion+gasto;
            }
        
            gasto = 0;

            aux1 = aux1->next;
            aux2 = aux2->next;
        }

        //txt Termina en "-".
        if(aux2->vacio==0){
            i = i+1;

            if(aux1->CS==67){ //Cv[C] [O]vO
                aux2->CA = 79;
                gasto = 5;
            }
            else{
                aux2->CA = 67;
                gasto = 10;
            }
        
            aux2->EstadoA = 0;
            aux2->EstadoS = 0;
            aux2->VAGON = 0;

            aux2->CS = 79;
            aux2->vacio = 1;

            gasto = gasto+5;
            gasto = gasto+50;

            fprintf(presupuesto,"\nPosicion %d:",i);
            fprintf(presupuesto,"\n\tIntegracion de %cv%c\n",aux2->CA,aux2->CS);
            fprintf(presupuesto,"\tGastos: %d Dolares\n",gasto);

            gastosIntegracion = gastosIntegracion+gasto;
        }
    }
    
    fprintf(presupuesto,"\n\nGastos Totales: %d Dolares\n\n",gastosIntegracion);
    actualizarCopia(Tren);
    actualizarCopiaPiezas(Tren);

    //Actualización de piezas obsoletas.
    fprintf(presupuesto,"%s","****************************************************************************\n\n");
    fprintf(presupuesto,"%s","Actualización de piezas obsoletas:\n");

    int modo=0;
    i = 0;
    Vagon aux = Tren;
    int gastosActualizacion = 0;

    while(aux!=NULL){
        //Actualizaciones de vagones.
        if(aux->vacio!=0){

            fprintf(presupuesto,"\nPosicion %d:\n",i);

            /* Conexion Anterior. */

            if(aux->CA==67 && aux->EstadoA>=15){    //Conexion tipo "C".
                aux->EstadoA = 0;
                gasto = 7;

                fprintf(presupuesto,"\tActualizacion Anclaje C.\n\tGasto: %d dolares.\n\n",gasto);
                gastosActualizacion = gastosActualizacion+gasto;
            }

            if(aux->CA==79 && aux->EstadoA>=6){    //Conexion tipo "O".
                aux->EstadoA = 0;
                gasto = 2;

                fprintf(presupuesto,"\tActualizacion Anclaje O.\n\tGasto: %d dolares.\n\n",gasto);
                gastosActualizacion = gastosActualizacion+gasto;
            }

            /* Vagon. */

            if(aux->VAGON>=84){ //Actualizacion de Vagon.
                aux->VAGON = 0;
                gasto = 30;

                fprintf(presupuesto,"\tActualizacion Vagon.\n\tGasto: %d dolares.\n\n",gasto);
                gastosActualizacion = gastosActualizacion+gasto;
            }

            /* Conexion Siguiente. */

            if(aux->CS==67 && aux->EstadoS>=15){    //Conexion tipo "C".
                aux->EstadoS = 0;
                gasto = 7;

                fprintf(presupuesto,"\tActualizacion Anclaje C.\n\tGasto: %d dolares.\n\n",gasto);
                gastosActualizacion = gastosActualizacion+gasto;
            }

            if(aux->CS==79 && aux->EstadoS>=6){    //Conexion tipo "O".
                aux->EstadoS = 0;
                gasto = 2;

                fprintf(presupuesto,"\tActualizacion Anclaje O.\n\tGasto: %d dolares.\n\n",gasto);
                gastosActualizacion = gastosActualizacion+gasto;
            }

        }

        i = i+1;

        aux = aux->next;
    }

    fprintf(presupuesto,"\nGastos Totales: %d dolares.\n\n",gastosActualizacion);
    fprintf(presupuesto,"****************************************************************************\n\n");
    fprintf(presupuesto,"Gastos Finales: %d dolares.",gastosCorrecion+gastosIntegracion+gastosActualizacion);

    actualizarCopia(Tren);
    actualizarCopiaPiezas(Tren);



    //Se cierran archivos que fueron abiertos.
    fflush(stdin);
    fclose(copia);
    fclose(presupuesto);
    fclose(copia_piezas);

    system("cls");
    printf("Presupuesto Actualizado.\n\n");
    printf("Presione una tecla para continuar . . .\n\n");
    getchar();getchar();
}

//Opcion 2.
void ImprimirPlano(){   //Lista.
    system("cls");

    FILE *fp = fopen("copia_estado.txt","r");
 	
 	char *Vagon = (char*)malloc(sizeof(char));
 	
 	
 	
 	while(!feof(fp)){
 		fscanf(fp,"%s",Vagon);
 		
        //Casos.
        if(*(Vagon+0)!=45){

            if(*(Vagon+0)==67){ //Empieza en C.
                printf(" )--");
            }
            if(*(Vagon+0)==79){ //Empieza en O.
                printf(" O--");
            }
            if(*(Vagon+1)=='v'){    //Vagon normal.
                printf("[v]");
            }
            if(*(Vagon+2)==79){ //Termina en O.
                printf("--O ");
            }
            if(*(Vagon+2)==67){ //Termina en C.
                printf("--( ");
            }

        }
        else{
            printf(" [-] ");
        }
        
	}
 	
    fflush(stdin);
 	fclose(fp);
 	
 	printf("\n\nPresione para continuar . . .\n");
}

//Opcion 3.
void EditarVagones(){
    int opcmenuEditar;
    do{
        system("cls");
	    printf("| 1.AGREGAR VAGONES | 2.MODIFICAR VAGONES | 3.ELIMINAR VAGONES | 4.SALIR |\n\n");
	    scanf("%d",&opcmenuEditar);
	}while(opcmenuEditar<1 || opcmenuEditar>4);
    
    Vagon Tren = NULL;

    FILE *copia = fopen("copia_estado.txt","r");

    int i,posicion;
    char *linea = (char*)malloc(sizeof(char));

    for(i=0;!feof(copia);i++){
        fscanf(copia,"%s",linea);
        Tren = CopiarVagones(Tren,linea);
    }

    Tren = copiarPiezas(Tren);

    Vagon nuevo = (Vagon)malloc(sizeof(struct vagon));

    //Opciones.
    switch (opcmenuEditar){
        
        //1. Agregar Vagones   Lista.
        case 1:
        
            do{
                system("cls");
                printf("Agregar Vagones.\n\n");
                printf("Ingrese posicion para agregar vagon: ");
                scanf("%d",&posicion);
            }while(posicion<0);

            Tren = agregarVagonEn(Tren,posicion);
            
            /*  Solucion Problema (Repite ultima posicion)  */
            Vagon aux = Tren;
            /*while((aux->next)->next!=NULL){
                aux = aux->next;
            }
            aux->next = NULL;*/

            system("cls");
            printf("Se agrego vagon.\n\n");
            printf("Presione una tecla para continuar . . .\n");

            actualizarCopia(Tren);
            actualizarCopiaPiezas(Tren);

            break;
        
        //2. Modificar Vagones  Lista.
        case 2:
            
            do{
                system("cls");
                printf("Modificar Vagones.\n\n");
                printf("Ingrese posicion que desea modificar: ");
                scanf("%d",&posicion);
            }while(posicion<0);

            aux = Tren;
            int contador=0,modo=0;
            int opcion;

            while(aux!=NULL){
                if(contador==posicion){

                    if(aux->vacio==0){
                        system("cls");
                        printf("Error.\n\tNo existe vagon.\n\n");
                        modo = 3;
                    }
                    else{
                        //Se llenan datos.
                        system("cls");
                        printf("Ingrese Conexion Anterior.\n\n");
                        do{
                            printf("1) C.\n2) O.\n\n");
                            scanf("%d",&opcion);
                        }while(opcion<1 || opcion>2);

                        if(opcion==1){
                            aux->CA = 67;
                        }
                        else{
                            aux->CA = 79;
                        }
	
                        system("cls");
                        printf("Ingrese Conexion Siguiente.\n\n");
                        do{
                            printf("1) C.\n2) O.\n\n");
                            scanf("%d",&opcion);
                        }while(opcion<1 || opcion>2);

                        if(opcion==1){
                            aux->CS = 67;
                        }
                        else{
                            aux->CS = 79;
                        }

                        aux->EstadoA = 0;
                        aux->EstadoS = 0;

                        modo = 1;
                        break;
                    }
                    
                }
                contador = contador+1;
                aux = aux->next;
            }

            if(modo==0){
                system("cls");
                printf("Error.\n\tPosicion [%d] no existe.\n\n",posicion);
            }
            if(modo==1){
                system("cls");
                printf("Vagon actualizado.\n\n");
            }

            /*  Solucion Problema (Repite ultima posicion)  */
            /*aux = Tren;
            while((aux->next)->next!=NULL){
                aux = aux->next;
            }
            aux->next = NULL;*/

            printf("Presione una tecla para continuar . . .\n");
            actualizarCopia(Tren);
            actualizarCopiaPiezas(Tren);

            break;

        //3. Eliminar Vagones.
        case 3:

            do{
                system("cls");
                printf("Eliminar Vagones.\n\n");
                printf("Ingrese posicion que desea eliminar: ");
                scanf("%d",&posicion);
            }while(posicion<0);

            modo = 0;
            Vagon ant = Tren;
            aux = Tren->next;
            contador = 0;

            if(posicion==0){
                Tren = Tren->next;
                modo = 1;
            }
            else{
                while(ant->next!=NULL){

                    if(contador==posicion){
                        ant->next = aux->next;
                        modo = 1;
                        break;
                    }

                    ant = ant->next;
                    aux = aux->next;
                    contador = contador+1;
                }
            }

            if(modo==0){
                system("cls");
                printf("Error.\n\tPosicion [%d] no existe.\n\n",posicion);
            }
            else{
                system("cls");
                printf("Vagon actualizado.\n\n");
            }

            /*  Solucion Problema (Repite ultima posicion)  */
            aux = Tren;
            /*while((aux->next)->next!=NULL){
                aux = aux->next;
            }
            aux->next = NULL;*/

            printf("Presione una tecla para continuar . . .\n");
            actualizarCopia(Tren);
            actualizarCopiaPiezas(Tren);

            break;

        //Vuelve al menu.
        case 4:
            Menu();
        break;

    }

    fflush(stdin);
    fclose(copia);
    getchar();getchar();
}

//Opcion 4.
void PresupuestoFuturo(){   //Lista.

    FILE *estado = fopen("estado_vagones.txt","r");
    FILE *futuro = fopen("presupuesto_futuro.txt","w");

    //Variables.
    int Cantidad_Meses,Actualizacion,Costo,i,gastoPosicion=0,gastoFinal=0;
    char *Meses = (char*)malloc(sizeof(char));

    do{
        system("cls");

        printf("Ingrese cantidad de Meses: ");
        scanf("%d",&Cantidad_Meses);
    }while(Cantidad_Meses<=0);

    fprintf(futuro,"%s","Presupuesto Futuro - ");
    fprintf(futuro,"%d ",Cantidad_Meses);
    fprintf(futuro,"%s\n","Meses.");

    for(i=0;!feof(estado);i++){
            
        //Se lee la posicion.
        fscanf(estado, "%s" ,Meses);

        if(*(Meses+0)!=45){

            //En esta parte se escribe la posición donde se actualiza.
            fprintf(futuro,"\n%s","Posición ");
            fprintf(futuro,"%d:\n",i);

            //Aca reviso las actualizaciones.

            /*  Actualizaciones.
                
                Vagon:      84 meses.
                Gancho O:   6 meses.
                Gancho C:   15 meses. */


            //Vagon.
            if(*(Meses+1)=='v'){
                Actualizacion = Cantidad_Meses/84;
                Costo = Actualizacion*30;

                //En esta parte hay que escribir en el txt la cantidad de Actualizaciones que recibe esta pieza.
                //Vagon - Actualizado "Actualizacion" veces - Gasto: "Costo" dolares.
                fprintf(futuro,"\n\tVagon - Actualizado ");
                fprintf(futuro,": %d veces - Gasto", Actualizacion);
                fprintf(futuro,": %d Dolares\n",Costo);

                gastoPosicion = gastoPosicion + Costo;
            }

            //Anclaje C.
            if(*(Meses+0)==67 || *(Meses+2)==67){
                Actualizacion = Cantidad_Meses/15;
                Costo = Actualizacion*7;

                //En esta parte hay que escribir en el txt la cantidad de Actualizaciones que recibe esta pieza.
                //Anclaje C - Actualizado "Actualizacion" veces - Gasto: "Costo" dolares.
                fprintf(futuro,"\n\tAnclaje C - Actualizado ");
                fprintf(futuro,": %d veces - Gasto", Actualizacion);
                fprintf(futuro,": %d Dolares\n",Costo);

                gastoPosicion = gastoPosicion + Costo;
            }
            
            //Anclaje O.
            if(*(Meses+0)==79 || *(Meses+2)==79){
                Actualizacion = Cantidad_Meses/6;
                Costo = Actualizacion*2;

                //En esta parte hay que escribir en el txt la cantidad de Actualizaciones que recibe esta pieza.
                //Anclaje O - Actualizado "Actualizacion" veces - Gasto: "Costo" dolares.
                fprintf(futuro,"\n\tAnclaje O - Actualizado ");
                fprintf(futuro,": %d veces - Gasto", Actualizacion);
                fprintf(futuro,": %d Dolares\n",Costo);

                gastoPosicion = gastoPosicion + Costo;
            }

            fprintf(futuro,"\n\nGastos: ");
            fprintf(futuro," %d Dolares\n",gastoPosicion);

        }

        gastoFinal = gastoFinal + gastoPosicion;
        gastoPosicion = 0;  //Se reinicia valor.

	}
    fprintf(futuro,"---------------------------------------------------------------------");
    fprintf(futuro,"\n\nGastos Totales: %d Dolares\n",gastoFinal);


    fflush(stdin);
    fclose(estado);
    fclose(futuro);
    system("cls");
    printf("Presupuesto Futuro Actualizado.\n\n");
    printf("Presione una tecla para continuar . . .\n\n");
    getchar();
}