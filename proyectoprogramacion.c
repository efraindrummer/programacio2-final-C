#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <conio.h>	
#include <locale.h>
#include <windows.h>
#define l 3 //constante definida de 3 para 3 calificaciones
#define MAX 100

typedef struct{
	char Carrera[20];
	char Alumno[40];
	int Matricula;
	float Calificacion[l];
}Alumnos;

int menu();
void Datos(FILE*prueba);
void Buscar(FILE*prueba,int n);
void Proma(Alumnos Reg[],int n);
void Mejorp(Alumnos Reg[],int n);
void esc(Alumnos Reg[],FILE*prueba,int c);
int Cargar(Alumnos R[],FILE*prueba);
void Peorp(Alumnos Reg[],int n);
void promc(Alumnos Reg[],int n);
void modificacion();
void modificar();
void ordMat(int n,Alumnos Reg[]);

//funciones por el metodo burbuja
void ordCarrera(int n,Alumnos Reg[]);
void ordProm(int n,Alumnos Reg[]);
float promAlumno(Alumnos Reg);
void imprimir_alumnos(int n, Alumnos Reg[]);

main(){
	
	FILE*prueba;
	int op, a, b, m;
	Alumnos Reg[MAX];
	setlocale(LC_ALL, "spanish");
	
	do{
		op=menu();
		switch(op){
			
			case 1: 
			printf("Cuantos alumnos desea ingresar\n"); scanf("%d",&a);
			esc(Reg,prueba,a);
			system("PAUSE");
			system("CLS");
			break;
			
			case 2: 
			a=Cargar(Reg,prueba); 
			Proma(Reg,a);
			system("PAUSE");
			system("CLS");
			break;
			
			case 3: 
			a=Cargar(Reg,prueba);
			promc(Reg,a);
			system("PAUSE");
			system("CLS");
			break;
			
			case 4: 
			a=Cargar(Reg,prueba); 
			Mejorp(Reg,a);
			system("PAUSE");
			system("CLS");
			break;
			
			case 5: 
			a=Cargar(Reg,prueba); 
			Peorp(Reg,a);
			system("PAUSE");
			system("CLS");
			break;
			
			case 6: 
			printf("¿Que registro desea buscar? \n\n"); scanf("%d",&b);
			Buscar(prueba,b-1);
			system("PAUSE");
			system("CLS");
			break;
			
			case 7: 
			modificacion();
			system("PAUSE");
			system("CLS");
			break;
			
			case 8: modificar();
			system("PAUSE");
			system("CLS");
			break;
			
			case 9: 
			Datos(prueba);
			system("PAUSE");
			system("CLS");
			break;
			
			case 10: 
			a=Cargar(Reg,prueba);
			ordMat(a, Reg);
			system("PAUSE");
			system("CLS");
			break;
			
			case 11: 
			a=Cargar(Reg,prueba);
			ordProm(a, Reg);
			system("PAUSE");
			system("CLS");
			break;
			
			case 12:
			a=Cargar(Reg,prueba);
			ordCarrera(a, Reg);
			system("PAUSE");
			system("CLS");
			break;
		}
	}while(op!=0);
}

int menu(){
	int op;

	printf("\t\t**********SISTEMA DE REGISTRO DE ALUMNOS**********\n\n");
	printf("\n\t\t\t1.-REGISTRO DE ALUMNOS");
	printf("\n\t\t\t2.-IMPRIMIR REGISTRO DE ALUMNOS");
	printf("\n\t\t\t3.-PROMEDIO POR CARRERA");
	printf("\n\t\t\t4.-MEJOR PROMEDIO");
	printf("\n\t\t\t5.-PEOR PROMEDIO");
	printf("\n\t\t\t6.-BUSCAR ALUMNO");
	printf("\n\t\t\t7.-MODIFICA POR MATRICULA");
	printf("\n\t\t\t8.-MODIFICAR POR NUMERO DE REGISTRO");
	printf("\n\t\t\t9.-MOSTRAR TODOS LOS ALUMNOS");
	printf("\n\t\t\t10.-ORDENAR POR MATRICULA");
	printf("\n\t\t\t11.-ORDENAR POR PROMEDIO");
	printf("\n\t\t\t12.-ORDENAR POR CARRERA");
	printf("\n\t\t\t0.-SALIR\n");
	printf("\n\n\t\t\tELIGA UNA OPCION");
	scanf("%d",&op);
	
	system("CLS");
	return op;
}

