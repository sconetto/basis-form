#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "locale.h"
#include "time.h"

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
#define passwd_len 10
#define MAXSTRING 300

enum boolean {
	true = 1, false = 0
};

typedef enum boolean bool;

struct _user {
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

void read_string(char *s);

void fflush_in();

void show_user(user profile);

char* make_passwrd();

char *validate_fullname(char *fullname) {
}

char *validate_firstname(char *firstname) {
}

user read_new_user();

int main(int argc, char const *argv[]) {
	read_new_user();
	return 0;
}

void read_string(char *s) {
	char c;
	int i = 0;
	do {
		c = getchar();
		if ( c != '\n') {
			s[i] = c;
		}
		i++;
	} while ( c != '\n' && c != '\0');
	s[--i] = '\0';
}

void fflush_in() {
	int ch;
	do {
		ch = fgetc(stdin);
	} while (ch != EOF && ch != '\n');
}

user read_new_user() {
	user new_user;
	char *string;
	string = (char*) malloc(sizeof(char));
	printf("Digite o nome completo do novo usuário: ");
	read_string(string);
	strcpy(new_user.fullname, string);
	printf("Digite o primeiro nome do novo usuário (lembre-se de usar minúsculas): ");
	read_string(string);
	strcpy(new_user.firstname, string);
	printf("Digite o primeiro último nome do novo usuário (lembre-se de usar minúsculas): ");
	read_string(string);
	strcpy(new_user.lastname, string);
	string = make_passwrd();
	strcpy(new_user.passwrd, string);
	strcpy(new_user.passwrdstd, passwrdbasis);
	strcpy(new_user.loginsgo, new_user.firstname);
	strcat(new_user.loginsgo, ".");
	strcat(new_user.loginsgo, new_user.lastname);
	strcpy(new_user.loginskype, skypeprefix);
	strcat(new_user.loginskype, new_user.loginsgo);
	strcpy(new_user.email, new_user.loginsgo);
	strcat(new_user.email, emailposfix);
	show_user(new_user);
}

void show_user(user profile) {
	printf("Nome completo do usuário: %s\n", profile.fullname);
	printf("Primeiro nome: %s\n", profile.firstname);
	printf("Último nome: %s\n", profile.lastname);
	printf("Senha (gerada): %s\n", profile.passwrd);
	printf("Senha (padrão): %s\n", profile.passwrdstd);
	printf("Login (SGO): %s\n", profile.loginsgo);
	printf("Login (Skype): %s\n", profile.loginskype);
	printf("Email: %s\n", profile.email);
}

char *make_passwrd() {
	char *new_passwd;
	int i;
	srand((unsigned)time(NULL));
	new_passwd = (char*) calloc((passwd_len + 1), sizeof(char));

	for (i = 0; i < passwd_len; ++i) {
		if(i >= 0 && i < 2) {
			new_passwd[i] = validcharslw[ rand() % strlen(validcharslw)];
		}
		else if(i >= 2 && i < 4) {
			new_passwd[i] = validcharsup[ rand() % strlen(validcharsup)];
		}
		else if(i >= 6 && i < 10) {
			new_passwd[i] = validnumbers[ rand() % strlen(validnumbers)];
		}
		else if(i >= 4 && i < 6) {
			new_passwd[i] = validsymbols[ rand() % strlen(validsymbols)];
		}
		new_passwd[i + 1] = 0x0;
	}
	new_passwd[passwd_len] = '\0';
	return new_passwd;
}