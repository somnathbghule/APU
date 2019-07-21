#include <src.h>

int main(int  argc, char **argv){

	

	//test no hole
	assert( findHole (noHoleFile()) == 0 );
	assert( findHole (oneHoleFile()) == 1 );
	assert( findHole (gtThanOneHoleFile()) > 1 );

	cleanUp();

	//return from main
	return (0);
}
