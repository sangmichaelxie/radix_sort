#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
  if(argc < 3) {
    cerr << "Usage: generate_numfile <output_file> <num_numbers>" << endl;
    exit(1);
  }

  ofstream fs(argv[1]);
  int num_numbers = atoi(argv[2]);
  for(int i = 0; i < num_numbers; i++) {
    fs << rand() << endl;
  }
  return 0;
}