void esc(Alumnos Reg[],FILE*prueba,int c){
	prueba=fopen("Proyecto.dat","a+b");
	
	if(prueba!=NULL){
		size_t wb;
		int i, y;
		
		for(i=0; i<c; i++){
			printf("\n");
			printf("Carrera: ");
			scanf(" %[^\n]",Reg[i].Carrera);
			
			printf("Nombre: ");
			scanf(" %[^\n]",Reg[i].Alumno);
			
			printf("Matricula: ");
			scanf("%d",&Reg[i].Matricula);
			
			for(y=0; y<l; y++){
				printf("\n");
				printf("Calificiones: ");
				scanf("%f",&Reg[i].Calificacion[y]);
			}
			system("CLS");
		}
		wb=fwrite(Reg,sizeof(Alumnos),c,prueba);
		printf("%d bytes escritos en %d elementos\n",wb*sizeof(Alumnos),wb);
		fclose(prueba);
	}else
	printf("Error al abrir %s \n",strerror(errno));	
}

void Datos(FILE*prueba){
	
	prueba=fopen("Proyecto.dat","r+b");
	
	if(prueba!=NULL){
		int i,y;
		Alumnos R;
		
		while(fread(&R,sizeof(Alumnos),1,prueba)==1){
			printf("\n");
			printf("Carrera....................: %s\n",R.Carrera);			
			printf("Nombre.....................: %s\n",R.Alumno);			
			printf("Matricula..................: %d\n",R.Matricula);
								
			for(y=0; y<l; y++)
			printf("Calificiones................: %0.2f\n",R.Calificacion[y]);
		}
		fclose(prueba);
	}else{
		printf("Error al abrir %s \n",strerror(errno));
	}
}

int Cargar(Alumnos R[],FILE*prueba){
	
	prueba=fopen("Proyecto.dat","r+b");
	int p=0, i, y;
	
	if(prueba!=NULL){
		size_t wb;
		
		while(fread(&R[p],sizeof(Alumnos),1,prueba)==1){
			p++;
		}
		fclose(prueba);
	}else{
	printf("Error al abrir %s \n",strerror(errno));	
	return p;
	}
}

void Buscar(FILE*prueba,int n){
	prueba=fopen("Proyecto.dat","r+b");
	
	if(prueba!=NULL){
		Alumnos Reg;
		int y;
		
		fseek(prueba,n*sizeof(Alumnos),SEEK_SET);
		fread(&Reg,sizeof(Alumnos),1,prueba);
		printf("\n\t\t\tCarrera................: %s\n",Reg.Carrera);			
		printf("\n\t\t\tNombre.................: %s\n",Reg.Alumno);			
		printf("\n\t\t\tMatricula..............: %d\n",Reg.Matricula);
		
		for(y=0; y<l; y++){
			printf("\n\t\t\tCalificiones...............:%0.2f\n",Reg.Calificacion[y]);
		}
		fclose(prueba);
	}else{
	printf("Error al abrir %s \n",strerror(errno));
	}
}

void Proma(Alumnos Reg[],int n){
	int pos, i, y;
	float suma=0, promedio;
		
	for(i=0; i<n; i++){
		suma=0;
		for(y=0; y<l; y++){
			suma+=Reg[i].Calificacion[y];
			promedio=suma/l;
			pos=i;
		}printf("\n\t\t\tEl Promedio de %s es: %0.2f\n",Reg[i].Alumno,promedio);
	}
}

