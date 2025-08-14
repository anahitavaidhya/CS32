//
//  router.cpp
//  Project4
//
//  Created by Anahita Vaidhya on 3/12/24.
//

#include "router.h"

//Helper Function to reconstruct path
vector<GeoPoint> Router::reconstructPath(HashMap<GeoPoint>& from, const Node& current) const{
    vector<GeoPoint> path;

    GeoPoint currentPOI = current.m_point;
    
    while(from.find(currentPOI.to_string()) != nullptr){
        currentPOI = from[currentPOI.to_string()];
        path.push_back(currentPOI);
    }
    
    //Reverse path
    reverse(path.begin(), path.end());
    return path;
}

vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const{
    //Min Heap
    priority_queue<Node> openList;
    HashMap<GeoPoint> path;
    HashMap<Node> closedList;
    
    Node start = Node(pt1);
    GeoPoint goal =  pt2;
    
    start.g = 0;
    start.h = start.cost(goal);

    openList.push(start);
    
    while(!openList.empty()){
        Node current = openList.top();
        openList.pop();
        
        //If reached the end
        if(current.m_point.latitude == goal.latitude && current.m_point.longitude == goal.longitude){
            return reconstructPath(path, current);
        }
        
        closedList.insert(current.m_point.to_string(), current);
        
        vector<GeoPoint> connectedPoints = m_gdb.get_connected_points(current.m_point);
        
        //Go through all the connected points and find the most optimized
        for(auto point : connectedPoints){
            if(closedList.find(point.to_string()) != nullptr){
                continue;
            }
            
            Node poi = Node(point);
            poi.g = current.g + current.cost(poi);
            poi.h = poi.cost(goal);
            
            openList.push(poi);
            path.insert(poi.m_point.to_string(), current.m_point);
        }
    }
    return {};
}
