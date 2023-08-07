#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
	char a[20] = "hello ";
	char b[] = {'w','o','r','l','d','!','\0'};		// the \0 is important
	
	a[0]='H';										// set the first character to be H
	char *c = strcat(a, b);							// join/concatenate a and b
	printf("The string c is: %s\n", c);
	printf("The length of c is: %d\n", strlen(c));	// call string length
	// find and replace the w with a W
	char *p = strchr(c,'w');						// returns pointer to first 'w' character
	*p = 'W';
	printf("The string c is now: %s\n", c);
	
	if (strcmp("cat", "dog")<=0){					// ==0 would be equal
		printf("cat comes before dog (lexicographically)\n");
	}
	//insert "to the" into the middle of "Hello World!" string - very messy!
	char *d = " to the";
	// Next line allocates memory to pointer cd equal to the total length of c and d
	char *cd = malloc(strlen(c) + strlen(d));		//malloc(n) allocates n bytes of memory to the pointer
	// copy the first 5 bytes (characters) of "Hello World!", that is Hello, to start of cd
	memcpy(cd, c, 5);								//memcpy(source, dest, size) - copys size bytes of memory form source to dest
	// copy d to 6th char & beyond of cd (that is, all of d placed after c)
	memcpy(cd+5, d, strlen(d));
	// now add "World!" to the end
	memcpy(cd+5+strlen(d), c+5, 7);
	printf("The cd string is: %s\n", cd);
	
	//tokenize cd string using spaces
	p = strtok(cd," ");
	while (p!=NULL){
		printf("Token: %s\n", p);
		printf("Does the source string change?: %s\n", cd);
		p = strtok(NULL, " ");
	}
	return 0;
}