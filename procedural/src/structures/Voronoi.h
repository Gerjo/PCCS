#ifndef VORONOI_H
#define VORONOI_H

#include <list>
#include <queue>
#include <set>
#include <functional>

#include "VPoint.h"
#include "Edge.h"
#include "Parabola.h"
#include "VEvent.h"

namespace PGC{
    typedef std::list<VPoint*>  Vertices;
    typedef std::list<Edge*>    Edges;

    class LIBEXPORT Voronoi{
    public:
        Voronoi();
        Edges* getEdges(Vertices* v, int w, int h);
    private:
        Vertices *		places;
        Edges *			edges;
        double			width, height;
        Parabola *		root;
        double			ly;

        std::set<VEvent *>	deleted;
        std::list<VPoint *> points;
        std::priority_queue<VEvent *, std::vector<VEvent *>, VEvent::CompareEvent> queue;

        void		insertParabola(VPoint * p);
        void		removeParabola(VEvent * e);
        void		finishEdge(Parabola * n);
        double		getXOfEdge(Parabola * par, double y);

        Parabola *  getParabolaByX(double xx);
        double		getY(VPoint * p, double x);
        void		checkCircle(Parabola * b);
        VPoint *	getEdgeIntersection(Edge * a, Edge * b);
    };
}

#endif /* VORONOI_H */