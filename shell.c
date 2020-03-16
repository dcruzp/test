#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#define max_args 13 
#define maxln_Com_Amb 105 


char comando [maxln_Com_Amb];
char *args [max_args]; 
int cantcmd = 0 ; 

char SHELL [maxln_Com_Amb]; 
char PATH [maxln_Com_Amb]; 
char HOME [maxln_Com_Amb]; 
char PWD [maxln_Com_Amb] ;

void separaArgs (void); 


/*estas son las funciones a ejecutar */ 
void execute_cd (void ); 
void execute_exit (void); 
void execute_dir_or_ls(void);
void execute_pwd(void) ; 
/*----------------------------------*/

void listaDir (void); 
void eco (void) ; 
void comExterno(void); 


/*estas son los flags del programa */ 
int continuar = 1;
/*---------------------------------*/


int main(int argc, char const *argv[])
{
	 

	getcwd (PWD,maxln_Com_Amb); 
	strcpy(PATH,getenv("PATH")); 
	//printf("%s\n", PATH);

	strcpy(HOME,PWD);
	strcpy(SHELL,PWD); 


	
	do {
		printf("%s>",PWD );
		__fpurge(stdin);

		memset(comando,'\0',maxln_Com_Amb);
		scanf("%[^\n]s" ,comando) ; 

		if (strlen(comando)>0) {
			separaArgs(); 

			if (strcmp (comando, "cd")==0 )execute_cd();

			else if (strcmp(comando ,"exit")==0)execute_exit();

			else if (strcmp (comando, "dir") ==0 || strcmp(comando, "ls")==0 )execute_dir_or_ls(); 

			else if (strcmp(comando,"pwd") ==0 ) execute_pwd () ; 
		}		
	}while(continuar);


	

	return 0;
}


void separaArgs (void){
	int i ; 
	for (i=0 ; i < max_args-1; i++) args[i]= NULL; 
	strtok(comando , " ") ; 
	i=0 ; 
	args[i] =comando ;
	while((args[++i]= strtok(NULL," "))!=NULL&& i <(max_args-2)); 
	cantcmd = i ; 
}




void execute_cd  (void ){
	if (args[1])
		if (chdir(args[1])!=0)
			printf("Error '%s'  no existe o np se puede cambiar a este directorio\n", args[1]);
		else getcwd(PWD,maxln_Com_Amb); 
}

void execute_exit (void){
	continuar = 0; 
}

void execute_dir_or_ls(void){
	char ruta [maxln_Com_Amb] ; 
	int archs ; 
	int cnt = -1; 
	struct dirent **lista ; 
	strcpy (ruta,PWD); 
	if (args[1]) strcat (ruta , "/"),strcat (ruta ,args[1]) ; 
	archs = scandir(ruta , &lista ,0,alphasort) ; 
	if (archs <0 )
		printf("Error , no existe o no se puede leer [%s]\n",ruta);
	else if (archs == 2 ){
		//solo encontro los directorios [ . , .. ] 
	}
	else {
		while(++cnt < archs ){
			if (strcmp(lista[cnt]->d_name, ".")!=0 && strcmp(lista[cnt]->d_name, "..")!=0)
				printf("%s\n", lista[cnt]->d_name);
		}
	}
}

void execute_pwd (void) {
	printf("%s\n", PWD);
}