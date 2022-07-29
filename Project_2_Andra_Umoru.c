#include <stdio.h>     //including the C standard library
#include <mpi.h>      //Including the MPI library 

// Cartesian topology 4 x 4
//  0 – 1 – 2  – 3
//  |   |   |    |
//  4 – 5 – 6  – 7
//  |   |   |    |
//  8 – 9 – 10 – 11
//  |   |   |    |
// 12 – 13 –14 – 15

// C Language main function
int main(int argc, char **argv)
{

  //Declaring the size and the rank variables
 int size,rank;
 
 	//Initializing the MPI Environment 
 MPI_Init(&argc,&argv);
 
 	// Getting number of process
 MPI_Comm_size(MPI_COMM_WORLD,&size); 
 
 	// Getting rank of the process
 MPI_Comm_rank(MPI_COMM_WORLD,&rank); 
 
 //Getting the number of dimensions
 int dim [2]={4,4};  
 
 //Getting the period --> [0, 0] means non - periodic 
 int per [2]={0,0};  
 MPI_Comm com;
 
 // Creating the cartesian topology
 MPI_Cart_create(MPI_COMM_WORLD,2,dim,per,1,&com);
 
 //Mapping the neighbours in the cartesian topology
 int cord [2]={0,0};
 int crank;
 MPI_Cart_coords(com,rank,2,cord);
 
 // Printing the cartesian topology together with the mappings
 printf("I am %d and my coordinates are (%d,%d)\n", rank, cord[0],cord[1]);
 printf(" my neighbours are:\n");
 int c,d,neighbour;
 for(c=0;c<2;c++)
 {
 for(d=-1;d<2;d++)
 { // shift left and right by 1 step (d=-1,d=1) 
 if (d!=0)
 {
 MPI_Cart_shift(com,c,d,&rank,&neighbour);
 if (neighbour>=0)
 printf(" neighbour [%d,%d] has rank %d\n",c,d,neighbour);
 }
 }
 }
 
 // Exiting or Terminating the cartesian MPI routine
 MPI_Finalize();
 
 return 0;
}
