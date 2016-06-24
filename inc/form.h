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
static const char validsymbols[] = "!@#$&*+-/";
static const char validnumbers[] = "0123456789";

#define sgologinurl "https://sgo.basis.com.br/login.jsp"
#define portalbasis "https://www.basis.com.br"
#define emailadmin "sgo-admins@basis.com.br"
#define passwrdbasis "basis123"
#define skypeprefix "basis."
#define emailposfix "@basis.com.br"
#define fileregister "registrousuarios"
#define fileemail "email"
#define filescript "script"
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
 Função para fechar o arquivo
*/
void close_file(FILE *infile);

/*
 Função para fazer o texto do email de envio para o usuário
*/
 void make_email(FILE *infile, user profile);

/*
 Função para fazer o script de criação do usuário
*/
 void make_script(FILE *infile, user profile);

/*
 Função para limpar arquivos temporários
*/
 void clean_temps();

/*
 Função para imprimir uma pequena interface visual
*/
 void interface();

#endif