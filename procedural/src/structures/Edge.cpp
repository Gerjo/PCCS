#include "Edge.h"
#include "Center.h"
#include "Corner.h"
namespace PGC{
    Edge::Edge(){
        isTraversable = true;
    }
    void Edge::binaryTraverse(Center* end){
        if(d0 == end || d1 == end){
            return;
        }
        
    }
}