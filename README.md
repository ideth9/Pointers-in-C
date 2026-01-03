# Description 
C program that dynamically creates an integer array, safely reads user input, sorts the values, and prints the result. 
It defines a custom IntArray structure to store the array length and a pointer to dynamically allocated memory. 
The program validates all user input using fgets and strtol to ensure only positive integers are accepted. 
After reading the values, it sorts the array, then prints the sorted array and frees all allocated memory to prevent leaks.
