#include "form.h"

int main() {
	unsigned int menu;
	user profile;
	setlocale(LC_ALL, "Portuguese");
	system("cls || clear");
	clean_temps();
	sleep(2);
	system("cls || clear");
	interface();
	system("cls || clear");
	do {
		menu_interface();
		printf("Escolha uma opção do menu: ");
		scanf("%u", &menu);
		while (menu > 5 || menu <= 0) {
			printf("Opção não reconhecida!!\n");
			sleep(2);
			system("cls || clear");
			menu_interface();
			printf("Escolha uma opção do menu: ");
			scanf("%u", &menu);
		}
		switch (menu) {
		case 1:
			profile = read_new_user();
			sleep(2);
			system("cls || clear");
			printf("Informações do novo usuário: \n");
			show_user(profile);
			break;
		case 2:
			break;
		case 3:
			system("cls || clear");
			show_register_users();
			break;
		case 4:
			break;
		case 5:
			printf("Terminando a execução...\n");
			printf("Obrigado por usar o sistema!!!\n\n");
			break;
		default:
			break;
		}
	} while (menu != 5);
	return 0;
}