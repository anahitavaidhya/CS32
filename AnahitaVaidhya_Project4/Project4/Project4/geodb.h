//
//  geodb.hpp
//  Project4
//
//  Created by Anahita Vaidhya on 3/8/24.
//

#ifndef geodb_hpp
#define geodb_hpp

#include "base_classes.h"
#include "hashmap.h"
#include <stdio.h>
using namespace std;

class GeoDatabase: public GeoDatabaseBase{
public:
    //Constructor
    GeoDatabase() {};
    //Destructor
    virtual ~GeoDatabase() {};
    //Load Function
    virtual bool load(const string& map_data_file);
    //Get POI Location
    virtual bool get_poi_location(const string& poi, GeoPoint& point) const;
    //Get Connected Points
    virtual vector<GeoPoint> get_connected_points(const GeoPoint& pt) const;
    //Get Street Name
    virtual string get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const;
    
private:
    //POI Name mapped to GeoPoint
    HashMap<GeoPoint> poiMap;
    //Starting GeoPoint mapped to connecting coordinates
    HashMap<vector<GeoPoint>> connectingPoints;
    //Segment to_string mapped to name of segment
    HashMap<string> segmentMap;
    //Helper Function for sorting before adding to segmentMap
    string getSegmentKey(GeoPoint pt1, GeoPoint pt2) const;
    //Helper Function for connecting points
    void addConnectingPoints(const GeoPoint& p1, const GeoPoint& p2);
    //Helper Functions to add into Segment Map
    void addIntoSegmentMap(const GeoPoint& p1, const GeoPoint& p2, const string& street_name);
};

#endif /* geodb_hpp */
