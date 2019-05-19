// Program Name: Lab 1
//
// Description:  
//  This assignment was to decode a binary file. 
//	The decoding was first to read the binary file, then to convert it to bits, and then to morse code. 
//	From the morse code a message can be further decoded. 
//
// What's on your mind about this lab?
//  The problem I had with this lab was dealing with the data itself and how to manipulate it.
//  It was hard to manage and think of solutions to read the bitset in 2 bits.
//  It was also tough trying to follow my Class Diagram since I wanted to try to emulate
//  what I was learning in Java, but I am starting to experience myself 
//  the differences between C++ and Java. I really enjoyed working on this lab.
//
// Author: Jason Yoon
//
// Date: 10/18/2018
//
// IDE Used: Visual Microsoft
//

#include <iostream>
#include <fstream> 
#include <string>
#include <bitset>
#include <vector>
using namespace std;


class MorseToLetters {
private:
	vector<pair<string, string>> Binary{
	{ "00", "/" },
	{ "01", "-" },
	{ "10","." },
	{ "11","/ /" },
	};

	vector<pair<string, string>> BinaryToWords{
	{ "/","" },{ " "," " },{ ".-", "A" },{ "-...", "B" },{ "-.-.", "C" },
	{ "-..","D" },{ ".", "E" },{ "..-.","F" },{ "--.","G" },{ "....","H" },
	{ "..","I" },{ ".---","J" },{ "-.-","K" },{ ".-..","L" },{ "--","M" },
	{ "-.","N" },{ "---","O" },{ ".--.","P" },{ "--.-","Q" },{ ".-.","R" },
	{ "...","S" },{ "-","T" },{ "..-","U" },{ "...-","V" },{ ".--","W" },
	{ "-..-","X" },{ "-.--","Y" },{ "--..","Z" },{ ".-.-","Ä" },{ "---.","Ö" },
	{ "..--","Ü" },{ "----","Ch" },{ "-----","0" },{ ".----","1" },{ "..---","2" },
	{ "...--", "3" },{ "....-", "4" },{ ".....","5" },{ "-....","6" },{ "--...","7" },
	{ "---..","8" },{ "----.","9" },{ ".-.-.-","." },{ "--..--","," },{ "..--..","?" },
	{ "..--.","!" },{ "---...",":" },{ ".-..-.","\"" },{ ".----.","\'" },{ "-...-","=" }
	};
public:
	MorseToLetters() {};
	vector<string> convertToMorse(vector<string> toBeConverted, int size);
	vector<string> FinalConverstion(vector<string> toBeConverted);
};

vector<string> MorseToLetters::convertToMorse(vector<string> toBeConverted, int size) {
	vector<string> conversionComplete;
	bool found = false;

	for (int index = 0; index < size; index++) {
		for (int vectorIndex = 0; vectorIndex < Binary.size() && found == false; vectorIndex++) {
			if (toBeConverted[index] == Binary[vectorIndex].first) {
				conversionComplete.push_back(Binary[vectorIndex].second);
				found = true;
			}

		}
		found = false;
	}

	return conversionComplete;

}


vector<string> MorseToLetters::FinalConverstion(vector<string> toBeConverted) {
	vector<string> conversionComplete;
	string container;
	string delimiter = "/";
	bool found = false;

	for (size_t i = 0; i != toBeConverted.size(); ++i)
		container = container + toBeConverted[i];

	size_t pos = 0;
	string token;
	while ((pos = container.find(delimiter)) != string::npos) {
		token = container.substr(0, pos);
		for (int vectorIndex = 0; vectorIndex < BinaryToWords.size() && found == false; vectorIndex++) {
			if (token == BinaryToWords[vectorIndex].first) {
				conversionComplete.push_back(BinaryToWords[vectorIndex].second);
				found = true;
			}
		}
		container.erase(0, pos + delimiter.length());
		found = false;
	}

	return conversionComplete;
}



class FileIO {
private:
	unsigned char* memblock;
	vector<string> convertedFile;
	int size;
public:
	FileIO() {};
	unsigned char* readFile(string FILE_NAME);
	vector<string> fileTwoBits(unsigned char* memblock);
	void setSize(int size) { this->size = size; }
	int getSize() { return size; }

};

unsigned char* FileIO::readFile(string FILE_NAME) { // reads the file
	streampos size = -1;
	ifstream file(FILE_NAME, ios::in | ios::binary);
	if (file.is_open()) {
		file.seekg(0, ios::end);
		size = file.tellg();
		memblock = new unsigned char[size];
		file.seekg(0, ios::beg);
		file.read((char*)memblock, size);
		setSize(size);
	}
	else {
		cerr << "Unable to open file:  " << FILE_NAME << endl;
	}
	file.close();

	return memblock;

}

vector<string> FileIO::fileTwoBits(unsigned char* memblock) {

	vector<string> convertedFile;
	string twoBitHolder;
	string holder;
	bitset<8> eightBitHolder;

	for (int index = 0; index < getSize(); index++) {
		bitset<8> eightBitHolder = memblock[index];
		holder = eightBitHolder.to_string();
		for (int splitBits = 0; splitBits < 4; splitBits++) {
			twoBitHolder = holder.substr(0, 2);
			convertedFile.push_back(twoBitHolder);
			holder.erase(0, 2);
		}
	}


	return convertedFile;
}




int main() {

	FileIO fileObj;
	MorseToLetters morseConversionObj;
	vector<string> morseData;
	vector<string> fileData;
	vector<string> finalConvertedData;
	unsigned char* memblock;
	

	memblock = fileObj.readFile("Morse.bin");
	fileData = fileObj.fileTwoBits(memblock);

	morseData = morseConversionObj.convertToMorse(fileData, fileObj.getSize());
	
	cout << "Printing out Morse Code of Binary File:" << endl;
	for (auto printMorse : morseData)
		cout << printMorse;


	finalConvertedData = morseConversionObj.FinalConverstion(morseData);

	cout << endl << endl << "Printing out decoded message:\n";
	for (auto printMsg : finalConvertedData)
		cout << printMsg;



	morseData.clear();
	fileData.clear();
	finalConvertedData.clear();


	cin.get();
	return 0;
}



