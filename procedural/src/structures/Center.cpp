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
        ++start->counter;
        Vector3 dir = *end->point - *point;
        direction = (dir.x > 0)? Direction::LEFT : Direction::RIGHT;

        vector<Center*>* availableNeighbours = new vector<Center*>();
        for(Center* other : neighbours){
            if(direction == getDirection(other)){
                availableNeighbours->push_back(other);
                continue;
            }
        }
        
        Center* next = availableNeighbours->at(0);
        float dist = point->distanceTo(*availableNeighbours->at(0)->point);
        float tempDist =0;
        for(Center* other : *availableNeighbours){
            if((tempDist = point->distanceTo(*other->point)) < dist){
                next = other;
                dist = tempDist;
            }
        }
        for(Edge* e: borders){
            if(e->d0 == next || e->d1 == next){
                start->path.push_back(e);
            }
        }
        delete availableNeighbours;
        next->binaryTraverse(start,end);
    }
    int Center::getDirection(Center* other){
        int d = 0;
        Vector3 dir = *other->point - *point;
        d += (dir.x > 0)? Direction::LEFT : Direction::RIGHT;
        
        return d;
    }
}