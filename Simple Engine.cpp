//main program
#include "stdafx.h"
#include <iostream>
#include "init.cpp"


using namespace std;

int main(){
	AllInit();
	int ctr = -1;
	for (auto index = 0; index < 64; index++) {
		ctr++;
		if (ctr == 8) {
			cout << endl; ctr = 0;
		}
		cout << SQ64ToSQ120[index] << "\t";
	}

	return 0;
}

