#include<stdio.h>
#include <stdlib.h>
#include <time.h>


/** Written by Manansh Shukla CPSC **/


//Fill the array with random numbers
void initialize(int *t, int rows, int columns, int random){
    int i;
    int j;
    for(i=0; i<rows; i++){
        for(j=0; j<columns; j++){
            *((t + i*columns) + j) = rand()%10 ;
        }
    }
}

//Display the table
void display(int *t, int rows, int columns){
    int i, j;
    for(i=0; i<rows; i++){
        printf("\n");
        for(j=0; j<columns; j++){
            printf("%d", *((t+i*columns) + j));
        }
        
    }
    printf("\n");
}


/* Sort Function
 * Take in a pointer to array, rows, columns, user pick, and size of matrix
 * Take these values and single out the numbers in the column we want to sort
 * Perform simple BUBBLE sort and then append back to matrix and return
 * 
 */


void sort(int *t, int rows, int columns, int pick, int size){
    int i;
    int j;
    int o, in, temp;
    int swapTable[size];

    //Take Column we want to sort and put into a 1D Array
    for(i=0; i<rows; i++){
        swapTable[i] = *((t + i * rows + pick));
    }

    //BUBBLE SORT - Sort this ARRAY
    for(o = 0; o < size-1; o++){
        for(in = o + 1; in < size; in++){
            if(swapTable[o] > swapTable[in]){
                temp = swapTable[o];
                swapTable[o] = swapTable[in];
                swapTable[in] = temp;
            }
        }
    }

    //Append to original array
    for(i = 0; i<rows; i++){
        *((t + i * rows + pick)) = swapTable[i];
    }
    
    //Print Sorted Array For User
    for(i=0; i<rows; i++){
        printf("\n");
        for(j=0; j<columns; j++){
            printf("%d", *((t+i*columns) + j));
        }
    }
    	printf("\n");
}


//Takes parameters and makes checks
void logFile(int *t, int N, int userPick){

	FILE *fptr =  fopen("assign1.log","a");
	if(fptr == NULL){
	printf("File cannot be opened or found");
	exit(1);
	}
	fprintf(fptr,"File Created Successfully\n");
	fprintf(fptr,"Table Generated\n");
	fprintf(fptr, "Matrix is of size:  %d", N);

	int i, j;
   	 for(i=0; i<N; i++){
             fprintf(fptr,"\n");
             for(j=0; j<N; j++){
           	 fprintf(fptr,"%d", *((t+i*N) + j));
        }

    }

    fprintf(fptr,"\n");
    fprintf(fptr, "User Picked: ");
    fprintf(fptr, " %d", userPick);
    
    



    
    fclose(fptr);

}

int randomNum(int max){
    int num;
    srand(time(0));
    num = rand() % max;
    return num;
}

//Main method
int main(int argc, char *argv[]) {
   
    int matrixSize;
    int userPick = 0;
    int maxNumber = 10;
  
    //Perform ATOI command to convert Char array to Int.
    matrixSize = atoi(argv[1]);
    int rows = matrixSize;
    int columns = matrixSize;
    //Initialize Array
    int table[matrixSize][matrixSize];
    

    
    //First Check for Matrix Size	
    if(matrixSize > 9|| matrixSize <= 0){
    
    printf("Sorry value not valid - Please pick 1-9");
    
    } else {
    //Fill Array with randomNums	    
    initialize((int *)table, rows, columns, randomNum(maxNumber));
    //We want to ask for userPick here (also display text)
    printf("Original Matrix with %d rows/columns", matrixSize);
    //Display original Array
    display((int *)table, rows, columns);

    int userChoice;
    int counter;
    //For loop that will loop depending on the size of the matrix 
    for(counter = 0; counter < matrixSize; counter++){
	printf("Pick a column to sort: ");
	scanf("%d", &userPick);
	// SORT THAT HOE
	sort((int *)table, rows, columns, userPick, matrixSize);
	printf("\n");
	printf("Press 8 to continue or 9 to exit");
	printf("\n");
	scanf("%d", &userChoice);

	//Check to see if user wants to continue
	if(userChoice == 9){
		printf("\n");
		break;
	} else if(userChoice == 8){
		printf("\n");
		printf("Ok lets continue");
		printf("\n");
	} else {
		printf("\n");
		printf("Not a valid command lol");
		printf("\n");
		
	}
    }

    printf("Thanks for using!\n");
    //LOG FILE!
    logFile((int *)table, matrixSize, userPick);    

    return 0;

}


}
    























   






    








   


        


        

    



