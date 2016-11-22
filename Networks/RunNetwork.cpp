#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include<stdlib.h>
#include<math.h>

using namespace std;
#define ITERS 100000


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

double weightUpdate(double t1, double t2, float currentWeight){
    double diff;
    diff = t2-t1;

    if (diff>0){
        return (10*exp(-diff)/0.5)/currentWeight;
    }
    else if (diff<0){
        return -(10*exp(diff)/0.5)/currentWeight;
    }
    else{return 0;}
}

int main(){

  int step = 0;
  cout<<"Enter Step -> ";
  cin>>step;
  cout<<endl;

  std::vector<Neuron> setNeuron;
  std::vector<float> Vo,V1,to,t1,m;

  fstream weightfile;
  weightfile.open("weightdist.txt", ios::out | ios::in);


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

  setNeuron[0].I = 1;
  //setNeuron[2].I = 0.25;
  //setNeuron[1].I = 0.001;

  std::vector< std::vector<float> > VectCond;

  for (int i = 0; i<numOfNodes; i++){
    std::vector<float> row;
    for (int j=0; j<numOfNodes; j++){
      row.push_back(0);
    }
    VectCond.push_back(row);
  }

  int a,b;
  float c;

  for(a,b,c; networkfile >> a >> b >> c; ){
    VectCond[a][b]=c;
  }

  std::vector< std::vector<float> > VectCondCopy = VectCond;


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

    std::vector< std::vector<int> > toCheck;

    for(int i=0; i<step; i++){
        std::vector<int> row;
        for (int j=0; j<numOfNodes; j++)
        {
          row.push_back(0);
        }
        toCheck.push_back(row);
      }

    for(int i=0; i<numOfNodes; i++){
        if (VectCond[0][i]){
          toCheck[0][i]=1;
        }
    }
    int flag=1;
    for(int stepper=1; stepper<step; stepper++){
        for (int i=0; i<numOfNodes; i++){
          for(int j=0; j<numOfNodes; j++){
            if (VectCond[i][j] && toCheck[stepper-1][i]){
              flag=1;
              for(int k=0; k<stepper; k++)
              {
                if(toCheck[k][j]){
                  flag=0;
                  break;
                }

              }
              if (flag){
                toCheck[stepper][j]=1;
              }
            }
          }
        }
      }
    cout<<endl;
    for (int i=0; i<step; i++){
      for(int j=0; j<numOfNodes; j++){
        cout<<i<<" "<<j<<" "<<toCheck[i][j]<<endl;
      }
    }





  fstream afile;
  afile.open("VxT.txt", ios::out | ios::in );

//run system
  afile << ITERS << endl;
float timer=0;

for(int j=0; j<ITERS; j++){
  //calculateSlope for all neurons
  for (int i =0; i<numOfNodes; i++){
    m[i] = setNeuron[i].calculateSlope(Vo[i]);
  }
  afile << 0 << " " << V1[0] << " " << t1[0] << endl;
  for(int i=0; i<numOfNodes; i++){

    //stepping voltage and time
    V1[i] = Vo[i] + m[i]*0.001;
    t1[i] = to[i] + 0.001;
    timer+=0.001;

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

        if (toCheck[step-1][i]){
        //cout << "Voltage = " << i << " " <<  V1[i] << " Time = " << t1[i] << endl;

        afile << i << " " << V1[i] << " " << t1[i] << endl;
      }


      //reset neuron to Ek(reset Voltage)


      Vo[i] = setNeuron[i].Ek;
      to[i] = t1[i];


    }
      //no spiking, keep going

    else{
        if (toCheck[step-1][i]){
        afile << i << " " << V1[i] << " " << t1[i] << endl;
      }

      Vo[i] = V1[i];
      to[i] = t1[i];

    }


    }
    if (!(j%5)){
    for(int pre=0; pre<numOfNodes; pre++){
      for(int post=0; post<numOfNodes; post++){
        if(VectCond[pre][post]>0){
        for(int precount=0, postcount=0; precount<SpikeTimes[pre][post][0].size() && postcount<SpikeTimes[pre][post][1].size(); precount++, postcount++){
          //cout<<SpikeTimes[pre][post][1][postcount]<< " "<< SpikeTimes[pre][post][0][precount]<<endl;
          // if (weightUpdate(SpikeTimes[pre][post][1][postcount], SpikeTimes[pre][post][0][precount], VectCond[pre][post])){
          //     cout<<pre << " "<< post << " "<< weightUpdate(SpikeTimes[pre][post][1][postcount], SpikeTimes[pre][post][0][precount], VectCond[pre][post])<< endl;
          //   }


          VectCond[pre][post]+=weightUpdate(SpikeTimes[pre][post][0][precount], SpikeTimes[pre][post][1][postcount], VectCond[pre][post]);

          SpikeTimes[pre][post][1].erase(SpikeTimes[pre][post][1].begin());
          SpikeTimes[pre][post][0].erase(SpikeTimes[pre][post][0].begin());

          //cout<<VectCond[pre][post]<<endl;
          if (VectCond[pre][post]<=0){
            VectCond[pre][post]=0;
          }
          if(VectCond[pre][post]>100){
            VectCond[pre][post]=100;
          }
        }
      }
    }
  }
}

for(int k=0; k<numOfNodes; k++){
  if (toCheck[step-1][k]){
    if (step==1 && VectCondCopy[0][k]){
      weightfile << 0 << " " <<  k << " " << VectCond[0][k]<<" "<< timer<< endl;
      continue;
    }
    for (int l=0; l<numOfNodes; l++){

      if(VectCondCopy[l][k] && toCheck[step-2][l]){
        weightfile << l << " " <<  k << " " << VectCond[l][k]<<" "<< timer <<endl;
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

//  networkfile << numOfNodes << endl;
cout << endl;
cout << endl;
  for(int i =0; i<numOfNodes; i++){
    for (int j=0; j<numOfNodes; j++){
      cout<< i << " " << j << " " << VectCond[i][j] << endl;
//      networkfile << i << " " << " " << VectCond[i][j]<< endl;
    }
  }

  weightfile.close();
  networkfile.close();
  afile.close();

  return 0;
}
