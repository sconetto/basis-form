#include "stdio.h"
#include "stdlib.h"

#define sgologinurl "https://sgo.basis.com.br/login.jsp"
#define portalbasis "https://www.basis.com.br"
#define emailadmin "sgo-admins@basis.com.br"
#define passwrdbasis "basis123"

typedef struct _user {
	char* fullname;
	char* loginsgo;
	char* loginskype;
	char* email;
	char* firstname;
	char* lastname;
	char* passwrd;
	char* passwrdstd;
} user;

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

void user_allocation(user recieved_user) {
	recieved_user.fullname = (char*) malloc(sizeof(char));
	recieved_user.loginsgo = (char*) malloc(sizeof(char));
	recieved_user.loginskype = (char*) malloc(sizeof(char));
	recieved_user.email = (char*) malloc(sizeof(char));
	recieved_user.firstname = (char*) malloc(sizeof(char));
	recieved_user.lastname = (char*) malloc(sizeof(char));
	recieved_user.passwrd = (char*) malloc(sizeof(char));
	recieved_user.passwrdstd = (char*) malloc(sizeof(char));
}

int main(int argc, char const *argv[]) {
	user new_user;
	char *s;
	s = (char*) malloc(sizeof(char));
	user_allocation(new_user);
	/*read_string(new_user.fullname);*/
	read_string(s);
	printf("%s\n", new_user.fullname);
	printf("%s\n%s\n%s\n%s\n", sgologinurl, portalbasis, emailadmin, passwrdbasis);
	return 0;
}