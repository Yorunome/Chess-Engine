//main program
#include "stdafx.h"
#include <iostream>
#include "Definitions.h"


using namespace std;

int main(){
	AllInit();
	int index = 0;
	for (index = 0; index < 64; index++) {
		if (index % 10 == 0) cout << endl;
		cout << SQ64ToSQ120[index];
	}

	return 0;
}