float promAlumno(Alumnos Reg){
	int pos, i, y;
	float suma=0, promedio;
		
		for(y=0; y<l; y++){
			suma+=Reg.Calificacion[y];
			promedio=suma/l;
		}
	return promedio;
}

void Mejorp(Alumnos Reg[],int n){
	
	int mejor, rango=6, i, y;
	float suma=0, promedio[20];
	
	for(i=0; i<n; i++){
		suma=0;
		for(y=0; y<l; y++)
		suma+=Reg[i].Calificacion[y];
		promedio[i]=suma/l;
		
		if(promedio[i]>rango){
			mejor=i;
			rango=promedio[i];	
		}
	}printf("\n\t\t\tEl mejor promedio lo tiene %s con: %0.2f\n",Reg[mejor].Alumno,promedio[mejor]);
}

void Peorp(Alumnos Reg[],int n){
	
	int peor, ra=8, i, y;
	float sum=0, prom[20];
	
	for(i=0; i<n; i++){
		sum=0;
		for(y=0; y<l; y++)
		sum+=Reg[i].Calificacion[y];
		prom[i]=sum/l;
		
		if(prom[i]<ra){
			ra=prom[i];	
			peor=i;
		}
	}printf("\n\t\t\tEl Peor promedio lo tiene %s con: %0.2f\n",Reg[peor].Alumno,prom[peor]);
}

void modificacion(){
	
    FILE*prueba;
    prueba=fopen("Proyecto.dat","r+b");
    
    if(prueba==NULL)
    exit(1);
    
    printf("Ingrese la matricula del alumno a modificar:");
    Alumnos Al;
    
    int i, existe=0, pos, mat;
    
    fread(&Al,sizeof(Alumnos),1,prueba);
    scanf("%d",&mat);
    
    while(!feof(prueba)){
        if(mat==Al.Matricula){
        	
       	   printf(" Carrera    Nombre       Matricula      \n %s         %s           %d\n\n ",Al.Carrera,Al.Alumno,Al.Matricula);
           printf("\n\t\t\tIngrese nueva carrera:");
           scanf("%s",Al.Carrera);
           
           printf("\n\t\t\tIngrese nuevo nombre:");
           scanf("%s",Al.Alumno);
           
           printf("\n\t\t\tIngrese nueva matricula:");
           scanf("%d",&Al.Matricula);
           
           for(i=0; i<l; i++){
           		printf("\n\t\t\tIngrese nuevas calificaciones:");
           		scanf("%f",&Al.Calificacion);
		   }
           pos=ftell(prueba)-sizeof(Alumnos);
           fseek(prueba,pos,SEEK_SET);
           fwrite(&Al,sizeof(Alumnos),1,prueba);
           
           printf("Se modifico correctamente\n");
           existe=1;
           break;
        }fread(&Al,sizeof(Alumnos),1,prueba);
    }
    if(existe==0)
    printf("No existe el alumno\n");
    fclose(prueba);
}

