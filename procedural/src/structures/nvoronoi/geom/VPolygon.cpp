#include "VPolygon.h"
#include <math.h>
namespace vor{
    namespace geom{
        VPolygon::VPolygon(vector<Vector3*>* verts):_verts(verts){
        }
        float VPolygon::area(){
            float retval = 0;
            
            for(vector<Vector3*>::iterator i = _verts->begin(); i != _verts->end(); ++i){
                vector<Vector3*>::iterator j = (i == _verts->end()-1)? _verts->begin() : i+1;
                retval += (*i)->x * (*j)->y - (*j)->x * (*i)->y;
            }
            return std::abs(retval/2);
        }
    }
}