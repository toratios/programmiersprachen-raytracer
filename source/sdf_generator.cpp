#include <string>
#include <fstream>
#include <iostream>
//#include <sys/stat.h>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
  
	const int imagecount = 180;

	for (int i = 1; i <= imagecount; ++i){

		ofstream fOut("scene" + to_string(i) + ".txt");		

		fOut
			<< "define material mat1 0.0 0.0 1.0 0.0 0.0 1.0 0.0 0.0 1.0 10 1 1" << endl
      << "define material mat2 1.0 0.5 0.0 1.0 0.5 0.0 1.0 0.5 0.0 300 1 1" << endl
      << "define camera testcam 100" << endl
      << "define light ambient 0.8 0.8 0.8" << endl
      << "define light testlight 2000 750 -700 0.5 0.8 0.9" << endl
      << "define light testlight2 0.0 0.0 100.0 1.0 1.0 1.0" << endl
      << "define shape box testbox1 10 10 10 -10 -10 -10 mat1" << endl
      << "define shape sphere testsphere2 100 0.0 -100 30 mat2" << endl
      << "define shape composite testcomp1 testbox1 testsphere2" << endl
      << "transform camera translate 0 0 -100" << endl
      << "transform camera rotate "<<((float)i)/2<<" 0 1 0" << endl;
      
		
		fOut.close();

	}

	return 0;
}