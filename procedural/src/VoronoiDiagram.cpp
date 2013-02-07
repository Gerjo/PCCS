#include "VoronoiDiagram.h"

namespace PGC{
    VoronoiDiagram::VoronoiDiagram(int width, int height, int numPoints, int relaxCount, bool distribute): width(width), height(height), numPoints(numPoints){
        child = nullptr;
        parent = nullptr;

        vdg = new vor::VoronoiDiagramGenerator();
        vertices = new vector<Vector3>();
        unsigned int tmprand = 1360265519;//(unsigned)time(NULL);
#ifdef _DEBUG
        cout << "seed = " << tmprand << endl << endl;
#endif
        srand(tmprand);
        float fx = 0;
        float fy = 0;
        for(unsigned int i = 0; i < numPoints; i++){
            fx = (float)(rand()/ (float) RAND_MAX);
            fy = (float)(rand()/ (float) RAND_MAX);
            vertices->push_back(Vector3(width * fx, height * fy));
        }
       // if(distribute) this->distribute(vertices);
        buildGraph(vertices);
        improveEdgeLength();
        relax(relaxCount);
    }
    VoronoiDiagram::~VoronoiDiagram(){
        delete vertices;
        delete vdg;
    }
    void VoronoiDiagram::openPaths(FF::Graph* searchGraph){
        list<FF::Node*> results;
        graph->Renew();
        graph->Search(searchGraph,results);
        int i = 0;
    }
    void VoronoiDiagram::distribute(vector<Vector3>* points){
        Vector3* last = nullptr;
        for(Vector3 v: *points){
            if(last = nullptr) {
                last = &v;
                continue;
            }
        }
    }
    void VoronoiDiagram::addChildDiagram(VoronoiDiagram* child){
        this->child = child;
        child->parent = this;
        Center::populateChildren(child->centers, centers);
    }
    VoronoiDiagram* VoronoiDiagram::getParent(){
        return parent;
    }
    VoronoiDiagram* VoronoiDiagram::getChild(){
        return child;
    }
    void VoronoiDiagram::buildGraph(vector<Vector3>* points){
        const int c = numPoints;
        float* xval = new float[c];
        float* yval = new float[c];

        for(unsigned int i = 0; i < numPoints; ++i){
            xval[i] = points->at(i).x;
            yval[i] = points->at(i).y;
        }
        vdg->generateVoronoi(xval,yval,numPoints,0,width,0,height,0);
        centers = &vdg->centers;
        corners = &vdg->corners;
        edges = &vdg->edges;

        for(Corner* c : *corners){
            Vector3* p = c->point;
            if(p->x >= width || p->x <= 0 || p->y >= height || p->y <= 0){
                c->isBorder = true;
            }
        }
        graph = vdg->graph;
        delete[] xval ;
        delete [] yval;
    }

    void VoronoiDiagram::relax(int count){
        for(int i = 0; i < count; ++i){
            float vx, vy;
            vertices->clear();

            vor::VoronoiDiagramGenerator* x = vdg;
            vdg = new vor::VoronoiDiagramGenerator();

            vector<Center*> centerList(*centers);
            centers = &x->centers;
            corners = &x->corners;
            edges = &x->edges;

            for(Center* c : centerList){
                vx = 0; vy = 0;
                if(c->corners.size() != 0){
                    for(Corner* cor : c->corners){
                        vx += cor->point->x;
                        vy += cor->point->y;
                    }
                    vx /= c->corners.size();
                    vy /= c->corners.size();
                }
                vertices->push_back(Vector3(vx,vy));
            }
            delete x;
            buildGraph(vertices);
        }
    }
    void VoronoiDiagram::improveEdgeLength(){
        vector<Vector3*> newPoints(corners->size());

        for(Corner* corner : *corners){
                if(corner->isBorder){
                newPoints.at(corner->index) = corner->point;
            }else{
                Vector3* tempvec = new Vector3(0,0);
                for(Center* c : corner->touches){
                    tempvec->x += c->point->x;
                    tempvec->y += c->point->y;
                }
                tempvec->x /= corner->touches.size();
                tempvec->y /= corner->touches.size();
                newPoints.at(corner->index) = tempvec;
            }
        }

        for(unsigned int i = 0; i < corners->size(); ++i){
            corners->at(i)->point = newPoints.at(i);
        }
    }
}