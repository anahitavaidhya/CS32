//
//  geodb.cpp
//  Project4
//
//  Created by Anahita Vaidhya on 3/8/24.
//
#include "geodb.h"
#include "hashmap.h"
#include "geotools.h"
#include "geopoint.h"
#include <iostream>
#include <fstream>
#include <sstream>

//Helper Functions
//Get Segment Key (sorts)
string GeoDatabase::getSegmentKey(GeoPoint pt1, GeoPoint pt2) const{
    double lat1 = pt1.latitude;
    double lon1 = pt1.longitude;
    
    double lat2 = pt2.latitude;
    double lon2 = pt2.longitude;
    
    if(lat1 < lat2){
        return pt1.to_string() + "-" + pt2.to_string();
    } else if (lat2 < lat1) {
        return pt2.to_string() + "-" + pt1.to_string();
    } else if (lon1 < lon2){
        return pt1.to_string() + "-" + pt2.to_string();
    } else {
        return pt2.to_string() + "-" + pt1.to_string();
    }
}
//Add Connecting Points
void GeoDatabase::addConnectingPoints(const GeoPoint& pt1, const GeoPoint& pt2) {
    vector<GeoPoint>* temp;
    
    temp = connectingPoints.find(pt1.to_string());
    if(temp != nullptr){
        temp->push_back(pt2);
    } else {
        connectingPoints.insert(pt1.to_string(), vector<GeoPoint>{pt2});
    }

    temp = connectingPoints.find(pt2.to_string());
    if(temp != nullptr){
        temp->push_back(pt1);
    } else {
        connectingPoints.insert(pt2.to_string(), vector<GeoPoint>{pt1});
    }
}

//Add Into Segment Map
void GeoDatabase::addIntoSegmentMap(const GeoPoint& p1, const GeoPoint& p2, const string& streetName) {
    // Create GeoPoint string
    string segmentCoords = getSegmentKey(p1, p2);
    // Add street to segmentMap
    segmentMap.insert(segmentCoords, streetName);
}


//Load
bool GeoDatabase::load(const string& map_data_file){
    ifstream infile(map_data_file);
        if (!infile)
            //If file isn't found, returns false
            return false;

        string line;
        // Process street segments
        while (getline(infile, line)) {
            string streetName = line;
            string lat1, lon1, lat2, lon2;
            int poiNum;
            
            //Inputs the lat1, lon1 and lat2, lon2
            infile >> lat1;
            infile >> lon1;
            infile >> lat2;
            infile >> lon2;
            
            //Inputs the number of POIs
            infile.ignore(10000, '\n');
            infile >> poiNum;
            
            //Ignore after the int
            infile.ignore(10000, '\n');
            
            // Create GeoPoints for street segments
            GeoPoint p1(lat1, lon1);
            GeoPoint p2(lat2, lon2);
            
            // Create a connection between points
            addConnectingPoints(p1, p2);
            // Add street into segment map
            addIntoSegmentMap(p1, p2, streetName);
            
            if (poiNum > 0) {
                GeoPoint mid = midpoint(p1, p2);
                //Create connecting points and add to segmentMap
                addConnectingPoints(p1, mid);
                addConnectingPoints(mid, p2);
                addIntoSegmentMap(p1, mid, streetName);
                addIntoSegmentMap(mid, p2, streetName);
                
                for (int i = 0; i < poiNum; i++) {
                    string poiName = "";
                    string poiLat, poiLon;
                    
                    // Get POI name and location
                    getline(infile, poiName, '|');
                    infile >> poiLat;
                    infile >> poiLon;
                    // Go to the next line
                    infile.ignore(10000, '\n');
                    
                    // Create GeoPoint out of point of interest
                    GeoPoint poiPoint(poiLat, poiLon);
                    // Add to poiMap
                    poiMap.insert(poiName, poiPoint);
                    
                    addConnectingPoints(mid, poiPoint);
                    // "a path" for midpoint to POI
                    addIntoSegmentMap(mid, poiPoint, "a path");
                }
            }
        }
    return true;
}

//Get POI location
bool GeoDatabase::get_poi_location(const string& poi, GeoPoint& point) const{
    const GeoPoint* poiLocation = poiMap.find(poi);
    // If the point of interest is found, set the GeoPoint parameter and return true
    if (poiLocation != nullptr) {
        point = *poiLocation;
        return true;
    } else {
        // If the point of interest is not found, return false
        return false;
    }
}

//Get Connected Points
vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const{
    // Vector of GeoPoints that are connected
    vector<GeoPoint> geopoints;
    // Try to find connected points of specified point in connectingPoints map
    if (connectingPoints.find(pt.to_string()) == nullptr) 
        // Point wasn't found
        return geopoints;
    else {
        geopoints = *(connectingPoints.find(pt.to_string()));
        return geopoints;
    }
}

//Get Street Name
string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const{
    string key = getSegmentKey(pt1, pt2);
    const string* streetNamePtr = segmentMap.find(key);
    
    if(streetNamePtr != nullptr)
        return *streetNamePtr;
    
    // If no matches found, return an empty string
    return "";
}

