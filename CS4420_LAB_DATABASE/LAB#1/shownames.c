#include <dirent.h>
#include <errno.h>
#include <stdio.h>
int main (int argc, char *argv[]) //no such thing as strings in C, just array of type char
{
	//argc = the total number of arugments when executing the compiled code.
	//argv = is an array of type string, where every single element/index is an argument
	//by default, the first argument [0] is when you execute the compiled source code: ./shownames.out
	//the second argument [1] is the directory (pathname to the directory) you wish to list the files of.
	struct dirent *direntp;
	// define a pointer with type directory stream (DIR): (to one of the five system calls in this case opendir)
	DIR *dt = opendir(argv[1]);

	// Check the number of arguments (argc). It should be two. If it
	//   is not two, then print an error message and exit the program:
	if (argc!=2)
	{
		fprintf (stderr, "Usage: %s directory name \n", argv[0]); //this is the error message
		return 1;
	}

	// The following lines should open the directory given by
	//   argument argv[1] (by using opendir).
	// Store it in your defined directory stream variable.
	// The rest checks if the system call returned a proper value
	//   if not an error message is printed and the program closed
	if (dt == NULL) //purpose of this if statement is to if the system call DOES NOT return a proper value
	{
		perror ( "Failed to open directory" ); //this is the error message 
		return 1;
	}

	// Read all the entries in this directory and store them in
	// direntp. readdir will read one entry at a time and increment
	// automatically. This is why it is in a while loop.
	// Then, print all the file names (using the struct from readdir).
	while ((direntp = readdir(dt))!= NULL)
		printf ("%s \n" , direntp->d_name);

	// close the defined directory stream.
	while ( ( closedir (dt) == -1) && ( errno == EINTR) );

	return 0;
}
