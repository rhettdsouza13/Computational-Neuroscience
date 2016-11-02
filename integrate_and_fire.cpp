#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include<stdlib.h>


using namespace std;

const int N = 20;
float VectCond[N][N];
float voltages[N];

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
          for (int i=0; i<N; i++){
            constant += (VectCond[neuronNum][i]*voltages[i])/this->C;

          }
          slope = constant;
          for (int i=0; i<N; i++){
            slope -= (VectCond[neuronNum][i]/this->C)*V;
          }
          return slope;
      }



};

int main()
{

  fstream network;
  network.open("net.txt", ios::out | ios::in );
  network << N << endl;

  std::vector<Neuron> setNeuron;

  int toCheck[3];
  toCheck[0]=0;
  toCheck[1]=1;
  toCheck[2]=5;

  float Vo[N],to[N],m[N],V1[N],t1[N];

  for (int i = 0; i<N; i++){
    setNeuron.push_back(Neuron(0.1,0,0.2,0.3,0.6,0.1,1));
    Vo[i] = setNeuron[i].Eleak;
    to[i] = 0;
    voltages[i]=setNeuron[i].Eleak;
  }


  setNeuron[0].I = 0.5;


  for (int i=0; i<N; i++){
    for (int j=0; j<N; j++){
      VectCond[i][j]=0;
    }
  }
  srand(time(NULL));
  for (int i=0; i<N; i++){
    for (int j=i+1; j<N; j++){
      if (rand()%10>5){
        VectCond[i][j]=10;
        VectCond[j][i]=10;
        network << i << " " << j << endl;
        }
    }
  }
//  VectCond[19][0] = 100;

  /*for (int i=1; i<N; i++){

    VectCond[i][j]==1000;
  }*/

    fstream afile;
    afile.open("VxT.txt", ios::out | ios::in );

//run system

  for(int j=0; j<10000; j++){
    //calculateSlope for all neurons
    for (int i =0; i<N; i++){
      m[i] = setNeuron[i].calculateSlope(Vo[i],i);
    }

    for(int i=0; i<N; i++){

      //stepping voltage and time
      V1[i] = Vo[i] + m[i]*0.0001;
      t1[i] = to[i] + 0.0001;

      //checking for threshold voltage

      if (V1[i]>=setNeuron[i].Ethresh){
        V1[i] = setNeuron[i].Espike;

        for (int k = 0; k<N; k++){
          if (VectCond[k][i]){
            Vo[k]+=0.07;
            //voltages[k]+=1;
          }
        }


        //printing ONLY for the chosen neuronal numbers
        if (i==toCheck[0] || i==toCheck[1] || i==toCheck[2]){
          //cout << "Voltage = " << i << " "<< V1[i] << " Time = " << t1[i] << endl;
          afile << V1[i] << " " << t1[i] << endl;
        }

        //reset neuron to Ek(reset Voltage)


        Vo[i] = setNeuron[i].Ek;
        to[i] = t1[i];
        voltages[i]=Vo[i];

      }
        //no spiking, keep going

      else{
          if (i==toCheck[0] || i==toCheck[1] || i==toCheck[2]){
          //cout << "Voltage = " << i << " " <<  V1[i] << " Time = " << t1[i] << endl;
          afile << V1[i] << " " << t1[i] << endl;
        }
        Vo[i] = V1[i];
        to[i] = t1[i];
        voltages[i]=Vo[i];
      }
      }
  }



  return 0;
}