void modificar(){
	FILE*prueba;
	prueba=fopen("Proyecto.dat","r+b");
	
	if(prueba!=NULL){
		Alumnos Reg;
		int op, c, y;
		
		printf("\nQue registro desea modificar: ");
		scanf("%d",&c);
		printf("\n");
		fseek(prueba,c*sizeof(Alumnos),SEEK_SET);
		fread(&Reg,sizeof(Alumnos),1,prueba);
		
		printf("Carrera..........................: %s\n",Reg.Carrera);			
		printf("Nombre...........................: %s\n",Reg.Alumno);			
		printf("Matricula........................: %d\n",Reg.Matricula);
		for(y=0; y<l; y++){
			printf("Calificacion....................: %0.2f\n\n",Reg.Calificacion[y]);
		}

		printf("\nSELECCIONA LA OPCION A MODIFICAR\n");
		printf("\n\t\t\t1.-Modificar Carrera");
		printf("\n\t\t\t2.-Modificar Nombre");
		printf("\n\t\t\t3.-Modificar Matricula");
		printf("\n\t\t\t4.-Modificar Calificiones");
		printf("\n\n\t\t\tELIGA LA OPCION:");
		scanf("%d",&op);
		system("CLS");
		
		switch(op){
			case 1:
			printf("\nModificar Carrera: ");
			scanf(" %[^\n]",Reg.Carrera);
			system("CLS");
			break;
			
			case 2:
			printf("\nModificar Nombre: ");
			scanf(" %[^\n]",Reg.Alumno);
			system("CLS");
			break;
			
			case 3: 
			printf("\nModificando Matricula: ");
			scanf("%d",&Reg.Matricula);
			system("CLS");
			break;
			
			case 4:
			for(y=0; y<l; y++){
				printf("Calificacion %d: ---------> ",y+1);
				scanf("%f",&Reg.Calificacion[y]);
			}
			system("CLS");
			break;
		}
		fseek(prueba,c*sizeof(Alumnos),SEEK_SET);
		fwrite(&Reg,sizeof(Alumnos),1,prueba);
		printf(" << Registro correctamente modificado >> \n");	
		
	}else{
		
		printf("Error al abrir %s \n",strerror(errno));	
		printf("\n");
		fclose(prueba);
	}
}

void promc(Alumnos Reg[],int n){
	
	char carr[5];
	int rango=6, i, y, c=0;
	float suma=0, promedio;
	
	printf("Carrera\n");
	scanf("%s",&carr);
	
	for(i=0; i<n; i++){
		if(strcmp(carr,Reg[i].Carrera)==0){
			c++;
			for(y=0; y<l; y++)
			suma+=Reg[i].Calificacion[y];
			promedio=suma/c;
		}
	}printf("Alumnos encontrados %d \n",c);
	printf("Promedio de la carrera %s %0.2f \n",carr,promedio);
}

void ordMat(int n,Alumnos Reg[]){
	
	int i,j;
	Alumnos aux;

	for (i=0;i<n;i++) 
	{ 
		for (j=0;j<n-1-i;j++) 
		{ 
			if (Reg[j].Matricula>=Reg[j+1].Matricula) 
			{ 
				aux=Reg[j]; 
				Reg[j]=Reg[j+1];
				Reg[j+1]=aux; 
			}
		}
	}
	printf("Nombre de matricula ordenados correctamente\n");
	imprimir_alumnos(n,Reg);
}

void ordProm(int n,Alumnos Reg[]){
	
	int  i, j;
	Alumnos aux;
		
	for(i=0; i<n; i++){		
		for(j=0; j<n-1; j++){
				
		if (promAlumno(Reg[j]) >=promAlumno( Reg[j+1] )) 
			{ 
				aux=Reg[j]; 
				Reg[j]=Reg[j+1];
				Reg[j+1]=aux; 
			}
		}
	}
	printf("Promedio ordenado correctamente\n");
	imprimir_alumnos(n,Reg);
}

void ordCarrera(int n,Alumnos Reg[]){
	
	int i,j;
	Alumnos aux;
	int comp=0;
	
	for(i=0;i<n;i++){
		
	    for(j=1;j<n-1;j++){
	    
		    comp = strcmp( Reg[j].Carrera, Reg[j+1].Carrera );
	        if(comp > 0){
	        	aux=Reg[j]; 
				Reg[j]=Reg[j+1];
				Reg[j+1]=aux; 
	        }
	    }
	}
	
	printf("carera ordenado correctamente\n");
	imprimir_alumnos(n,Reg);	
}

void imprimir_alumnos(int n,Alumnos Reg[]){
	
	int i;
	
	for(i=0; i<n; i++){
		
		printf("\n\t\t\tNombre.................: %s\n",Reg[i].Alumno);
		printf("\n\t\t\tMatricula..............: %d\n",Reg[i].Matricula);
		printf("\n\t\t\tCarrera................: %s\n",Reg[i].Carrera);
		printf("\n\t\t\tPromedio...............: %f\n",promAlumno(Reg[i]));
		
	}
}

