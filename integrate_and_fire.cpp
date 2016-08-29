#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
std::vector<std::vector<float> > VectCond(3, std::vector<float>(3,0));
float voltages[3] = {0.3,0.3,0.3};
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
      float calculateSlope(float V, int neuronNum){
          float slope,constant;
          constant = (this->I + (this->gleak*this->Eleak))/this->C;
          for (int i=0; i<3; i++){
            constant += (VectCond[neuronNum][i]*voltages[i])/this->C;

          }
          slope = constant;
          for (int i=0; i<3; i++){
            slope -= (VectCond[neuronNum][i]/this->C)*V;
          }
          return slope;
      }



};

int main()
{
  std::vector<Neuron> setNeuron;

  setNeuron.push_back(Neuron(0.1,0.3,0.2,0.3,0.6,0.1,1));
  setNeuron.push_back(Neuron(0.1,0,0.2,0.3,0.6,0.1,1));
  setNeuron.push_back(Neuron(0.1,0,0.2,0.3,0.6,0.1,1));

  VectCond[0][2]=0;
	VectCond[1][0]=10;
	VectCond[2][1]=10;

  /*for (int i=0; i<3; i++){
    for (int j=0; j<3; i++)
    {
      cout << VectCond[i][j];
    }
    cout << endl;
  }*/


  float Vo[3],to[3],m[3],V1[3],t1[3];
  Vo[0] = setNeuron[0].Eleak;
  Vo[1] = setNeuron[1].Eleak;
  Vo[2] = setNeuron[2].Eleak;

  to[0] = 0;
  to[1] = 0;
  to[2] = 0;
  fstream afile;
  afile.open("VxT.txt", ios::out | ios::in );
  for(int j =0; j<=200; j++){
    m[0] = setNeuron[0].calculateSlope(Vo[0],0);
    m[1] = setNeuron[1].calculateSlope(Vo[1],1);
    m[2] = setNeuron[2].calculateSlope(Vo[2],2);
    for(int i=0; i<3; i++){
    V1[i] = Vo[i] + m[i]*0.005;
    t1[i] = to[i] + 0.005;

    if (V1[i]>=setNeuron[i].Ethresh){
      V1[i] = setNeuron[i].Espike;
      cout << "Voltage = " << i << " "<< V1[i] << " Time = " << t1[i] << endl;
      afile << V1[i] << " " << t1[i] << endl;
      Vo[i] = setNeuron[i].Ek;
      to[i] = t1[i];
      voltages[i]=Vo[i];

    }
    else{
    cout << "Voltage = " << i << " " <<  V1[i] << " Time = " << t1[i] << endl;
    afile << V1[i] << " " << t1[i] << endl;
    Vo[i] = V1[i];
    to[i] = t1[i];
    voltages[i]=Vo[i];
    }
    }
  }



  return 0;
}
