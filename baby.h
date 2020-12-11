#include <string>

// Using the standard name space
using namespace std;

class baby{
	public:
		char store[32][32]; //Main Memory
		int accumulator[32]; //Arimetic Storage
		int CI[32]; //Current Instruction or Program Counter (Storage of the file input)[holds address] 
		int PI[32]; //Present Instruction (The fetch from store input) [Hold opcode]
		int status;
		bool negate;

		//constructor and deconstructor
		baby();
		~baby();

		//Initialisation, basic running and required converting
		void initialise();
		void cpu(int address);
		int convertBinary(char binary[]); //Convert binary to decimal
		string convertDecimal(int decimal); //Convert Decimal to binary
		int convertString(string binary);

		//Loading file
		void loadBinaryFromFile(); //normal loading

		// Fetch/Execute
		void getInstructions(); //Assembler loading
		void fetch(int address); //Fetch code and add to PI
		int decode(); //Decode the instruction code
		void execute(int decode);
		void displayAccumulator();
		void displayStore();


		int getStatus();
		bool getNegate();
		bool setNegate(bool n);

		//Commands
		void JMP(int address); //CI = S
		void JRP(int address); //CI = CI + S
		void LDN(int address); //A = -S
		void STO(int address); //S = A
		void SUB(int address); //A = A - S
		void CMP(); //if A < 0 then CI = CI + 1
		void STP(); //STOP
};

