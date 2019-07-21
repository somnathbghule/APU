#include <src.h>

//int stat(const char *pathname, struct stat *statbuf);
int checkFileExits( const char *fName ){
	struct stat statbuf;
	int result = stat(fName, &statbuf);
	if ( result == -1 ){
		return 0;
	}
	return 1;
}

int openFileCreatIfNotExists( const char *fName ){
	int fd = open( fName, O_RDWR | O_CREAT , 0666 );
	return fd;
}

int noHoleFile(){
	int fd=0;
	int exists = checkFileExits( NO_HOLE_FILE_NAME );
	DPRINTF("exists: %d\n", exists);
	fd = openFileCreatIfNotExists( NO_HOLE_FILE_NAME );
	if ( fd == -1 ){
		DPRINTF("openFileCreatIfNotExists failed\n");
		exists = 0;
	}
	int offset = 0;
	char tempBuf[]="somnath";
	while ( !exists && write(fd, tempBuf, CHUNK_SIZE) && (offset+=CHUNK_SIZE) < FILE_MAX_SIZE ); 

	return fd;
}

int oneHoleFile() {

	int fd=0;
	int exists = checkFileExits( ONE_HOLE_FILE_NAME );
	DPRINTF( "exists: %d\n", exists );
	fd = openFileCreatIfNotExists( ONE_HOLE_FILE_NAME );
	if ( fd == -1 ) {
		DPRINTF( "openFileCreatIfNotExists failed\n" );
		exists = 0;
	}
	int offset = 0;
	char tempBuf[]="somnath";
	offset += CHUNK_SIZE;
	lseek(fd, offset, SEEK_SET);
	while ( !exists && write( fd, tempBuf, CHUNK_SIZE ) && (offset+=CHUNK_SIZE) < FILE_MAX_SIZE ); 
	return fd;
}

int gtThanOneHoleFile() {

	int fd=0;
	int exists = checkFileExits( GT_THAN_ONE_HOLE_FILE_NAME );
	DPRINTF( "exists: %d\n", exists );
	fd = openFileCreatIfNotExists( GT_THAN_ONE_HOLE_FILE_NAME );
	if ( fd == -1 ) {
		DPRINTF( "openFileCreatIfNotExists failed\n" );
		exists = 0;
	}
	int offset = 0;
	char tempBuf[]="somnath";
	
	offset += CHUNK_SIZE;
	lseek(fd, offset, SEEK_SET);
	
	write( fd, tempBuf, CHUNK_SIZE );
	offset += CHUNK_SIZE;
	
	offset += CHUNK_SIZE;
	lseek(fd, offset, SEEK_SET);

	while ( !exists && write( fd, tempBuf, CHUNK_SIZE ) && (offset+=CHUNK_SIZE) < FILE_MAX_SIZE ); 
	return fd;
}

void cleanUp(){

	int status=remove( NO_HOLE_FILE_NAME );
	if ( status )
		DPRINTF ("remove (%s) failed\n", NO_HOLE_FILE_NAME);

	status=remove( ONE_HOLE_FILE_NAME );
	if ( status )
		DPRINTF ("remove (%s) failed\n", ONE_HOLE_FILE_NAME);
	status=remove( GT_THAN_ONE_HOLE_FILE_NAME );
	if ( status )
		DPRINTF ("remove (%s) failed\n", GT_THAN_ONE_HOLE_FILE_NAME);

}
/*
 *
 * On Sucess returns hole count, else return -1
 *
 */

int findHole(int fd) {

	char tempbuf[CHUNK_SIZE];
	int holeCount = 0;
	lseek(fd, 0, SEEK_SET);
	while( read( fd, tempbuf, CHUNK_SIZE ) == CHUNK_SIZE ) {
		DPRINTF("%s ", tempbuf);
		DPRINTF("%d ", ( ( tempbuf[0] & 0xFF ) && ( tempbuf[1] & 0xFF ) && ( tempbuf[2] & 0xFF ) && ( tempbuf[3] & 0xFF ) ) );
		if(! ( ( tempbuf[0] & 0xFF ) && ( tempbuf[1] & 0xFF ) && ( tempbuf[2] & 0xFF ) && ( tempbuf[3] & 0xFF ) )){
			holeCount++;
		}
	}	
	DPRINTF("holeCount: %d \n", holeCount);
	close(fd);
	return holeCount;	
}

