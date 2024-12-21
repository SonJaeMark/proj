#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define STR_MAX_SIZE 1024
#define STR_MIN_SIZE 128


//------------------------------UTILS------------------------------


void hello(char name[STR_MIN_SIZE]);
void fgetsNoNewline(char input[STR_MAX_SIZE], char output[STR_MAX_SIZE]);
int strSplit(char input[STR_MAX_SIZE], char output[STR_MAX_SIZE][STR_MAX_SIZE], char delimiter[STR_MIN_SIZE]);
bool isPasswordTypedCorrectly(char password[STR_MIN_SIZE], char retypedPassword[STR_MIN_SIZE]);
void inputStrValueInit(char strField[STR_MAX_SIZE], char validatedStrField[STR_MAX_SIZE]);
bool dateChecker(int MM, int DD, int YYYY);
void currentDateGetterStr(char dateInStr[STR_MIN_SIZE]);
void currentDateGetterInt(char dateInStr[STR_MIN_SIZE], int *date);
int strMonthToInt(char month[STR_MAX_SIZE]);
void csvFormatter(char listOfString[STR_MIN_SIZE][STR_MIN_SIZE], char csvFormattedStr[STR_MAX_SIZE], int arrSize);
int generateId();
void scanF(char buffer[STR_MAX_SIZE], char output[STR_MAX_SIZE]);





//------------------------------USER------------------------------



typedef struct UserDetails{

    int id;
    char password[STR_MIN_SIZE];
    char firstName[STR_MIN_SIZE];
    char middleName[STR_MIN_SIZE];
    char lastName[STR_MIN_SIZE];
    int dateOfBirth[3]; // {month, date, year}
    char email[STR_MIN_SIZE];
    char homeAdd[STR_MIN_SIZE];
} UserDetails;

typedef struct Student{
    struct UserDetails userDetails;
    char gradeLevel[STR_MAX_SIZE];
    char section[STR_MAX_SIZE];
    // grades[0] = math, grades[1] = eng, grades[2] = sci, 
    // grades[3] = fil, grades[4] = history, grades[5] = p.e.
    float grades[6]; 
}Student;

typedef struct Teacher{
    struct UserDetails userDetails;
    char sections[STR_MAX_SIZE][5];
}Teacher;

int registerUser();
int login();
int logout();

//------------------------------DATABASE------------------------------

int saveToDb(char *strData, bool isTeacher);
int saveStudentDetails(Student student);
void getUserPasswordById(char *id, char *passwordFromDb, bool isTeacher);



















//------------------------------MAIN------------------------------
//------------------------------MAIN------------------------------
//------------------------------MAIN------------------------------
//------------------------------MAIN------------------------------
int main(){

    printf("Hello world!!!\n");
    registerUser();

    
    return 0;
}
//------------------------------MAIN------------------------------
//------------------------------MAIN------------------------------
//------------------------------MAIN------------------------------
//------------------------------MAIN------------------------------











//------------------------------USER------------------------------



int registerUser(){
     
    char firstName[STR_MAX_SIZE];
    char middleName[STR_MAX_SIZE];
    char lastName[STR_MAX_SIZE];
    int dateOfBirth[5]; // {month, date, year}
    char email[STR_MAX_SIZE];
    char homeAdd[STR_MAX_SIZE];
    char dobBuff[STR_MAX_SIZE];
    char dobConBuff[STR_MAX_SIZE][STR_MAX_SIZE];
    char delim[STR_MIN_SIZE] = " ";

    dateOfBirth[0] = 0;
    dateOfBirth[1] = 0;
    dateOfBirth[2] = 0;


    printf("Enter First Name:");
    fgetsNoNewline(firstName, firstName);

    printf("Enter Middle Name:");
    fgetsNoNewline(middleName, middleName);

    printf("Enter Last Name:");
    fgetsNoNewline(lastName, lastName);
    
    printf("Enter Birthday:");
    fgetsNoNewline(dobBuff, dobBuff);

    printf("Enter Email:");
    fgetsNoNewline(email, email);

    printf("Enter Home Address:");
    fgetsNoNewline(homeAdd, homeAdd);

    strSplit(dobBuff, dobConBuff, delim);
    
    for(int i = 0; i < 3; i++){
        dateOfBirth[i] = atoi(dobConBuff[i]);
    }


    printf("%s %s %s\n", firstName, middleName, lastName);
    printf("%d/%d/%d\n", dateOfBirth[0], dateOfBirth[1], dateOfBirth[2]);
    printf("%s\n", email);
    printf("%s\n", homeAdd);
   
}




int login(){}
int logout(){}




//------------------------------UTILS------------------------------

void hello(char name[STR_MIN_SIZE]){

    printf("Hello %s\n", name);
    printf("Hello %s\n", name);

}

// param char input -> input string must be supplied with 'char str[STR_MAX_SIZE];'
// param char output -> this out will be used as call back
// it also has built in fgets equivalent of scanf 
void  fgetsNoNewline(char input[STR_MAX_SIZE], char output[STR_MAX_SIZE]){
    char buffer[STR_MAX_SIZE];

    strcpy(buffer, input);

	if (fgets(buffer, sizeof(buffer), stdin) == NULL) { 
		printf("Fail to read the input stream");
        strcpy(buffer, "AYAW KO NAAAA HUHUHUHUHHUHU");
	} 
	else { 
		buffer[strcspn(buffer, "\n")] = '\0'; 
	} 
    strcpy(output, buffer);
}       

