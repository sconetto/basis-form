#include "form.h"

int main() {
	unsigned int menu;
	int quantity;
	int i;
	user profile;
	user *profiles = NULL;
	setlocale(LC_ALL, "Portuguese");
	system("cls || clear");
	clean_temps();
	sleep(2);
	system("cls || clear");
	interface();
	system("cls || clear");
	clean_log();
	clean_domain_csv();
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
		fflush_in();
		switch (menu) {
		case 1:
			profile = read_new_user();
			sleep(2);
			system("cls || clear");
			printf("Informações do novo usuário: \n");
			show_user(profile);
			make_log(profile);
			make_domain_csv(profile);
			fflush_in();
			getchar();
			system("cls || clear");
			break;
		case 2:
			printf("Quantos usuários deseja cadastrar?: ");
			scanf("%d", &quantity);
			fflush_in();
			profiles = malloc(quantity * sizeof(user));
			for (i = 0; i < quantity; ++i) {
				profile = read_new_user();
				sleep(2);
				system("cls || clear");
				printf("Informações do novo usuário: \n");
				show_user(profile);
				fflush_in();
				profiles[i] = profile;
				make_log(profile);
				make_domain_csv(profile);
				sleep(2);
				system("cls || clear");
			}
			printf("Listando usuários criados: \n");
			for (i = 0; i < quantity; ++i) {
				show_user(profiles[i]);
				printf("\n");
			}
			printf("Todos os arquivos dos usuários estão em doc/log.txt!!\n");
			printf("Aperte ENTER para continuar a execução");
			getchar();
			system("cls || clear");
			break;
		case 3:
			system("cls || clear");
			show_register_users();
			break;
		case 4:
			printf("Terminando a execução...\n");
			printf("Obrigado por usar o sistema!!!\n\n");
			break;
		default:
			printf("Opção não válida!\n");
			break;
		}
	} while (menu != 4);
	return 0;
}