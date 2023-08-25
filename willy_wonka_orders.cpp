/*  Programa Anual : Deposito e armazenamento de produtos na FABRICA  WILLY WONKA

Alunos:

Pedro Arthur B.K N°27
Last update 2020



Instruções por Professora  Ariane Scarelli.

*/

//Bibliotecas
#include <stdio.h>
#include <conio.h>
//#include <conio.c>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#define COL 100
#define LIN 40

//----------------------------------------------------------------------

//Ponteiro 
FILE *fp_Empresa;

//----------------------------------------------------------------------

//Estruturas
struct stEmpresa
{
	char Empresa [30];
	int Id;
	char Produto [30];
	char qtde [10];
	char Origem [25];
	char Custo [10];
	char Email_Parceiro [30];
	char excluido;
	
}cadastro;

//----------------------------------------------------------------------
  

//Cabeçalhos (Protótipos)
void cadast();
void gotoxy(int x, int y);
void textcolor(int newcolor);
void textbackground(int newcolor);
void intro();
void borda();
void cursor(int x);
void menu();
void tela_menu();
int setas(int, int, int, int, int);
void salvar_dados();
void tela_cadastrar_PARCEIRO();
int valida_id_EMPRESA();
void limpa_char(char limpa[], const int tam);
void limpa_linha(const int linha);
void mostra_dados();
void tela_dados();
void aviso();
void ver(int *i);
void pesquisa_cod();
void tela_consultar_Empresa();
void tela_consultar_Empresa_geral();
void consultar_parceiro();
void consultar_Empresa_geral_especifico(int linha_tabela, int pag);
void consultar_Empresa();
void mostraconteudo();
void mostra();
void sobre();
void finalizar_programa();

//----------------------------------------------------------------------

text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 40, 100, 1, 1};

