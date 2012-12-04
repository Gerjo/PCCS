#include "Center.h"

namespace PGC{
    Center::Center(Vector3* _point): neighbours(0), borders(0), corners(0), point(_point){
        direction = 0;
        counter = 0;
    }
    void Center::binaryTraverse(Center* end){
        binaryTraverse(nullptr, end);
    }
    void Center::binaryTraverse(Center* start, Center* end){
        if(start == nullptr) start = this;
        if(this == end) return;

        direction = getDirection(end);
        Center* next;
        vector<Center*> eligibleNeighbours;
        for(Center* c : neighbours){
            if(c == end) { 
                eligibleNeighbours.push_back(c); 
                break;
            }
            if(getDirection(c) == direction){
                eligibleNeighbours.push_back(c);
            }
        }
        next = eligibleNeighbours[0];
        float dist = point->distanceTo(*next->point);
        float tempDist = 0;
        for(Center* c : eligibleNeighbours){
            if((tempDist = point->distanceTo(*c->point)) < dist){
                dist = tempDist;
                next = c;
            }
        }
        for(Edge* e : borders){
            if(e->d0 == next || e->d1 == next){
                start->path.push_back(e);
            }
        }
        next->binaryTraverse(start,end);
    }
    int Center::getDirection(Center* other){
        int d = 0;
        Vector3 dir = *other->point - *point;
        d += (dir.x < 0)? Direction::LEFT : Direction::RIGHT;
        
        return d;
    }
}