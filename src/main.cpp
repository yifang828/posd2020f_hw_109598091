#include <iostream>
#include <fstream>
using namespace std;

//read from input.txt, write to output.txt
int main(int argc, char *argv[])
{
    //注意在bash下路徑不要用倒斜線，記得前綴'/mnt/d/User/NTUT_workspace/posd/109598091_hw'
    const string prefix = "/mnt/d/User/NTUT_workspace/posd/109598091_hw/";
    ifstream ifile(prefix + argv[1]);
    ofstream ofile(prefix + argv[2]);

    string txt;
    while (getline(ifile, txt))
    {
        ofile << txt << endl;
    }
    ifile.close();
    ofile.close();
    return 0;
}