void gotoxy(int x, int y)
{
  COORD c;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//----------------------------------------------------------------------

void cursor(int x) 
{
	switch (x) 
	{
		case 0: 
		{
			CONSOLE_CURSOR_INFO cursor = {1, FALSE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
		case 1: 
		{
			CONSOLE_CURSOR_INFO cursor = {1, TRUE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
	}
}

//----------------------------------------------------------------------

void textcolor(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0xf0) | newcolor);
   vActual.attribute = (csbi.wAttributes & 0xf0) | newcolor;
}

//----------------------------------------------------------------------

void textbackground(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0x0f) | (newcolor << 4));
   vActual.attribute = (csbi.wAttributes & 0x0f) | (newcolor << 4);
}

//----------------------------------------------------------------------

//Principal
main()
{
	system("mode con: cols=100 lines=40"); //muda o tamanho da tela
	SetConsoleTitle("Chocolate LTDA - Willy Wonka"); //muda o nome na barra do Windows
	//system ("color x,y");    ---> x = plano de fundo , y = cor da letra.
	system ("color 4f");
	setlocale(LC_ALL,"Portuguese");
	intro();

	menu();
	/*cadast();
	mostraconteudo();*/
	finalizar_programa();
	
}

//----------------------------------------------------------------------

//Funções
void tela_cadastrar_PARCEIRO()
{
	int ci = 10;
	int li = 10;
	
	borda();
	
	textcolor(15); 
	gotoxy(42,6);printf("CADASTRO DE PARCEIRO");
	
	setlocale(LC_ALL,"Portuguese");
	
	textcolor(15); 
	gotoxy(ci,li);printf("ID da Empresa:");
	gotoxy(ci,li+3);printf("Nome da Empresa:");
	gotoxy(ci,li+6);printf("Origem:");
	gotoxy(ci,li+9);printf("Produto:");
	gotoxy(ci,li+12);printf("Quantidade de seu produto (Kg):");
	gotoxy(ci,li+15);printf("Valor final de seu produto(R$):");
	gotoxy(ci,li+18);printf("E-MAIL de sua empresa:");


}

//----------------------------------------------------------------------

void cadast()
{
	//system ("color x,y");    ---> x = plano de fundo , y = cor da letra.
	system ("color 4f");
	int p;
	
		while(true)
	{
		system("cls");
  		tela_cadastrar_PARCEIRO();
		if((fp_Empresa = fopen ("Empresa.bin","ab+")) == NULL)
		{
			textcolor(15); 
			gotoxy(37,30);printf("ERRO ao abrir o arquivo");
			textcolor(15);
			getch();
			gotoxy(3,35);
			exit(1);
		}
		else
		{
			cursor(1);
			int aux_id = valida_id_EMPRESA(); 
			if(aux_id == 0) 
			{
				fclose(fp_Empresa);
				return;
			}
			else
			{
				int Empresa;
				cadastro.Id = aux_id;
				
				do 
				{
					
					cursor(1);
					limpa_char(cadastro.Empresa,30); 
					setlocale(LC_ALL,"Portuguese");
					gotoxy(27,13);gets(cadastro.Empresa); 
					
					gotoxy(33,15);textcolor(0);textbackground(14);printf("O cursor volta em uma forma de corrgir caso digitou errado!");
					textbackground(4);
					textcolor(15);
					setlocale(LC_ALL,"C");
					p = 1;
					if(strlen(cadastro.Empresa) < 1) 
					{
						textcolor(15); 
						setlocale(LC_ALL,"Portuguese");
						gotoxy(42,30);printf("Campo obrigatório");
						setlocale(LC_ALL,"C");
						textcolor(15);
						cursor(0);
						getch();
						limpa_linha(30); 
						tela_cadastrar_PARCEIRO();
						p = 0;
					}
					else if(strlen(cadastro.Empresa) > 30) 
					{
						textcolor(15); 
						setlocale(LC_ALL,"Portuguese");
						gotoxy(34,30);printf("Limite de 30 dígitos ");
						setlocale(LC_ALL,"C");
						textcolor(15); 
						cursor(0);
						getch();
						limpa_linha(13); 
						limpa_linha(30); 
						tela_cadastrar_PARCEIRO();
						p = 0;
					}
				}while(p == 0);
				
				//----------------------------------------------------------------

				
				do 
				{
					
					cursor(1);
					limpa_char(cadastro.Empresa,30); 
					setlocale(LC_ALL,"Portuguese");
					gotoxy(27,13);gets(cadastro.Empresa); 
					setlocale(LC_ALL,"C");
					p = 1;
					if(strlen(cadastro.Empresa) < 1) 
					{
						textcolor(15); 
						setlocale(LC_ALL,"Portuguese");
						gotoxy(42,30);printf("Campo obrigatório");
						setlocale(LC_ALL,"C");
						textcolor(15);
						cursor(0);
						getch();
						limpa_linha(30); 
						tela_cadastrar_PARCEIRO();
						p = 0;
					}
					else if(strlen(cadastro.Empresa) > 30) 
					{
						textcolor(15); 
						setlocale(LC_ALL,"Portuguese");
						gotoxy(34,30);printf("Limite de 30 dígitos ");
						setlocale(LC_ALL,"C");
						textcolor(15); 
						cursor(0);
						getch();
						limpa_linha(13); 
						limpa_linha(30); 
						tela_cadastrar_PARCEIRO();
						p = 0;
					}
				}while(p == 0);
				
				//----------------------------------------------------------------
				
				do 
				{
					cursor(1);
					limpa_char(cadastro.Origem,25); 
					setlocale(LC_ALL,"Portuguese");
					gotoxy(18,16);gets(cadastro.Origem); 
					setlocale(LC_ALL,"C");
					p = 1;
					if(strlen(cadastro.Origem) < 1) 
					{
						textcolor(15); 
						setlocale(LC_ALL,"Portuguese");
						gotoxy(42,30);printf("Campo obrigatório");
						setlocale(LC_ALL,"C");
						textcolor(15); 
						cursor(0);
						getch();
						limpa_linha(30);
						tela_cadastrar_PARCEIRO();
						p = 0;
					}
					else if(strlen(cadastro.Origem) > 25) 
					{
						textcolor(10); 
						setlocale(LC_ALL,"Portuguese");
						gotoxy(33,30);printf("Limite de 25 dígitos ");
						setlocale(LC_ALL,"C");
						textcolor(15); 
						cursor(0);
						getch();
						limpa_linha(16); 
						limpa_linha(30); 
						tela_cadastrar_PARCEIRO();
						p = 0;
					}
				}while(p == 0);
				
				//----------------------------------------------------------------
				
				do 
				{
					cursor(1);
					limpa_char(cadastro.Produto,30); 
					setlocale(LC_ALL,"Portuguese");
					gotoxy(19,19);gets(cadastro.Produto); 
					setlocale(LC_ALL,"C");
					p = 1;
					if(strlen(cadastro.Produto) < 1) 
					{
						textcolor(15); 
						setlocale(LC_ALL,"Portuguese");
						gotoxy(42,30);printf("Campo obrigatório");
						setlocale(LC_ALL,"C");
						textcolor(15);
						cursor(0);
						getch();
						limpa_linha(30); 
						tela_cadastrar_PARCEIRO();
						p = 0;
					}
					else if(strlen(cadastro.Produto) > 30) 
					{
						textcolor(15);
						setlocale(LC_ALL,"Portuguese");
						gotoxy(32,30);printf("Limite de 30 dígitos");
						setlocale(LC_ALL,"C");
						textcolor(15); 
						cursor(0);
						getch();
						limpa_linha(19); 
						limpa_linha(30); 
						tela_cadastrar_PARCEIRO();
						p = 0;
					}
				}while(p == 0);
				
				
				//----------------------------------------------------------------
				
				do 
				{
					cursor(1);
				//	limpa_char(cadastro.qtde,30); 
					setlocale(LC_ALL,"Portuguese");
					gotoxy(42,22);gets(cadastro.qtde); 
					setlocale(LC_ALL,"C");
					p = 1;
					if(strlen(cadastro.qtde) < 0) 
					{
						textcolor(15); 
						setlocale(LC_ALL,"Portuguese");
						gotoxy(42,30);printf("Campo obrigatório");
						setlocale(LC_ALL,"C");
						textcolor(15);
						cursor(0);
						getch();
						limpa_linha(30); 
						tela_cadastrar_PARCEIRO();
						p = 0;
					}
					else if(strlen(cadastro.qtde) > 30) 
					{
						textcolor(15);
						setlocale(LC_ALL,"Portuguese");
						gotoxy(32,30);printf("Limite de 30 dígitos");
						setlocale(LC_ALL,"C");
						textcolor(15); 
						cursor(0);
						getch();
						limpa_linha(19); 
						limpa_linha(30); 
						tela_cadastrar_PARCEIRO();
						p = 0;
					}
				}while(p == 0);
				
				//----------------------------------------------------------------
				
				do 
				{
					cursor(1);
				//	limpa_char(cadastro.Custo,10); 
					setlocale(LC_ALL,"Portuguese");
					gotoxy(42,25);gets(cadastro.Custo); 
					setlocale(LC_ALL,"C");
					p = 1;
					if(strlen(cadastro.Custo) < 0) 
					{
						textcolor(15); 
						setlocale(LC_ALL,"Portuguese");
						gotoxy(42,30);printf("Campo obrigatório");
						setlocale(LC_ALL,"C");
						textcolor(15);
						cursor(0);
						getch();
						limpa_linha(30); 
						tela_cadastrar_PARCEIRO();
						p = 0;
					}
					else if(strlen(cadastro.Custo) > 30) 
					{
						textcolor(15);
						setlocale(LC_ALL,"Portuguese");
						gotoxy(32,30);printf("Limite de 30 dígitos");
						setlocale(LC_ALL,"C");
						textcolor(15); 
						cursor(0);
						getch();
						limpa_linha(19); 
						limpa_linha(30); 
						tela_cadastrar_PARCEIRO();
						p = 0;
					}
				}while(p == 0);
				
			//----------------------------------------------------------------

				
				do 
				{
					cursor(1);
					limpa_char(cadastro.Email_Parceiro,60); 
					setlocale(LC_ALL,"Portuguese");
					gotoxy(34,28);gets(cadastro.Email_Parceiro); 
					setlocale(LC_ALL,"C");
					p = 1;
					if(strlen(cadastro.Email_Parceiro) < 1) 
					{
						textcolor(15); 
						setlocale(LC_ALL,"Portuguese");
						gotoxy(42,30);printf("Campo obrigatório");
						setlocale(LC_ALL,"C");
						textcolor(15);
						cursor(0);
						getch();
						limpa_linha(30); 
						tela_cadastrar_PARCEIRO();
						p = 0;
					}
					else if(strlen(cadastro.Email_Parceiro) > 30) 
					{
						textcolor(15);
						setlocale(LC_ALL,"Portuguese");
						gotoxy(32,30);printf("Limite de 30 dígitos");
						setlocale(LC_ALL,"C");
						textcolor(15); 
						cursor(0);
						getch();
						limpa_linha(19); 
						limpa_linha(30); 
						tela_cadastrar_PARCEIRO();
						p = 0;
					}
				}while(p == 0);
				
				//----------------------------------------------------------------
				
				cursor(0);
				textcolor(15); 
				gotoxy(32,30);printf("Tem certeza que deseja salvar? (S/N)");
				while(true)
				{
					int tecla = getch();
					if(tecla == 's' || tecla == 'S')
					{
						if(fwrite(&cadastro, sizeof(cadastro), 1, fp_Empresa) != 1)
						{
							limpa_linha(30);
							gotoxy(38,30);printf("Erro ao salvar o cadastro");
							fclose(fp_Empresa);
							getch();
							break;
						}
						else
						{
							fflush(fp_Empresa);
							fclose(fp_Empresa);
							limpa_linha(30);
							gotoxy(37,30);printf("Cadastro salvo com sucesso!");
							getch();
							break;
						}
					}
						else if(tecla == 'n' || tecla == 'N')
						{
							limpa_linha(30);
							fclose(fp_Empresa);
							gotoxy(41,30);printf("Cadastro cancelado");
							getch();
							break;
						}
				}
			}
		}
		limpa_linha(30); 
		gotoxy(33,30);printf("Deseja continuar cadastrando? (S/N)");
		while(true)
		{
			int tecla = getch();
			
			if(tecla == 'S' || tecla == 's')
				break;
				
			else if(tecla == 'N' || tecla == 'n')
				return;
				
		}
	}
}


//----------------------------------------------------------------------



int valida_id_EMPRESA()
{
	char c_id_Empresa[4];
	int i_id_Empresa;
	int p;
	do
	{
		limpa_char(c_id_Empresa, 4);  
		
		textcolor(6);
		gotoxy(5,37);printf("Digite ZERO como ID para voltar ao Menu");
		textcolor(15); 
		p = 1;
		cursor(1);
		gotoxy(25,10);gets(c_id_Empresa);
		
		if((strlen(c_id_Empresa)) < 0) 
		{
			textcolor(15); 
			setlocale(LC_ALL,"Portuguese");
			gotoxy(42,30);printf("Campo obrigatório");
			setlocale(LC_ALL,"C");
			cursor(0);
			getch();
			system("cls");
			tela_cadastrar_PARCEIRO();
			p = 0;
		}
		
		else if((strlen(c_id_Empresa)) <2 && c_id_Empresa[0] == '0') 
		{
			return 0;
		}
		
		else if((strlen(c_id_Empresa)) > 3) 
		{
			textcolor(15);
			setlocale(LC_ALL,"Portuguese");
			gotoxy(36,30);printf("Limite de 3 números para a ID");
			setlocale(LC_ALL,"C");
			cursor(0);
			getch();
			system("cls");
			tela_cadastrar_PARCEIRO();
			p = 0;
		}
		
		else if(c_id_Empresa[0] != '0' && c_id_Empresa[0] != '1' && 
				c_id_Empresa[0] != '2' && c_id_Empresa[0] != '3' && 
				c_id_Empresa[0] != '4' && c_id_Empresa[0] != '5' &&  
				c_id_Empresa[0] != '6' && c_id_Empresa[0] != '7' && 
				c_id_Empresa[0] != '8' && c_id_Empresa[0] != '9')
				{
					textcolor(15); 
					setlocale(LC_ALL,"Portuguese");
					gotoxy(39,30);printf("Somente números inteiros");
					setlocale(LC_ALL,"C");
					cursor(0);
					getch();
					system("cls");
					tela_cadastrar_PARCEIRO();
					p = 0;
				}
		
		else if(c_id_Empresa[1] != '0' && c_id_Empresa[1] != '1' && 
				c_id_Empresa[1] != '2' && c_id_Empresa[1] != '3' && 
				c_id_Empresa[1] != '4' && c_id_Empresa[1] != '5' &&  
				c_id_Empresa[1] != '6' && c_id_Empresa[1] != '7' && 
				c_id_Empresa[1] != '8' && c_id_Empresa[1] != '9' &&
				c_id_Empresa[1] != NULL)
				{
					textcolor(15); 
					setlocale(LC_ALL,"Portuguese");
					gotoxy(39,30);printf("Somente números inteiros");
					setlocale(LC_ALL,"C");
					cursor(0);
					getch();
					system("cls");
					tela_cadastrar_PARCEIRO();
					p = 0;
				}
				
		else if(c_id_Empresa[2] != '0' && c_id_Empresa[2] != '1' && 
				c_id_Empresa[2] != '2' && c_id_Empresa[2] != '3' && 
				c_id_Empresa[2] != '4' && c_id_Empresa[2] != '5' &&  
				c_id_Empresa[2] != '6' && c_id_Empresa[2] != '7' && 
				c_id_Empresa[2] != '8' && c_id_Empresa[2] != '9' &&
				c_id_Empresa[2] != NULL)
				{
					textcolor(15);
					setlocale(LC_ALL,"Portuguese");
					gotoxy(39,30);printf("Somente números inteiros");
					setlocale(LC_ALL,"C");
					cursor(0);
					getch();
					system("cls");
					tela_cadastrar_PARCEIRO();
					p = 0;
				}
		
		else 
		{
			i_id_Empresa = atoi(c_id_Empresa);
			rewind(fp_Empresa); 
			
			while(fread(&cadastro,sizeof(cadastro),1,fp_Empresa) == 1 && (i_id_Empresa != cadastro.Id )); 
			if(i_id_Empresa == cadastro.Id) 
			{
				textcolor(15); 
				setlocale(LC_ALL,"Portuguese");
				gotoxy(44,30);printf("ID já em uso");
				setlocale(LC_ALL,"C");
				cursor(0); 
				getch();
				system("cls"); 
				tela_cadastrar_PARCEIRO(); 
				cursor(1);
				p = 0;
			}
		}
	}while(p == 0);
	gotoxy(5,37);printf("                                           "); 
	
	return i_id_Empresa;
}

//----------------------------------------------------------------------

void limpa_char(char limpa[], const int tam)
{
	for(int i=0; i<tam; i++)
		limpa[i] = NULL;
}

//----------------------------------------------------------------------

void limpa_linha(const int linha)
{
	for(int i=4; i<98; i++)
	{
		gotoxy(i,linha);printf(" ");
	}
}

//----------------------------------------------------------------------



//----------------------------------------------------------------------

void menu()
{
	int op2;
	int num;
	int tes;
	int op1;
	int pes;
	
	int opcao;
	while(true)
	{
		tela_menu();
		opcao = setas(25,12,10,2,0);
		switch(opcao)
		{
			case 1: 
				{ 
					cadast();
					break;
				}
			
			case 3: 
				{
					consultar_Empresa();
					//mostra_dados();
					break;
				}
			case 4: 
				{
					sobre();
					break;
				}

			case 10: 
				{
					textcolor(11);
					textbackground(0);
					gotoxy(32,33);printf(" Tem certeza que deseja finalizar? (S/N) ");
					textcolor(15);
					textbackground(4);
					while(true)
					{
						int tecla;
						tecla = getch();
						if(tecla == 's' || tecla == 'S')
						{
							return;
						}
						else if(tecla == 'n' || tecla == 'N')
						{
							break;
						}
					}
				}
		}
	}
}

//----------------------------------------------------------------------
void tela_dados()
{
//	mostra();

	system("color 2f");
	textcolor(15);
	gotoxy(3,1);printf(" _______________________________________________________________________________________________");
	gotoxy(3,2); printf("| Código |     Empresa     |    Origem    |       Produto      | Quantidade |     E-mail      |");
	gotoxy(3,3); printf("|--------|-----------------|--------------|--------------------|------------|-----------------|");
	gotoxy(3,4); printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,5); printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,6); printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,7); printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,8); printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,9); printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,10);printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,11);printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,12);printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,13);printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,14);printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,15);printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,16);printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,17);printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,18);printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,19);printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,20);printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,21);printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,22);printf("|        |                 |              |                    |            |                 |");
	gotoxy(3,23);printf("|________|_________________|______________|____________________|____________|_________________|");
	mostra();
}


