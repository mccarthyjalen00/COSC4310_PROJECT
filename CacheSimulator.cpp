//**********************************
//COSC 4310 Computer Architecture Section 48F
//Name: Jalen McCarthy
//Date: November 17, 2022
//Instructor: Jiangjiang(Jane) Liu
//Cache Project C++ Code
//**********************************

#include <iostream>
using namespace std;

//Create Functions to complete Cache
void StartProcess();
void MainMemoryData();
void PrintTable();
void DirectMapping(int BlockNumber);
void AssociativeMapping(int BlockNumber);
void SetMapping(int BlockNumber);

//Variables needed for input
//Each Set Associativity Option is a range of 50...main memory is a range of 100
int directMapping[50],associativeMapping[50],setMapping[50],mainMemory[100],OrderOfData[50];
double timeToReadFromCache,timeToReadFromMemory,timeToCompare;
int numberOfLines,numberOfSet,numberOfLinesInSet,fetchMemory;

//Output that is displayed for each set associativity options
double TimeDirectMapping,TimeAssociativeMapping,TimeSetMapping;
double TimeForDM,TimeForAM,TimeForSM;
int hitDirectMapping,hitAssociativeMapping,hitSetMapping;
int missDirectMapping,missAssociativeMapping,missSetMapping;

//Driver Code
int main (){
    // Create Cache Memory
    cout<<"\n\nInput number of lines in Cache Memory: ";
    cin>>numberOfLines;
    cout<<"\n\nInput time to read data from Cache (in secs): " ;
    cin>>timeToReadFromCache;
    cout<<"\n\nInput time to read data from Main Memory (in secs): ";
    cin>>timeToReadFromMemory;
    cout<<"\n\nInput time to compare data in Cache (in secs): ";
    cin>>timeToCompare;
    cout<<"\n\nEnter number of Sets in Set Associative Mapping: ";
    cin>>numberOfSet;
    numberOfLinesInSet = numberOfLines / numberOfSet;

    //Call Functions to help run program
    StartProcess();
    MainMemoryData();

    //Input number of memory calls user wants to use
    cout<<"\n\nInput number of Memory calls to be made: ";
    cin>>fetchMemory;
    //Input memory read calls in order based on block number
    cout<<"\n\nInput Memory read Calls in Order by specifying Block number:\n";
    for(int i = 0; i < fetchMemory; i++) {
        cin>>OrderOfData[i];
    }
    //Loop through array and will help update each set associativity option
    for(int i = 0; i < fetchMemory; i++) {
        int number = OrderOfData[i];
        cout<<"\n\n\n\nAfter "<<number<<" --> "<<mainMemory[number]<<"\n";
        DirectMapping(number);
        AssociativeMapping(number);
        SetMapping(number);
        PrintTable();
    }
    // Display latest table after information is updated
    cout<<"\n\n\t\t\tComparison \n\n\tDirect Map   Fully Associative Map     Set Associative Map\n";
    cout<<"Time(secs)"<<TimeDirectMapping<<"\t\t\t"<<TimeAssociativeMapping<<"\t\t\t\t\t\t\t"<<TimeSetMapping<<"\n";
    cout<<"Hit\t\t  " <<hitDirectMapping <<"\t\t\t\t"<<hitAssociativeMapping<<"\t\t\t\t\t\t\t\t"<<hitSetMapping<<"\n";
    cout<<"Miss\t  "<<missDirectMapping<<"\t\t\t\t"<<missAssociativeMapping<<"\t\t\t\t\t\t\t\t"<<missSetMapping<<"\n";
    return 0;
}
//Set variables to 0
void StartProcess(){
    int i;
    TimeForDM = 0; TimeForAM = 0; TimeForSM = 0;
    hitDirectMapping =0; hitAssociativeMapping = 0; hitSetMapping = 0;
    missDirectMapping = 0; missAssociativeMapping = 0; missSetMapping = 0;
    // Loop through array
    for( i = 0; i < 50; i++){
        directMapping[i] = 0; associativeMapping[i] = 0; setMapping[i] = 0;
    }
    for( i = 0; i < 100; i++) {
        mainMemory[i] = 0;
    }
}
//Input values for main memory
void MainMemoryData(){
    int n,i;
    cout<<"\n\n\n\n\n\n\n\n\t\t\n Input memory: (Only from 0-99)\n";
    cout<<"\n\nInput in the given format { Block No. Data(in Numbers only)}\n";
    cout<<"\n\nInput number of blocks: ";
    cin>>n;
    for( i = 0; i < n; i++) {
        int val,data;
        cin>>val>>data;
        mainMemory[val] = data;
    }
    //Display main meory with block number and data
    cout<<"\n\n\n\t\t\tDisplay Main Memory";
    cout<<"\n\nBlock Number Data\n";
    for(i = 0; i < 100; i++){
        if (mainMemory[i]!=0) {
            cout<<"   "<<i<<"         "<<mainMemory[i];
            cout<<"\n";
        }
    }
}
// Display Table
void PrintTable(){
    cout<<"\n\n\t\t\tTable\n";
    cout<<"Line number     Direct      Associative        Set\n";
    for(int i = 0; i < numberOfLines; i++) {
        cout<<"   "<<i<<"\t\t\t"<<directMapping[i]<<"\t\t\t"<<associativeMapping[i]<<"\t\t\t\t\t"<<setMapping[i]<<"\n";
    }
}
// Direct Mapping Calculations
void DirectMapping(int number){
    if (directMapping[number % numberOfLines] == mainMemory[number]) {
        cout<<"Time used for Direct Mapping operation = "<<timeToReadFromCache;
        TimeDirectMapping = TimeDirectMapping + timeToReadFromCache;
        hitDirectMapping++;
    }
    else {
        directMapping[number%numberOfLines] = mainMemory[number];
        cout<<"Time used for Direct Mapping operation = "<<timeToReadFromMemory+timeToReadFromCache;
        TimeDirectMapping = TimeDirectMapping + timeToReadFromMemory + timeToReadFromCache;
        missDirectMapping++;
    }
}
// Fully Associative Mapping Calculation
void AssociativeMapping(int number){
    int i;
    for(i = 0; i < numberOfLines; i++) {
        if ( associativeMapping[i] == mainMemory[number]) {
            cout<<"\nTime used for Fully Associative Mapping operation= "<<(i+1)*timeToCompare + timeToReadFromCache;
            TimeAssociativeMapping = TimeAssociativeMapping + (i+1)*timeToCompare + timeToReadFromCache;
            hitAssociativeMapping++;
            break;
        }
    }
    if ( i == numberOfLines){
        int j;
        for( j = 0; j < numberOfLines; j++) {
            if(associativeMapping[j] == 0 ){
                associativeMapping[j] = mainMemory[number];
                break;
            }
        }
        if (j == numberOfLines){
            associativeMapping[0] = mainMemory[number];
        }
        cout<<"\nTime used for Fully Associative Mapping operation = "<<(i)*timeToCompare + timeToReadFromCache+ timeToReadFromMemory;
        TimeAssociativeMapping = TimeAssociativeMapping + (i+j)*timeToCompare + timeToReadFromCache + timeToReadFromMemory;
        missAssociativeMapping++;
    }
}
// Set Associative Mapping Calculation
void SetMapping(int number){
    int set,i;
    set = number % numberOfSet;
    for(i = set*numberOfLinesInSet; i < (set + 1)*numberOfLinesInSet; i++) {
        if( setMapping[i] == mainMemory[number]){
            cout<<"\nTime used for Set Associative Mapping(2/4 way) operation= "<< ((i-(set*numberOfLinesInSet))*timeToCompare) + timeToReadFromCache;
            TimeSetMapping = TimeSetMapping + ((i-(set*numberOfLinesInSet))*timeToCompare) + timeToReadFromCache ;
            hitSetMapping++;
            break;
        }
    }
    if (i == (set + 1)*numberOfLinesInSet){
        int j;
        for( j = set*numberOfLinesInSet; j < (set + 1)*numberOfLinesInSet; j++) {
            if(setMapping[j] == 0 ){
                setMapping[j] = mainMemory[number];
                break;
            }
        }
        if (j == (set + 1)*numberOfLinesInSet){
            setMapping[set*numberOfLinesInSet] = mainMemory[number];
        }
        cout<<"\nTime used for Set Associative(2/4 way) Mapping Operation = "<<((i-(set*numberOfLinesInSet))*timeToCompare) + timeToReadFromCache + timeToReadFromMemory;
        TimeSetMapping = TimeSetMapping + ((i + j -(set*numberOfLinesInSet))*timeToCompare) + timeToReadFromCache + timeToReadFromMemory;
        missSetMapping++;
    }
}
