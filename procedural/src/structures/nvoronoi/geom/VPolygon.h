#ifndef VPOLYGON_H
#define VPOLYGON_H

#include <CompileConfig.h>
#include <phantom.h>
#include <vector>

using std::vector;
using phantom::Vector3;
namespace vor{
    namespace geom{
        class LIBEXPORT VPolygon{
        public:
            VPolygon(vector<Vector3*>* verts);
            float area();
            Winding winding();
        private:
            vector<Vector3*>* _verts;
        };
        enum Winding{
            CLOCKWISE,
            COUNTERCLOCKWISE
        };
    }
}

#endif /*POLYGON_H */