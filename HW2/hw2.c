#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  int fd;
  int wrt;
  int locations[10];

  char *buf;
  char *word;
  
  
  fd = open("file.txt", O_RDWR);

  if(fd < 0)
    {
      perror("open error");
      exit(1);
    }

  wrt = read(fd, &locations[0], sizeof(int));
  printf("loc = %d\n", locations[0]);
  
  if(wrt < 0)
    {
      perror("read error");
      close(fd);
      exit(1);
    }

  wrt = lseek(fd, sizeof(char*), SEEK_SET);

  if(wrt < 0)
    {
      perror("lseek error");
      close(fd);
      exit(1);
    }

  printf("buf = %s\n", buf);
  
  close(fd);

  return 0;
}
