/*
1) Lab #2 Task 1: SImilar to the UNIX command cat, create a c program called show, to where show can
display the contents of the choosen file which is followed by the word show in the terminal.

*/


#include <fcntl.h> //system call function for open();
#include <unistd.h> //system call function for read(), wirte(), close()
#include <stdio.h> //required lib for regular input/output also contains perror()
#include <string.h> // so we can use strlen
#include <stdlib.h> //allows us to use atoi() to convert from str to int

int main(int argc, char *argv[]) //Paranmeter of this method requires the path to where the .txt file is located. This is evident when running show.c in the terminal when the
{
  // opne() --> file_path (string format), RWX permissions); This system call will open a file and obtain a file descriptor (represented as a postive integer for other system calls below). THus you will store the file descriptor in a int varibale. The File Descriptor gives you the I/O resources
  int FD = open(argv[3], O_RDWR);

  //remember for each system call, you must do an error check via a conditional statement. Thus, if the actual error occurs you dont use printf but rather perror
  //perror is a great system call used to determine if a fellow system call has an Error
  if(FD == -1){ //-1 means the FD does not exsist and thus the file doesnt exsist
    perror("File may not exsist, see if path is correct");
  }

  //read(file_descriptor, string *buffer, intmax_size_of_string). This system call pulls the bytes or chars from the file descriptor and stores it into the memory buffer/array of type char.In short, it's simply reading the data and storing it in the array
  //first paramter: is the variable of the int type that stores the file descriptor (where to read from?)
  //second parameter: This is usually an array of type char (for a string?), A pointer to a memory buffer. This array must have enough space to hold up to x bytes (where to put the data?)
  //third paramter: What is the MAX amount of bytes you want to read?
  int Bytes_Read = 0; //the number of chars read
  char Array_MB[100]; //can hold up to 100 bytes
  int Max_Bytes = 128;
  //we do this in a while loop
  int Count = 0;
  int Value1 = atoi(argv[1]); //converts string into int
  int Value2 = atoi(argv[2]);
  while((Bytes_Read = read(FD, Array_MB, Max_Bytes)) > 0){ //if there is actual content to read, the while loop will keep readung until it hits zero it'll never be -1 unless there is nothing to read
    if(Count!=Value1 || Count!=Value2){
      continue;
    }
    //write(file_descriptor, string *buffer, int num_chars_to_write). This system call pushes bytes from our memory buffer (array type char where the data is stored) and writes/prints it whatever is in the first argument of this function
    if(write(argv[4], Array_MB, Bytes_Read) != Bytes_Read){ //for the first argument of write, dont use the FD, this will simply re-wriote the contents from memory buffer or array back to the original file rather than the terminal. The fourth argument will be the destination_text/.txt file
      perror("error when writing to the destination text file");
      close(FD);
    }
  }
  if(Bytes_Read == -1){
    perror("nothing to read");
  }

  close(FD); //To close the FD
  return 0;

}
