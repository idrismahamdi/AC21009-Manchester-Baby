// including c++ libaries
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <math.h>
#include "baby.h"

// Using the standard name space
using namespace std;

baby::baby()
{
	for(int x = 0; x < 32; x++){
		for(int y = 0; y < 32; y++){
			store[y][x] = '0';
		}
		accumulator[x] = 0;
		CI[x] = 0;
		PI[x] = 0;
	}
	status = 0;
	negate = false;
}

baby::~baby()
{

}

int main(){
	baby manBaby;

	manBaby.initialise();

	int address = 0;

	manBaby.getInstructions();

	do{
		if(manBaby.negate==false)
		{
			address++;
		}
		else if ( manBaby.negate==true)
		{
			address++;
			address++;
			manBaby.negate = false;
		}
		cout << address << endl;
		manBaby.cpu(address);
	}while(manBaby.status != -1);
	return 0;
}

void baby::initialise(){
	for(int x = 0; x < 32; x++){
		for(int y = 0; y < 32; y++){
			store[y][x] = '0';
		}
		accumulator[x] = 0;
		CI[x] = 0;
		PI[x] = 0;
	}
	status = 0;
	negate = false;
}

void baby::displayStore()
{
	cout << "\n\n" << "STORE" << endl;
	cout << "      Operand      " << "   Memory Bits            " << " Opcode " << "NULL " << endl;
	cout << "    |-------------|" << " |---------------------|" << " |------|" << " |---------------------------------------------|" <<  endl;
	cout << "     1  2  4  8 16  1  2  4  8 16 32 64 128 1  2  4  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16  " << endl;

	for(int i = 0; i < 32; ++i)
	{
		if((i)<10)
			cout << " " << (i) << "  ";
		else
			cout << " " << (i) << " ";

		for(int j = 0; j < 32; ++j)
		{	

			if(store[i][j] == '0'){
				cout << " . ";
			}
			else if(store[i][j] == '1'){
				cout << " | ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void baby::displayAccumulator()
{
	cout << "\n\n" << "ACCUMULATOR" << endl;
	cout << "      Operand      " << "   Memory Bits           " << " Opcode " << "  NULL " << endl;
	cout << "    |-------------|" << " |---------------------|" << " |------|" << " |---------------------------------------------|" <<  endl;
	cout << "     1  2  4  8 16  1  2  4  8 16 32 64 128 1  2  4  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16  " << endl;
	cout << "    ";
	for(int i = 0; i < 32; ++i)
	{
			if(accumulator[i] == 0)
				cout << " . ";
			else if(accumulator[i] == 1)
				cout << " | ";
	}
	cout << endl;

}

void baby::getInstructions(){
	string Line;
	ifstream file;
	file.open("BabyTest1-MC.txt");

	int lineNumber = 0;

	if(Line[0] == ' '){
		cout << "Nothing in file" << endl;
	}else{
		cout << "File found" << endl;
	}

	do{
		getline (file, Line);
		for(int i = 0; i <=32; i++){
			char character = Line[i];
			if(character == '0'){
				store[lineNumber][i] = character;
			}else if(character == '1'){
				store[lineNumber][i] = character;
			}
		}
		lineNumber++;
	}while(!file.eof());

	file.close();
}

void baby::cpu(int address){
	int decodeVal = 0;
	//fetches binary from specified line
	fetch(address);
	//decode the binary opcode and store in PI
	decodeVal = decode();
	//Execute opcode on address, executed code will store within the CI
	execute(decodeVal);
	displayAccumulator();
	displayStore();

	for(int i=0; i <32; i++)
	{
		if(store[address][i] == '1'){
			CI[i] = 1;
		}else{
			CI[i] = 0;
		}
		
	}
	cin.get();
}


void baby::fetch(int address){
	for(int i = 0; i<32; i++){
		if(store[address][i] == '1'){
			PI[i] = 1;
		}else{
			PI[i] = 0;
		}
		
		cout << PI[i];
	}
	cout << endl;
}

int baby::decode()
{
	int decode = 0;
	int decodeValue[3] = {1,2,4};

	for(int index = 0; index <3; index++)
	{
		decode += PI[index+13]*decodeValue[index];
	}

	return decode;
	
}

void baby::execute(int decode){
	int address = 0;
	int array[5]={1,2,4,8,16};
	for(int index = 0; index <5; index++)
	{
		address += PI[index]*array[index];
	}



	cout << address << endl;
	cout << decode << endl;
	switch(decode){
		case 0:
			cout<< "JMP" << endl;
			JMP(address);
			break;
		case 1:
			cout<< "JRP" << endl;
			JRP(address);
			break;
		case 2:
			cout<< "LDN" << endl;
			LDN(address);
			break;
		case 3:
			cout<< "STO" << endl;
			STO(address);
			break;
		case 4:
			cout<< "SUB" << endl;
			SUB(address);
			break;
		case 5:
			cout<< "SUB" << endl;
			SUB(address);
			break;
		case 6:
			cout<< "CMP" << endl;
			CMP();
			break;
		case 7:
			cout<< "STP" << endl;
			STP();
			break;

	}
}


int baby::convertBinary(char binary[32])
{
	int len = strlen(binary);
  	int total, counter = 0;   

  	for(int i=len-1;i>=0;i--){
   	 
   	 	if ((int)binary[i]==49)
   	 	{
      		total = total + (1*pow(2,counter));
     	}
     	
        counter++;
     	

 
 	 }

 	 return total;



}

string baby::convertDecimal(int decimal)
{
	int power=128;
	string binary = "";
	int counter =0;

	do
	{
		if(decimal<power)
		{
			binary = binary+"0";
		}
		else
		{
			binary = binary+"1";
			decimal -= power;
		}

		power /= 2;
		counter++;
	}while(counter!=8);

	return binary;
}

int baby::convertString(string binary){
	
	//reads binary into stringstream
    stringstream convert(binary); 

	//initialise binaryInt
    int binaryInt = 0; 
	//read stringstream into binaryInt
    convert >> binaryInt; 
  
    return binaryInt; 

}

void baby::JMP(int address)
{
    for (int i=0; i<32; i++)
    {
        if(store[address][i] == '1'){
			CI[i] = 1;
		}else{
			CI[i] = 0;
		}
    }
}


void baby::JRP(int address)
{
    int hold = 0;
    
    for (int i=0; i<31; i++){
        if ((CI[31 - i] == '0') && (store[address][31-i] == '0')){
                if (hold == 0){
                    CI[31 - i] = 0;
                }else
                {
                    hold--;
                    CI[31 - i] = 1;
                }
                    
               
            }
          
            else if ((CI[31 - i] == 1) != (store[address][31-i] == 1))
            {
               CI[31 - i] = '1';
            } else
            {
                hold += 1;
            }
   }         
}            

void baby::LDN(int address)
{
 	cout << address << endl;
 	
    for(int i = 0; i<32; i++){
		if(store[address][i] == '1'){
			accumulator[i] = 1;
		}else if(store[address][i]=='0'){
			accumulator[i] = 0;
		}
		
	}

    for(int i = 0; i < 32; i++)
    {
 
        if(store[address][i]=='0')
        {
            accumulator[i]=1;
        }
 
        if(store[address][i]=='1')
        {
            accumulator[i]=0;
        }
 
    }
 
    int add =1;
    int carry=0;
 
    for(int i = 0; i <32; i++)
    {
 
        if (accumulator[i]==0 && add==0)
        {
            accumulator[i]=0;
        }
        else if(accumulator[i]==1 && add==0)
        {
            accumulator[i]=1;
        }
        else if(accumulator[i]==0 && add==1)
        {
            accumulator[i]=1;
            add=0;
        }
        else if (accumulator[i]==1 && add==1)
        {
            accumulator[i]=0;
            carry=1;
        }
        
        
        if (accumulator[i]==0 && carry==1  && add==1 )
        {
            accumulator[i]=1;
            carry=0;
        }
        else if (accumulator[i]==1&& carry==1 && add==0 )
        {
            accumulator[i]=1;
            carry=0;
        }
        else if (accumulator[i]==1 && carry==1 && add==1)
        {
            accumulator[i]=1;
            carry=1;
        }
        
 
    }
 
    
}
 
void baby::SUB(int address){
	// Subtract the content of the specified line from the accumulator

		cout << " Memory Address    = " << address << endl;

		cout << " Accumulator Negated     = ";
		for(int index = 0; index < 32; index++)
		{
				//Accumulator[index]=Store[address][index];
				cout << accumulator[index];
				// adding 1
		}

		cout << "\n Subtract Memory         = ";

		for(int index = 0; index < 32; index++)
		{
			//Store[StoreLine][index]=Accumulator[index];
			cout << store[address][index];
		}


		//Accumulator minus store
		int carryone=0;
					for(int index = 0; index <32; index++)
					{
						// 0 + 1
						if(accumulator[index]==0 && store[address][index]=='1')
						{
							accumulator[index]=1;
						}
						if(accumulator[index]==1 && store[address][index]=='0')
						{
							accumulator[index]=1;
						}
						if(accumulator[index]==0 && store[address][index]=='0')
						{
							accumulator[index]=0;
						}
						if (accumulator[index]==0 && store[address][index]=='0')
						{
							accumulator[index]=0;
						}
						if(accumulator[index]==0 && store[address][index]=='1')
						{
							accumulator[index]=1;
						}
						if(accumulator[index]==1 && store[address][index]=='0')
						{
							accumulator[index]=1;
						}
						if (accumulator[index]==1 && store[address][index]=='1' )
						{
											accumulator[index]=0;
						}

						if (accumulator[index]==1 && store[address][index]=='1' && carryone==1)
						{
							accumulator[index]=1;
						}
						if (accumulator[index]==1 && store[address][index]=='0' && carryone==1)
						{
							accumulator[index]=1;
						}
						if (accumulator[index]==0 && store[address][index]=='1' && carryone==1)
						{
							accumulator[index]=1;
						}
						if (accumulator[index]==0 && store[address][index]=='0' && carryone==1)
						{
							accumulator[index]=1;
						}
					}
}

void baby::CMP(){
	int AccValue = -1;
	int control[32];
	for(int i = 0; i <32; i++){
		control[i] = CI[i];
	}

	int AccIndex[8]={1,2,4,8,16,32,64,128};
	for(int index =5; index < 12; index++)
	{
		AccValue = AccValue + (accumulator[index] * AccIndex[index]);
	}

	int AccIndex2[16]={256,512,1024,2048,4096,8192,16382,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608};
	for(int index =16; index < 31; index++)
	{
		AccValue = AccValue + (accumulator[index] * AccIndex2[index]);
	}

	if(accumulator[31]==1)
	{
		cout << " Negative - Perform flip flop" << endl;
		negate=true;
	}

	if(AccValue<0)
	{
		int ControlI =0;
		for(int index = 0; index < 8; index++)
		{
			ControlI = ControlI + (accumulator[index] * AccIndex[index]);
		}
		// If CI is less than zero skip the next step
		if(ControlI <0)
		{

			// Increment the CI by i
			int array[5]={1,2,4,8,16};
			for(int index = 0; index < 5; index++)
			{
				ControlI=ControlI+(control[index]*array[index]);
			}
			ControlI++;
			string binaryConverted = convertDecimal(ControlI);

			for(int index = 0; index < 5; index++)
			{
				CI[index] = binaryConverted.at(index);
			}

		}
		else
		{
			cout <<" ACC VAL = " << ControlI << endl;
		}
	}
}


void baby::STO(int address)
{
    for(int i = 0; i < 32; i++)
    {
    	if(accumulator[i] == 1){
    		store[address][i] = '1';
    	}else{

    		store[address][i] = '0';
    	}
    }
    
}

void baby::STP(){
	status = -1;
}
