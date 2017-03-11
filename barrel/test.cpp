#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char *argv[]) {
  cout << "argc: " << argc << endl;
  double is, io;
  io = 16.0;
  is = log (io)/log((double)2.0);
  cout  << "log2 16 = " << is << endl;  
  return 0;
}
