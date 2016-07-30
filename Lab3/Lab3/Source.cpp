#include <fstream>
#include <iostream>
#include <vector>
#include "StudentRecord.h"
#include "Grade.h"
#include <iomanip>

using namespace std;
bool ReadStudentRecord(StudentRecord* studentRecord, int& numberOfRecord);
bool readDelimiter(string input, std::vector<string>& output, char delimiter);
void PrintGrade(StudentRecord* studentRecord, int numberOfRecords);

int main()
{
	int numberOfRecords;
	StudentRecord studentRecord[1024];

	//Read StudentRecords
	ReadStudentRecord(studentRecord, numberOfRecords);

	//Print out read result
	cout << "There are " << numberOfRecords << " student records." << endl;


	//Calculation
	PrintGrade(studentRecord, numberOfRecords);

	cin.get();
}

void PrintGrade(StudentRecord* studentRecord, int numberOfRecords)
{
	for (int i = 0; i < numberOfRecords; i++)
	{
		double QuizTotal, QuizFinal, MidtermFinal, FinalFinal, FinalScaled, FinalGrade;
		char LetterGrade;
	
		QuizTotal = studentRecord[i].quiz1 + studentRecord[i].quiz2;
		QuizFinal = QuizTotal / 20;
		MidtermFinal = studentRecord[i].midterm*.01;
		FinalFinal = studentRecord[i].finalexam*.01;
		FinalScaled = FinalFinal * 2;
		FinalGrade = ((FinalScaled + MidtermFinal + QuizFinal) / 4)*100;
		if (FinalGrade >= 90)
			LetterGrade = 'A';
		else if (FinalGrade <= 90 && FinalGrade >= 80)
			LetterGrade = 'B';
		else if (FinalGrade <= 80 && FinalGrade >= 70)
			LetterGrade = 'C';
		else if (FinalGrade <= 70 && FinalGrade > 60)
			LetterGrade = 'D';
		else if (FinalGrade <= 60)
			LetterGrade = 'F';
		cout << endl 
			<< studentRecord[i].name <<"'s final grade is " <<  FinalGrade<< " or a " << LetterGrade << ". " << endl;
		
		
	}
	
}


///////////////////////////////////////////////////
//Function: Read Student Record from a file
//Return: bool
//		  true - success read student records
//		  false - faile to read student records
///////////////////////////////////////////////////
bool ReadStudentRecord(StudentRecord* studentRecord, int& numberOfRecords)
{
	using namespace std;
	ifstream is;
	const string INPUTFILENAME = "studentrecords.txt";
	try {
		is.open(INPUTFILENAME);

		numberOfRecords = 0;

		string readline;
		while (!is.eof())
		{
			is >> readline;
			cout << readline << endl;

			char delimiter = ',';
			std::vector<string> output;
			readDelimiter(readline, output, delimiter);

			int index = 0;
			std::vector<string>::iterator recordIterator;
			for (recordIterator = output.begin(); recordIterator != output.end(); recordIterator++)
			{
				switch (index)
				{
				case NAME:
					studentRecord[numberOfRecords].name = *recordIterator;
					break;
				case QUIZ1:
					studentRecord[numberOfRecords].quiz1 = std::stoi(*recordIterator);
					break;
				case QUIZ2:
					studentRecord[numberOfRecords].quiz2 = std::stoi(*recordIterator);
					break;
				case MIDTERM:
					studentRecord[numberOfRecords].midterm = std::stoi(*recordIterator);
					break;
				case FINALEXAM:
					studentRecord[numberOfRecords].finalexam = std::stoi(*recordIterator);
					break;
				}
				index++;
			}
			numberOfRecords++;
		}

		is.close();
	}
	catch (ifstream::failure e)
	{
		cout << "Exception Open/Read/Close file";
		return false;
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////
//Function: readDelimiter, read delimiter string into a vector<string>
//parameter: 
//string input - input string
//std::vector<string>& output - return vector<string>
//char delimiter -- delimiter
//return: bool
//		true -- if there is delimiter in the string
//		false - if there is no string
/////////////////////////////////////////////////////////////////////////
bool readDelimiter(string input, std::vector<string>& output, char delimiter)
{
	string acc = "";
	
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == delimiter)
		{
			output.push_back(acc);
			acc = "";
		}
		else
		{
			acc += input[i];
		}
	}
	if (acc.size() != 0)
		output.push_back(acc);
	else
	{
		if( input.size() == 0 )
			return false;
	}
	return true;
}