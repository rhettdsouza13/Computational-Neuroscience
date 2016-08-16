#include<iostream>
#include<fstream>
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
      float calculateSlope(float V){
          float slope;
          slope = ((this->I + (this->gleak*this->Eleak))/this->gleak)-V;
          return slope;
      }
      float runNeuron(){

        float Vo,to,m,V1,t1;
        Vo = Eleak;
        to = 0;
        fstream afile;
        afile.open("VxT.txt", ios::out | ios::in );
        for(int i =0; i<=200; i++){
          m = calculateSlope(Vo);

          V1 = Vo + m*0.01;
          t1 = to + 0.01;

          if (V1>=this->Ethresh){
            V1 = this->Espike;
            cout << "Voltage = " << V1 << " Time = " << t1 << endl;
            afile << V1 << " " << t1 << endl;
            Vo = this->Ek;
            to = t1;

            continue;
          }
          cout << "Voltage = " << V1 << " Time = " << t1 << endl;
          afile << V1 << " " << t1 << endl;
          Vo = V1;
          to = t1;

        }

      }

};

int main()
{
  Neuron singleNeuron(0.1,0.3,0.1,0.3,0.5,0.1,1);

  singleNeuron.runNeuron();

  return 0;
}
