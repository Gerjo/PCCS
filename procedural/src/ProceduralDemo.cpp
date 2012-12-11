#include "ProceduralDemo.h"
#include <graphics/shapes/Polygon.h>
#include "structures/fortune/voronoi.h"
#include <list>

ProceduralDemo::ProceduralDemo(): GameState(), corners(0), centers(0),_edges(0), count(50000){

}
ProceduralDemo::~ProceduralDemo(){
    //getGraphics().clear();
    //delete camera;
    delete v;
    delete vertices;
}

vector<Data*> ProceduralDemo::generateWorld(int relaxCount){
    v = new vor::VoronoiDiagramGenerator();
    vertices = new vector<Vector3>();
    srand(time(NULL));

    isUp = true;
    start = temp = end = 0;
    for(int i = 0; i < count; i++){
        vertices->push_back(Vector3(w * (float)((rand()/ (float) RAND_MAX)), h * (float)((rand()/ (float) RAND_MAX))) );
    }
    clock_t begin, end;
    begin = clock();
    buildGraph(vertices);

    for(int i = 0; i < relaxCount; ++i){
        relaxation(*centers);
    }
    for(Center* c : *centers){
        if(c->getArea() < 80)
            c->isBlocked = true;
    }
    /*for(int i = 0; i < 50; ++i){
    float f = ((float)rand() / (float) RAND_MAX);
    int j = (int) (count* f);
    centers->at(j)->binaryTraverse(centers->at(0));
    }*/
    return buildJSON(true);
}
vector<Data*> ProceduralDemo::buildJSON(bool useCenters){
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
        for(Edge* e : *_edges){
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
void ProceduralDemo::buildGraph(vector<Vector3>* points){
    float* xval = new float[count];
    float* yval = new float[count];
    map<Vector3, Center*>* centerLookup;

    for(int i = 0; i < count; ++i){
        xval[i] = points->at(i).x;
        yval[i] = points->at(i).y;
    }
    v->generateVoronoi(xval,yval,count,0,w,0,h,0);
    centerLookup = &v->centerLookup;
    centers = &v->centers;
    corners = &v->corners;
    _edges = &v->edges;

    for(Corner* c : *corners){
        Vector3* p = c->point;
        if(p->x >= w || p->x <= 0 || p->y >= h || p->y <= 0){
            c->isBorder = true;
        }
    }

    delete[] xval ;
    delete [] yval;
}

void ProceduralDemo::relaxation(vector<Center*> centerList){
    float vx, vy;
    vertices->clear();

    vor::VoronoiDiagramGenerator* x = v;
    v = new vor::VoronoiDiagramGenerator();
    centers = &v->centers;
    corners = &v->corners;
    _edges = &v->edges;
    for(Center* c : centerList){
        vx = 0; vy = 0;
        for(Corner* cor : c->corners){
            vx += cor->point->x;
            vy += cor->point->y;
        }
        vx /= c->corners.size();
        vy /= c->corners.size();
        vertices->push_back(Vector3(vx,vy));
    }
    buildGraph(vertices);
    delete x;
}

void ProceduralDemo::update(const PhantomTime& time){
    Composite::update(time);

    /* MouseState* m = getDriver()->getInput()->getMouseState();
    mousePos = m->getPosition();*/
    /*if(m->isButtonDown(Buttons::LEFT_MOUSE) && isUp){
    start = temp;
    isUp = false;
    }
    if(m->isButtonUp(Buttons::LEFT_MOUSE) && !isUp){
    isUp = true;
    }
    if(start != 0){
    start->binaryTraverse(temp);
    }*/
    //getGraphics().clear();
    //drawVonoroi();
}
void ProceduralDemo::drawVonoroi(){
    for(Edge* e : *_edges){
        /* voronoi edges */

        if(!e->isTraversable){
            getGraphics().beginPath()
                .setFillStyle(phantom::Colors::RED)
                .line(*e->v0->point, *e->v1->point)
                .fill();
        }else{
            /* delaunay edges */
            getGraphics().beginPath()
                .setFillStyle(phantom::Colors::GREEN)
                .line(*e->d0->point, *e->d1->point)
                .fill();
        }
    }
    /*if(start != 0){
    for(Edge* e : start->path){
    getGraphics().beginPath()
    .setFillStyle(phantom::Colors::GREEN)
    .line(*e->d0->point, *e->d1->point)
    .fill();
    }
    }*/
    // for(Center* center : *centers){
    /*if(center->point->distanceToSq(mousePos) < 200){
    temp = center;
    for(Edge* e : center->borders){
    getGraphics().beginPath()
    .setFillStyle(phantom::Colors::HOTPINK)
    .line(*e->v0->point,*e->v1->point)
    .fill();
    }
    }*/
    /*getGraphics().beginPath()
    .setFillStyle(phantom::Colors::RED)
    .rect(center->point->x,center->point->y,2,2)
    .fill();
    for(Corner* c : center->corners){
    if(c->isBorder){
    for(Edge* e : center->borders){
    getGraphics().beginPath()
    .setFillStyle(phantom::Colors::RED)
    .line(*e->v0->point, *e->v1->point)
    .fill();
    }
    }
    }*/
    //}
}

