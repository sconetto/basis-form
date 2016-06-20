#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define sgologinurl "https://sgo.basis.com.br/login.jsp"
#define portalbasis "https://www.basis.com.br"
#define emailadmin "sgo-admins@basis.com.br"
#define passwrdbasis "basis123"
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

char *validate_fullname(char *fullname) {
	char character;
	printf("%s\n", fullname);
	printf("O nome acima mostrado está correto? [S|n] ");
	fflush(stdin);
	character = getchar();
	if (tolower(character) == 's') {
		printf("Voltado a execução normal\n");
		return fullname;
	}
	else {
		printf("Digite o nome completo novamente: ");
		read_string(fullname);
		validate_fullname(fullname);
	}
	return fullname;
}

char *validate_firstname(char *firstname) {
	char character;
	printf("%s\n", firstname);
	printf("O nome acima mostrado está correto? [S|n] ");
	fflush(stdin);
	character = getchar();
	fflush(stdin);
	if (tolower(character) == 's') {
		printf("Voltado a execução normal\n");
		return firstname;
	}
	else {
		printf("Digite o primeiro nome novamente (lembre-se de usar minúsculas): ");
		fflush(stdin);
		read_string(firstname);
		validate_fullname(firstname);
	}
	return firstname;
}

user read_new_user() {
	user new_user;
	char *string;
	string = (char*) malloc(sizeof(char));
	printf("Digite o nome completo do novo usuário: ");
	read_string(string);
	string = validate_fullname(string);
	strcpy(new_user.fullname, string);
	printf("Digite o primeiro nome do novo usuário (lembre-se de usar minúsculas): ");
	read_string(string);
	string = validate_firstname(string);
}

int main(int argc, char const *argv[]) {
	read_new_user();
	return 0;
}