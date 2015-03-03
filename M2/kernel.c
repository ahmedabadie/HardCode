void readString(char*);
void printString(char*);
void printCharacter(char*);

// interrupt(I_NUM, AX, BX, CX, DX)
// AX = AH*256+AL

int main() {
	char line[80];
  // printString("Hello World"); //TASK 1
  printString("Enter a line: "); // TASK 2
  readString(line); // TASK 2
  printString("Echo: "); // TASK 2
  printString(line); // TASK 2
  while(1){}
}

// New line does not start from the beginning in readString

void readString(char* string) {
	char enter = 0xd;
	char backspace = 0x8;
	char linefeed = 0xa;
	char end = 0x0;

	char letter = interrupt(0x16, 0, 0, 0, 0);

	int i = 0;
	while(letter != enter){
		if (letter == backspace){
			if (i > 0) {
				printCharacter(backspace);
				printCharacter(end);
				printCharacter(backspace);
				i--;
			}
		} else {
			string[i] = letter;
			printCharacter(string[i]);
			i++;
		}
		letter = interrupt(0x16, 0, 0, 0, 0);
	}
	string[i] = linefeed;
	string[i+1] = end;
	printCharacter(linefeed);
}

void printCharacter(char character){
	interrupt(0x10, 0xE*256+character, 0, 0, 0);
}

void printString(char* string) {
	int i = 0;
  while(string[i] != '\0'){
    interrupt(0x10, 0xE*256+string[i], 0, 0, 0);
    i++;
  }
}