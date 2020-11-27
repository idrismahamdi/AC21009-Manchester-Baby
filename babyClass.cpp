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
	int convertBinary();
	string convertDecimal();

	//Loading file
	void loadBinaryFromFile(); //normal loading

	// Fetch/Execute
	void getInstructions(); //Assembler loading
	void fetch();
	void decode();
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
