//FileName: cA4.c
//ProjectName: cA4
//Author: Alex Guerrero
//Date: November 14, 2013
//Description:  This program calculates the total flying time, including layover time 
//				when the user enters a departing city and a destination city from the 
//				list of cities provided.



//include files
#include<stdio.h>



//disables a warning to allow the use of the getNum()
#pragma warning(disable: 4996)



//Constants used for rangeCheck function
#define minSize 1
#define maxSize 6


 
//constant multi-dimensional array used to hold flying times and layover times
const int kFlyingAndLayoverTimes[2][5] = 
{
	{255, 238, 235, 134, 207}, 
	{80, 46, 689, 53, 0}
};



//Constant char multi-dimensional array used to hold city names
const char cities[6][12] = {"1 - Toronto", "2 - Atlanta", "3 - Austin", "4 - Denver", "5 - Chicago", "6 - Buffalo"};



//Function prototypes
int getNum( void );
void printCities( const char cities[][12] );
void calcFlyingTime( const char cities[][12], const int kFlyingAndLayoverTimes[][5], int departureCity, int destinationCity );
int rangeCheck( int value, int minValue, int maxValue );



int main( void )
{
	//program variables initialized to 0
	int departureCity = 0;
	int destinationCity = 0;
	int rangeValue = 0;

	while( 1 )
	{
		//loop 
		while( 1 )
		{
			//Following code informs the user of what the program does as well as displays the cities using the printCities() function
			printf("***************************************************************************\n\n");
			printf("This program calculates total travel time for the cities listed below.\n\n\n");
			printCities( cities );
			printf("\n");
			//Informs user to exit the program by entering 0 or to enter the departure city of choice
			printf("To exit the program, please enter 0 now.\n");
			printf("Please enter the number corresponding to the city you are departing from.\n\n");


			//following code calls getNum() to retrieve user input and then proceeds to validate input using 
			//the rangeCheck function and its return values
			//If the user enters 0, exit the while loop.  If the user input is out of range, break out of the loop and reprompt the user to choose again
			departureCity = getNum();
			if( departureCity == 0 )
			{
				break;
			}
			
			rangeValue = rangeCheck( departureCity, minSize, maxSize );
			if( rangeValue == 0 )
			{
				break;
			}
			

			//Prompts user to enter a destination city
			printf("\n");
			printf("Please enter the number corresponding to the destination city.\n\n");


			//following code calls getNum() to retrieve user input for the destination city and then proceeds to validate input using 
			//the rangeCheck function and its return values
			//If the user input is out of range, the users choice of departure city and destination city are equal 
			//or the departure city is greater in value than the destination city entry,
			//the program prints an error message to the user and break out of the loop 
			//reprompt the user to choose again
			destinationCity = getNum();
			rangeValue = rangeCheck( destinationCity, minSize, maxSize );
			if( rangeValue == 0 )
			{
				break;
			}
			if( departureCity == destinationCity )
			{
				printf("\n\n\n");
				printf("ERROR: Departure number must be less than the destination number\n\n\n"); 
				printf("\n\n");
				break;
			}
			if( departureCity > destinationCity )
			{
				printf("\n\n\n");
				printf("ERROR: Departure number must be less than the destination number\n\n"); 
				printf("\n\n");
				break;
			}
			

			//Once cities have been entered and validated, calcFlyingTime() is called to calculate flying times for the user
			calcFlyingTime( cities, kFlyingAndLayoverTimes, departureCity, destinationCity );


		}
		//If departure city equals 0, exit the program
		if( departureCity == 0 )
		{
			break;
		}
	}

	printf("Goodbye\n");

	return 0;
}



//FunctionName: printCities
//Description:  Prints the contents of the array passed in as an argument using a while loop.
//Parameters: const char cities[][12]
//Return Values: Void
void printCities( const char cities[][12] )
{
	int count = 0;

	printf("   Cities\n");
	printf("************\n");

	//While count is less than or equal to 5, display data
	while( count <= 5 )
	{
		printf("%s\n", cities[count]);
		++count;
	}
}



//FunctionName: getNum
//Description:  gets user inputted numbers from the keyboard
//Parameters: void
//Return Values: number
int getNum( void )
{
	//array is 80 bytes in size and variable record stores the string
	char record[80] = {0};
	int number = 0;

	//fgets() is used to get a string from the keyboard
	fgets( record, sizeof(record), stdin );

	//extract a number from the string; sscanf() returns a number
    //corresponding with the number of items found in the string
    //if the user did not enter a number recognizable by the system,
    //set number to -1
	if( sscanf( record, "%d", &number ) != 1 )
	{
		number = -1;
	}

	return number;
}



//FunctionName: rangeCheck
//Description: Checks the user inputted data for valid entries (1 - 6).
//Parameters: int value, int minValue, int maxValue
//Return Values: valueOfRange
int rangeCheck( int value, int minValue, int maxValue )
{
    //varialbe used for return value
    int valueOfRange = 0;

    //if the user inputted data is out of range return 0, if data is in range return 1
    //if data is out of range, user is informed with a printf statement
    if( value < minValue || value > maxValue )
    {
		printf("\n\n");
        printf("ERROR: The value entered is out of range.\n\n");
		printf("Values must be between 1 and 6. Please check the list of cities again.\n\n\n");
        
        valueOfRange = 0;
    }
    else
    {
        valueOfRange = 1;
    }

    return valueOfRange;
}



//FunctionName: calcFlyingTime( const char cities[][12], const int flyingAndLayoverTimes[][5], int departureCity, int destinationCity )
//Description: Function calculates total flying time using a running total using the parameters listed and displays the time to the user.
//Parameters:  const char cities[][12], const int flyingAndLayoverTimes[][5], int departureCity, int destinationCity 
//Return Values: void
void calcFlyingTime( const char cities[][12], const int kFlyingAndLayoverTimes[][5], int departureCity, int destinationCity )
{
	//Variables initialized
	int layoverTime = 0;
	int sum = 0;
	int hours = 0;
	int minutes = 0;
	int startingCity = departureCity;
	int endingCity = destinationCity;

	//While user departure city choice is less than the destination city choice,
	//loop and calculate a running total of flying times and layover times.  
	while( departureCity < destinationCity )
	{
		sum = sum + kFlyingAndLayoverTimes[0][ departureCity -1 ] + layoverTime;
		layoverTime = kFlyingAndLayoverTimes[1][ departureCity - 1 ];
		++departureCity;
	}

	//When running total is calculated, divide sum by 60 to get the hours and use modulus to determine the remainder for the minutes.
	//Place totals into hours and minutes variables.
	//inform user of departure and destination choices and calculated flying time
	hours = sum/60;
	minutes = sum%60;
	printf("\n\n\n");
	printf("Your total travel time from %s to %s is %d:%d\n\n", cities[ startingCity - 1 ], cities[ endingCity - 1 ], hours, minutes);
	printf("\n\n");
}