#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
int main(int argc, char const *argv[]) {

  /* code */
  srand(time(NULL));
  for (int i =0; i<10; i++)
  {
    cout<< rand()%10 << endl;


  }

}
