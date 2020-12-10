
class baby{

	public:
		string store[32][32]; //Main Memory
		int accumulator[32]; //Arimetic Storage	


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

void baby::getInstructions(){
	string Line;
	string input;
	string names[10][10];
	int values[10];
	int location[10];
	int index = 0;
	int nameI = 0;
	int valueI = 0;

	bool var = false;
	int lineNum = 0;
	bool end = false;

	ifstream file("BabyTest1-Assembler.txt");
	getline(file, Line);


	do{
		do{
			if(end == false){
				char character = Line.at(index);
				if(character != " " || character != ":" || character != ";"){
					input += character;
				}
				if(character == ";"){
					break;
				}
				if(input.compare("END") == 0){
					end = true;
				}


				if(character == ":" && end == false){
					names[nameI] = input;
					nameI++;
					input="";
				}
				if(input.compare("VAR") == 0){
					var = true;
					input = "";
				}
				if(var == true){
					values[valueI] = atoi(input);
					var = false;
					location[valueI] = lineNum;
					input = "";
					valueI++;
				}

				if(input.compare("LDN") == 0){
					store[lineNum][13] = "0";
					store[lineNum][14] = "1";
					store[lineNum][15] = "0";
					input = "";
				}else if(input.compare("STO") == 0){
					store[lineNum][13] = "1";
					store[lineNum][14] = "1";
					store[lineNum][15] = "0";
					input = "";
				}else if(input.compare("SUB") == 0){
					store[lineNum][13] = "0";
					store[lineNum][14] = "0";
					store[lineNum][15] = "1";
					input = "";
				}else if(input.compare("CMP") == 0){
					store[lineNum][13] = "0";
					store[lineNum][14] = "1";
					store[lineNum][15] = "1";
					input = "";
				}else if(input.compare("STP") == 0){
					store[lineNum][13] = "1";
					store[lineNum][14] = "1";
					store[lineNum][15] = "1";				
					input = "";
				}
			}else{
				if(character == ":" && end == false){
					names[nameI] = input;
					nameI++;
					input="";
				}
				if(input.compare("VAR") == 0){
					var = true;
					input = "";
				}
				if(var == true){
					values[valueI] = atoi(input);
					var = false;
					input = "";
					valueI++;
				}
				
			}

			index++;
		}while(Line.at(index) != ";")
		lineNum++;
		getline(file, Line);
	}while(Line.size() != 0);


	file.clear();
	file.seekg(0);
	valueI = 0;
	nameI = 0;
	line = 0;

	do{
		do{
				
			if(character != " " || character != ":" || character != ";"){
					input += character;
			}

			if(character == ";"){
				break;
			}
			if(input.compare(names[nameI] == 0)){
				string binary = convertBinary(location[nameI]);
				for(int i = 4; i >= 0; i--){
					store[line][i] = binary[i];
				}
			}
			index++;
		}while(Line.at(index) != ";")
		lineNum++;
		getline(file, Line);
	}while(Line.size() != 0);

	file.close();
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


