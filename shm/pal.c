#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

char *reverse(char *string);

int isPalindrome(char *string, char *revers) {
	return strcmp(string, revers) == 0;
}

int main(void)
{
  const char *name = "OS";	// file name
  const int SIZE = 4096;		// file size

  int shm_fd;		// file descriptor, from shm_open()
  char *shm_base;	// base address, from mmap()

  /* open the shared memory segment as if it was a file */
  shm_fd = shm_open(name, O_RDONLY, 0666);
  if (shm_fd == -1) {
    printf("cons: Shared memory failed: %s\n", strerror(errno));
    exit(1);
  }

  /* map the shared memory segment to the address space of the process */
  shm_base = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
  if (shm_base == MAP_FAILED) {
    printf("cons: Map failed: %s\n", strerror(errno));
    // close and unlink?
    exit(1);
  }

  /* read from the mapped shared memory segment */
  //display("cons", shm_base, 64);	// first as bytes, then as a string
  char *string = malloc(strlen(shm_base));
  sprintf(string, "%s", shm_base);
  printf("%s",
  char *revers = reverse(string);
  if (isPalindrome(string, revers))
	  printf("It is a palindrome");
  else printf("It is not a palindrome");

  
/* remove the mapped shared memory segment from the address space of the process */
//  if (munmap(shm_base, SIZE) == -1) {
    //printf("cons: Unmap failed: %s\n", strerror(errno));
    //exit(1);
  //}

  /* close the shared memory segment as if it was a file */
//  if (close(shm_fd) == -1) {
    //printf("cons: Close failed: %s\n", strerror(errno));
    //exit(1);
  //}

  /* remove the shared memory segment from the file system */
 if (shm_unlink(name) == -1) {
   printf("cons: Error removing %s: %s\n", name, strerror(errno));
    exit(1);
 }
//  }
shm_unlink(name);
  return 0;
}

char *reverse(char *string) {
	char *rev = calloc(strlen(string) + 1, 1);
	for (int i=0; i<strlen(string); i++) {
		rev[i] = string[strlen(string)-i];
	}
	return rev;

}