//-------------------------------------------------------------------

void ver(int *i)
{
	gotoxy(5,*i);printf(" ", cadastro.Id);
	gotoxy(10,*i);printf(" ",cadastro.Empresa);
	gotoxy(17,*i);printf(" ",cadastro.Origem);
	gotoxy(24,*i);printf(" ",cadastro.Produto); 
	gotoxy(31,*i);printf(" ",cadastro.qtde);
	gotoxy(38,*i);printf(" ", cadastro.Email_Parceiro); 	
	
}


//-------------------------------------------------------------------

void mostra_dados()
{

//	FILE *fp_Empresa;
	int i=3;
	char y;
	char tes;
	long fposicao;
	
	fp_Empresa=fopen("Empresa.bin","rb+");
	tela_dados();
	
	while(!feof(fp_Empresa))
	{
		
		if(fread(&cadastro, sizeof(cadastro), 1,fp_Empresa) == 1 )
		{
			ver(&i); 
			i++;
		}
	
		if (i==23)
		{
			fposicao=ftell(fp_Empresa);
			gotoxy(15,24);printf("(qualquer tecla para mudar de página ou  <enter> para retornar ao menu)");
			y=getche();
			if(y==13)
			{
				system("cls");
				int menu();
				menu();
			}
			system("cls");
			tela_dados();	
			i=3;
			ver(&i);
		}
	}
	fclose(fp_Empresa);
	gotoxy(25,24);printf("(Tecle <enter> para retornar ao menu)");
	tes=getch();
	while(tes!=13)
	{
		tes=getch();
	}
	if(tes==13)
 	{
		system("cls");
		int menu();
		menu();
	}
}

//-------------------------------------------------------------------

//----------------------------------------------------------------------


void pesquisa_cod()
{
	FILE *fp_Empresa;
	int cod;
	int a;
	char volt;
	int num;
	
	fp_Empresa=fopen("Empresa.bin", "rb+");
	do
	{
		system("cls");
		borda();
		gotoxy(42,6);textcolor(15);printf("PESQUISA POR CÓDIGO");
		gotoxy(35,11);textcolor(15); printf("(digite 0 para retornar ao menu)");
		gotoxy(40,9); textcolor(15); printf("Código para pesquisa: ");
		gotoxy(10,7);printf("----------------------------------------------------------------------------------");
		do
		{
			gotoxy(63,9);num=scanf("%d", &cod);
			if(num!=1)
			{
				gotoxy(30,10);textcolor(15);printf("(DIGITE UM NÚMERO)");
				textcolor(2);
				gotoxy(50,8);printf("        ");
				gotoxy(50,8);scanf("%s");
			}
		}while(num!=1);
		gotoxy(30,10);printf("                  ");
		int num1;
		while(cod<0)
		{
			gotoxy(50,8); printf("     ");
			borda();
				do
			{
				gotoxy(50,8);num1=scanf("%d", &cod);
				if(num1!=1)
				{
					gotoxy(37,10);textcolor(15);printf("(DIGITE UM NÚMERO)");
					textcolor(15);
					gotoxy(63,3);printf("       ");
					gotoxy(50,8);scanf("%s");
				}
			}while(num1!=1);
			gotoxy(37,10);printf("                    ");
		}
		gotoxy(22,9); 
		borda();
		rewind(fp_Empresa);
		if(cod==0)
		{
			system("cls");
			int menu();
			menu();
		}
		while(!feof(fp_Empresa))
		{
			a=0;
			while (a == 0)
			{
				if (fread(&cadastro, sizeof(cadastro), 1, fp_Empresa)==1)
				{
					if (cadastro.Id==cod)
					{
						system("cls");
						mostra_dados();
						//mostra();
					/*textcolor(15);
					textbackground(2);
						gotoxy(28,10); printf("Código: %d", cadastro.Id);
						gotoxy(28,11); printf("Nome: %s", cadastro.Empresa);
						gotoxy(28,12); printf("Origem: %s", cadastro.Origem);
						gotoxy(28,13); printf("Produto: %s", cadastro.Produto);
						gotoxy(28,14); printf("Quantidade:", cadastro.qtde);
						gotoxy(28,15); printf("E-mail: %s", cadastro.Email_Parceiro);
						textbackground(4);*/
						a = 1;
						break;
						
					}
				}
				else 
				{
					a=2;
				}
			}
			if(a == 2)
			{
				gotoxy(25,14); textcolor(15); printf("*********CÓDIGO NÃO ENCONTRADO*********");
				break;
			}
	
		}
		gotoxy(28,19); textcolor(15); printf("Deseja pesquisar outro código? (s/n): ");
		gotoxy(65,19); volt=getch();
		while(volt!='N' and volt!='n' and volt!='S' and volt !='s')
		{
			gotoxy(65,19); printf("    "); 
			gotoxy(65,19); volt=getch();
		}
		if (volt=='N' or volt=='n')
		{
			system("cls");
			int menu();
			menu();
		}
		if (volt=='S' or volt=='s')
		{
			system("cls");
		}
		} while(volt=='S'or volt=='s');
}



