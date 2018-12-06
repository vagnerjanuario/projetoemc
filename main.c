#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
#include<locale.h>
#include<time.h>
#include<ctype.h>


struct Contato{
	char nome[50];
	char sobrenome [30];
	char num[15];
}contato, aux2;

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

void cadastrousuario(){
	system("cls");
	system("mode 100, 50");

	FILE *parq;
    parq = fopen("agenda.txt", "rb");
    char op;
    int i,j;
    char aux[21];

	gotoxy(2, 2);
	putchar(201);
	gotoxy(2, 49);
	putchar(200);
	gotoxy(99, 2);
	putchar(187);
	gotoxy(99, 49);
	putchar(188);

	for(i = 3; i < 99; i++){
		gotoxy(i, 2);
		putchar(205);
		gotoxy(i, 49);
		putchar(205);
	}

	for(i = 3; i < 49; i++){
		gotoxy(2, i);
		putchar(186);
		gotoxy(99, i);
		putchar(186);
	}

    gotoxy(38,5);
    printf("Adicionar novo contato");
    fflush(stdin);
    gotoxy(35,8);
    printf("Digite seu nome: ");
    fflush(stdin);
    gets(contato.nome);
    fflush(stdin);
    gotoxy(35,9);
    printf("Digite seu sobrenome:");
    fflush(stdin);
    gets(contato.sobrenome);
    fflush(stdin);
    gotoxy(35,10);
    printf("Digite seu número:");
    fflush(stdin);
    gets(contato.num);
    fflush(stdin);

    for(j=0;j<strlen(contato.num);j++){
    	if(isalpha(contato.num[j])!=0){
    		printf("Numero invalido. Digite novamente\n");
    		system("pause");
    		cadastrousuario();
    	}
	}

	while(fread(&aux2, sizeof(struct Contato), 1,parq)==1){
    	if(!strcmp(aux2.nome, contato.nome)){
    		printf("Número já cadastrado!\n");
    		system("pause");
		}
    }
    fclose(parq);

    printf("\nDeseja confirmar (s/n): ");
    op = getchar();
    if(op == 's' || op == 'S'){
    	parq=fopen("agenda.txt", "ab");
    	if(parq == NULL) printf("Erro ao abrir arquivo!");
    	else{
    		fwrite(&contato, sizeof(struct Contato), 1, parq);
		}
		fclose(parq);
	}else
		if(op=='n'||op=='N'){
			printf("CADASTRO CANCELADO!\n");
			system("pause");
		}
	else{
		printf("Opção inválida\nDigite novamente\n");
        system("pause");
        cadastrousuario();
	}
	getch();
	menuusuario();
}

void consulta1(void){
	system("cls");

    FILE *parq;
    parq= fopen("agenda.txt","rb");
    if(parq==NULL)
    	printf("Erro ao abrir o arquivo!");
    else{
    	while(fread(&contato, sizeof(struct Contato), 1, parq)==1){
    		/*if(!strcmp(contato.nome, aux)){
    			puts(contato.nome);
    			puts(contato.sobrenome);
    			puts(contato.num);
			}else
			if(strcmp(contato.nome, aux)!=0){
				printf("Contato não encontrado!\n");
				system("pause");
				menuusuario();
			}*/

			puts(contato.nome);
			puts(contato.sobrenome);
    		puts(contato.num);
    		printf("\n\n");
    	}
	}
	fclose(parq);
	system("pause");
}

void excluir1(){
	system("cls");

	char nome[30];

	printf("Nome: ");
	fflush(stdin);
	gets(nome);
	fflush(stdin);

	FILE *parq = fopen("agenda.txt", "rb");
	FILE *aux = fopen("auxiliar.txt", "ab");
	fflush(stdin);
		while(fread(&contato, sizeof(struct Contato), 1, parq)==1){
		if(strcmp(nome, contato.nome) != 0)
			fwrite(&contato, sizeof(struct Contato), 1, aux);
	}
	fclose(parq);
	fclose(aux);
	remove("agenda.txt");
	rename("auxiliar.txt", "agenda.txt");
}

int menuusuario(){
	system("cls");
	int i;
	int op;


	//quadradinho

	for(i=39;i<64;i++){
		gotoxy(i,10);
		putchar(196);
		gotoxy(i,15);
		putchar(196);
	}

	for(i=11;i<15;i++){
		gotoxy(38,i);
		putchar(179);
		gotoxy(64,i);
		putchar(179);
	}

	gotoxy(38,10);
	putchar(218);
	gotoxy(64,10);
	putchar(191);
	gotoxy(38,15);
	putchar(192);
	gotoxy(64,15);
	putchar(217);

	//segundo quadradinho
	gotoxy(46,10);
	putchar(193);
	gotoxy(55,10);
	putchar(193);
	gotoxy(55,8);
	putchar(191);
	gotoxy(46,8);
	putchar(218);
	gotoxy(46,9);
	putchar(179);
	gotoxy(55,9);
	putchar(179);

	for(i=47;i<55;i++){
		gotoxy(i,8);
		putchar(196);
	}

	gotoxy(30, 5);
	printf("=========================");
	gotoxy(39,6);
	printf("AGENDA\n");
	gotoxy(30,7);
	printf("=========================");
	gotoxy(47,9);
    printf("Contatos");
    gotoxy(39,11);
    printf("1-ADICIONAR NOVO USUARIO");
	gotoxy(39,12);
	printf("2-LISTAR CONTATOS");
	gotoxy(39,13);
	printf("3-EXCLUIR CONTATO");
	gotoxy(39,14);
	printf("0-RETORNAR");
	gotoxy(40,16);
    printf("OPCAO DESEJADA:");
    scanf("%d",&op);
	return op;
}

int main() {
	int controle = 1;

	while(controle){
		int op = menuusuario();
		switch(op){
			case 0:
				controle = 0;
				break;
			case 1:
				cadastrousuario();
				break;
			case 2:
				consulta1();
				break;
			case 3:
				excluir1();
				break;
			default:
				printf("opcao invalida\n");
		}
	}
}
