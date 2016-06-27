#include "form.h"

int main() {
	int menu;
	user profile;
	setlocale(LC_ALL, "Portuguese");
	system("cls || clear");
	clean_temps();
	sleep(2);
	system("cls || clear");
	interface();
	system("cls || clear");
	menu = 0;
	profile = read_new_user();
	sleep(2);
	
	system("cls || clear");
	printf("Informações do novo usuário: \n");
	show_user(profile);
	return 0;
}