//----------------------------------------------------------------------

void mostra()
{
	//mostra_dados();
     	     textcolor(15);
	
	gotoxy(6,4); printf("%d", cadastro.Id);
	gotoxy(13,4); printf("%s", cadastro.Empresa);
	gotoxy(33,4); printf("%s", cadastro.Origem);
	gotoxy(47,4); printf("%s", cadastro.Produto);
	gotoxy(68,4); printf("%s", cadastro.qtde);
	gotoxy(80,4); printf("%s", cadastro.Email_Parceiro);

	//a = 1;
	//break;
}
//----------------------------------------------------------------------



//----------------------------------------------------------------------


void tela_menu()
{
	
	
	textbackground(4); 
	system("cls");
	borda();
	textcolor(15); 
	gotoxy(50,6);printf("MENU");
	textcolor(15); 
	setlocale(LC_ALL,"Portuguese");
	gotoxy(25,12);printf("Cadastrar parceiro"); 
	gotoxy(25,14);printf("------------Willy Wonka---------"); 
	gotoxy(25,16);printf("Consultar dados"); 
	gotoxy(25,18);printf("Sobre"); 
	gotoxy(25,20);printf("------------Willy Wonka---------"); 
	gotoxy(25,22);printf("**Bem-Vindo estrelinhas, a terra diz olá!**");
	gotoxy(25,24);printf("*Sabiam, minha fabríca é unica ");
	gotoxy(25,25);printf("que mistura chocolate com uma ");
	gotoxy(25,26);printf("Cachoeira.*");
	textcolor(6);
	gotoxy(25,28);printf("-> O chocolate faz você se sentir apaixonado! <-");
	textcolor(15);
	gotoxy(25,30);printf("Finalizar Programa");
	

	
	textcolor(15);
	gotoxy(5,37);printf("Utilize as ");
	textcolor(0);
	textbackground(15); 
	printf("[SETAS]");
	textcolor(15); 
	textbackground(4); 
	printf(" para mover e ");
	textcolor(0); 
	textbackground(15); 
	printf("[ENTER]");
	textcolor(15);
	textbackground(4);
	printf(" para selecionar");
	textcolor(15);
	aviso();
	
}

//----------------------------------------------------------------------
void aviso()
{	
	textbackground(14); 
	textcolor(0); 
	gotoxy(50,10); printf("**-> Apenas é possivel interação          ");
	gotoxy(50,11); printf("com o usuario pelos campos de             ");
	gotoxy(50,12); printf("cadastro, consulta, sobre e finalizar <-**");
	textbackground(4);
	


}

//----------------------------------------------------------------------

int setas(int col, int lin, int num_de_op, int distancia_das_op, int esc_volta) 
{
	cursor(0); 
	col -=3;
	int fp_Empresa = 1;
	int tecla;
	textcolor(0); 
	gotoxy(col,lin);printf("->"); 
	do
	{
		tecla = getch();
		switch(tecla)
		{
			case 72: 
			{
				if(fp_Empresa == 1)
				{
					gotoxy(col,lin);printf("  ");
					lin += (num_de_op-1)*distancia_das_op;
					gotoxy(col,lin);printf("->");
					fp_Empresa = num_de_op;
				}
				else
				{
					gotoxy(col,lin);printf("  ");
					lin -= distancia_das_op;
					gotoxy(col,lin);printf("->"); 
					fp_Empresa--;
				}
				break;
			}
			case 80: 
			{
				if(fp_Empresa == num_de_op)
				{
					gotoxy(col,lin);printf("  ");
					lin -= (num_de_op - 1)*distancia_das_op;
					gotoxy(col,lin);printf("->"); 
					fp_Empresa = 1;
				}
				else
				{
					gotoxy(col,lin);printf("  ");
					lin += distancia_das_op;
					gotoxy(col,lin);printf("->"); 
					fp_Empresa++;
				}
				break;	
				}
			case 27: 
			{
				if(esc_volta == 1) 
					return 0;
				else
					break;
			}
		}
	}while(tecla != 13); 
	textcolor(15); 
	return fp_Empresa; 
}

//----------------------------------------------------------------------

