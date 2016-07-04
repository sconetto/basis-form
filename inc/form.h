/*
  Biblioteca das funções.
*/

#ifndef _FORM_H
#define _FORM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>

static const char validcharslw[] = "abcdefghijklmnopqrstuvwxyz";
static const char validcharsup[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char validsymbols[] = "!@#$";
static const char validnumbers[] = "0123456789";

enum assignment {
	auditor = 1, fiscalrequisitante, fiscaltecnico, fiscaltecassistente, gestor, requisitante, requisitanteassistente, todos
};

enum contract {
	agu = 1, basis, cade, camara, cldf, eb, ebcolog, faap, fdc, fnde, funasa, fundacentro,
	gafisa, hub, ibama, marinha, mma, mt, poupex, recall, sdh, stc
};

typedef enum assignment assignment;

typedef enum contract contract;

#define sgologinurl "https://sgo.basis.com.br/login.jsp"
#define portalbasis "https://www.basis.com.br"
#define emailadmin "sgo-admins@basis.com.br"
#define passwrdbasis "basis123"
#define skypeprefix "basis."
#define emailposfix "@basis.com.br"
#define fileregister "registrousuarios"
#define fileemail "email"
#define filescript "script"
#define filescriptbd "scriptbd"
#define filelog "log"
#define passwd_len 10
#define MAXSTRING 300

struct _user {
	unsigned int id;
	char fullname[MAXSTRING];
	char loginsgo[MAXSTRING];
	char loginskype[MAXSTRING];
	char email[MAXSTRING];
	char firstname[MAXSTRING];
	char lastname[MAXSTRING];
	char passwrd[MAXSTRING];
	char passwrdstd[MAXSTRING];
};

typedef struct _user user;

/*
 Função de ler strings
*/
void read_string(char *s);

/*
 Função para limpar o buffer do teclado
*/
void fflush_in();

/*
 Função para mostrar a struct do usuário
*/
void show_user(user profile);

/*
 Função para criar uma nova senha
*/
char* make_passwrd();

/*
 Função para validar o nome completo
*/
char *validate_fullname(char *fullname);

/*
 Função para validar o primeiro nome
*/
char *validate_firstname(char *firstname);

/*
 Função para validar o primeiro nome
*/
char *validate_lastname(char *lastname);

/*
 Função para ler os dados de um novo usuário
*/
user read_new_user();

/*
 Função para abrir arquivo
*/
FILE* open_file(FILE *infile, char *filename, char *mode);

/*
 Função para fazer o texto do email de envio para o usuário
*/
void make_email(FILE *infile, user profile);

/*
 Função para fazer o script de criação do usuário no SGO
*/
void make_script(FILE *infile, user profile);

/*
 Função para fazer o script de criação do usuário no banco de dados
*/
void make_script_bd(FILE *infile, user profile);

/*
 Função para limpar arquivos temporários
*/
void clean_temps();

/*
 Função para imprimir uma pequena interface visual
*/
void interface();

/*
 Função para converter o número da atribuição para texto
*/
void convert_assignement(char *s, unsigned int assignment);

/*
 Função para converter o número do contrato para texto
*/
void convert_contract(char *s, unsigned int contract);

/*
 Função para imprimir uma pequena interface visual de menu
*/
void menu_interface();

/*
 Função mostrar os usuários cadastrados no arquivo
*/
void show_register_users();

/*
 Função para criar o log quando vários usuários forem criados
*/
void make_log();

/*
 Função para log de execução do registro de vários usuários
*/
void clean_log();

#endif