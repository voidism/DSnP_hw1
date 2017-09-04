#include "fstream.h"
#include <string>
#include <iostream>

int main(){
    
    fstream file1(./rrronly.csv);
    file1 << "1,2,,3,4\r5,,6,7,8\r9,1,2,,3";
    file1.close();
}
