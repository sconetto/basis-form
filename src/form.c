#include "form.h"

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
	return;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
void fflush_in() {
	int ch;
	do {
		ch = fgetc(stdin);
	} while (ch != EOF && ch != '\n');
	return;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
void show_user(user profile) {
	printf("Nome completo do usuário: %s\n", profile.fullname);
	printf("Primeiro nome: %s\n", profile.firstname);
	printf("Último nome: %s\n", profile.lastname);
	printf("Senha (gerada): %s\n", profile.passwrd);
	printf("Senha (padrão): %s\n", profile.passwrdstd);
	printf("Login (SGO): %s\n", profile.loginsgo);
	printf("Login (Skype): %s\n", profile.loginskype);
	printf("Email: %s\n", profile.email);
	return;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
char *make_passwrd() {
	char *new_passwd;
	int i;
	srand((unsigned)time(NULL));
	new_passwd = (char*) calloc((passwd_len + 1), sizeof(char));

	for (i = 0; i < passwd_len; ++i) {
		if (i >= 0 && i < 2) {
			new_passwd[i] = validcharslw[ rand() % strlen(validcharslw)];
		}
		else if (i >= 2 && i < 4) {
			new_passwd[i] = validcharsup[ rand() % strlen(validcharsup)];
		}
		else if (i >= 6 && i < 10) {
			new_passwd[i] = validnumbers[ rand() % strlen(validnumbers)];
		}
		else if (i >= 4 && i < 6) {
			new_passwd[i] = validsymbols[ rand() % strlen(validsymbols)];
		}
		new_passwd[i + 1] = 0x0;
	}
	new_passwd[passwd_len] = '\0';
	return new_passwd;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
char *validate_fullname(char *fullname) {
	char option;
	printf("%s\n", fullname);
	printf("O nome do usuário apresentado em cima está correto? [S\\n]: ");
	option = getchar();
	if (option == '\n') {
		printf("Retornando à execução...\n");
	}
	else if (tolower(option) != 's') {
		printf("Por favor digite novamete o nome do usuário: ");
		fflush_in();
		read_string(fullname);
		fullname = validate_fullname(fullname);
		return fullname;
	}
	else {
		fflush_in();
		printf("Retornando à execução...\n");
	}
	return fullname;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
char *validate_firstname(char *firstname) {
	char option;
	printf("%s\n", firstname);
	printf("O primeiro nome do usuário apresentado em cima está correto? [S\\n]: ");
	option = getchar();
	if (option == '\n') {
		printf("Retornando à execução...\n");
	}
	else if (tolower(option) != 's') {
		printf("Por favor digite novamete o primeiro nome do usuário (lembre-se de usar minúsculas): ");
		fflush_in();
		read_string(firstname);
		firstname = validate_fullname(firstname);
		return firstname;
	}
	else {
		fflush_in();
		printf("Retornando à execução...\n");
	}
	return firstname;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
char *validate_lastname(char *lastname) {
	char option;
	printf("%s\n", lastname);
	printf("O último nome do usuário apresentado em cima está correto? [S\\n]: ");
	option = getchar();
	if (option == '\n') {
		printf("Retornando à execução...\n");
	}
	else if (tolower(option) != 's') {
		printf("Por favor digite novamete o último nome do usuário (lembre-se de usar minúsculas): ");
		fflush_in();
		read_string(lastname);
		lastname = validate_fullname(lastname);
		return lastname;
	}
	else {
		fflush_in();
		printf("Retornando à execução...\n");
	}
	return lastname;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
user read_new_user() {
	user new_user;
	FILE* infile;
	char *string;
	char option;
	char aux;
	int counter = 0;
	infile = NULL;
	string = (char*) malloc(sizeof(char));
	printf("Digite o nome completo do novo usuário: ");
	read_string(string);
	validate_fullname(string);
	strcpy(new_user.fullname, string);
	printf("Digite o primeiro nome do novo usuário (lembre-se de usar minúsculas): ");
	read_string(string);
	validate_firstname(string);
	strcpy(new_user.firstname, string);
	printf("Digite o primeiro último nome do novo usuário (lembre-se de usar minúsculas): ");
	read_string(string);
	validate_lastname(string);
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

	printf("Deseja salvar usuário no registro? [S\\n]: ");
	option = getchar();
	if (option == '\n') {
		infile = open_file(infile, fileregister, "a+");
		do {
			aux = fgetc(infile);
			if (aux == '\n') counter++;
		} while (aux != EOF);
		if (counter == 0) {
			fprintf(infile, "ID|NOME COMPLETO|PRIMEIRO NOME|ÚLTIMO NOME|LOGIN SGO|SENHA SGO|LOGIN SKYPE|SENHA SKYPE|EMAIL BASIS|SENHA EMAIL\n");
		}
		else if (counter < 0) {
			printf("Erro ao ler os registros!!!\n");
		}
		else {
			new_user.id = (unsigned int)counter;
			fprintf(infile, "%u|%s|%s|%s|%s|%s|%s|%s|%s|%s\n", new_user.id, new_user.fullname, new_user.firstname, new_user.lastname, new_user.loginsgo, new_user.passwrd, new_user.loginskype, new_user.passwrd, new_user.email, new_user.passwrdstd);
		}
		fclose(infile);
	}
	else if (tolower(option) != 's') {
		printf("Pulando esta etapa\n");
		new_user.id = 0;
	}
	else {
		infile = open_file(infile, fileregister, "a+");
		do {
			aux = fgetc(infile);
			if (aux == '\n') counter++;
		} while (aux != EOF);
		if (counter == 0) {
			fprintf(infile, "ID|NOME COMPLETO|PRIMEIRO NOME|ÚLTIMO NOME|LOGIN SGO|SENHA SGO|LOGIN SKYPE|SENHA SKYPE|EMAIL BASIS|SENHA EMAIL\n");
		}
		else if (counter < 0) {
			printf("Erro ao ler os registros!!!\n");
		}
		else {
			new_user.id = (unsigned int)counter;
			fprintf(infile, "%u|%s|%s|%s|%s|%s|%s|%s|%s|%s\n", new_user.id, new_user.fullname, new_user.firstname, new_user.lastname, new_user.loginsgo, new_user.passwrd, new_user.loginskype, new_user.passwrd, new_user.email, new_user.passwrdstd);
		}
		fclose(infile);
	}

	fflush_in();
	printf("Deseja gerar email para usuário? [S\\n]: ");
	option = getchar();
	if (option == '\n') {
		printf("Gerado email: arquivo doc/emailtemp.txt\n");
		make_email(infile, new_user);
	}
	else if (tolower(option) != 's') {
		printf("Pulando esta etapa\n");
	}
	else {
		printf("Gerado email: arquivo doc/emailtemp.txt\n");
		make_email(infile, new_user);
	}

	fflush_in();
	printf("Deseja gerar script para criação do usuário? [S\\n]: ");
	option = getchar();
	if (option == '\n') {
		printf("Gerado script: arquivo doc/scripttemp.txt\n");
		make_script(infile, new_user);
	}
	else if (tolower(option) != 's') {
		printf("Pulando esta etapa\n");
	}
	else {
		printf("Gerado script: arquivo doc/scripttemp.txt\n");
		make_script(infile, new_user);
	}

	return new_user;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
FILE* open_file(FILE *infile, char *filename, char *mode) {
	if (strcmp(filename, fileregister) == 0) {
		infile = fopen("./doc/registrousuarios.txt", mode);
	}
	else if (strcmp(filename, fileemail) == 0) {
		infile = fopen("./doc/emailtemp.txt", mode);
	}
	else if (strcmp(filename, filescript) == 0) {
		infile = fopen("./doc/scripttemp.txt", mode);
	}
	else {
		/*to implement*/
	}
	if (infile == NULL) {
		printf("Erro ao abrir o arquivo ou arquivo não encontrado!\nFechando o programa\n");
	}
	return infile;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
void close_file(FILE *infile) {
	fclose(infile);
	return;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
void make_email(FILE *infile, user profile) {
	infile = open_file(infile, fileemail, "w+");
	fprintf(infile, "Prezado %s\n", profile.fullname);
	fprintf(infile, "Segue seu login e senha para acessar o SGO, Sistema de Gestão de Ocorrências da Basis:\n");
	fprintf(infile, "login: %s\n", profile.loginsgo);
	fprintf(infile, "senha: %s\n", profile.passwrd);
	fprintf(infile, "\nVocê pode fazer login aqui <%s> ou acessar nosso portal <%s>, no menu \"Área Segura\" há um link para o SGO.\n", sgologinurl, portalbasis);
	fprintf(infile, "\nEm caso de dúvidas ou dificuldade para acessar o sistema, entre em contato através do email:\n\n%s", emailadmin);
	fprintf(infile, "\n\nAtenciosamente.\n");
	fclose(infile);
	return;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
void make_script(FILE *infile, user profile) {
	char *desc;
	desc = (char*)malloc(sizeof(char));
	infile = open_file(infile, filescript, "w+");
	fflush_in();
	printf("Adicione uma descrição para o usuário: ");
	read_string(desc);
	profile.firstname[0] = toupper(profile.firstname[0]);
	profile.lastname[0] = toupper(profile.lastname[0]);
	fprintf(infile, "dsadd user \"cn=%s,cn=Users,dc=basis,dc=com,dc=br\" -upn %s@basis.com.br -samid %s -fn \"%s\" -ln \"%s\" -display \"%s\" ", profile.fullname, profile.loginsgo, profile.loginsgo, profile.firstname, profile.lastname, profile.fullname);
	fprintf(infile, "-email \"%s\" -pwd %s -pwdneverexpires yes -desc \"%s\" -memberOf \"cn=Basis,cn=Users,dc=basis,dc=com,dc=br\"-uc", profile.email, profile.passwrd, desc);
	return;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
void clean_temps() {
	FILE* infile;
	int status;
	infile = NULL;
	status = 1;
	status = remove("./doc/emailtemp.txt");
	if (status == 0) {
		printf("O email temporário foi limpo com sucesso!\n");
		infile = open_file(infile, fileemail, "w+");
		fclose(infile);
		status = 1;
	}
	else {
		printf("Erro ao limpar email temporário\n");
		status = -1;
	}

	status = remove("./doc/scripttemp.txt");
	if (status == 0) {
		printf("O script temporário foi limpo com sucesso!\n");
		infile = open_file(infile, filescript, "w+");
		fclose(infile);
		status = 1;
	}
	else {
		printf("Erro ao limpar script temporário\n");
		status = -1;
	}
	return;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
void interface() {
	int i  = 0 ;
	for (i = 0; i < 14; ++i) {
		printf("*");
	}
	printf("\n*   teste    *\n");
	for (i = 0; i < 14; ++i) {
		printf("*");
	}
	printf("\n");
}