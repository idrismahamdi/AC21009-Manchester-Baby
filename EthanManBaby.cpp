class baby{

	public:
		string store[32][32]; //Main Memory
		int accumulator[32]; //Arimetic Storage
		int CI[32]; //Current Instruction or Program Counter (Storage of the file input)[holds address] 
		int PI[32]; //Present Instruction (The fetch from store input) [Hold opcode]


	//constructor and deconstructor
	baby();
	~baby();

	//Initialisation, basic running and required converting
	void initialise();
	void cpu();
	int convertBinary(); //Convert binary to decimal
	string convertDecimal(); //Convert Decimal to binary

	//Loading file
	void loadBinaryFromFile(); //normal loading

	// Fetch/Execute
	void getInstructions(); //Assembler loading
	void fetch(); //Fetch code and add to PI
	void decode(); //Decode the instruction code
	void execute();

	//Commands
	void JMP(); //CI = S
	void JRP(); //CI = CI + S
	void LDN(); //A = -S
	void STO();	//S = A
	void SUB();	//A = A - S
	void CMP(); //if A < 0 then CI = CI + 1
	void STP(); //STOP
}

void main(){
	baby manBaby;

	manBaby.initialise();

	int status = 0;
	int address = 0;

	do{
		manBaby.cpu(address);
	}while(state !=0);
}

void baby::initialise(){
	for(int x = 0; x < 32; x++){
		for(int y = 0; y < 32; y++){
			store[y][x] = '0'
		}
		accumulator[x] = 0;
		CI[x] = 0;
		PI[x] = 0;
	}
}

void baby::cpu(int address){
	int decode = 0;

	//fetches binary from specified line
	fetch(address);
	//decode the binary opcode and store in PI
	decode = decode(address);
	//Execute opcode on address, executed code will store within the CI
	execute(decode, address);
}

void baby::getInstructions(){
	string Line;
	File file;
	file.open ("BabyTest1-MC.txt");

	int lineNumber = 0;

	if(Line[0] == ' '){
		cout << "Nothing in file" << endl
	}else{
		cout << "File found" << endl
	}

	do{
		cout << " " << Line;
		for(int i = 0; i <=32; i++){
			char character = Line.at(i);
			if(character == '0'){
				store[lineNumber][i] = character;
			}else{
				store[lineNumber][i] = character;
			}
		}
		lineNumber++;
		getline (file, Line);
	}while(lineNumber < 32);

	file.close();
}

void baby::fetch(int address){
	for(int i = 0; i<32; i++){
		PI[i] = store[address][i];
	}
}

void baby::decode(){

}

void baby::execute(decode, address){

	address=0;
	int array[5]={1,2,4,8,16};
	for(int index=0; index<5; index++)
	{
		address=address+PresentInstruction[index]*array[index];
	}

	switch(decode){
		case 0:
		{
			JMP(address);
		}
		case 1:
		{
			JRP(address);
		}
		case 2:
		{
			LDN(address);
		}
		case 3:
		{
			STO(address);
		}
		case 4:
		{
			SUB(address);
		}
		case 5:
		{
			SUB(address);
		}
		case 6:
		{
			CMP();
		}
		case 7:
		{
			STP();
		}

	}
}

void baby::SUB(){
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
			cout << Store[address][index];
		}


		//Accumulator minus store
		int accValue = convertBinary(accumulator);
		int storeValue = convertBinary(store[address]);

		accValue = accValue - storeValue;
		string accum = convertDecimal(accValue);

		//Add rewrite value back to accumulator
		for(int i = 0; i < 32; i++){
			accumulator[i] = stoi(accum[i]);
		}
}

void baby::CMP(){
	int AccValue = -1;

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








	if(AccValue<0)
	{

		int CI =0;
		for(int index = 0; index < 8; index++)
		{
			CI = CI + (Accumulator[index] * AccIndex[index]);
		}
		// If CI is less than zero skip the next step
		if(CI <0)
		{

			// Increment the CI by i
			int array[5]={1,2,4,8,16};
			for(int index = 0; index < 5; index++)
			{
				CI=CI+(ControlInstruction[index]*array[index]);
			}
			CI++;
			string binaryConverted = convertDecimal(CI);

			for(int index = 0; index < 5; index++)
			{
				ControlInstruction[index] = binaryConverted.at(index);
			}
		}
		else
		{
			cout <<" ACC VAL = " << CI << endl;
		}
	}
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


void Baby::JMP(int decode)
{

    
    for (int i=0; i<32; i++)
    {
        
        CI[i] += std::stoi(store[decode][i]);
    }

}


void Baby::JRP(int decode)
{
    int hold = 0;
    
    for (int i=0; i<31; i++)
        {
            if ((CI[31 - i] == '0') && (store[decode][31-i] == '0')
            {
                if (hold == 0){
                    CI[31 - i] = 0;
                }else
                {
                    hold--;
                    CI[31 - i] = 1;
                }
                    
               
            }
          
            else if ((!(CI[31 - i] == 1)) != (!(store[decode][31-i]) == 1))
            {
               CI[31 - i] = '1';
            } else
            {
                hold += 1;
            }
            
            
            
        }
    
}
