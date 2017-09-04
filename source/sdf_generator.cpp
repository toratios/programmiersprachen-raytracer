#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
  
	const int imagecount = 181;

	for (int i = 1; i <= imagecount; i = i +30){

		ofstream fOut("scene" + to_string(i) + ".txt");		

		fOut


      //Camera
      << "define camera eye 110" << endl
      
      << "transform camera rotate "<<(15+(float)i)/2<<" 0 1 0" << endl
      << "transform camera translate 0 0 -1200" << endl
      

      //Lights
      << "define light ambient 0.1 0.1 0.1" << endl
      << "define light light_1 0.0 2000.0 0.0 1.0 1.0 1.0" << endl
      //<< "define light light_2 -1200.0 1300.0 500.0 1.0 1.0 1.0" << endl
      

      //Materials
      << "define material black 0.5 0.5 0.5 0.0 0.0 0.0 0.03 0.03 0.03 0.0 1.0 1.0" << endl
      << "define material white 0.5 0.5 0.5 0.5 0.5 0.5 0.5 0.5 0.5 0.0 1.0 1.0" << endl
      << "define material blue 0.1 0.8 0.7 0.1 0.8 0.7 0.1 0.8 0.7 200.0 1.0 1.0" << endl
      << "define material yellow 0.8 0.7 0.1 0.8 0.7 0.1 0.8 0.7 0.1 200.0 1.0 1.0" << endl
      << "define material red 1.0 0.0 0.0 1.0 0.0 0.0 1.0 0.0 0.0 1000.0 1.0 1.0" << endl
      << "define material purple 0.7 0.1 8.0 0.7 0.1 1.0 0.7 0.1 1.0 500 1.0 1.0" << endl

      //Floor
      << "define shape box floor_1_1 -750.0 -360.0 750.0 -500.0 -359.0 500.0 white" << endl
      << "define shape box floor_1_2 -500.0 -360.0 750.0 -250.0 -359.0 500.0 black" << endl
      << "define shape box floor_1_3 -250.0 -360.0 750.0 0.0 -359.0 500.0 white" << endl
      << "define shape box floor_1_4 0.0 -360.0 750.0 250.0 -359.0 500.0 black" << endl
      << "define shape box floor_1_5 250.0 -360.0 750.0 500.0 -359.0 500.0 white" << endl
      << "define shape box floor_1_6 500.0 -360.0 750.0 750.0 -359.0 500.0 black" << endl

      << "define shape composite floor_row_1 floor_1_1 floor_1_2 floor_1_3 floor_1_4 floor_1_5 floor_1_6" << endl


      << "define shape box floor_2_1 -750.0 -360.0 500.0 -500.0 -359.0 250.0 black" << endl
      << "define shape box floor_2_2 -500.0 -360.0 500.0 -250.0 -359.0 250.0 white" << endl
      << "define shape box floor_2_3 -250.0 -360.0 500.0 0.0 -359.0 250.0 black" << endl
      << "define shape box floor_2_4 0.0 -360.0 500.0 250.0 -359.0 250.0 white" << endl
      << "define shape box floor_2_5 250.0 -360.0 500.0 500.0 -359.0 250.0 black" << endl
      << "define shape box floor_2_6 500.0 -360.0 500.0 750.0 -359.0 250.0 white" << endl

      << "define shape composite floor_row_2 floor_2_1 floor_2_2 floor_2_3 floor_2_4 floor_2_5 floor_2_6" << endl


      << "define shape box floor_3_1 -750.0 -360.0 250.0 -500.0 -359.0 0.0 white" << endl
      << "define shape box floor_3_2 -500.0 -360.0 250.0 -250.0 -359.0 0.0 black" << endl
      << "define shape box floor_3_3 -250.0 -360.0 250.0 0.0 -359.0 0.0 white" << endl
      << "define shape box floor_3_4 0.0 -360.0 250.0 250.0 -359.0 0.0 black" << endl
      << "define shape box floor_3_5 250.0 -360.0 250.0 500.0 -359.0 0.0 white" << endl
      << "define shape box floor_3_6 500.0 -360.0 250.0 750.0 -359.0 0.0 black" << endl

      << "define shape composite floor_row_3 floor_3_1 floor_3_2 floor_3_3 floor_3_4 floor_3_5 floor_3_6" << endl


      << "define shape box floor_4_1 -750.0 -360.0 0.0 -500.0 -359.0 -250.0 black" << endl
      << "define shape box floor_4_2 -500.0 -360.0 0.0 -250.0 -359.0 -250.0 white" << endl
      << "define shape box floor_4_3 -250.0 -360.0 0.0 0.0 -359.0 -250.0 black" << endl
      << "define shape box floor_4_4 0.0 -360.0 0.0 250.0 -359.0 -250.0 white" << endl
      << "define shape box floor_4_5 250.0 -360.0 0.0 500.0 -359.0 -250.0 black" << endl
      << "define shape box floor_4_6 500.0 -360.0 0.0 750.0 -359.0 -250.0 white" << endl

      << "define shape composite floor_row_4 floor_4_1 floor_4_2 floor_4_3 floor_4_4 floor_4_5 floor_4_6" << endl


      << "define shape box floor_5_1 -750.0 -360.0 -250.0 -500.0 -359.0 -500.0 white" << endl
      << "define shape box floor_5_2 -500.0 -360.0 -250.0 -250.0 -359.0 -500.0 black" << endl
      << "define shape box floor_5_3 -250.0 -360.0 -250.0 0.0 -359.0 -500.0 white" << endl
      << "define shape box floor_5_4 0.0 -360.0 -250.0 250.0 -359.0 -500.0 black" << endl
      << "define shape box floor_5_5 250.0 -360.0 -250.0 500.0 -359.0 -500.0 white" << endl
      << "define shape box floor_5_6 500.0 -360.0 -250.0 750.0 -359.0 -500.0 black" << endl

      << "define shape composite floor_row_5 floor_5_1 floor_5_2 floor_5_3 floor_5_4 floor_5_5 floor_5_6" << endl


      << "define shape box floor_6_1 -750.0 -360.0 -500.0 -500.0 -359.0 -750.0 black" << endl
      << "define shape box floor_6_2 -500.0 -360.0 -500.0 -250.0 -359.0 -750.0 white" << endl
      << "define shape box floor_6_3 -250.0 -360.0 -500.0 0.0 -359.0 -750.0 black" << endl
      << "define shape box floor_6_4 0.0 -360.0 -500.0 250.0 -359.0 -750.0 white" << endl
      << "define shape box floor_6_5 250.0 -360.0 -500.0 500.0 -359.0 -750.0 black" << endl
      << "define shape box floor_6_6 500.0 -360.0 -500.0 750.0 -359.0 -750.0 white" << endl

      << "define shape composite floor_row_6 floor_6_1 floor_6_2 floor_6_3 floor_6_4 floor_6_5 floor_6_6" << endl

      << "define shape composite floor floor_row_1 floor_row_2 floor_row_3 floor_row_4 floor_row_5 floor_row_6" << endl

      //Objects
      << "define shape sphere red_sphere 450.0 -50.0 -450.0 200.0 red" << endl

      << "define shape sphere blue_sphere 300.0 -100.0 -0.0 150.0 blue" << endl

      << "define shape sphere purple_sphere 50.0 -200.0 -400.0 100.0 purple" << endl



      << "define shape composite objects red_sphere blue_sphere purple_sphere" << endl


      << "define shape composite everything floor objects" << endl;

		
		fOut.close();

	}

	return 0;
}