#include"HdmapEngine.h"


int road_id;
int laneSection_id=0;

HdmapEngine::HdmapEngine(){
	
}
HdmapEngine::~HdmapEngine(){
	
}


vector<string> split(const string& str, const string& delim) {  
  vector<string> res;  
  if("" == str) return res;  
  //先将要切割的字符串从string类型转换为char*类型  
  char * strs = new char[str.length() + 1] ; //不要忘了  
  strcpy(strs, str.c_str());   
 
  char * d = new char[delim.length() + 1];  
  strcpy(d, delim.c_str());  
 
  char *p = strtok(strs, d);  
  while(p) {  
    string s = p; //分割得到的字符串转换为string类型  
    res.push_back(s); //存入结果数组  
    p = strtok(NULL, d);  
  }  
 
  return res;  
} 


void HdmapEngine::printRoad(){
	cout<<"section size"<<lansectionList.size()<<endl;
	for (int i = 0; i < roadList.size(); ++i)
	{
		cout<<"road_id "<<roadList[i].road_id<<" "<<"predecessor_elementType "<<roadList[i].predecessor_elementType<<" "<<"predecessor_id " <<roadList[i].successor_elementType<<" "<<"successor_elementType "<<roadList[i].successor_elementType<<" "<<"  successor_id " <<roadList[i].successor_id<<"  road_length  "<<roadList[i].length<<endl;
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
	laneSectionMap[section.laneSection_id]=section;
    
  
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

   //车道长度、车道中心点线
   
   XMLElement* centerLineNode=laneNode->FirstChildElement("centerLine");
   if(centerLineNode!=NULL){
     XMLElement* geometryNode=centerLineNode->FirstChildElement("geometry");
     if(geometryNode!=NULL){
       lane.lane_length=atof(geometryNode->Attribute("length"));
       XMLElement* pointSetNode=geometryNode->FirstChildElement("pointSet");
       if(pointSetNode!=NULL){
       	  XMLElement* pointNode=pointSetNode->FirstChildElement("point");
       	  while(pointNode!=NULL){
            Point point;
            point.x=atof(pointNode->Attribute("x"));
            point.y=atof(pointNode->Attribute("y"));
            point.z=atof(pointNode->Attribute("z"));
            //cout<<"x "<< point.x<<" y "<<point.y<<"  z "<<point.z<<endl;
            lane.centerLinePoints.push_back(point);
       	  	pointNode=pointNode->NextSiblingElement("point");

       	  }        
       }  
     //cout<<"车道长度"<<lane.lane_length<<endl;
      }
   }

  //获得车道边界
  XMLElement* borderNode=laneNode->FirstChildElement("border");
  if(borderNode!=NULL){
   XMLElement* geometryNode=borderNode->FirstChildElement("geometry");
   if(geometryNode!=NULL){
   XMLElement* pointSetNode1=geometryNode->FirstChildElement("pointSet");
   if(pointSetNode1 !=NULL){
      XMLElement* pointNode=pointSetNode1->FirstChildElement("point");
      //获取车道边界点
      while(pointNode!=NULL){
        Point point;
        point.x=atof(pointNode->Attribute("x"));
        point.y=atof(pointNode->Attribute("y"));
        point.z=atof(pointNode->Attribute("z"));
        lane.borderPoints.push_back(point);

        pointNode=pointNode->NextSiblingElement("point");
      }
    }
   }

   //获取车道边界类型
   XMLElement* borderTypeNode=borderNode->FirstChildElement("borderType");
   while(borderTypeNode!=NULL){
       BorderType borderType;
       if(borderTypeNode->Attribute("type")!=NULL)
       borderType.type=borderTypeNode->Attribute("type");
       if(borderTypeNode->Attribute("color")!=NULL)
       borderType.color=borderTypeNode->Attribute("color");
       if(borderTypeNode->Attribute("sOffset")!=NULL)
       borderType.sOffset=atof(borderTypeNode->Attribute("sOffset"));
       if(borderTypeNode->Attribute("eOffset")!=NULL)
       borderType.eOffset=atof(borderTypeNode->Attribute("eOffset"));
       lane.borderTypes.push_back(borderType);

       borderTypeNode=borderTypeNode->NextSiblingElement("borderType");
    } 
   }

  //获取车道宽度
   XMLElement* sampleAssociatesNode=laneNode->FirstChildElement("sampleAssociates");
   if(sampleAssociatesNode!=NULL){
    XMLElement* sampleAssociateNode=sampleAssociatesNode->FirstChildElement("sampleAssociate");
    while(sampleAssociateNode!=NULL){

       WidthsampleAssociate widthsampleAssociate;
       if(sampleAssociateNode->Attribute("sOffset")!=NULL)
          widthsampleAssociate.sOffset=atof(sampleAssociateNode->Attribute("sOffset"));
       if(sampleAssociateNode->Attribute("leftWidth")!=NULL)
          widthsampleAssociate.leftWidth=atof(sampleAssociateNode->Attribute("leftWidth"));
       if(sampleAssociateNode->Attribute("rightWidth")!=NULL)
          widthsampleAssociate.rightWidth=atof(sampleAssociateNode->Attribute("rightWidth"));

       widthsampleAssociate.width=widthsampleAssociate.leftWidth + widthsampleAssociate.rightWidth;
       lane.widthsampleAssociates.push_back(widthsampleAssociate);
       sampleAssociateNode=sampleAssociateNode->NextSiblingElement("sampleAssociate");
      }
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
   //加入lanemap
   laneMap[lane.uid]=lane;


	
}




bool HdmapEngine::paserJunction(XMLElement* junctionNode){

   Junction junction;

   Connection connection; 
   cout<<"解析junction"<<endl;
   connection.junction_id=atoi(junctionNode->Attribute("id"));
   junction.id=atoi(junctionNode->Attribute("id"));
   XMLElement* connectionNode=junctionNode->FirstChildElement("connection");
   while(connectionNode!=NULL){
     int in_road_id=atoi(connectionNode->Attribute("incomingRoad"));
     connection.in_road_id=in_road_id;
     int connectionRoad_id=atoi(connectionNode->Attribute("connectingRoad"));
     for(int i=0;i<roadList.size();i++){
     	//cout<<"i"<<i<<endl;
     	//cout<<"roadid "<<roadList[i].road_id<<endl;
     	//cout<<"inroadid"<<in_road_id<<endl;
       if(roadList[i].road_id==in_road_id){
       	  //cout<<"laneSections size"<<roadList[i].laneSections.size()<<endl;
          for(int j=0;j<roadList[i].laneSections.size();j++){
          	//cout<<"j"<<j<<endl;
            for(int z=0;z<roadList[i].laneSections[j].lanes.size();z++){
            	//cout<<"z"<<z<<endl;
              for(int y=0;y<roadList[i].laneSections[j].lanes[z].successors.size();y++){
              	   //cout<<"y"<<y<<endl;
                    if(atoi(split(roadList[i].laneSections[j].lanes[z].successors[y],"_")[0].c_str())==connectionRoad_id){
                      //cout<<"进入路口车道为"<<roadList[i].laneSections[j].lanes[z].uid<<" 路口虚拟车道为 "<<roadList[i].laneSections[j].lanes[z].successors[y];
                      connection.in_lane_id=roadList[i].laneSections[j].lanes[z].uid;
                      connection.virtualLaneId=roadList[i].laneSections[j].lanes[z].successors[y];
                      auto  lanemapiter=laneMap.find(roadList[i].laneSections[j].lanes[z].successors[y]);
                      if(lanemapiter!=laneMap.end()){
                      	 connection.centerLinePoints.assign(lanemapiter->second.centerLinePoints.begin(),lanemapiter->second.centerLinePoints.end());
                      }

                      // for (int cc = 0; cc < connection.centerLinePoints.size(); ++cc)
                      // {
                      // 	/* code */
                      // 	cout<<"x"<<connection.centerLinePoints[cc].x<<"  y  "<<connection.centerLinePoints[cc].y<<endl;
                      // }
                     
                    //搜索驶离路口的车道
                     
                    for(int a=0;a<roadList.size();a++){
                       if(roadList[a].road_id==atoi(split(roadList[i].laneSections[j].lanes[z].successors[y],"_")[0].c_str())){
                       	int section_index=atoi(split(roadList[i].laneSections[j].lanes[z].successors[y],"_")[1].c_str());
                       for(int b=0;b<roadList[a].laneSections[section_index].lanes.size();b++){
                           if(roadList[a].laneSections[section_index].lanes[b].uid==roadList[i].laneSections[j].lanes[z].successors[y]){
                             //cout<<"驶离路口的车道 ";
                             for(int c=0;c<roadList[a].laneSections[section_index].lanes[b].successors.size();c++){
                             	//cout<<roadList[a].laneSections[section_index].lanes[b].successors[c]<<endl;
                             	connection.out_lane_id=roadList[a].laneSections[section_index].lanes[b].successors[c];
                             	connection.out_road_id=atoi(split(roadList[a].laneSections[section_index].lanes[b].successors[c],"_")[0].c_str());
                             	connectionList.push_back(connection);
                             	junction.connections.push_back(connection);
                             	connectionMap[connection.virtualLaneId]=connection;



                             }

                           }
                         

                         }

                       }

                    }
                    }
              }  
            }
          }
        }
     }

   	connectionNode=connectionNode->NextSiblingElement("connection");
   }

   junctionList.push_back(junction);
   junctionMap[junction.id]=junction;
   




}

bool HdmapEngine::paserRoad(XMLElement* roadNode){

	 string predecessor_elementType;
	  int predecessor_id=INT_MAX;
	  int successor_id=INT_MAX;
	  string successor_elementType;
	  double road_length;
	  road_id=atoi(roadNode->Attribute("id"));

	  XMLElement* linkNode = roadNode->FirstChildElement("link");
	  XMLElement* lanes=roadNode->FirstChildElement("lanes");
	  XMLElement* laneSection=lanes->FirstChildElement("laneSection");
      
	 XMLElement* sucNode = linkNode->FirstChildElement("successor");

	 if (sucNode != NULL)
			{
				//cout << sucNode->Attribute("elementType") << " " << sucNode->Attribute("elementId") << endl;
				successor_elementType=sucNode->Attribute("elementType");	

                successor_id=atoi(sucNode->Attribute("elementId"));


			}
			XMLElement* preNode = linkNode->FirstChildElement("predecessor");
	 if (preNode != NULL)
			{
				//cout << preNode->Attribute("elementType") << " " << preNode->Attribute("elementId") << endl;
				predecessor_elementType=preNode->Attribute("elementType");

	            predecessor_id=atoi(preNode->Attribute("elementId"));
			}

     Road road(road_id,predecessor_elementType,predecessor_id,successor_elementType,successor_id);

     
     laneSection_id=0;
     
     while(laneSection!=NULL){
        
        paserLaneSection(laneSection,road);
       
        laneSection_id++;
     	laneSection = laneSection->NextSiblingElement("laneSection");
     }
     road.length=road.getRoadLength();
     roadList.push_back(road);
     roadMap[road.road_id]=road;





	
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