#include <iostream>
#include <sstream>

using namespace std;

class baby{

	public:
		string store[32][32]; //Main Memory
		int accumulator[32]; //Arimetic Storage
		int CI[32]; //Current Instruction or Program Counter (Storage of the file input)
		int PI[32]; //Present Instruction (The fetch from store input)


	//constructor and deconstructor
	baby();
	~baby();

	//Initialisation, basic running and required converting
	void initialise();
	void cpu();
	int convertBinary(); //Convert binary to decimal
	string convertDecimal(); //Convert Decimal to binary
	int convertString(); //Convert String Binary to Int Binary Value

	//Loading file
	void loadBinaryFromFile(); //normal loading

	// Fetch/Execute
	void getInstructions(); //Assembler loading
	void fetch(); //Fetch code and add to PI
	void decode(); //Decode the instruction code
	void execute();

	//Commands
	void JMP();
	void JRP();
	void LDN();
	void STO();
	void SUB();
	void CMP();
	void STP();
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

int baby::convertString(String binary){
	
	//reads binary into stringstream
    stringstream convert(binary); 

	//initialise binaryInt
    int binaryInt = 0; 
	//read stringstream into binaryInt
    convert >> binaryInt; 
  
    return binaryInt; 

}

int ManchesterBaby::decode(int address)
{

	int decode = 0;
	int decodeValue[3] = {1,2,4};

	for(int index = 0; index <3; index++)
	{
		decode = decode + PI[index+13]*decodeValue[index];
	}

	/* decode = integer value assigned to an instruction
	*  returns 		Instruction
	*	0				JMP
	*	1				JRP
	*	2				LDN
	*	3				STO
	*	4				SUB
	*	5				SUB
	*	6				CMP
	*	7				STP
	*
	*/

	return decode;
}