void intro()
{
      	gotoxy(18,5);printf("%s",__TIME__);
      	gotoxy(17,5);printf("|");
        gotoxy(5,5);printf("%s",__DATE__);
        
	int li = 10;
	int ci = 26;
	
	int li_load = 15;
	int ci_load = 50;
	
	int vel = 10; //velocidade em que as letras são escritas
	int vel_load = 15; //velocidade do loading
	
	int tecla = 0;	
	cursor(0);	
    borda();
	
	textcolor(15); 
	
	gotoxy(85,35);printf("Loading...");
	
	textbackground(15); 
	
	textbackground(4); 

	
	textbackground(0); 
	
	//ANIMA logo
	
	textbackground(0);
	textcolor (15);
	
	gotoxy(30,5);printf("                                         ");
	Sleep(vel);
	gotoxy(30,6);printf("                                         ");
	Sleep(vel);
	gotoxy(30,7);printf("                                         ");
	Sleep(vel);
	gotoxy(30,8);printf("                                         ");
	Sleep(vel);
	gotoxy(30,9);printf("                                         ");
	Sleep(vel);
	gotoxy(30,10);printf("                                        ");
	Sleep(vel);
	gotoxy(30,11);printf("                                        ");
	Sleep(vel);
	gotoxy(30,12);printf("                                        ");
	Sleep(vel);
	gotoxy(30,13);printf("                                        ");
	Sleep(vel);
	gotoxy(30,14);printf("                                        ");
	Sleep(vel);
	gotoxy(30,15);printf("                                        ");
	Sleep(vel);
	gotoxy(30,16);printf("                                        ");
	Sleep(vel);
	gotoxy(30,17);printf("                                        ");
	Sleep(vel);
	gotoxy(30,18);printf("                                        ");
	Sleep(vel);
	gotoxy(30,19);printf("                                        ");
	Sleep(vel);
	gotoxy(30,20);printf("                                        ");
	Sleep(vel);
	//-----------------------
	gotoxy(31,5);printf(" ");
	Sleep(vel);
	gotoxy(32,5);printf(" ");
	Sleep(vel);
	gotoxy(33,5);printf(" ");
	Sleep(vel);
	gotoxy(34,5);printf(" ");
	Sleep(vel);
	gotoxy(35,5);printf(" ");
	Sleep(vel);
	gotoxy(36,5);printf(" ");
	Sleep(vel);
	gotoxy(37,5);printf(" ");
	Sleep(vel);
	gotoxy(38,5);printf(" ");
	Sleep(vel);
	gotoxy(39,5);printf(" ");
	Sleep(vel);
	gotoxy(40,5);printf(" ");
	Sleep(vel);
	gotoxy(41,5);printf(" ");
	Sleep(vel);
	gotoxy(42,5);printf(" ");
	Sleep(vel);
	gotoxy(43,5);printf(" ");
	Sleep(vel);
	gotoxy(44,5);printf(" ");
	Sleep(vel);
	gotoxy(45,5);printf(" ");
	Sleep(vel);
	gotoxy(46,5);printf(" ");
	Sleep(vel);
	gotoxy(47,5);printf(" ");
	Sleep(vel);
	gotoxy(48,5);printf(" ");
	Sleep(vel);
	gotoxy(49,5);printf(" ");
	Sleep(vel);
	gotoxy(50,5);printf(" ");
	Sleep(vel);
	gotoxy(51,5);printf(" ");
	Sleep(vel);
	gotoxy(52,5);printf(" ");
	Sleep(vel);
	gotoxy(53,5);printf(" ");
	Sleep(vel);
	gotoxy(54,5);printf(" ");
	Sleep(vel);
	gotoxy(55,5);printf(" ");
	Sleep(vel);
	gotoxy(56,5);printf(" ");
	Sleep(vel);
	gotoxy(57,5);printf(" ");
	Sleep(vel);
	gotoxy(58,5);printf(" ");
	Sleep(vel);
	gotoxy(59,5);printf(" ");
	Sleep(vel);
	gotoxy(60,5);printf(" ");
	Sleep(vel);
	gotoxy(61,5);printf(" ");
	Sleep(vel);
	gotoxy(62,5);printf(" ");
	Sleep(vel);
	gotoxy(63,5);printf(" ");
	Sleep(vel);
	gotoxy(64,5);printf(" ");
	Sleep(vel);
	gotoxy(65,5);printf(" ");
	Sleep(vel);
	gotoxy(66,5);printf(" ");
	Sleep(vel);
	gotoxy(67,5);printf(" ");
	Sleep(vel);
	gotoxy(68,5);printf(" ");
	Sleep(vel);
	gotoxy(69,5);printf(" ");
	Sleep(vel);
	//----------------------
	gotoxy(70,5);printf(" ");
	Sleep(vel);
	gotoxy(70,6);printf(" ");
	Sleep(vel);
	gotoxy(70,7);printf(" ");
	Sleep(vel);
	gotoxy(70,8);printf(" ");
	Sleep(vel);
	gotoxy(70,9);printf(" ");
	Sleep(vel);
	gotoxy(70,10);printf(" ");
	Sleep(vel);
	gotoxy(70,11);printf(" ");
	Sleep(vel);
	gotoxy(70,12);printf(" ");
	Sleep(vel);
	gotoxy(70,13);printf(" ");
	Sleep(vel);
	gotoxy(70,14);printf(" ");
	Sleep(vel);
	gotoxy(70,15);printf(" ");
	Sleep(vel);
	gotoxy(70,16);printf(" ");
	Sleep(vel);
	gotoxy(70,17);printf(" ");
	Sleep(vel);
	gotoxy(70,18);printf(" ");
	Sleep(vel);
	gotoxy(70,19);printf(" ");
	Sleep(vel);
	gotoxy(70,20);printf(" ");
	Sleep(vel);
    //-----------------------
	gotoxy(30,21);printf("                                        ");
	Sleep(vel);
	gotoxy(30,22);printf(" ");
	Sleep(vel);
	gotoxy(30,23);printf(" ");
	Sleep(vel);
	gotoxy(30,24);printf(" ");
	Sleep(vel);
	gotoxy(30,25);printf(" ");
	Sleep(vel);
	gotoxy(70,21);printf(" ");
	Sleep(vel);
	gotoxy(70,22);printf(" ");
	Sleep(vel);
	gotoxy(70,23);printf(" ");
	Sleep(vel);
	gotoxy(70,24);printf(" ");
	Sleep(vel);
	gotoxy(70,25);printf(" ");
	Sleep(vel);
	//-----------------------
	//faixa 
	textbackground(5); //roxo
	
	gotoxy(30,22);printf(" ");
	Sleep(vel);
	gotoxy(30,23);printf("                                         ");
	Sleep(vel);
	gotoxy(30,24);printf("                                        ");
	Sleep(vel);
	gotoxy(30,25);printf(" ");
    Sleep(vel);
	//------------------------
	gotoxy(31,22);printf(" ");
	Sleep(vel);
	gotoxy(32,22);printf(" ");
	Sleep(vel);
	gotoxy(33,22);printf(" ");
	Sleep(vel);
	gotoxy(34,22);printf(" ");
	Sleep(vel);
	gotoxy(35,22);printf(" ");
	Sleep(vel);
	gotoxy(36,22);printf(" ");
	Sleep(vel);
	gotoxy(37,22);printf(" ");
	Sleep(vel);
	gotoxy(38,22);printf(" ");
	Sleep(vel);
	gotoxy(39,22);printf(" ");
	Sleep(vel);
	gotoxy(40,22);printf(" ");
	Sleep(vel);
	gotoxy(41,22);printf(" ");
	Sleep(vel);
	gotoxy(42,22);printf(" ");
	Sleep(vel);
	gotoxy(43,22);printf(" ");
	Sleep(vel);
	gotoxy(44,22);printf(" ");
	Sleep(vel);
	gotoxy(45,22);printf(" ");
	Sleep(vel);
	gotoxy(46,22);printf(" ");
	Sleep(vel);
	gotoxy(47,22);printf(" ");
	Sleep(vel);
	gotoxy(48,22);printf(" ");
	Sleep(vel);
	gotoxy(49,22);printf(" ");
	Sleep(vel);
	gotoxy(50,22);printf(" ");
	Sleep(vel);
	gotoxy(51,22);printf(" ");
	Sleep(vel);
	gotoxy(52,22);printf(" ");
	Sleep(vel);
	gotoxy(53,22);printf(" ");
	Sleep(vel);
	gotoxy(54,22);printf(" ");
	Sleep(vel);
	gotoxy(55,22);printf(" ");
	Sleep(vel);
	gotoxy(56,22);printf(" ");
	Sleep(vel);
	gotoxy(57,22);printf(" ");
	Sleep(vel);
	gotoxy(58,22);printf(" ");
	Sleep(vel);
	gotoxy(59,22);printf(" ");
	Sleep(vel);
	gotoxy(60,22);printf(" ");
	Sleep(vel);
	gotoxy(61,22);printf(" ");
	Sleep(vel);
	gotoxy(62,22);printf(" ");
	Sleep(vel);
	gotoxy(63,22);printf(" ");
	Sleep(vel);
	gotoxy(64,22);printf(" ");
	Sleep(vel);
	gotoxy(65,22);printf(" ");
	Sleep(vel);
	gotoxy(66,22);printf(" ");
	Sleep(vel);
	gotoxy(67,22);printf(" ");
	Sleep(vel);
	gotoxy(68,22);printf(" ");
	Sleep(vel);
	gotoxy(69,22);printf(" ");
	Sleep(vel);
	//------------------------
	gotoxy(70,22);printf(" ");
	Sleep(vel);
	gotoxy(70,23);printf(" ");
	Sleep(vel);
	gotoxy(70,24);printf(" ");
	Sleep(vel);
	gotoxy(70,25);printf(" ");
	Sleep(vel);
	//-----------------------
	gotoxy(69,25);printf(" ");
    Sleep(vel);
	gotoxy(68,25);printf(" ");
	Sleep(vel);
	gotoxy(67,25);printf(" ");
	Sleep(vel);
	gotoxy(66,25);printf(" ");
	Sleep(vel);
	gotoxy(65,25);printf(" ");
	Sleep(vel);
	gotoxy(64,25);printf(" ");
	Sleep(vel);
	gotoxy(63,25);printf(" ");
	Sleep(vel);
	gotoxy(62,25);printf(" ");
	Sleep(vel);
	gotoxy(61,25);printf(" ");
	Sleep(vel);
	gotoxy(60,25);printf(" ");
	Sleep(vel);
    gotoxy(59,25);printf(" ");
	Sleep(vel);
	gotoxy(58,25);printf(" ");
	Sleep(vel);
	gotoxy(57,25);printf(" ");
	Sleep(vel);
	gotoxy(56,25);printf(" ");
	Sleep(vel);
	gotoxy(55,25);printf(" ");
	Sleep(vel);
	gotoxy(54,25);printf(" ");
	Sleep(vel);
	gotoxy(53,25);printf(" ");
	Sleep(vel);
	gotoxy(52,25);printf(" ");
	Sleep(vel);
	gotoxy(51,25);printf(" ");
	Sleep(vel);
	gotoxy(50,25);printf(" ");
	Sleep(vel);
	gotoxy(49,25);printf(" ");
	Sleep(vel);
	gotoxy(48,25);printf(" ");
	Sleep(vel);
	gotoxy(47,25);printf(" ");
	Sleep(vel);
	gotoxy(46,25);printf(" ");
	Sleep(vel);
	gotoxy(45,25);printf(" ");
	Sleep(vel);
	gotoxy(44,25);printf(" ");
	Sleep(vel);
	gotoxy(43,25);printf(" ");
	Sleep(vel);
	gotoxy(42,25);printf(" ");
	Sleep(vel);
	gotoxy(41,25);printf(" ");
	Sleep(vel);
	gotoxy(40,25);printf(" ");
	Sleep(vel);
	gotoxy(39,25);printf(" ");
	Sleep(vel);
	gotoxy(38,25);printf(" ");
	Sleep(vel);
	gotoxy(37,25);printf(" ");
	Sleep(vel);
	gotoxy(36,25);printf(" ");
	Sleep(vel);
	gotoxy(35,25);printf(" ");
	Sleep(vel);
	gotoxy(34,25);printf(" ");
	Sleep(vel);
	gotoxy(33,25);printf(" ");
	Sleep(vel);
	gotoxy(32,25);printf(" ");
	Sleep(vel);
	gotoxy(31,25);printf(" ");
	Sleep(vel);
	//-----------------------
	//ultima parte
	textbackground(0);
	
	gotoxy(23,26);printf(" ");
    Sleep(vel);
	gotoxy(20,27);printf("                                                             ");
	Sleep(vel);
	gotoxy(20,28);printf("                                                             ");
	Sleep(vel);
	gotoxy(20,29);printf(" ");
	Sleep(vel);
	//-----------------------
	gotoxy(80,26);printf(" ");
	Sleep(vel);
	gotoxy(79,26);printf(" ");
	Sleep(vel);
	gotoxy(78,26);printf(" ");
	Sleep(vel);
	gotoxy(77,26);printf(" ");
	Sleep(vel);
	gotoxy(76,26);printf(" ");
	Sleep(vel);
	gotoxy(75,26);printf(" ");
	Sleep(vel);
	gotoxy(74,26);printf(" ");
	Sleep(vel);
	gotoxy(73,26);printf(" ");
	Sleep(vel);
	gotoxy(72,26);printf(" ");
	Sleep(vel);
	gotoxy(71,26);printf(" ");
	Sleep(vel);
	gotoxy(70,26);printf(" ");
	Sleep(vel);
	gotoxy(69,26);printf(" ");
	Sleep(vel);
	gotoxy(68,26);printf(" ");
	Sleep(vel);
	gotoxy(67,26);printf(" ");
	Sleep(vel);
	gotoxy(66,26);printf(" ");
	Sleep(vel);
	gotoxy(65,26);printf(" ");
	Sleep(vel);
	gotoxy(64,26);printf(" ");
	Sleep(vel);
	gotoxy(63,26);printf(" ");
	Sleep(vel);
	gotoxy(62,26);printf(" ");
	Sleep(vel);
	gotoxy(61,26);printf(" ");
	Sleep(vel);
	gotoxy(60,26);printf(" ");
	Sleep(vel);
    gotoxy(59,26);printf(" ");
    Sleep(vel);
	gotoxy(58,26);printf(" ");
	Sleep(vel);
	gotoxy(57,26);printf(" ");
	Sleep(vel);
	gotoxy(56,26);printf(" ");
	Sleep(vel);
	gotoxy(55,26);printf(" ");
	Sleep(vel);
	gotoxy(54,26);printf(" ");
	Sleep(vel);
	gotoxy(53,26);printf(" ");
	Sleep(vel);
	gotoxy(52,26);printf(" ");
	Sleep(vel);
	gotoxy(51,26);printf(" ");
	Sleep(vel);
	gotoxy(50,26);printf(" ");
	Sleep(vel);
	gotoxy(49,26);printf(" ");
	Sleep(vel);
	gotoxy(48,26);printf(" ");
	Sleep(vel);
	gotoxy(47,26);printf(" ");
	Sleep(vel);
	gotoxy(46,26);printf(" ");
	Sleep(vel);
	gotoxy(45,26);printf(" ");
	Sleep(vel);
	gotoxy(44,26);printf(" ");
	Sleep(vel);
	gotoxy(43,26);printf(" ");
	Sleep(vel);
	gotoxy(42,26);printf(" ");
	Sleep(vel);
	gotoxy(41,26);printf(" ");
	Sleep(vel);
	gotoxy(40,26);printf(" ");
	Sleep(vel);
	gotoxy(39,26);printf(" ");
	Sleep(vel);
	gotoxy(38,26);printf(" ");
	Sleep(vel);
	gotoxy(37,26);printf(" ");
	Sleep(vel);
	gotoxy(36,26);printf(" ");
	Sleep(vel);
	gotoxy(35,26);printf(" ");
	Sleep(vel);
	gotoxy(34,26);printf(" ");
	Sleep(vel);
	gotoxy(33,26);printf(" ");
	Sleep(vel);
	gotoxy(32,26);printf(" ");
	Sleep(vel);
	gotoxy(31,26);printf(" ");
	Sleep(vel);
	gotoxy(30,26);printf(" ");
	Sleep(vel);
	gotoxy(29,26);printf(" ");
	Sleep(vel);
	gotoxy(28,26);printf(" ");
	Sleep(vel);
	gotoxy(27,26);printf(" ");
	Sleep(vel);
	gotoxy(26,26);printf(" ");
	Sleep(vel);
	gotoxy(25,26);printf(" ");
	Sleep(vel);
	gotoxy(24,26);printf(" ");
	Sleep(vel);
	gotoxy(23,26);printf(" ");
	Sleep(vel);
	gotoxy(22,26);printf(" ");
	Sleep(vel);
	gotoxy(21,26);printf(" ");
	Sleep(vel);
	gotoxy(20,26);printf(" ");
	Sleep(vel);
	//-----------------------
	gotoxy(80,26);printf(" ");
	Sleep(vel);
	gotoxy(80,27);printf(" ");
	Sleep(vel);
	gotoxy(80,28);printf(" ");
	Sleep(vel);
	gotoxy(80,29);printf(" ");
	Sleep(vel);
	//-----------------------
	gotoxy(80,29);printf(" ");
	Sleep(vel);
	gotoxy(79,29);printf(" ");
	Sleep(vel);
	gotoxy(78,29);printf(" ");
	Sleep(vel);
	gotoxy(77,29);printf(" ");
	Sleep(vel);
	gotoxy(76,29);printf(" ");
	Sleep(vel);
	gotoxy(75,29);printf(" ");
	Sleep(vel);
	gotoxy(74,29);printf(" ");
	Sleep(vel);
	gotoxy(73,29);printf(" ");
	Sleep(vel);
	gotoxy(72,29);printf(" ");
	Sleep(vel);
	gotoxy(71,29);printf(" ");
	Sleep(vel);
	gotoxy(70,29);printf(" ");
	Sleep(vel);
	gotoxy(69,29);printf(" ");
	Sleep(vel);
	gotoxy(68,29);printf(" ");
	Sleep(vel);
	gotoxy(67,29);printf(" ");
	Sleep(vel);
	gotoxy(66,29);printf(" ");
	Sleep(vel);
	gotoxy(65,29);printf(" ");
	Sleep(vel);
	gotoxy(64,29);printf(" ");
	Sleep(vel);
	gotoxy(63,29);printf(" ");
	Sleep(vel);
	gotoxy(62,29);printf(" ");
	Sleep(vel);
	gotoxy(61,29);printf(" ");
	Sleep(vel);
	gotoxy(60,29);printf(" ");
	Sleep(vel);
    gotoxy(59,29);printf(" ");
    Sleep(vel);
	gotoxy(58,29);printf(" ");
	Sleep(vel);
	gotoxy(57,29);printf(" ");
	Sleep(vel);
	gotoxy(56,29);printf(" ");
	Sleep(vel);
	gotoxy(55,29);printf(" ");
	Sleep(vel);
	gotoxy(54,29);printf(" ");
	Sleep(vel);
	gotoxy(53,29);printf(" ");
	Sleep(vel);
	gotoxy(52,29);printf(" ");
	Sleep(vel);
	gotoxy(51,29);printf(" ");
	Sleep(vel);
	gotoxy(50,29);printf(" ");
	Sleep(vel);
	gotoxy(49,29);printf(" ");
	Sleep(vel);
	gotoxy(48,29);printf(" ");
	Sleep(vel);
	gotoxy(47,29);printf(" ");
	Sleep(vel);
	gotoxy(46,29);printf(" ");
	Sleep(vel);
	gotoxy(45,29);printf(" ");
	Sleep(vel);
	gotoxy(44,29);printf(" ");
	Sleep(vel);
	gotoxy(43,29);printf(" ");
	Sleep(vel);
	gotoxy(42,29);printf(" ");
	Sleep(vel);
	gotoxy(41,29);printf(" ");
	Sleep(vel);
	gotoxy(40,29);printf(" ");
	Sleep(vel);
	gotoxy(39,29);printf(" ");
	Sleep(vel);
	gotoxy(38,29);printf(" ");
	Sleep(vel);
	gotoxy(37,29);printf(" ");
	Sleep(vel);
	gotoxy(36,29);printf(" ");
	Sleep(vel);
	gotoxy(35,29);printf(" ");
	Sleep(vel);
	gotoxy(34,29);printf(" ");
	Sleep(vel);
	gotoxy(33,29);printf(" ");
	Sleep(vel);
	gotoxy(32,29);printf(" ");
	Sleep(vel);
	gotoxy(31,29);printf(" ");
	Sleep(vel);
	gotoxy(30,29);printf(" ");
	Sleep(vel);
	gotoxy(29,29);printf(" ");
	Sleep(vel);
	gotoxy(28,29);printf(" ");
	Sleep(vel);
	gotoxy(27,29);printf(" ");
	Sleep(vel);
	gotoxy(26,29);printf(" ");
	Sleep(vel);
	gotoxy(25,29);printf(" ");
	Sleep(vel);
	gotoxy(24,29);printf(" ");
	Sleep(vel);
	gotoxy(23,29);printf(" ");
	Sleep(vel);
	gotoxy(22,29);printf(" ");
	Sleep(vel);
	gotoxy(21,29);printf(" ");
	Sleep(vel);
	gotoxy(20,29);printf("          ");
	
	textbackground(2); 
	textcolor(15); 
	gotoxy(73,21);printf("Chocolate LTDA.");
	textbackground(4);
	
	textcolor(15); 
	gotoxy(42,30);printf("Seja Bem-Vindo(a)");
	
	setlocale(LC_ALL,"Portuguese");
	gotoxy(35,32);printf("Pressione ");
	  
	textbackground(15); 
	textcolor(0); 
	printf("[ESPAÇO]");
	
	textbackground(4); 
	textcolor(15); 
	printf(" para continuar...");
	
	setlocale(LC_ALL,"C");
	
	while(tecla != 32)
	{
		tecla = getch();
	}
	
	system("cls");
}

