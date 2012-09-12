#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define BUFFER_SIZE 512

/* Parse a line into an array around delimiter, the ary_size
 * parameter limits the number of component parsed to ary_size
 * returns the number of component read or -1 in case of an error */
int parse_line(char **line, char **ary, int ary_size, char *delimiter)
{
	ary[0] = strtok(*(line), delimiter);
	int nargs = 0;
	while (ary[nargs] != NULL) {
		if (++nargs == ary_size) {
			errno = E2BIG;
			return -1;
		}
		ary[nargs] = strtok(NULL, delimiter);
	}
	return nargs;
}

/* Read a line from fd into ary and returns 
 * - the number of characters read
 * - -1 if something failed 			*/ 
int read_line(char **ary)
{	
	char buffer[BUFFER_SIZE];
	int buffer_length = 0;
	int line_length = 0;
	char *line = (char *) malloc(sizeof(char) * BUFFER_SIZE);
	char *old_line;
	if (line == NULL) 
		return -1;
	while (fgets(buffer, BUFFER_SIZE, stdin)) {
		buffer_length = strlen(buffer);
		line_length += buffer_length;
		/* We keep a reference to the line if realloc fails */
		old_line = line; 
		line = realloc(line, line_length + 1);
		if (line == NULL) {
			free(old_line);
			return -1;
		}
		strncat(line, buffer, buffer_length);
		if (buffer[buffer_length-1] == '\n')
			break;
	}
	/* If the read failed not because of EOF */
	if (ferror(stdin) == 0) {
		*(ary) = line;
		return line_length;
	} else {
		return -1;
	}
}

int main(void) 
{
	char *val;
	int k = read_line(&val);
	char *ary[10];
	printf("%d %d\n", k, parse_line(&val, ary, 10, " "));
	return 0;

}





