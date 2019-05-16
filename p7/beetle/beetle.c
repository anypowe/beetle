//beetle.c
//nick powers
//26 jan 2016
//
//Assignment 1: C Warm-up
//
//Call executable as: 
//$ ./beetle [inches integer] [long int # of beetles]
//
//This program simulates drunken beetle life expectancy 
//of a beetle moving on an NxN inch square.
// 
//-The beetle moves in a straight line in a random direction.
//-It moves one inch/second and rests for one second and repeats.
//-If after 1 second the beetle is off the square,
// it is dead (because it fell into the boiling oil below)
//
//this program checks for correct command line input
//usage: ./beetle [long int] [long int]
//checks for valid, positive, non-overflow long ints
//for large input values, overflow may result from
//calculating the average
//--------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include "child.h"

int main(int argc, char *argv[]){

  int i, alive;
  double x,y, average, randradians; //beetle's position at a given time
  long int inches, beetles, seconds, sum;
  char *end;
  
  FILE *read_from, *write_to;
  char result[80], canvas_name[5];
  int childpid, half;
  long sleepsec;
  long sleepnan;
  int tomill;
  struct timespec time;
  
  tomill = 100;

  //checks correct number of arguments
  if(argc != 3){
    printf("Program needs exactly 2 arguments\n");
    printf("$ ./beetle [long int:inches] [long int:num beetles]\n");
    return -1;
  }//if wrong number of arguments


  //checks argument 1
  errno = 0; //global variable, copied from the strtol man page
  inches = strtol(argv[1], &end, 0);

  if(*end != '\0'){
    printf("arg 1 contains invalid characters for a decimal number\n");
    return -1;
  }//if arg1 bad input

  //this if statement is modified from the strtol man page
  if((errno == ERANGE && (inches == LONG_MAX || inches == LONG_MIN))
     || (errno != 0 && inches == 0)){
    printf("arg 1 was out of range for long integer type\n");
    return -1;
  }//if arg1 over/underflow
  if(inches <= 0){
    printf("need positive number of inches\n");
    return -1;
  }//if negative 


  //checks argument 2
  errno = 0;
  beetles = strtol(argv[2], &end, 0);
  
  if(*end != '\0'){
    printf("arg 2  contains invalid characters for a decimal number\n");
    return -1;
  }//if arg2 bad input

  //this if statement is modified from the strtol man page
  if((errno == ERANGE && (beetles == LONG_MAX || beetles == LONG_MIN))
     || (errno != 0 && beetles == 0)){
    printf("arg 2 was out of range for long integer type\n");
    return -1;
  }//if arg1 over/underflow
  if(beetles <= 0){
    printf("need positive number of beetles\n");
    return -1;
  }//if negative 
  //done with arg checking
  //------------------------------------------

  fprintf(stderr,"About to create wish child\n");
  childpid = start_child("wish",&read_from,write_to);
  fprintf(stderr,"Created wish");

  fprintf(write_to,"source beetle.tcl");
  fprintf(stderr,"wish: source beetle.tcl\n");
  sum = 0;

  for(i = 0; i < beetles; i++){
    //each beetle starts out in the middle of the square
    //if x/y reaches negative, or x/y > inches, the beetle's boiled
    x = ((double)inches)/2.0; 
    y = ((double)inches)/2.0; 
    seconds = 0;
    alive  = 1; //treat as bool, 0 == false, 1 == alive
    
    while(alive){
      
      //randradians = fmod((double)random(), (2*M_PI));
      //randradians = 2.0*random()/RAND_MAX*M_PI;
      randradians = rand();
      x += cos(randradians);
      y += sin(randradians);
      
      if((x > (double)inches) || (x < 0.0) ||
	 (y > (double)inches) || (y < 0.0)){
	seconds++;
	alive  = 0;
      }//if the beetle is fallen
      else{
	seconds += 2;
      }//else it lives for now
    }//while the beetle is alive
    
    sum += seconds;
  }//for each beetle
  
  average = (double)sum/(double)beetles;//average seconds alive 4 beetles

  printf("%ld by %ld square, %ld beetles, mean beetle lifetime is %.1f\n",
	 inches, inches, beetles, average);
  return 0;
}//main