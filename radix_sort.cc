#include <fstream>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <string>

using namespace std;

queue<string> oddBuckets[10]; //buckets used to hash on odd radix
queue<string> evenBuckets[10]; //buckets used to hash on even radix

bool hashToBucket(string& num, int radix) {
  bool returnVal = true;
  int pos = num.length() - radix - 1;
  int bucketIndex;
  if(pos < 0) { 
    bucketIndex = 0;
  } else { 
    if(!isdigit(num[pos])) {
	cerr << "Error: An non-numeric entry was in the file." << endl;
	exit(1);
      }
    bucketIndex = num[pos] - '0';  
    returnVal = false;
  }
  (radix % 2 == 0)? evenBuckets[bucketIndex].push(num) : oddBuckets[bucketIndex].push(num);
  return returnVal;
}

bool rehash(int radix) {
  bool finished = true;
  queue<string> *filledBuckets = (radix % 2 == 0)? oddBuckets : evenBuckets;
  for(int i = 0; i < 10; i++) {
    while(!filledBuckets[i].empty()) {
      if(!hashToBucket(filledBuckets[i].front(), radix)) finished = false;
      filledBuckets[i].pop();
    }
  }
  return finished;
}

void printResults(int radix) {
  queue<string> *filledBuckets = (radix % 2 == 0)? evenBuckets : oddBuckets;
  for(int i = 0; i < 10; i++) {
    while(!filledBuckets[i].empty()) {
      cout << filledBuckets[i].front() << endl;
      filledBuckets[i].pop();
    }
  }
}

int main(int argc, char *argv[]) {
  if(argc < 2) {
    cerr << "Usage: ./radix_sort <input_file>" << endl;
    return 1;
  }
  ifstream fs(argv[1]);
  int radix = 0;
  while(true) {
    string line;
    getline(fs, line);
    if(fs.fail()) break;
    hashToBucket(line, radix);
  }

  while(true) {
    radix++;
    if(rehash(radix)) break;
  }
  
  printResults(radix);
  return 0;
}
