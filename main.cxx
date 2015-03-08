#include <iostream>
#include "directory.hxx"

using std::cout;
using std::endl;
using std::cin;

void usage() {
	cout << "imgorg [directory]" << endl;
	cout << "sorts files in a directory" << endl;
	cout << "warning! destructive to filenames!" << endl;
}

bool confirm() {
	char really;
	cout << "**WARNING** imgorg is destructive!" << endl;
	cout << "Really overwrite the filenames? (Y/N)" << endl;
	cin >> really;

	switch(really) {
		case 'Y':
			return true;
		case 'N':
			return false;
		default:
			return false;
	}	
}

int main(int argc, char **argv) {
	if(argc < 2) usage();

	else {
		if(!confirm())
			return 0;

		Directory dir(argv[1]);

		dir.open();
		dir.rename();
		dir.close();
	}

	return 0;
}
