//WRITTEN BY MANANSH
#include<stdio.h>
#include <stdlib.h>
#include <time.h>

//Minesweeper game!

/** Initialize the Game **/
void initializeGame(char *gameBoard, int rows, int columns){
	int i, j;
/** We want to fill the char array with X's **/	
	char x = 'X';
	for(i=0; i<rows; i++){
		for(j=0; j<columns; j++){
			*((gameBoard + i*columns) + j) = x;
		}	
	}  

}

/* Returns random float value */
float randomNum(int n, int m, int neg){
	float num;

	if(neg == 1){
	//m is the upper bound	
	num = (float)rand() / (float)(RAND_MAX / m);
	num = -num;
	return num;

	} else {
	/* If we want to return a positive value */
	num = (float)rand() / (float)(RAND_MAX / m);
	return num;
	}
}

/** Print Game **/ 
void displayGame(char *board, int rows, int columns){
	int i, j;
	for(i=0; i<rows; i++){
		printf("\n");
		for(j=0; j<columns; j++){
			printf("%c ", *((board+i*columns) + j));	
		
		}
	}
	printf("\n");

}

/**  CALCUATE SCORE     **/

float calcScore(float num){

	float total;
	total += num;
	return total;

}

void logScore(char *name, float score, float timePlayed){


//RECORD PLAYER NAME, SCORE, AND TOTAL TIME PLAYED.
	

	FILE *fptr = fopen("players.log", "a");
	if(fptr == NULL){
	printf("File cannot be opened or found!\n");
	exit(1);
	}
	fprintf(fptr, "File Generated Successfully\n");
	fprintf(fptr, "Player Name: %s\n", name);
	fprintf(fptr, "Player Score: %.2f\n", score);
	fprintf(fptr, "Total Time Elapsed: %.0fs\n", timePlayed);	
	fprintf(fptr, "\n");    
	//Close the file
	fclose(fptr);


    }
void exitGame(){
	printf("Thanks for Playing!");
}

/** Display all the players who have played **/
void displayTopScores(){

	int c;
	FILE *fptr;
	if((fptr= fopen("players.log", "r")) == NULL) {
		printf("File cannot be opened, or was not found!");	
		exit(1);	
	}
	
	if(fptr) {
		while((c = getc(fptr)) != EOF){
			putchar(c);
		}
			
	fclose(fptr);
	}
}


