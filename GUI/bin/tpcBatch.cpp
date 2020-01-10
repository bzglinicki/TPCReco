#include <iostream>

#include "DataManager.h"
#include "SigClusterTPC.h"
#include "TrackBuilder.h"

int main(){

  DataManager aDataManager;
  TrackBuilder aTkBuilder;
  EventTPC *aEvent = 0;
  
  //TEST ---
  std::string dataFileName = "/home/akalinow/scratch/ELITPC/data/neutrons/EventTPC_2018-06-19T15:13:33.941.root"; 
  std::string geometryFileName = "/home/akalinow/scratch/ELITPC/data/neutrons/geometry_mini_eTPC_2018-06-19T15:13:33.941.dat"; 

  aDataManager.loadGeometry(geometryFileName);  
  aDataManager.loadDataFile(dataFileName);
  aDataManager.loadTreeEntry(3);

  aEvent = aDataManager.getCurrentEvent();
  if(!aEvent) {
    std::cout<<__FUNCTION__<<" NULL EventTPC pointer"<<std::endl;
    return -1;
  }

  aTkBuilder.setEvent(aEvent);
  aTkBuilder.reconstruct();
  
  return 0;
}
