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
//Use random() instead of rand() for better results
//
//Results for 10x10 square and 10k beetle should yield 67.0 life expectancy...
//We only get to 66.8 ... 
/*
Functions Used:
printf() - output
strtolong() - from math.h, converts string to a long int
random() - returns pseudo random number
cos(), sin() - math
--------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[]){

  int i, alive;
  double x,y, average, randradians; //beetle's position at a given time
  long int inches, beetles, seconds, sum;//square length, #beetles, second alive, sum of all seconds
  char *end;

  //checks correct number of arguments
  if(argc != 3){
    printf("Program needs exactly 2 arguments\n");
    printf("$ ./beetle [long int:inches] [long int:num beetles]\n");
    return -1;
  }//if wrong number of arguments


  //checks argument 1

/* 
  //Attempted Character by character check: UNTESTED
  for(i = 0; argv[1][i] != '\0'; i++){
    if((argv[1][i] < 48) || (argv[1][i] > 57)){
	if((i == 0) && argv[1][i] == '+'){
	  ;//do nothing
	}//if first char
	else{
	   printf("arg 1 contains invalid characters for a decimal number\n");
	   printf("ERROR ON: %d : %c\n\n", argv[1][i], argv[1][i]);
	   return -1;
	}//else
    }//if char is not a numeric
  }//end for
*/

  errno = 0; //global variable, copied from the strtol man page
  inches = strtol(argv[1], &end, 0);

  if(*end != '\0'){
    printf("arg 1 contains invalid characters for a decimal number\n");
    return -1;
  }//if arg1 bad input

  //this if statement is modified from the strtol man page
  //ERANGE from error.h, which flags if there's a range error
  //LONG_MAX, LONG_MIN constants for the range of long ints from limits.h 
  //LONG_MAX == +9223372036854775807, LONG_MIN == -92[...]08

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
 
  sum = 0;

  for(i = 0; i < beetles; i++){
    //each beetle starts out in the middle of the square
    //if x/y reaches negative, or x/y > inches, the beetle's boiled
    x = ((double)inches)/2.0; 
    y = ((double)inches)/2.0; 
    seconds = 0;   //beetle starts out at zero seconds before moving
    alive  = 1; //treat as bool, 0 == false, 1 == alive
    
    while(alive){
      //randradians = fmod((double)random(), (2*M_PI));
      //randradians = 2.0*random()/RAND_MAX*M_PI;
      randradians = random();
      x += cos(randradians);

      randradians = random(); 
      y += sin(randradians);
      
      if((x > (double)inches) || (x < 0.0) ||  //if the beetle has fallen off
	 (y > (double)inches) || (y < 0.0)){
	seconds++;
	alive  = 0;
      }//if the beetle is fallen
      else{
	seconds += 2;//it moves for 1 second + rests for 1 sec. = 2 more seconds
      }//else it lives for now
    }//while the beetle is alive
    
    sum += seconds;
  }//for each beetle
  
  average = (double)sum/(double)beetles;//average seconds alive 4 beetles

  printf("%ld by %ld square, %ld beetles, mean beetle lifetime is %.1f\n",
	 inches, inches, beetles, average);
  return 0;
}//main

