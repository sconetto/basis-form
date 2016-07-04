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
		system("cls || clear");
	}
	else if (tolower(option) != 's') {
		printf("Pulando esta etapa\n");
		system("cls || clear");
	}
	else {
		printf("Gerado email: arquivo doc/emailtemp.txt\n");
		make_email(infile, new_user);
		system("cls || clear");
	}

	fflush_in();
	printf("Deseja gerar script para criação do usuário (SGO)? [S\\n]: ");
	option = getchar();
	if (option == '\n') {
		system("cls || clear");
		printf("Gerado script: arquivo doc/scripttemp.txt\n");
		make_script(infile, new_user);
		system("cls || clear");
	}
	else if (tolower(option) != 's') {
		system("cls || clear");
		printf("Pulando esta etapa\n");
		system("cls || clear");
	}
	else {
		system("cls || clear");
		printf("Gerado script: arquivo doc/scripttemp.txt\n");
		make_script(infile, new_user);
		system("cls || clear");
	}
	fflush(stdin);
	fflush_in();
	printf("Deseja gerar script para criação do usuário (Banco de Dados)? [S\\n]: ");
	option = getchar();
	if (option == '\n') {
		system("cls || clear");
		printf("Gerado script: arquivo doc/scriptbdtemp.txt\n");
		make_script_bd(infile, new_user);
	}
	else if (tolower(option) != 's') {
		system("cls || clear");
		printf("Pulando esta etapa\n");
	}
	else {
		system("cls || clear");
		printf("Gerado script: arquivo doc/scriptbdtemp.txt\n");
		make_script_bd(infile, new_user);
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
	else if (strcmp(filename, filescriptbd) == 0) {
		infile = fopen("./doc/scriptbdtemp.txt", mode);
	}
	else if (strcmp(filename, filelog) == 0) {
		infile = fopen("./doc/log.txt", mode);
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
	int i;
	char *desc;
	char *contract;
	char *function;
	desc = (char*)malloc(sizeof(char));
	contract = (char*)malloc(sizeof(char));
	function = (char*)malloc(sizeof(char));
	infile = open_file(infile, filescript, "w+");
	fflush_in();
	printf("Adicione uma descrição para o usuário: ");
	read_string(desc);
	printf("Informe a função do usuário (Programador/Analista/Fábrica | Aperte enter ou s para usuário padrão)\nOBS: Procure digitar sem acentos e com minúsculas: ");
	read_string(function);
	for (i = 0; i < (int)strlen(function); ++i) {
		function[i] = tolower(function[i]);
	}

	if (strncmp(function, "\n", 1) == 0 || strncmp(function, "\0", 1) == 0 || strncmp(function, "s\0", 2) == 0 || strncmp(function, "S\0", 2) == 0) {
		printf("O usuário só será incluso no grupos padrões de uso do SGO!!\n");
		sleep(1);
		profile.firstname[0] = toupper(profile.firstname[0]);
		profile.lastname[0] = toupper(profile.lastname[0]);
		fprintf(infile, "dsadd user \"cn=%s,cn=Users,dc=basis,dc=com,dc=br\" -upn %s@basis.com.br -samid %s -fn \"%s\" -ln \"%s\" -display \"%s\" ", profile.fullname, profile.loginsgo, profile.loginsgo, profile.firstname, profile.lastname, profile.fullname);
		fprintf(infile, "-email \"%s\" -pwd %s -pwdneverexpires yes -desc \"%s\" -memberOf \"cn=Basis,cn=Users,dc=basis,dc=com,dc=br\" \"cn=jira-users,cn=Users,dc=basis,dc=com,dc=br\" ", profile.email, profile.passwrd, desc);
	}
	else if (strcmp(function, "programador") == 0) {
		printf("Informe o contrato do Programador (lembre-se de usar minúsculas | escreva o contrato do mesmo modo que no SGO): ");
		read_string(contract);
		profile.firstname[0] = toupper(profile.firstname[0]);
		profile.lastname[0] = toupper(profile.lastname[0]);
		fprintf(infile, "dsadd user \"cn=%s,cn=Users,dc=basis,dc=com,dc=br\" -upn %s@basis.com.br -samid %s -fn \"%s\" -ln \"%s\" -display \"%s\" ", profile.fullname, profile.loginsgo, profile.loginsgo, profile.firstname, profile.lastname, profile.fullname);
		fprintf(infile, "-email \"%s\" -pwd %s -pwdneverexpires yes -desc \"%s\" -memberOf \"cn=Basis,cn=Users,dc=basis,dc=com,dc=br\" \"cn=jira-users,cn=Users,dc=basis,dc=com,dc=br\" ", profile.email, profile.passwrd, desc);
		fprintf(infile, "\"cn=%s-basis,cn=Users,dc=basis,dc=com,dc=br\" \"cn=%s-codificadores,cn=Users,dc=basis,dc=com,dc=br\" -uc", contract, contract);
	}
	else if (strcmp(function, "analista") == 0) {
		printf("Informe o contrato do Analista (lembre-se de usar minúsculas | escreva o contrato do mesmo modo que no SGO): ");
		read_string(contract);
		profile.firstname[0] = toupper(profile.firstname[0]);
		profile.lastname[0] = toupper(profile.lastname[0]);
		fprintf(infile, "dsadd user \"cn=%s,cn=Users,dc=basis,dc=com,dc=br\" -upn %s@basis.com.br -samid %s -fn \"%s\" -ln \"%s\" -display \"%s\" ", profile.fullname, profile.loginsgo, profile.loginsgo, profile.firstname, profile.lastname, profile.fullname);
		fprintf(infile, "-email \"%s\" -pwd %s -pwdneverexpires yes -desc \"%s\" -memberOf \"cn=Basis,cn=Users,dc=basis,dc=com,dc=br\" \"cn=jira-users,cn=Users,dc=basis,dc=com,dc=br\" ", profile.email, profile.passwrd, desc);
		fprintf(infile, "\"cn=%s-basis,cn=Users,dc=basis,dc=com,dc=br\" \"cn=%s-documentadores,cn=Users,dc=basis,dc=com,dc=br\" -uc", contract, contract);
	}
	else if (strcmp(function, "fabrica") == 0) {
		printf("Informe a qual Fábrica o usuário pertence: \n");
		printf("(AM | BH | BW | CD | CG | CJ | CL | CS | DG | EA | FN | FNDE | JJ | QL | TS | WO | WP): ");
		read_string(contract);
		for (i = 0; i < (int)strlen(function); ++i) {
			function[i] = tolower(function[i]);
		}
		profile.firstname[0] = toupper(profile.firstname[0]);
		profile.lastname[0] = toupper(profile.lastname[0]);
		fprintf(infile, "dsadd user \"cn=%s,cn=Users,dc=basis,dc=com,dc=br\" -upn %s@basis.com.br -samid %s -fn \"%s\" -ln \"%s\" -display \"%s\" ", profile.fullname, profile.loginsgo, profile.loginsgo, profile.firstname, profile.lastname, profile.fullname);
		fprintf(infile, "-email \"%s\" -pwd %s -pwdneverexpires yes -desc \"%s\" -memberOf \"cn=Basis,cn=Users,dc=basis,dc=com,dc=br\" \"cn=jira-users,cn=Users,dc=basis,dc=com,dc=br\" ", profile.email, profile.passwrd, desc);
		fprintf(infile, "\"cn=fabricas-externas,cn=Users,dc=basis,dc=com,dc=br\" \"cn=fabrica-%s,cn=Users,dc=basis,dc=com,dc=br\" -uc", contract);
	}
	else {
		printf("Função não encontrada!!\nVoltando à execução...\n\n");
		sleep(1);
	}
	fclose(infile);
	return;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
void make_script_bd(FILE *infile, user profile) {
	unsigned int assignment = 0;
	unsigned int contract = 0;
	char *assignmenttext;
	char *contracttext;
	assignmenttext = (char*)malloc(sizeof(char));
	contracttext = (char*)malloc(sizeof(char));
	infile = open_file(infile, filescriptbd, "w+");
	fflush_in();
	printf("Atribuições já cadastradas:\n1 - Auditor\n2 - Fiscal requisitante\n3 - Fiscal técnico\n4 - Fiscal técnico assistente\n5 - Gestor de negócio\n");
	printf("6 - Requisitante\n7 - Requisitante assistente\n8 - Todos\n");
	printf("Qual atribuição do usuário ?: ");
	scanf("%u", &assignment);
	if ((assignment <= 0) || (assignment >= 9)) {
		printf("Valor de atribuição inválida!!!\n");
		sleep(1);
		system("clear || cls");
		printf("Atribuições já cadastradas:\n1 - Auditor\n2 - Fiscal requisitante\n3 - Fiscal técnico\n4 - Fiscal técnico assistente\n5 - Gestor de negócio\n");
		printf("6 - Requisitante\n7 - Requisitante assistente\n8 - Todos\n");
		printf("Qual atribuição do usuário ?: ");
		scanf("%u", &assignment);
		while ((assignment <= 0) || (assignment >= 9)) {
			printf("Valor de atribuição inválida!!!\nDigite novamente a atribuição: ");
			scanf("%u", &assignment);
		}
	}
	system("clear || cls");
	printf("Contratos já cadastrados:\n1 - AGU\t\t12 - FUNDACENTRO\n2 - BASIS\t13 - GAFISA\n3 - CADE\t14 - HUB\n");
	printf("4 - CAMARA\t15 - IBAMA\n5 - CLDF\t16 - MARINHA\n6 - EB\t\t17 - MMA\n7 - EBCOLOG\t18 - MT\n8 - FAAP\t19 - POUPEX\n");
	printf("9 - FDC\t\t20 - RECALL\n10 - FNDE\t21 - SDH\n11 - FUNASA\t22 - STC\n");
	printf("Qual o contrato do usuário ?: ");
	scanf("%u", &contract);
	if ((contract <= 0) || (contract >= 23)) {
		printf("Valor de contrato inválido!!!\n");
		sleep(1);
		system("clear || cls");
		printf("Contratos já cadastrados:\n1 - AGU\t\t12 - FUNDACENTRO\n2 - BASIS\t13 - GAFISA\n3 - CADE\t14 - HUB\n");
		printf("4 - CAMARA\t15 - IBAMA\n5 - CLDF\t16 - MARINHA\n6 - EB\t\t17 - MMA\n7 - EBCOLOG\t18 - MT\n8 - FAAP\t19 - POUPEX\n");
		printf("9 - FDC\t\t20 - RECALL\n10 - FNDE\t21 - SDH\n11 - FUNASA\t22 - STC\n");
		printf("Qual o contrato do usuário ?: ");
		scanf("%u", &contract);
		while ((contract <= 0) || (contract >= 23)) {
			printf("Valor de contrato inválido!!!\nDigite novamente o contrato: ");
			scanf("%u", &contract);
		}
	}
	convert_assignement(assignmenttext, assignment);
	convert_contract(contracttext, contract);
	if (strcmp(assignmenttext, "NULL") == 0) {
		if (strcmp(contracttext, "NULL") == 0) {
			fprintf(infile, "INSERT INTO [jiraproducao].[sgo].[usuario] ([idusuario],[area_requisitante_idarea_requisitante],[matricula],[portaria],[atribuicao],[contrato],[ativo])\n");
			fprintf(infile, "VALUES ('%s', NULL, NULL, NULL, NULL, NULL, 1)\nGO", profile.loginsgo);
		}
		else if (strcmp(contracttext, "NULL") != 0) {
			fprintf(infile, "INSERT INTO [jiraproducao].[sgo].[usuario] ([idusuario],[area_requisitante_idarea_requisitante],[matricula],[portaria],[atribuicao],[contrato],[ativo])\n");
			fprintf(infile, "VALUES ('%s', NULL, NULL, NULL, NULL, '%s', 1)\nGO", profile.loginsgo, contracttext);
		}
		else {
			/* nothing */
		}
	}
	else if (strcmp(assignmenttext, "NULL") != 0) {
		if (strcmp(contracttext, "NULL") == 0) {
			fprintf(infile, "INSERT INTO [jiraproducao].[sgo].[usuario] ([idusuario],[area_requisitante_idarea_requisitante],[matricula],[portaria],[atribuicao],[contrato],[ativo])\n");
			fprintf(infile, "VALUES ('%s', NULL, NULL, NULL, '%s', NULL, 1)\nGO", profile.loginsgo, assignmenttext);
		}
		else if (strcmp(contracttext, "NULL") != 0) {
			fprintf(infile, "INSERT INTO [jiraproducao].[sgo].[usuario] ([idusuario],[area_requisitante_idarea_requisitante],[matricula],[portaria],[atribuicao],[contrato],[ativo])\n");
			fprintf(infile, "VALUES ('%s', NULL, NULL, NULL, '%s', '%s', 1)\nGO", profile.loginsgo, assignmenttext, contracttext);
		}
		else {
			/* nothing */
		}
	}
	else {
		/* nothing */
	}
	fclose(infile);
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
		printf("O script do SGO temporário foi limpo com sucesso!\n");
		infile = open_file(infile, filescript, "w+");
		fclose(infile);
		status = 1;
	}
	else {
		printf("Erro ao limpar script temporário\n");
		status = -1;
	}

	status = remove("./doc/scriptbdtemp.txt");
	if (status == 0) {
		printf("O script do BD temporário foi limpo com sucesso!\n");
		infile = open_file(infile, filescriptbd, "w+");
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
	for (i = 0; i < 40; ++i) {
		printf("*");
	}
	printf("\n*   Sistema de inclusão de usuários    *\n");
	for (i = 0; i < 40; ++i) {
		printf("*");
	}
	printf("\n* Versão:  0.0.1                       *");
	printf("\n* Autor:   João Pedro Sconetto         *");
	printf("\n* Contato: joao.sconetto@basis.com.br  * \n*\t   sconetto.joao@gmail.com     *\n");
	for (i = 0; i < 40; ++i) {
		printf("*");
	}
	printf("\n* Licensa MIT (disponível em):         *");
	printf("\n*               https://goo.gl/U689hW  *\n");
	for (i = 0; i < 40; ++i) {
		printf("*");
	}
	printf("\n");
	sleep(5);
	return;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
void convert_assignement(char *s, unsigned int assignment) {
	switch (assignment) {
	case auditor:
		strcpy(s, "auditor");
		break;
	case fiscalrequisitante:
		strcpy(s, "fiscal requisitante");
		break;
	case fiscaltecnico:
		strcpy(s, "fiscal técnico");
		break;
	case fiscaltecassistente:
		strcpy(s, "fiscal técnico assistente");
		break;
	case gestor:
		strcpy(s, "gestor de negócio");
		break;
	case requisitante:
		strcpy(s, "requisitante");
		break;
	case requisitanteassistente:
		strcpy(s, "requisitante assistente");
		break;
	case todos:
		strcpy(s, "todos");
		break;
	default:
		printf("Erro ao converter a atribuição.\nAtribuição não encontrada!!\n");
		strcpy(s, "NULL");
		break;
	}
	return;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
void convert_contract(char *s, unsigned int contract) {
	switch (contract) {
	case agu:
		strcpy(s, "AGU");
		break;
	case basis:
		strcpy(s, "NULL");
		break;
	case cade:
		strcpy(s, "CADE");
		break;
	case camara:
		strcpy(s, "CAMARA");
		break;
	case cldf:
		strcpy(s, "CLDF");
		break;
	case eb:
		strcpy(s, "EB");
		break;
	case ebcolog:
		strcpy(s, "EBCOLOG");
		break;
	case faap:
		strcpy(s, "FAAP");
		break;
	case fdc:
		strcpy(s, "FDC");
		break;
	case fnde:
		strcpy(s, "FNDE");
		break;
	case funasa:
		strcpy(s, "FUNASA");
		break;
	case fundacentro:
		strcpy(s, "FUNDACENTRO");
		break;
	case gafisa:
		strcpy(s, "GAFISA");
		break;
	case hub:
		strcpy(s, "HUB");
		break;
	case ibama:
		strcpy(s, "IBAMA");
		break;
	case marinha:
		strcpy(s, "MARINHA");
		break;
	case mma:
		strcpy(s, "MMA");
		break;
	case mt:
		strcpy(s, "MT");
		break;
	case poupex:
		strcpy(s, "POUPEX");
		break;
	case recall:
		strcpy(s, "RECALL");
		break;
	case sdh:
		strcpy(s, "SDH");
		break;
	case stc:
		strcpy(s, "STC");
		break;
	default:
		printf("Erro ao converter o contrato.\nContrato não encontrado!!\n");
		strcpy(s, "NULL");
		break;
	}
	return;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
void menu_interface() {
	int i  = 0 ;
	printf("\t");
	for (i = 0; i < 51; ++i) {
		printf("*");
	}
	printf("\n\t*       Escolha a opção desejada:                 *\n\t");
	for (i = 0; i < 51; ++i) {
		printf("*");
	}
	printf("\n\t*    1 - Criar um usuário                         *");
	printf("\n\t*    2 - Criar vários usuários                    *");
	printf("\n\t*    3 - Visualizar usuários cadastrados          *");
	printf("\n\t*    4 - Sair                                     *\n");
	printf("\t");
	for (i = 0; i < 51; ++i) {
		printf("*");
	}
	printf("\n\n");
	return;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
void show_register_users() {
	FILE *infile;
	user *users = NULL;
	int i, aux;
	unsigned int counter = 0;
	infile = NULL;
	infile = open_file(infile, fileregister, "r+");

	do {
		aux = fgetc(infile);
		if (aux == '\n') counter++;
	} while (aux != EOF);

	users = (user*) malloc(counter * sizeof(user));
	rewind(infile);

	if (counter <= 0) {
		printf("Não há usuários registrados\nVoltando ao menu\n\n");
		sleep(2);
	}
	else {
		for (i = 1; i < (int)counter; ++i) {
			do {
				aux = fgetc(infile);
				if (aux == '\n') break;
			} while (aux != EOF);
			fscanf(infile, "%u|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", &users[i].id, users[i].fullname, users[i].firstname, users[i].lastname, users[i].loginsgo, users[i].passwrd, users[i].loginskype, users[i].passwrd, users[i].email, users[i].passwrdstd);
		}

		for (i = 1; i < (int)counter; ++i) {
			printf("ID do usuário: %u\n", users[i].id);
			printf("Nome completo do usuário: %s\n", users[i].fullname);
			printf("Primeiro nome: %s\n", users[i].firstname);
			printf("Último nome: %s\n", users[i].lastname);
			printf("Senha (gerada): %s\n", users[i].passwrd);
			printf("Senha (padrão): %s\n", users[i].passwrdstd);
			printf("Login (SGO): %s\n", users[i].loginsgo);
			printf("Login (Skype): %s\n", users[i].loginskype);
			printf("Email: %s\n\n", users[i].email);
			sleep(1);
		}
	}
	fflush_in();
	getchar();
	fclose(infile);
	system("clear || cls");
	return;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
void make_log() {
	FILE *infile = NULL;
	FILE *readfile = NULL;
	char character;
	int i;
	infile = open_file(infile, filelog, "a+");
	readfile  = open_file(readfile, fileemail, "r");
	while ((character = fgetc(readfile)) != EOF) {
		fputc(character, infile);
	}
	fputc('\n', infile);
	for (i = 0; i < 50; ++i) {
		fputc('-', infile);
	}
	fputc('\n', infile);
	fclose(readfile);
	readfile  = open_file(readfile, filescript, "r");
	while ((character = fgetc(readfile)) != EOF) {
		fputc(character, infile);
	}
	fputc('\n', infile);
	for (i = 0; i < 50; ++i) {
		fputc('-', infile);
	}
	fputc('\n', infile);
	fclose(readfile);
	readfile  = open_file(readfile, filescriptbd, "r");
	while ((character = fgetc(readfile)) != EOF) {
		fputc(character, infile);
	}
	fputc('\n', infile);
	for (i = 0; i < 50; ++i) {
		fputc('-', infile);
	}
	fputc('\n', infile);
	fclose(readfile);
	fclose(infile);
	return;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
void clean_log() {
	FILE* infile;
	int status;
	infile = NULL;
	status = 1;
	status = remove("./doc/log.txt");
	if (status == 0) {
		infile = open_file(infile, filelog, "w+");
		fclose(infile);
		status = 1;
	}
	else {
		printf("Erro ao limpar log\n");
		status = -1;
	}
	return;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/