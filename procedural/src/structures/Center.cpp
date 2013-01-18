#include "Center.h"
#include <algorithm>
namespace PGC{
    Center* Center::bar = nullptr;
    Center::Center(Vector3* _point): neighbours(0), borders(0), corners(0), sortedCorners(0),children(0), point(_point){
        parent = nullptr;
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
                    dist = parent->point->distanceToSq(*child->point);
                    prospect = parent;
                }else{
                    newDist = parent->point->distanceToSq(*child->point);
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