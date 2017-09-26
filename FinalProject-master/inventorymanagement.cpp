#include "Inventory.h"

#include "Menu.h"

using namespace std;

int main(int argc, char const *argv[]) {
	/* code */

	Inventory temp = Inventory();
	Menu session = Menu();
	session.loginMenu();
	session.managerMenu();



	return 0;
}
