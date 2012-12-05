#include "Edge.h"
#include "Center.h"
#include "Corner.h"
namespace PGC{
    Edge::Edge(){
        isTraversable = false;
    }
    void Edge::binaryTraverse(Center* end){
        if(d0 == end || d1 == end){
            return;
        }
        
    }
}