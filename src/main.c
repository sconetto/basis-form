#include "form.h"

int main() {
	user profile;
	setlocale(LC_ALL, "Portuguese");
	profile = read_new_user();
	show_user(profile);
	return 0;
}