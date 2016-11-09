#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include<stdlib.h>
#include<math.h>

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
          slope = (this->I - (this->gleak*(V - this->Eleak)))/this->C;

          return slope;
      }



};

double weightUpdate(double t1, double t2){
    double diff;
    diff = t2-t1;

    if (diff>0){
        return exp(-diff/0.1);
    }
    else if (diff<0){
        return -(exp(diff/0.1));
    }
    else{return 0;}
}

int main(){
  int toCheck[3];
  toCheck[0]=0;
  toCheck[1]=1;
  toCheck[2]=2;

  std::vector<Neuron> setNeuron;

  std::vector<float> Vo,V1,to,t1,m;



  fstream networkfile;
  networkfile.open("network.txt",  ios::out | ios::in);

  int numOfNodes;


  networkfile >> numOfNodes;
  cout<<numOfNodes<<endl;

  for (int i=0; i<numOfNodes; i++){
    V1.push_back(0);
    to.push_back(0);
    t1.push_back(0);
    m.push_back(0);
    setNeuron.push_back(Neuron(0.1,0,0.2,0.3,0.6,0.1,1));
    Vo.push_back(setNeuron[i].Eleak);
  }

  setNeuron[0].I = 0.5;
  //setNeuron[1].I = 0.001;

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

  std::vector< std::vector< std::vector<std::vector<float> > > > SpikeTimes;

    for (int i = 0; i<numOfNodes; i++){
      std::vector< std::vector<std::vector<float> > > row;
      for (int j=0; j<numOfNodes; j++){
        std::vector<float> pre;
        std::vector<float> post;
        std::vector<std::vector<float> > mid;

        mid.push_back(pre);
        mid.push_back(post);

        row.push_back(mid);
      }
      SpikeTimes.push_back(row);
    }

  fstream afile;
  afile.open("VxT.txt", ios::out | ios::in );

//run system

for(int j=0; j<10000; j++){
  //calculateSlope for all neurons
  for (int i =0; i<numOfNodes; i++){
    m[i] = setNeuron[i].calculateSlope(Vo[i]);
  }

  for(int i=0; i<numOfNodes; i++){

    //stepping voltage and time
    V1[i] = Vo[i] + m[i]*0.0001;
    t1[i] = to[i] + 0.0001;

    //checking for threshold voltage

    if (V1[i]>=setNeuron[i].Ethresh){
      V1[i] = setNeuron[i].Espike;

      for (int k = 0; k<numOfNodes; k++){
        if(VectCond[i][k]){
          SpikeTimes[i][k][0].push_back(t1[i]);
        }
        if(VectCond[k][i]){
          SpikeTimes[k][i][1].push_back(t1[i]);
        }

      }

      for (int k=0; k<numOfNodes; k++){
          Vo[k]+=(0.01*VectCond[i][k]);
      }


      //printing ONLY for the chosen neuronal numbers
      if (i==toCheck[0] || i==toCheck[1] || i==toCheck[2]){
        //cout << "Voltage = " << i << " "<< V1[i] << " Time = " << t1[i] << endl;
        afile << V1[i] << " " << t1[i] << endl;
      }

      //reset neuron to Ek(reset Voltage)


      Vo[i] = setNeuron[i].Ek;
      to[i] = t1[i];


    }
      //no spiking, keep going

    else{
        if (i==toCheck[0] || i==toCheck[1] || i==toCheck[2]){
        //cout << "Voltage = " << i << " " <<  V1[i] << " Time = " << t1[i] << endl;
        afile << V1[i] << " " << t1[i] << endl;
      }
      Vo[i] = V1[i];
      to[i] = t1[i];

    }


    }
    for(int pre=0; pre<numOfNodes; pre++){
      for(int post=0; post<numOfNodes; post++){
        if(VectCond[pre][post]>0){
        for(int precount=0, postcount=0; precount<SpikeTimes[pre][post][0].size() && postcount<SpikeTimes[pre][post][1].size(); precount++, postcount++){
          //cout<<SpikeTimes[pre][post][1][postcount]<< " "<< SpikeTimes[pre][post][0][precount]<<endl;
          cout<<weightUpdate(SpikeTimes[pre][post][1][postcount], SpikeTimes[pre][post][0][precount])<<endl;
          VectCond[pre][post]+=weightUpdate(SpikeTimes[pre][post][1][postcount], SpikeTimes[pre][post][0][precount]);
          //cout<<VectCond[pre][post]<<endl;
          if (VectCond[pre][post]<=0){
            VectCond[pre][post]=0;
          }
        }
      }
    }
  }

}
  // for(int i=0; i<numOfNodes; i++){
  //   for(int j=0; j<numOfNodes; j++){
  //     for (int k =0; k<SpikeTimes[i][j][0].size(); k++){
  //     cout<<i<< " " << j << " " << SpikeTimes[i][j][0][k] << endl;}
  //     for (int k =0; k<SpikeTimes[i][j][1].size(); k++){
  //     cout<<i<< " " << j << " " << SpikeTimes[i][j][1][k] << endl;}
  //   }
  // }
  // fstream outNet;
  // outNet.open("newNetwork.txt", ios::out | ios::in);

  for(int i =0; i<numOfNodes; i++){
    for (int j=0; j<numOfNodes; j++){
      cout<< i << " " << j << " " << VectCond[i][j] << endl;
    }
  }


  return 0;
}
