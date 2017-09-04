/****************************************************************************
  FileName     [ p2Main.cpp ]
  PackageName  [ p2 ]
  Synopsis     [ Define main() function ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2016-present LaDs(III), GIEE, NTU, Taiwan ]
  Student      [ b05901033 Jexus Chuang ]
****************************************************************************/
#include <iostream>
#include <string>
#include "p2Table.h"
#include <cstdlib>
#include <cstdio>

using namespace std;

int main()
{
   Table table;

   // Read in the csv file. Do NOT change this part of code.
   string csvFile;
   cout << "Please enter the file name: ";
   getline(cin,csvFile);
   if (table.read(csvFile)){
      cout << "File \"" << csvFile << "\" was read in successfully." << endl;
    }
   else {
      cerr << "Failed to read in file \"" << csvFile << "\"!" << endl;
      exit(-1); // csvFile does not exist.
   }

   // TODO read and execute commands
   while (true) {
        cout << ">>> ";
        string ind;
        getline(cin,ind);
        table.command(ind);
   }
}

