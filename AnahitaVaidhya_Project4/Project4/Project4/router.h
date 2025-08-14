//
//  router.h
//  Project4
//
//  Created by Anahita Vaidhya on 3/12/24.
//

#ifndef router_h
#define router_h

#include <stdio.h>
#include <queue>
#include <functional>
#include "hashmap.h"
#include "base_classes.h"
#include "geotools.h"
using namespace std;

class Router: public RouterBase {
public:
    Router(const GeoDatabaseBase& geo_db):m_gdb(geo_db){}
    virtual ~Router(){}
    virtual vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
    
private:
    const GeoDatabaseBase& m_gdb;
    //Node Struct
    struct Node{
        GeoPoint m_point;
        double g, h;
        //Constructor
        Node(const GeoPoint& point){
            m_point = point;
            g = 0;
            h = 0;
        }
        //Different parameters
        Node(const GeoPoint& point, double m_g, double m_h){
            m_point = point;
            g = m_g;
            h = m_h;
        }
        //Simple Constructor
        Node(){
            g = 0;
            h = 0;
        }
        //Returns distance
        double cost(const GeoPoint& end){
            return distance_earth_km(m_point, end);
        }
        //Returns distance
        double cost(const Node& end){
            return distance_earth_km(m_point, end.m_point);
        }
        //Operator <
        bool operator<(const Node& other) const{
            return (this->g + this->h) > (other.g + other.h);
        }
         
    };
    //Reconstruct Path Function
    vector<GeoPoint> reconstructPath(HashMap<GeoPoint>& from, const Node& current) const;
};

#endif /* router_hpp */
