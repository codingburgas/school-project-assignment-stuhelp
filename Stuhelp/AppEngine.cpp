#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ofstream outfile;

	outfile.open("Begining.txt", ios_base::app);
	outfile << "Data";
}