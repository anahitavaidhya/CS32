//
//  tour_generator.hpp
//  Project4
//
//  Created by Anahita Vaidhya on 3/13/24.
//

#ifndef tour_generator_h
#define tour_generator_h

#include <stdio.h>
#include "stops.h"
#include "base_classes.h"
#include "tourcmd.h"
#include "geotools.h"
using namespace std;

class TourGenerator: public TourGeneratorBase {
public:
    TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router);
    virtual ~TourGenerator();
    virtual vector<TourCommand> generate_tour(const Stops& stops) const;
private:
    const GeoDatabaseBase& m_gdb;
    const RouterBase& m_router;
    string getDirection(double angle) const;
    string getTurnDirection(double angle) const;
};

#endif /* tour_generator_h */
