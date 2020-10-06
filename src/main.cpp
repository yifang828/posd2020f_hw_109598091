#include <iostream>
#include <fstream>
#include "terminal.h"
using namespace std;

//read from input.txt, write to output.txt
int main(int argc, char *argv[])
{
    //注意在bash下路徑不要用倒斜線
    ifstream ifile(argv[1]);
    ofstream ofile(argv[2]);
    string txt;
    string in = " ";
    string result;
    while (getline(ifile, txt))
    {
        in = in +" "+ txt;
    }
    in = in + " " + argv[3] + " " + argv[4];
    Terminal t(in);
    ofile<< t.showResult()<<endl;
    
    ifile.close();
    ofile.close();
    return 0;
}