//----------------------------------------------------------------------


void borda() 
{
	textbackground(15);
	for(int i = 2; i<=99; i++) // linha
	{
		gotoxy(i,2); printf(" ");
		gotoxy(i,39); printf(" ");
	}
	for (int j = 2; j<=39; j++) // coluna
	{
		gotoxy(2,j); printf(" ");
		gotoxy(3,j); printf(" ");
		gotoxy(99,j); printf(" ");
		gotoxy(98,j); printf(" ");
	}
	textbackground(4);
}

//----------------------------------------------------------------------


/*void cursor(int x) 
{
	switch (x) 
	{
		case 0: 
		{
			CONSOLE_CURSOR_INFO cursor = {1, FALSE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
		case 1: 
		{
			CONSOLE_CURSOR_INFO cursor = {1, TRUE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
	}
}*/

//----------------------------------------------------------------------


void finalizar_programa()
{
	int ci = 10;
	int li = 10;
	system("cls");
	borda();
	gotoxy(30,20);printf("Obrigado por utilizar nosso Programa.");
	getch();
	gotoxy(3,35);
}

//----------------------------------------------------------------------

void sobre()
{
	int ci = 8;
	int li = 11;
	
	int tecla = 0;
	
	system("cls");
	borda();
//----------------------------------------------------
	
	textcolor(0);     
	textbackground(2);
	gotoxy(45,6);printf("    SOBRE    ");
	textbackground(4);
	textcolor(15);
	gotoxy(10,8);printf("----------------------------------------------------------------------------------");
	textbackground(3);
	gotoxy(ci,li);printf("Chocolate LTDA - Willy Wonka ");
	textcolor(0); 
	printf("Desenvolvida pelos estudantes");
	printf(" 71C");
	printf(" CTI");
	printf(" Bauru");
	printf(" 2020");
	printf(":        ");
	textcolor(15); 
	textbackground(0); 
//----------------------------------------------------
        setlocale(LC_ALL,"Portuguese");
	gotoxy(ci+2,li+3);printf("Maria Teresa         ");	
	textbackground(0); 	
	gotoxy(ci+22,li+3);printf(" Número: 21");
	textcolor(15); 
	textbackground(0); 
	gotoxy(ci+2,li+6);printf("Pedro Arthur B.K");
	textbackground(0);
	printf("     Número: 27");
//----------------------------------------------------

	textbackground(14); 
	textcolor (0);
	gotoxy(ci,li+12);printf("Professora orientadora: ");
	printf("Ariane Scarelli");
//----------------------------------------------------
	setlocale(LC_ALL,"C");
	textbackground(11); 
	textcolor(0); 
	gotoxy(39,34);printf("Pressione");
	textbackground(11); 
	textcolor(0); 
	printf("[ENTER]");
	textcolor(0); 
	textbackground(11);
	printf(" para voltar");
	
	while(tecla != 13)
	{
		tecla = getch();
	}
}

