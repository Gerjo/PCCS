#include "Center.h"
#include <algorithm>
namespace PGC{
    Center* Center::bar = nullptr;

    Center::Center(Vector3* _point): neighbours(0), borders(0), corners(0), sortedCorners(0),children(0), point(_point), inTree(false), isStart(false), isEnd(nullptr), hasSpawnLocation(false) {
        parent = nullptr;
        neighbouringParent = nullptr;
        nextStage = nullptr;
        direction = 0;
        counter = 0;
        isBlocked = false;
        isBorder = false;
        area = 0;
    }

    Center::~Center(){
        delete point;
    }

    void Center::populateChildren(vector<Center*>* childList, vector<Center*>* centerList){
        float dist = 0;
        float newDist = 0;
        Center* prospect = 0;
        for(Center* child: *childList){
            for(Center* parent: *centerList){
                if(prospect == 0){
                    dist = parent->point->distanceToSq(child->point);
                    prospect = parent;
                }else{
                    newDist = parent->point->distanceToSq(child->point);
                    if(newDist < dist){
                        prospect = parent;
                        dist = newDist;
                    }
                }
            }
            prospect->children.push_back(child);
            child->parent = prospect;
            prospect = 0; 
        }
        setAsBorder(childList);
    }

    void Center::closeBorder(Center* neighbour){
        for(Center* child : children){
            if(child->isBorder){
                if(child->neighbouringParent != neighbour) child->isBlocked = true;
            }
        }
    }

    void Center::setAsBorder(vector<Center*>* childList){
        Center* check = 0;
        Center* prospect = 0;
        Center* prospectX = 0, *prospectY = 0;
        float dist;
        for(Center* child : *childList){
            if(!child->isBorder){
                check = child->parent;
                prospect = prospectX = prospectY = child;
                for(Center* neighbour : child->neighbours){
                    if(check != neighbour->parent){
                        child->isBorder = neighbour->isBorder = true;
                        child->neighbouringParent = neighbour->parent;
                        neighbour->neighbouringParent = child->parent;
                    }
                    if(prospectX == child){
                        if(neighbour->point->x < child->point->x) prospectX = neighbour;
                    }
                    if(prospectY == child){
                        if(neighbour->point->y < child->point->y) prospectY = neighbour;
                    }
                }
            }
        }
    }

    Center* Center::getParent(){
        if(parent == nullptr) return 0;
        return parent;
    }
    
    float Center::getArea(){
        if(area > 0){
            return area;
        }

        sortCorners();
        float surface = 0;
        for(auto it = sortedCorners.begin(); it != sortedCorners.end()-1; ++it){
            auto it1 = it + 1;
            float f1 = this->point->distanceTo(*(*it)->point);
            float f2 = this->point->distanceTo(*(*it1)->point);
            surface += 0.5f * (f1 + f2);
        }
        area = surface / sortedCorners.size();
#ifdef _DEBUG
        //cout << "Center.cpp: " << area << endl;
#endif
        return area;
    }
    float Center::getAreaWithNeighbours(){
        float accum = 0;
        for(Center* c : neighbours){
            accum += c->getArea();
        }
        return getArea() + accum;
    }

    void Center::sortCorners(bool clockwise){
        sortedCorners = corners;
        bar = this;
        sort(sortedCorners.begin(),sortedCorners.end(),Center::compareWith);
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
        direction = start->getDirection(end);
        Center* next;
        vector<Center*> eligibleNeighbours;
        for(Center* c : neighbours){
            if(c == end) { 
                eligibleNeighbours.push_back(c); 
                c->isEnd = this;
                break;
            }
            if(getDirection(c) == direction){
                eligibleNeighbours.push_back(c);
            }
        }
        if(eligibleNeighbours.empty()) return;
        next = eligibleNeighbours[0];
        float dist = end->point->distanceTo(*next->point);
        float tempDist = 0;
        for(Center* c : eligibleNeighbours){
            if((tempDist = end->point->distanceTo(*c->point)) < dist){
                dist = tempDist;
                next = c;
                next->isPath.push_back(this);
            }
        }
        for(Edge* e : borders){
            if(e->d0 == next || e->d1 == next){
                e->isTraversable = true;
                start->path.push_back(e);
            }
        }
        next->binaryTraverse(start, end);
    }

    void Center::binaryTraverseBySander(Center *start, Center *end) {
        if(start == nullptr) start = this;
        if(start == end)
            return;

        bool goingLeft = start->getDirection(end) == 4;
        vector<Center*> suitableNeighbours;
        for(Center *neighbour : start->neighbours) {
            if(goingLeft == (start->getDirection(neighbour) == 4)) {
                suitableNeighbours.push_back(neighbour);
            }
        }

        float currentDistanceToEnd = 1000000.0f;
        Center *next = nullptr;
        for(Center *neighbour : suitableNeighbours) {
            if(currentDistanceToEnd > end->point->distanceTo(*neighbour->point)) {
                next = neighbour;
                currentDistanceToEnd = end->point->distanceTo(*neighbour->point);
            }
        }
        if(next == nullptr) 
            return; // No more way to continue. This should not happen, consider making the currentDistanceToEnd higher.
        
        next->isPath.push_back(start);
        binaryTraverseBySander(next, end);
    }

    int Center::getDirection(Center* other){
        int d = 0;
        Vector3 dir = *other->point - *point;
        d += (dir.x < 0)? Direction::LEFT : Direction::RIGHT;

        return d;
    }
}