#include "form.h"

int main() {
	user profile;
	setlocale(LC_ALL, "Portuguese");
	system("cls || clear");
	clean_temps();
	sleep(2);
	system("cls || clear");
	interface();
	system("cls || clear");
	profile = read_new_user();
	sleep(2);
	
	system("cls || clear");
	printf("Informações do novo usuário: \n");
	show_user(profile);
	printf("Terminando a execução...\n");
	printf("Obrigado por usar o sistema!!!\n\n");
	return 0;
}