//-------------------------------------------------------------------

void consultar_Empresa_geral()
{
	int lin = 11; 
	int ult = 31; 
	int ci = 8; 
	int pag = 1; 
	int tecla;
	int f; 
	int aux_lin;
	
	system("cls");
	borda();
	
	if((fp_Empresa = fopen ("Empresa.bin","rb")) == NULL)
	{
		textcolor(15); 
		gotoxy(40,30);printf("Nenhum cliente cadastrado");
		fclose(fp_Empresa);
		textcolor(15);
		getch();
		return;
	}
	rewind(fp_Empresa);
	
	while(true)
	{
		if(f == 2)
			rewind(fp_Empresa);
			
		f = 0;
		tela_consultar_Empresa_geral();
		
		while(true)
		{
			
			if((fread(&cadastro,sizeof(cadastro),1,fp_Empresa)) != 1) 
			{
				if( !feof(fp_Empresa) ) 
				{
					textcolor(15);
					gotoxy(39,36);printf("ERRO ao ler o arquivo");
					textcolor(15); 
					getch();
					gotoxy(3,35);
					exit(1);
				}
				else 
				{
					break;
				}
					
			}
			
			
			if(lin > ult)
			{
				setlocale(LC_ALL,"Portuguese");
				
				textcolor(0); 
				textbackground(15); 
				
				gotoxy(5,37);printf("[ESPAÇO]");
				
				textcolor(15); 
				textbackground(4); 
				
				printf(" - próxima página");
				
				setlocale(LC_ALL,"C");
				f = 1;
				break;
			}
		}
				
		textbackground(0);
		textcolor(15);
			
		gotoxy(ci+85,35);printf("%d",pag); 
		
		textbackground(4);
		textcolor(15); 
		
		aux_lin = 11;
		
		while(true) 
		{
			tecla = getch();
			
			if(tecla == 27)
			{
				fclose(fp_Empresa);
				return;
			}
			
			if(tecla == 8) 
			{
				lin = 11;
				pag = 1;
				f = 2;
				break;
			}
			
			if(f == 1)
			{
				if(tecla == 32) 
				{
					lin = 11;
					pag++;
					break;
				}
			}
			
			if(tecla == 72) 
			{
				if(aux_lin > 11)
				{
					textcolor(15); 
					
					gotoxy(6,aux_lin);printf("  "); 
					aux_lin -= 2;
					gotoxy(6,aux_lin);printf("->"); 
					
					textcolor(15); 
				}
				
				else 
				{
					textcolor(15); 
					
					gotoxy(6,aux_lin);printf("  "); 
					aux_lin = lin - 2;
					gotoxy(6,aux_lin);printf("->");
					
					textcolor(15); 
				}
			}
			
			else if(tecla == 80)
			{
				if(aux_lin < lin-2)
				{
					textcolor(15);
					
					gotoxy(6,aux_lin);printf("  ");
					aux_lin += 2;
					gotoxy(6,aux_lin);printf("->");
					
					textcolor(15);
				}
				
				else 
				{
					textcolor(10); 
					
					gotoxy(6,aux_lin);printf("  "); 
					aux_lin = 11;
					gotoxy(6,aux_lin);printf("->"); 
					
					textcolor(15); 
				}
			}
			
			else if(tecla == 13) 
			{
				consultar_Empresa_geral_especifico(aux_lin,pag);
				f = 2;
				lin = 11;
				pag = 1;
				break;
			}
		}
	}
}

