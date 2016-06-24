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
	sleep(2);
	menu = 0;
	profile = read_new_user();
	printf("\n\n");
	show_user(profile);
	return 0;
}