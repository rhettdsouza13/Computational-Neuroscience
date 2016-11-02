#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include<stdlib.h>

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
          slope = (this->I + (this->gleak*(V - this->Eleak)))/this->C;

          return slope;
      }

};


int main(){

  std::vector<float> Vo,V1,to,t1,m;

  fstream networkfile;
  networkfile.open("network.txt",  ios::out | ios::in);

  int numOfNodes;

  networkfile >> numOfNodes;
  cout<<numOfNodes<<endl;

  for (int i=0; i<numOfNodes; i++){

    Vo.push_back(0);
    V1.push_back(0);
    to.push_back(0);
    t1.push_back(0);
    m.push_back(0);

  }

  std::vector< std::vector<float> > VectCond;

  for (int i = 0; i<numOfNodes; i++){
    std::vector<float> row;
    for (int j=0; j<numOfNodes; j++){
      row.push_back(0);
    }
    VectCond.push_back(row);
  }

  for(int a,b,c; networkfile >> a >> b >> c; ){
    VectCond[a][b]=c;
  }

  for (int i = 0; i<numOfNodes; i++){
    for (int j=0; j<numOfNodes; j++){
      cout<<i<<" "<<j<<" "<<VectCond[i][j]<<endl;
    }
  }


  return 0;
}