//----------------------------------------------------------------------

void tela_consultar_Empresa_geral()
{
	int li = 8;
	int ci = 5;
	
	
	system("cls");
	borda();
	textbackground(4); 
	
	textcolor(15); 
	gotoxy(26,4);printf("Consulta de parceiro geral");
	
	textbackground(15); 
	textcolor(0);
	gotoxy(5,4);printf("[ESC]");
	
	textbackground(4); 
	textcolor(15); 
	printf(" - sair");
	
	textbackground(15); 
	textcolor(0); 
	gotoxy(5,35);printf("[BACKSPACE]");
	
	textbackground(4);
	textcolor(15); 
	setlocale(LC_ALL,"Portuguese");
	printf(" - primeira página");
	setlocale(LC_ALL,"C");
	
	textbackground(15);
	textcolor(0); 
	gotoxy(37,35);printf("[SETAS]");
	
	textbackground(4);
	textcolor(15); 
	printf(" - navegar");
	
	textbackground(15); 
	textcolor(0); 
	gotoxy(37,37);printf("[ENTER]");
	
	textbackground(4); 
	textcolor(15); 
	printf(" - selecionar cliente");
	
	textcolor(15); 
	gotoxy(6,11);printf("->"); 
	
	textbackground(4);
	for(int i = li; i < li+25; i++) 
	{
		gotoxy(ci,i);printf(" ");
		gotoxy(ci+91,i);printf(" ");
	}
	
	for(int i = ci+1; i < ci+91;i++) 
	{
		gotoxy(i,li-1);printf(" ");
		gotoxy(i,li+25);printf(" ");
	}
	
	textbackground(4); 
	
	gotoxy(ci,li-1);printf(" ");
	gotoxy(ci,li+25);printf(" ");
	gotoxy(ci+91,li-1);printf(" ");	
	gotoxy(ci+91,li+25);printf(" ");
	
	textbackground(4);
	textcolor(15); 
	
	for(int i = li; i < li+25; i++) 
	{
		gotoxy(ci+7,i);printf("|"); 
		gotoxy(ci+50,i);printf("|");
		gotoxy(ci+72,i);printf("|"); 
	}
	
	for(int i = ci+1; i<ci+91; i++)
	{
		textcolor(7); 
		gotoxy(i,li+2);printf("-"); 
		if(i == 12)
		{
			textcolor(0); 
			gotoxy(i,li+2);printf("+");
			textcolor(7); 
		}
		else if(i == 55)
		{
			textcolor(0); 
			gotoxy(i,li+2);printf("+");
			textcolor(7); 
		}
		else if(i == 77)
		{
			textcolor(0); 
			gotoxy(i,li+2);printf("+");
			textcolor(7); 
		}
	}
	
	textcolor(11); 
	
	gotoxy(ci+3,li+1);printf("ID");
	gotoxy(ci+26,li+1);printf("Empresa");
	gotoxy(ci+58,li+1);printf("Origem");
	gotoxy(ci+78,li+1);printf("Email");
	
	setlocale(LC_ALL,"Portuguese");
	gotoxy(ci+83,35);printf("Pág."); 
	setlocale(LC_ALL,"C");
	mostra();
	textcolor(15);
	textbackground(4);
}


//----------------------------------------------------------------------


void tela_consultar_Empresa()
{
	int li = 17;
	int ci = 43;
	
	textcolor(15); 
	textbackground(4);
	
	system("cls");
	borda();
	
	
	gotoxy(ci-11,li-7);printf("Consulta De Parceiro");
	
	textcolor(15); 
	
	gotoxy(ci,li);printf("Consulta Geral"); 
	gotoxy(ci,li+2);printf("------------Willy Wonka---------"); 
	gotoxy(ci,li+4);printf("Consulta por ID"); 
	gotoxy(ci,li+6);printf("Voltar"); 
	
	textcolor(15); 
	gotoxy(5,37);printf("Utilize as ");
	
	textcolor(0);
	textbackground(15);
	
	printf("[SETAS]");
	
	textcolor(15); 
	textbackground(4); 
	printf(" para mover e ");
	
	textcolor(0); 
	textbackground(15); 
	printf("[ENTER]");
	
	textcolor(15);
	textbackground(4); 
	printf(" para selecionar");

	
	textcolor(15); 
	textbackground(4); 
}


//----------------------------------------------------------------------


void consultar_Empresa_geral_especifico(int linha_tabela, int pag)
{
	int ci = 10;
	int li = 10;
	
	int tecla = 0;
	
	int linha_struct;
	int cont = 0;
	
	int total_pedidos = 0;
	float total = 0;
	
	switch(linha_tabela) 
	{
		case 11:
		{
			linha_struct = 1 + ((pag-1) * 11);
			break;
		}
		
		case 13:
		{
			linha_struct = 2 + ((pag-1) * 11);
			break;
		}
		
		case 15:
		{
			linha_struct = 3 + ((pag-1) * 11);
			break;
		}
		
		case 17:
		{
			linha_struct = 4 + ((pag-1) * 11);
			break;
		}
		
		case 19:
		{
			linha_struct = 5 + ((pag-1) * 11);
			break;
		}
		
		case 21:
		{
			linha_struct = 6 + ((pag-1) * 11);
			break;
		}
		
		case 23:
		{
			linha_struct = 7 + ((pag-1) * 11);
			break;
		}
		
		case 25:
		{
			linha_struct = 8 + ((pag-1) * 11);
			break;
		}
		
		case 27:
		{
			linha_struct = 9 + ((pag-1) * 11);
			break;
		}
		
		case 29:
		{
			linha_struct = 10 + ((pag-1) * 11);
			break;
		}
		
		case 31:
		{
			linha_struct = 11 + ((pag-1) * 11);
			break;
		}
	}
	
	system("cls");
	
	borda();
	
	setlocale(LC_ALL,"Portuguese");
	
	textcolor(15); 
	gotoxy(26,4);printf("Consulta geral de parceiro");
	
	textcolor(15); 
	gotoxy(ci,li);printf("ID do parceiro:");
	gotoxy(ci,li+3);printf("Nome da empresa:");
	gotoxy(ci,li+6);printf("Origem:");
	gotoxy(ci,li+9);printf("Produto:");
	gotoxy(ci,li+12);printf("E-mail:");

	setlocale(LC_ALL,"C");
	
	rewind(fp_Empresa);
	
	while(cont < linha_struct) 
	{
		fread(&cadastro,sizeof(cadastro),1,fp_Empresa);
		
	
	}
	
	gotoxy(ci+15,li);printf("%d",cadastro.Id);
	gotoxy(ci+17,li+3);printf("%s",cadastro.Empresa);
	gotoxy(ci+8,li+6);printf("%s",cadastro.Origem);
	gotoxy(ci+10,li+9);printf("%s",cadastro.Produto);
	

	
	textcolor(15); 
	gotoxy(39,34);printf("Pressione ");
	
	textbackground(15); 
	textcolor(0); 
	printf("[ENTER]");
	
	textcolor(10);
	textbackground(4); 
	printf(" para voltar");
	
	while(tecla != 13)
	{
		tecla = getch();
	}
	
	fclose(fp_Empresa);
}


//----------------------------------------------------------------------


void consultar_Empresa()
{
	int opcao;
	while(true)
	{
		tela_consultar_Empresa();
		opcao = setas(43,17,4,2,0);
		
		switch(opcao)
		{
			case 1:
			{
				consultar_Empresa_geral();
				break;
			}
		/*	case 2: 
			{
				consultar_cliente_nome();
				break;
			}*/
			case 3: 
			{
			     	pesquisa_cod();
				break;	
			}
			case 4:
			{
				return;
			}
		}
	}
}