/*
    param input -> string
    param output -> this will output an array of strings
    param delimiter -> character that the function use as separation 
    return the number of element in an array of char -1
    use case -> ("lastname,firstname,middlename" ) ("lastname" "firstname" "middlename") (",")   
*/
int strSplit(char input[STR_MAX_SIZE], char output[STR_MAX_SIZE][STR_MAX_SIZE], char delimiter[STR_MIN_SIZE]){

    int i = 0;

    // Returns first token
    char* token = strtok(input, delimiter);

    // Keep printing tokens while one of the
    // delimiters present in input[STR_MAX_SIZE].
    while (token != NULL) {
        strcpy(output[i], token);
        token = strtok(NULL, delimiter);
        i++;
    }

    return i;
}

// simply check if the password typed correctly 
bool isPasswordTypedCorrectly(char password[STR_MIN_SIZE], char retypedPassword[STR_MIN_SIZE]){
    return strcmp(password, retypedPassword) == 0;
}

// param strField -> this will come from the user input with data type of string or char string[STR_MAX_SIZE]
// param validatedStrField -> output of the function
// basically this will put "NULL" if the user skip or didn't input a string in a field
void inputStrValueInit(char strField[STR_MAX_SIZE], char validatedStrField[STR_MAX_SIZE]){
    char emptyStr[10];
    strcmp(emptyStr, strField) == 0 ? strcpy(strField, "NULL") : strcpy(validatedStrField, strField);
}

//-------------------------------------date functions---------------------------------------------------------------


// param MM -> month 
// param -> day
// param -> year
// return true if the date input is verified otherwise false
// verify if the date input of the user is valid
bool dateChecker(int MM, int DD, int YYYY){

    char dateStr[STR_MIN_SIZE];
    int date[3];
    
    currentDateGetterStr(dateStr);
    currentDateGetterInt(dateStr, date);
    if(!(YYYY > date[2] - 65 && YYYY < date[2] - 7)) return false; // current year - 65 to current year - 6, age should be around 7yo to 65yo
    if(DD < 1 || DD > 31) return false; // check if day is less than 1 or greater than 31 if so it will return false
    if(MM > 12 || MM < 1) return false; // check if the month exceed 12 or less than 1
    if((MM == 4 || MM == 6 || MM == 9 || MM == 11) && ( DD >= 31)) return false; // check if the input month mismatch with date e.g. 2/31 this will return false 
    if((MM == 2) && (YYYY % 4 == 0) && (DD > 29)) return false; // check if leap year and day is greater than 29
    if((MM == 2 && DD > 28) && !(YYYY % 4 == 0)) return false;

    return true;
}

// param dateInStr -> call back acts as return and output current date in string 'Fri Dec 20 12:00:00 2024'
void currentDateGetterStr(char dateInStr[STR_MIN_SIZE]){
    time_t t;   // not a primitive datatype
    time(&t);
    strcpy(dateInStr, ctime(&t));
}

// param dateInStr -> it will accepts a string 
// param date -> this is a call back and output date in int date[3] 
// => date[0] will return month in numeric form
// => date[1] will return day in numeric form
// => date[2] will return year in numeric form
void currentDateGetterInt(char dateInStr[STR_MAX_SIZE], int *date){
    
    char dateInStrBuff[STR_MAX_SIZE];
    char splitedDate[STR_MAX_SIZE][STR_MAX_SIZE ];
    char delim[STR_MIN_SIZE] = " ";

    // see line 88
    currentDateGetterStr(dateInStrBuff);
    
    // see line 41
    int len = strSplit(dateInStrBuff, splitedDate, delim);

    for (int i = 0; i < len; i++){
        // see line 120
        if(i == 1) date[0] = strMonthToInt(splitedDate[i]);
        if(i == 2) date[1] = atoi(splitedDate[i]);
        if(i == 4) date[2] = atoi(splitedDate[i]);
    }
    
}

// simply convert month to numeric value
int strMonthToInt(char month[STR_MAX_SIZE]){
    int monthInInt = 0;

    if(strcmp("Jan", month) == 0) monthInInt = 1;
    if(strcmp("Feb", month) == 0) monthInInt = 2;
    if(strcmp("March", month) == 0) monthInInt = 3;
    if(strcmp("Mar", month) == 0) monthInInt = 3;
    if(strcmp("Apr", month) == 0) monthInInt = 4;
    if(strcmp("May", month) == 0) monthInInt = 5;
    if(strcmp("Jun", month) == 0) monthInInt = 6;
    if(strcmp("Jul", month) == 0) monthInInt = 7;
    if(strcmp("Aug", month) == 0) monthInInt = 8;
    if(strcmp("Sept", month) == 0) monthInInt = 9;
    if(strcmp("Oct", month) == 0) monthInInt = 10;
    if(strcmp("Nov", month) == 0) monthInInt = 11;
    if(strcmp("Dec", month) == 0) monthInInt = 12;

    return monthInInt;
}



// param listOfString -> array of strings 
// param csvFormattedStr -> call back for outputting concatinated string array in csv form e.g. "Juan" "Dela" "Cruz" => "Juan,Dela,Cruz"
// param arrSize -> count of element in listOfString
void csvFormatter(char listOfString[STR_MIN_SIZE][STR_MIN_SIZE], char csvFormattedStr[STR_MAX_SIZE], int arrSize){
    char delim[STR_MIN_SIZE] = ",";
    for(int i = 0; i < arrSize; i++){
        strcat(csvFormattedStr, listOfString[i]);
        if(i < arrSize-1) strcat(csvFormattedStr, delim);
    }
}

int generateId(){

    FILE *file;
    char filename[] = "db/secrete_password.txt";
    if(access(filename, F_OK)!=0){
        file = fopen(filename, "w");
        fprintf(file, "%d", 240000);
        fclose(file);

        return 240000;
    }

    file = fopen(filename, "w");

}