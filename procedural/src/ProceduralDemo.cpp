#include "ProceduralDemo.h"
#include <graphics/shapes/Polygon.h>
#include "structures/fortune/voronoi.h"
#include <list>
ProceduralDemo::ProceduralDemo(): GameState(), corners(0), centers(0),_edges(0), count(10){
    getDriver()->enableCamera(camera = getDriver()->createCamera());
    w = getPhantomGame()->getWorldSize().x;
    h = getPhantomGame()->getWorldSize().y;

    v = new vor::VoronoiDiagramGenerator();
    vertices = new vector<Vector3>();
    srand(2);

    isUp = true;
    start = temp = end = 0;
    for(int i = 0; i < count; i++){
        vertices->push_back(Vector3(w * (float)((rand()/ (float) RAND_MAX)), h * (float)((rand()/ (float) RAND_MAX))) );
    }

    buildGraph(vertices);
    for(int i = 0; i < 0; ++i){
        relaxation(*centers);
    }
    /*for(int i = 0; i < 10; ++i){
    float f = ((float)rand() / (float) RAND_MAX);
    int j = (int) (1000* f);
    centers->at(j)->binaryTraverse(centers->at(0));
    }*/
    drawVonoroi();
}  
ProceduralDemo::~ProceduralDemo(){
    getGraphics().clear();
    delete camera;
    delete vertices;
    delete v;
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
    delete v;
    v = new vor::VoronoiDiagramGenerator();
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
                .setFillStyle(phantom::Colors::BLACK)
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
    for(Center* center : *centers){
        /*if(center->point->distanceToSq(mousePos) < 200){
        temp = center;
        for(Edge* e : center->borders){
        getGraphics().beginPath()
        .setFillStyle(phantom::Colors::HOTPINK)
        .line(*e->v0->point,*e->v1->point)
        .fill();
        }
        }*/
        getGraphics().beginPath()
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
        }
    }
}

