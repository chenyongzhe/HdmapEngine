#include"element/Road.h"

Road::Road(){

}
Road::~Road(){
  //delete this;
}

Road::Road(int road_id,string & predecessor_elementType,int predecessor_id, string successor_elementType,int successor_id){
	this->road_id=road_id;
	this->predecessor_elementType=predecessor_elementType;
	this->predecessor_id=predecessor_id;
	this->successor_elementType=successor_elementType;
	this->successor_id=successor_id;
	//this->road_length=road_length;
}

// double Road::parser_length_fromxML(XMLElement* lanes){
// 	XMLElement* laneSection = lanes->FirstChildElement("laneSection");
// 	if(laneSection== NULL){
//            return -2;
// 	}

// 	XMLElement* center = laneSection->FirstChildElement("center");
// 	if(center== NULL){
//            return -2;
// 	}
// 	XMLElement* lane = center->FirstChildElement("lane");
// 	if(lane== NULL){
//            return -3;
// 	}
// 	XMLElement* centerline =lane->FirstChildElement("centerLine");
// 	if(centerline== NULL){
//            return -4;
// 	}
// 	XMLElement* geometry =centerline->FirstChildElement("geometry");
// 	if(geometry== NULL){
//            return -5;
// 	}
// 	string length_str=geometry->Attribute("length");
// 	double length=atof(length_str.c_str());

// 	return length;

// } 


double Road::getRoadLength(){
	double len=0;
    for(int i=0;i<laneSections.size();i++){
        len+=laneSections[i]->length;
            
    }
    return len;

}