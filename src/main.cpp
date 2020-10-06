#include <iostream>
#include <fstream>
#include "terminal.h"
using namespace std;

//read from input.txt, write to output.txt
int main(int argc, char *argv[])
{
    //注意在bash下路徑不要用倒斜線，記得前綴'/mnt/d/User/NTUT_workspace/posd/109598091_hw'
    // const string prefix = "/mnt/d/User/NTUT_workspace/posd/109598091_hw/";
    // const string prefix = "../";
    // ifstream ifile(prefix + argv[1]);
    // ofstream ofile(prefix + argv[2]);
    ifstream ifile(argv[1]);
    ofstream ofile(argv[2]);
    string txt;
    string in = " ";
    string result;
    while (getline(ifile, txt))
    {
        in = in +" "+ txt;
        // ofile << txt << endl;
    }
    in = in + " " + argv[3] + " " + argv[4];
    Terminal t(in);
    ofile<< t.showResult()<<endl;
    
    ifile.close();
    ofile.close();
    return 0;
}