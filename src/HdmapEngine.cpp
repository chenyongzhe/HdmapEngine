#include"HdmapEngine.h"


int road_id;
int laneSection_id=0;

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


bool HdmapEngine::paserLaneSection(XMLElement* sectionNode,Road& road){
  //cout<<"解析Lanesection"<<endl;
  LaneSection section;

  XMLElement* center = sectionNode->FirstChildElement("center");
	if(center== NULL){
           return false;
	}
	XMLElement* lane = center->FirstChildElement("lane");
	if(lane== NULL){
           return false;
	}
	XMLElement* centerline =lane->FirstChildElement("centerLine");
	if(centerline== NULL){
           return  false;
	}
	XMLElement* geometry =centerline->FirstChildElement("geometry");
	if(geometry== NULL){
           return false;
	}
	string length_str=geometry->Attribute("length");
	double length=atof(length_str.c_str());	
	section.length=length;
	section.laneSection_id=laneSection_id;
	//解析Lane
    if(sectionNode!=NULL){
       //left
        XMLElement* leftNode=sectionNode->FirstChildElement("left");
        if(leftNode!=NULL){
        	XMLElement* laneNode=leftNode->FirstChildElement("lane");
            while(laneNode!=NULL){
           
                 paserLane(laneNode,section);
                
                 laneNode = laneNode->NextSiblingElement("lane");

            }

        }

       //center
       XMLElement* centerNode=sectionNode->FirstChildElement("center");
       if(centerNode!=NULL){
           XMLElement* laneNode=centerNode->FirstChildElement("lane");
            while(laneNode!=NULL){
                 paserLane(laneNode,section);  
                 laneNode = laneNode->NextSiblingElement("lane");
            }
        }

       //right
       XMLElement* rightNode=sectionNode->FirstChildElement("right");
       if(rightNode!=NULL){
           XMLElement* laneNode=rightNode->FirstChildElement("lane");
            while(laneNode!=NULL){
                 paserLane(laneNode,section);  
                 laneNode = laneNode->NextSiblingElement("lane");
            }
        }


    }
	//加入到road

	road.laneSections.push_back(section);
	lansectionList.push_back(section);
    
  
}


bool HdmapEngine::paserLane(XMLElement* laneNode,LaneSection& laneSection){
   //cout<<"解析Lane"<<endl;
   Lane lane;
   string uid=laneNode->Attribute("uid");
   lane.uid=uid;
   lane.turn_type=laneNode->Attribute("turnType");
   lane.type=laneNode->Attribute("type");
   lane.road_id=road_id;
   if(laneNode->Attribute("direction")!=NULL){
   	lane.direction=laneNode->Attribute("direction");
   }else{
   	lane.direction="unknow";
   }

   //车道长度
   
   XMLElement* centerLineNode=laneNode->FirstChildElement("centerLine");
   if(centerLineNode!=NULL){
     XMLElement* geometryNode=centerLineNode->FirstChildElement("geometry");
     if(geometryNode!=NULL)
       lane.lane_length=atof(geometryNode->Attribute("length"));
     //cout<<"车道长度"<<lane.lane_length<<endl;

   }

   //车道限速
   XMLElement* speedNode=laneNode->FirstChildElement("speed");
   if(speedNode!=NULL){
   	 lane.speed_limit=atof(speedNode->Attribute("max"));
   }
   //cout<<"车道限速 "<<lane.speed_limit<<endl;


   //获取前驱后继
   XMLElement* linkNode=laneNode->FirstChildElement("link");
   if(linkNode!=NULL){
     XMLElement* subNode=linkNode->FirstChildElement();
     //cout<<subNode->Name()<<endl;
     while(subNode!=NULL){
        //cout<<subNode->Name()<<endl;
        string subName=subNode->Name();
        if(subName=="predecessor"){
        //前驱
          string id=subNode->Attribute("id");	
          lane.predecessors.push_back(id);

        }else if(subName=="successor"){
        //后继
          string id=subNode->Attribute("id");	
          lane.successors.push_back(id);

        }else if(subName=="neighbor"){
         //邻近车道

           
           string side=subNode->Attribute("side");
           	   //左邻近
               if(side=="left"){
                   string dir=subNode->Attribute("direction");
                   if(dir=="same"){
                   	   //cout<<"同向左近邻"<<endl;
                       lane.leftNeighbor_sameDirect_id=subNode->Attribute("id");
                   }else if(dir=="opposite"){
                   	   //cout<<"反向左近邻"<<endl;
                       lane.leftNeighbor_reverseDirect_id=subNode->Attribute("id");
                   }

                }else if(side=="right"){
                	//右邻近

                   string dir=subNode->Attribute("direction");
                   if(dir=="same"){
                   	   //cout<<"同向右近邻"<<endl;
                       lane.rightNeighbor_sameDirect_id=subNode->Attribute("id");
                   }else if(dir=="opposite"){
                   	   //cout<<"反向右近邻"<<endl;
                       lane.rightNeighbor_reverseDirect_id=subNode->Attribute("id");
                   }
                }


        }


     	subNode=subNode->NextSiblingElement();
     }

   }
   
   


   //加入到lanesection
   laneSection.lanes.push_back(lane);
   //添加到laneList
   laneList.push_back(lane);


	
}

bool HdmapEngine::paserJunction(XMLElement* junctionNode){
   
   Junction junction; 
   cout<<"解析junction"<<endl;
   junction.id=atoi(junctionNode->Attribute("id"));
   XMLElement* connectionNode=junctionNode->FirstChildElement("connection");
   whie(connectionNode!=NULL){
     junction.in_road_id=atoi(connectionNode->Attribute("incomingRoad"));
     

   	connectionNode=connectionNode->NextSiblingElement("connection");
   }

   




}

bool HdmapEngine::paserRoad(XMLElement* roadNode){

	 string predecessor_elementType;
	  int predecessor_id=INT_MAX;
	  int successor_id=INT_MAX;
	  string successor_elementType;
	  double road_length;
	  road_id=atoi(roadNode->Attribute("id"));

	  XMLElement* linkNode = roadNode->FirstChildElement();
	  XMLElement* lanes=roadNode->FirstChildElement("lanes");
	  XMLElement* laneSection=lanes->FirstChildElement("laneSection");
      
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
     laneSection_id=0;
     
     while(laneSection!=NULL){
        
        paserLaneSection(laneSection,road);
       
        laneSection_id++;
     	laneSection = laneSection->NextSiblingElement("laneSection");
     }




	
}


bool HdmapEngine::paserApolloxml(const char* file_name){

    tinyxml2::XMLDocument doc;
    if(doc.LoadFile(file_name)!= XML_SUCCESS) return false;
    
	XMLElement* root = doc.RootElement();
	XMLElement* roadNode = root->FirstChildElement("road");
	
	while (roadNode != NULL)
	{        
	    
	  
	   
		//XMLElement* cpyNode = roadNode;
		string name = roadNode->Attribute("name");
		if (name.substr(0, 4) == "Road")
		{
			//cout << roadNode->Attribute("id") << endl;
			//string road_id_str=;
			paserRoad(roadNode);
			

		}else if(name.substr(0, 8)=="junction"){

           paserJunction(roadNode);

       }
        
		roadNode = roadNode->NextSiblingElement();
       
		
	}
    cout<<"road size"<<roadList.size()<<endl;
		printRoad();

	return true;

}