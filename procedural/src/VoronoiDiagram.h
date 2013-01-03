#ifndef VORONOIDIAGRAM_H
#define VORONOIDIAGRAM_H

#include <CompileConfig.h>
#include <phantom.h>
#include <physics/Vector3.h>

#include "structures/Center.h"
#include "structures/Corner.h"
#include "structures/Edge.h"
#include "structures/fortune/voronoi.h"
namespace PGC{
    class LIBEXPORT VoronoiDiagram{
    public:
        VoronoiDiagram(int width, int height, int numPoints, int relaxCount = 0);
        ~VoronoiDiagram();

        void relax(int count);
        void improveEdgeLength();

    private: //functions
        void buildGraph(vector<Vector3>* points);

    private: //properties
        float width, height, numPoints;

        vector<Vector3>*    vertices;
        vector<Corner*>*    corners;
        vector<Center*>*    centers;
        vector<Edge*>*      edges;

        vor::VoronoiDiagramGenerator* vdg;
    };
}

#endif /* VORONOIDIAGRAM_H */