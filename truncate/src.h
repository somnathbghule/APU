#ifndef SRC_H
#define SRC_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>

#define CHUNK_SIZE 8 //in byte
#define FILE_MAX_SIZE 64 //inbyte

#define DEBUG 1

#define NO_HOLE_FILE_NAME "test_no_hole.tmp"
#define ONE_HOLE_FILE_NAME "test_one_hole.tmp"
#define GT_THAN_ONE_HOLE_FILE_NAME "test_gt_than_one_hole.tmp"

int checkFileExits(const char *fName);
int findHole(int fd);
int openFileCreatIfNotExists(const char *fName);
int noHoleFile();
int oneHoleFile();
int gtThanOneHoleFile();
void cleanUp();

#ifdef DEBUG
	#define DPRINTF  printf
#else
	#define DPRINTF(...)
#endif

#endif
