#include "Center.h"

namespace PGC{
    Center::Center(Vector3* _point): neighbours(0), borders(0), corners(0), point(_point){
        direction = 0;
        counter = 0;
        isBlocked = false;
        area = 0;
    }
    Center::~Center(){
        delete point;
    }

    float Center::getArea(){
        if(area > 0){
            return 0;
        }
        Corner* begin = (*corners.begin());
        float maxX = begin->point->x, minX = begin->point->x;
        float maxY = begin->point->y, minY = begin->point->y;
        for(Corner* c : corners){
            Vector3 p = *c->point;
            maxX = (p.x > maxX)? p.x : maxX;
            minX = (p.x < minX)? p.x : maxX;
            maxY = (p.y > maxY)? p.x : maxY;
            minY = (p.y < minY)? p.x : minY;
        }
        return area = (maxX - minX) * (maxY - minY);
    }

    void Center::binaryTraverse(Center* end){
        binaryTraverse(nullptr, end);
    }
    void Center::binaryTraverse(Center* start, Center* end){
        if(start == nullptr){
            start = this;
            start->path.clear();
            counter = 0;
        }
        if(this == end) return;
        start->counter++;
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
        float dist = end->point->distanceTo(*next->point);
        float tempDist = 0;
        for(Center* c : eligibleNeighbours){
            if((tempDist = end->point->distanceTo(*c->point)) < dist){
                dist = tempDist;
                next = c;
            }
        }
        for(Edge* e : borders){
            if(e->d0 == next || e->d1 == next){
                e->isTraversable = true;
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