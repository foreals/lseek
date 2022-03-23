#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  char choice = ' ';
  int fd;            //file descriptor
  int i = 0;         //loop variable to fill locations array
  int seek;          //lseek
  int locations[10]; //locations of words
  int key;           //key
  char word;         //word found from key
  char *inserted = (char*) malloc(sizeof(char*)); //word inserted from user

  FILE *infile;
  infile = fopen("file.txt", "r+");

  if(!infile)
    {
      perror("fopen input");
      exit(EXIT_FAILURE);
    }

  fd = fileno(infile);

  while(i < 10)
  {
    fscanf(infile, "%d", &locations[i]);
    printf("%d\n", locations[i]);
    i++;
  }

  
  while(tolower(choice) != 'q')
    {
      printf("Enter s for search, i for insertion, or q to quit: ");
      scanf("\n%c", &choice);
      if(tolower(choice) == 's')
	{
	  //ask for key
	  printf("Enter a key (0-9): ");
	  scanf("\n%d", &key);
	  //lseek
	  seek = lseek(fd, locations[key]+28, SEEK_SET);
	  printf("%d\n", seek);
	  if(seek < 0)
	    {
	      perror("lseek error");
	      fclose(infile);
	      exit(1);
	    }
	  seek = read(fd, &word, sizeof(char));
	  while(word != '\\'){
	    printf("%c", word);
	    seek = read(fd, &word, sizeof(char));
	  }
	  printf("\n");
	}
      else if(tolower(choice) == 'i')
	{
	  //insert
	  printf("Enter a word you would like to insert: ");
	  scanf("\n%s", inserted);
	  seek = write(fd, (void *) lseek(fd, 0, SEEK_END), sizeof(inserted));
	}
      else if(tolower(choice) != 'q' && tolower(choice) != 'i'
	      && tolower(choice) != 's')
	{
	  printf("Error: Please enter s, i, or q\n");
	}
    }
  

  fclose(infile);
  return 0;
}
