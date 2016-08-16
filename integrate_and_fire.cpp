#include<iostream>
using namespace std;

class Neuron{

  public:
      float C,I,gleak,Eleak,Ethresh,Ek,Espike;

      Neuron(float C, float I, float gleak, float Eleak, float Ethresh, float Ek, float Espike){
        this->C = C;
        this->I = I;
        this->gleak = gleak;
        this->Eleak = Eleak;
        this->Ethresh = Ethresh;
        this->Ek = Ek;
        this->Espike = Espike;
      }

      float runNeuron(){



        return Espike;
      }

};

int main()
{
  Neuron singleNeuron(0.1,0.1,0.1,0.1,0.2,0.3,0.4);

  cout << singleNeuron.runNeuron();

  return 0;
}
