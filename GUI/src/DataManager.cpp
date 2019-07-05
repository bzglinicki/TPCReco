#include<cstdlib>
#include <iostream>

#include "TCanvas.h"

#include "GeometryTPC.h"
#include "EventTPC.h"

#include "DataManager.h"
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
DataManager::DataManager() {

  myTree = 0;
  nEvents = 0;
  currentEvent = 0;
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
DataManager::~DataManager() {

}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
void DataManager::loadGeometry(const std::string & fileName){
  
  myGeometryPtr = std::make_shared<GeometryTPC>(fileName.c_str());
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
void DataManager::loadDataFile(const std::string & fileName){

  std::string treeName = "TPCData";
  
  myFile = std::make_shared<TFile>(fileName.c_str(),"READ");
  if(!myFile){
    std::cerr<<"File: "<<fileName<<"not found!"<<std::endl;
    return;
  }
  
  myTree = (TTree*)myFile->Get(treeName.c_str());
  myTree->SetBranchAddress("Event", &currentEvent);
  nEvents = myTree->GetEntries();
  loadEvent(0);

  std::cout<<"File: "<<fileName<<" loaded."<<std::endl;
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
void DataManager::loadEvent(unsigned int iEvent){

  if(!myTree){
    std::cerr<<"ROOT tree not available!"<<std::endl;
    return;
  }
  currentEvent->SetGeoPtr(0);
  myTree->GetEntry(iEvent);
  currentEvent->SetGeoPtr(myGeometryPtr);
  myCurrentEntry = iEvent;
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
EventTPC* DataManager::getCurrentEvent() const{

  return currentEvent;
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
EventTPC* DataManager::getNextEvent(){

  if(myCurrentEntry<nEvents){
    loadEvent(++myCurrentEntry);
  }

  return currentEvent;
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
EventTPC* DataManager::getPreviousEvent(){

  if(myCurrentEntry>0){
    loadEvent(--myCurrentEntry);
  }

  return currentEvent;
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
std::shared_ptr<GeometryTPC> DataManager::getGeometry() const{

  return myGeometryPtr;
  
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
unsigned int DataManager::numberOfEvents() const{

  return nEvents;
  
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
unsigned int DataManager::currentEventNumber() const{

  if(currentEvent){
    return currentEvent->GetEventId();
  }
  
  return 0;
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
