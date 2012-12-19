#include "Procedural.h"
#include <graphics/shapes/Polygon.h>
#include "structures/fortune/voronoi.h"

Procedural::Procedural(): Composite(), corners(0), centers(0),edges(0), count(1000){
    worldWidth = 5000;
    worldHeight = 5000;
}  
Procedural::~Procedural(){
    getGraphics().clear();
    delete voronoiDiagram;
    delete vertices;
}

vector<Data*> Procedural::generateWorld(int relaxCount){
    voronoiDiagram = new vor::VoronoiDiagramGenerator();
    vertices = new vector<Vector3>();
    unsigned int tmprand = (unsigned)time(NULL);
#ifdef _DEBUG
    cout << "seed = " << tmprand << endl << endl;
#endif
    srand(tmprand);
    float fx = 0;
    float fy = 0;
    for(unsigned int i = 0; i < count; i++){
        fx = (float)(rand()/ (float) RAND_MAX);
        fy = (float)(rand()/ (float) RAND_MAX);
        vertices->push_back(Vector3(worldWidth * fx, worldHeight * fy));
    }

    buildGraph(vertices);
    for(int i = 0; i < relaxCount; ++i){
        relaxation(*centers);
    }
    float av = 0;
    float counter = 0;
    for(Center* c : *centers){
        if(c->getArea() < 80)
            c->isBlocked = true;
        av += c->getArea();
        ++counter;
    }
    av /= counter;
    cout << "average area = " << av << endl << endl;
    /*for(int i = 0; i < 50; ++i){
    float f = ((float)rand() / (float) RAND_MAX);
    int j = (int) (count* f);
    centers->at(j)->binaryTraverse(centers->at(0));
    }*/
    return buildJSON(true);
}
void Procedural::buildGraph(vector<Vector3>* points){
    float* xval = new float[count];
    float* yval = new float[count];

    for(unsigned int i = 0; i < count; ++i){
        xval[i] = points->at(i).x;
        yval[i] = points->at(i).y;
    }
    voronoiDiagram->generateVoronoi(xval,yval,count,0,worldWidth,0,worldHeight,0);
    centers = &voronoiDiagram->centers;
    corners = &voronoiDiagram->corners;
    edges = &voronoiDiagram->edges;

    for(Corner* c : *corners){
        Vector3* p = c->point;
        if(p->x >= worldWidth || p->x <= 0 || p->y >= worldHeight || p->y <= 0){
            c->isBorder = true;
        }
    }

    delete[] xval ;
    delete [] yval;
}

void Procedural::relaxation(vector<Center*> centerList){
    float vx, vy;
    vertices->clear();

    vor::VoronoiDiagramGenerator* x = voronoiDiagram;
    voronoiDiagram = new vor::VoronoiDiagramGenerator();

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
    improveEdgeLength();
}
void Procedural::improveEdgeLength(){
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
            tempvec->x /= corners->size();
            tempvec->y /= corners->size();
            newPoints.at(corner->index) = tempvec;
        }
    }

    for(unsigned int i = 0; i < corners->size(); ++i){
        corners->at(i)->point = newPoints.at(i);
    }
}

vector<Data*> Procedural::buildJSON(bool useCenters){
    vector<Data*> dataList;
    if(useCenters){
        for(Center* c : *centers){
            if(c->isBlocked){
                float x = (c->point->x);
                float y = (c->point->y);
                Data* data = new Data();
                (*data)("type") = "tree";
                (*data)("height")   = 100;
                (*data)("width")    = 106;
                (*data)("x")        = x;
                (*data)("y")        = y;
                dataList.push_back(data);
            }
        }
    }else{
        for(Edge* e : *edges){
            if(!e->isTraversable){
                float x = (e->v0->point->x + e->v1->point->x)/2;
                float y = (e->v0->point->y + e->v1->point->y)/2;
                Data* data = new Data();
                (*data)("type") = "tree";
                (*data)("height")   = 100;
                (*data)("width")    = 106;
                (*data)("x")        = x;
                (*data)("y")        = y;
                dataList.push_back(data);
            }
        }
    }
    return dataList;
}

