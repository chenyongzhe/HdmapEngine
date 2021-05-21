#include"HdmapEngine.h"




HdmapEngine::HdmapEngine(){
	
}
HdmapEngine::~HdmapEngine(){
	
}


void HdmapEngine::printRoad(){
	for (int i = 0; i < roadList.size(); ++i)
	{
		cout<<"road_id "<<roadList[i].road_id<<" "<<"predecessor_elementType "<<roadList[i].predecessor_elementType<<" "<<"predecessor_id " <<roadList[i].predecessor_id<<" "<<"road_length"<<roadList[i].road_length<<endl;
	}
}


bool HdmapEngine::paserLaneSection(XMLElement* section){



}


bool HdmapEngine::paserLane(XMLElement* lane){


	
}

bool HdmapEngine::paserJunction(XMLElement* junction){


}

bool HdmapEngine::paserRoad(XMLElement* road){
	
}


bool HdmapEngine::paserApolloxml(const char* file_name){

    tinyxml2::XMLDocument doc;
    if(doc.LoadFile(file_name)!= XML_SUCCESS) return false;
    
	XMLElement* root = doc.RootElement();
	XMLElement* roadNode = root->FirstChildElement("road");
	
	while (roadNode != NULL)
	{        
	    int road_id;
	   string predecessor_elementType;
	  int predecessor_id=INT_MAX;
	  int successor_id=INT_MAX;
	  string successor_elementType;

	   double road_length;
		//XMLElement* cpyNode = roadNode;
		string name = roadNode->Attribute("name");
		if (name.substr(0, 4) == "Road")
		{
			//cout << roadNode->Attribute("id") << endl;
			//string road_id_str=;
			road_id=atoi(roadNode->Attribute("id"));

			XMLElement* linkNode = roadNode->FirstChildElement();
			XMLElement* lanes=roadNode->FirstChildElement("lanes");
			XMLElement* sucNode = linkNode->FirstChildElement();

			if (sucNode != NULL)
			{
				//cout << sucNode->Attribute("elementType") << " " << sucNode->Attribute("elementId") << endl;
				string successor_elementType=sucNode->Attribute("elementType");	
                successor_id=atoi(sucNode->Attribute("elementId"));


					}
			XMLElement* preNode = sucNode->NextSiblingElement();
			if (preNode != NULL)
			{
				//cout << preNode->Attribute("elementType") << " " << preNode->Attribute("elementId") << endl;
				predecessor_elementType=preNode->Attribute("elementType");
	            predecessor_id=atoi(preNode->Attribute("elementId"));
			}

          Road road(road_id,predecessor_elementType,predecessor_id,successor_elementType,successor_id,Road::parser_length_fromxML(lanes));

          roadList.push_back(road);

		}
        
		roadNode = roadNode->NextSiblingElement();
		
	}
    cout<<"road size"<<roadList.size()<<endl;
		printRoad();

	return true;

}