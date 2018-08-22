#include <iostream>
#include "Controller.h"

using namespace std;

int main()
{
  //Fl::lock();
  /*thread one(receiving);
  one.join();
  */
  Controller boss;
  boss.run_the_show();
  return 0;
}