int main(int argc, char *argv[]){


/** Variable Declarations **/
	int xCord, yCord, matrixSize;	
	int rows, columns;
/** Command Line Arguements Handling **/
	matrixSize = atoi(argv[2]);
	rows = matrixSize;
	columns = matrixSize;	
	char *name = argv[1];

/** Array Declaration **/
	float gameTable[matrixSize][matrixSize];	//This array will have all of our random floats
	char displayTable[matrixSize][matrixSize];	//This array will have the X's and +'s and -'s
	

/** Command Line Arguement, BOUNDS CHECK **/
	if(matrixSize > 20 || matrixSize < 5){
	
		printf("Sorry, your command line argument is not valid. Please relaunch within the bounds of 5 - 20 \n");
	
	} else {
	srand(time(0));
	printf("Nice to meet you %s.", name);
        

/** Where we can start calling functions to get the game started **/
	int x=0;
	//THE LIMIT OF NEGATIVE NUMBERS THAT CAN EXSIST IN A GIVEN GAME
	int negativeWhile = 0.2 * (matrixSize * matrixSize);
	//WE NEED TO ACCOUNT FOR THE twenty percent NEGATIVE NUMBERS SOMEHO
	int i, j;
	int counter = 0;
	/** FILL ARRAY WITH REQUIRED FLOATS **/
	
	for(i=0; i<rows; i++){
		for(j=0; j<columns; j++){
			if(counter < negativeWhile){
				gameTable[i][j] = randomNum(0, 15, 1);
				counter++;
			} else {
				gameTable[i][j] = randomNum(0, 15, 0);
			}
		}
	
	}
	/**  PICK RANDOM SPOTS OF THE TABLE AND SET TO VALUES    **/
	int randXCord, randYCord;	
	randXCord = rand() & (matrixSize - 1);
	randYCord = rand() & (matrixSize - 1);
	gameTable[randXCord][randYCord] = 1000.0;

	/** PICK RANDOM SPOTS TO DOUBLE SCORE OR HALF SCORE **/
	int randXDouble, randYDouble;
	randXDouble = rand() & (matrixSize - 1);
	randYDouble = rand() & (matrixSize - 1);
	gameTable[randXDouble][randYDouble] = 2000.0;

	/** PICK RANDOM SPOTS TO HALF SCORE **/
	int randXHalf, randYHalf;
	randXHalf = rand() & (matrixSize - 1);
	randYHalf = rand() & (matrixSize - 1);
	gameTable[randXHalf][randYHalf] = 3000.0;

	/** INTIALIZE GAME BOARD **/

	initializeGame((char *)displayTable, rows, columns);
	
	/** DISPLAY GAME BOARD **/
	
	displayGame((char *)displayTable, rows, columns);

	time_t start, end;
	float currentPick;
	float gameScore = 0;
	int continueGame = 0;
	int game = 0;
	float tempTimer = 60;
	int gameCount = 0;
	int matrixSquare = (matrixSize * matrixSize);

	//do while loop start here.
	do {
	
	printf("Score: %.2f\n", gameScore);
    printf("Time: %.0f\n", tempTimer);

	start = time(NULL);
	printf("Enter X Cord: \n");
	scanf("%d", &xCord);
	printf("Enter Y Cord: \n");
	scanf("%d", &yCord);
	printf("\n");
	end = time(NULL);
	currentPick = gameTable[xCord][yCord];

	
	//CALCULATE DIFFERENCE FOR TIMER:
	tempTimer -= difftime(end, start);

	int newScore;
	int newHalfScore;
	//CHECK IF USER ENTRY IS WITHIN CORRECT BOUNDS

	if(xCord <= matrixSize && yCord <= matrixSize){

	/** Determine whether to print negative or positive number **/
		if(currentPick < 0){
			printf("UNLUCKY! YOU HIT A MINE. Lost %.2f Points\n", currentPick);
			displayTable[xCord][yCord] = '-';
			displayGame((char *)displayTable, rows, columns);
			gameCount++;
			gameScore+=currentPick;	
	
		/** Print Positive Num **/

		} else if(currentPick > 0 && currentPick < 999) {

			printf("LUCKY! YOU GOT POINTS. Gained %.2f Points\n", currentPick);
			displayTable[xCord][yCord] = '+';
			displayGame((char *)displayTable, rows, columns);
			gameCount++;
			gameScore+=currentPick;
	
		/** Print Time Suprise Package **/

		} else if(currentPick == 1000.0){
			printf("INCREASE IN TIME HAHA NICE!\n");
			displayTable[xCord][yCord] = '@';
			displayGame((char *)displayTable, rows, columns);
			gameCount++;
			tempTimer+=10;
	
		/** Print Score Doubled Suprise Package **/

		} else if(currentPick == 2000.0){
			printf("YOUR SCORE GETS DOUBLED NICE!\n");
			displayTable[xCord][yCord] = '$';
			displayGame((char *)displayTable, rows, columns);
			gameCount++;

			/* Double Algorithm */
			newScore = (int)gameScore;
			newScore = newScore << 1;
			printf("THE DOUBLED INT IS %d\n", newScore);
			newScore = (float)newScore;
			gameScore = newScore;
		
		/** Print Score Halved Suprise Package **/	
			
		} else if(currentPick == 3000.0){
			printf("OH NO YOUR SCORE GOT HALVED!\n");
			displayTable[xCord][yCord] = '!';
			displayGame((char *)displayTable, rows, columns);
			gameCount++;
			/* HALVE ALGORITHM */
			newHalfScore = (int)gameScore;
			newHalfScore = newHalfScore >> 1;
			newHalfScore = (float)newHalfScore;
			gameScore = newHalfScore;
		}	

	} else {

        printf("Sorry that pick is not with the correct bounds of %d x %d \n", matrixSize, matrixSize);
		printf("\n");
	}
	/** Display NAME, SCORE and TIMER **/
	
	printf("Player Name: %s\n ", name);
	printf("Current Score: %.2f\n", gameScore);
	printf("Time: %.0f\n ", tempTimer);


	/** CHECK IF GAME IS WON **/

	if(tempTimer <= 0){
		printf("GAME OVER!\n");
		break;
	//SCORE LESS THAN 0 AFTER FIRST TURN 	
	} else if(gameCount >= 2  &&  gameScore <= 0){
		printf("GAME OVER!\n");
		break;
	//IF EVERY PIECE OF THE BOARD HAS BEEN PICKED
	} else if(gameCount == matrixSquare){
		printf("GAME OVER!\n");
		break;
	} else {
		game = 0;
	}
		
	/**  ASK USER IF THEY WOULD LIKE TO CONTINUE  **/
	printf("Would you like to Quit? Press 8 to QUIT! Press 9 to continue \n");
	scanf("%d", &continueGame);

	if(continueGame == 8){
	
		game = 1;
	
	} else if(continueGame == 9){
	
		game = 0;

	} else {
	
		printf("Not a valid choice");
	
	}

	} while(game == 0);	


	/**  WHERE WE FINISH THE GAME! -> INCLUDE TOTAL SCORE< WIN/LOSE MESSAGE   **/
	
	float scoreToPrint;
	scoreToPrint = calcScore(gameScore);
	float timeElapsed;
	timeElapsed = 60 - tempTimer;
	int logPick;

	printf("Thanks for playing! Your final score is: %.2f\n", gameScore);
	logScore(name, gameScore, timeElapsed);
	printf("Would you like to see leaderboards? Press 1 to View or 0 to quit \n");
	scanf("%d", &logPick);
	
	if(logPick == 1){
		//displayTopScores()
		//READ LOG FILE
		displayTopScores();
	} else {
		exitGame();	
	}

	}
	return 0;
}









