//
//  tour_generator.cpp
//  Project4
//
//  Created by Anahita Vaidhya on 3/13/24.
//

#include "tour_generator.h"

TourGenerator::TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router) : m_gdb(geodb), m_router(router){}

TourGenerator::~TourGenerator(){}

//Helper Functions
//Get Direction Calculation
string TourGenerator::getDirection(double angle) const {
    if (angle >= 0 && angle < 22.5)
        return "east";
    else if (angle >= 22.5 && angle < 67.5)
        return "northeast";
    else if (angle >= 67.5 && angle < 112.5)
        return "north";
    else if (angle >= 112.5 && angle < 157.5)
        return "northwest";
    else if (angle >= 157.5 && angle < 202.5)
        return "west";
    else if (angle >= 202.5 && angle < 247.5)
        return "southwest";
    else if (angle >= 247.5 && angle < 292.5)
        return "south";
    else if (angle >= 292.5 && angle < 337.5)
        return "southeast";
    else
        return "east";
}

//Get Turn Direction Calculation
string TourGenerator::getTurnDirection(double angle) const {
    if (angle >= 1 && angle < 180)
        return "left";
    else
        return "right";
}

//Tour Generator
vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const {
    vector<TourCommand> instructions;
    
    for (int i = 0; i < stops.size(); i++) {
        string poi;
        string talkingPoint;
        //Initializes the poi and talkingPoint
        stops.get_poi_data(i, poi, talkingPoint);
        
        //Create commentary TourCommands
        TourCommand commentary;
        commentary.init_commentary(poi, talkingPoint);
        //Load it into vector of instructions
        instructions.push_back(commentary);
        
        if ((i + 1) < stops.size()) {
            GeoPoint current;
            GeoPoint next;
            
            m_gdb.get_poi_location(poi, current);
            
            string nextPOIName;
            stops.get_poi_data(i+1, nextPOIName, talkingPoint);
            m_gdb.get_poi_location(nextPOIName, next);
            
            // Get route between POIs
            vector<GeoPoint> route = m_router.route(current, next);
            
            for (int j = 0; j < route.size()-1; j++) {
                GeoPoint p1 = route[j], p2 = route[j + 1];
                TourCommand proceed;
                double angleLine = angle_of_line(p1, p2);
                proceed.init_proceed(getDirection(angleLine), m_gdb.get_street_name(p1, p2), distance_earth_miles(p1, p2), p1, p2);
                instructions.push_back(proceed);
                
                if ((j+2) < route.size()) {
                    string streetName1 = m_gdb.get_street_name(route[j], route[j+1]);
                    string streetName2 = m_gdb.get_street_name(route[j+1], route[j+2]);
                    if ( streetName1 != streetName2) {
                        GeoPoint p3 = route[j+2];
                        if (angle_of_line(p1, p2) >= 1 && angle_of_line(p1, p2) <= 359 && angle_of_line(p2, p3) >= 1 && angle_of_line(p2, p3) <= 359) {
                            TourCommand turn;
                            double angleTurn = angle_of_turn(p1, p2, p3);
                            turn.init_turn(getTurnDirection(angleTurn), streetName2);
                            instructions.push_back(turn);
                        }
                    }
                }
            }
        }
    }
    
    return instructions;
}
