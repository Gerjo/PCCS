#include "VoronoiDiagram.h"

namespace PGC{
    VoronoiDiagram::VoronoiDiagram(int width, int height, int numPoints, int relaxCount, bool distribute): width(width), height(height), numPoints(numPoints){
        child = nullptr;
        parent = nullptr;

        vdg = new vor::VoronoiDiagramGenerator();
        vertices = new vector<Vector3>();
        unsigned int tmprand = (unsigned)time(NULL);
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
    bool VoronoiDiagram::generateTree(float depth){
        ceilf(depth);
        //finding the node with the most connections
        Center* root = nullptr;
        for(Center* center : *centers){
            if(!center->isBorder){
                root = center;
                break;
            }
        }
        unsigned size = root->neighbours.size();
        for(Center* center : *centers){
            if(center->neighbours.size() > size && !center->isBorder){
                root = center;
                size = center->neighbours.size();
            }
        }
        root->inTree = true;
        return findChildren(root,nullptr,depth);
    }
    bool VoronoiDiagram::findChildren(Center* root, Center* dNeighbour, float depth){
        if(depth < 0) return false;
        vector<vector<Center*>> checkLists;
        vector<Center*> check;
        if(dNeighbour != nullptr){
            check = findSharedNodes(root, dNeighbour);
            checkLists.push_back(check);
        }

        Center* c1, * c2;
        c1 = c2 = nullptr;

        c1 = root->neighbours.back();
        unsigned size = c1->neighbours.size();
        // find child 1
        for(Center* center : root->neighbours){
            if(runChecks(center, checkLists)){
                if(depth == 1){
                    if(center->neighbours.size() == 3 && !center->inTree){
                        c1 = center; // on the fore last run, a center with exactly 3 connections gets preference
                        break;
                    }
                }
                if(center->neighbours.size() > size && !center->inTree){
                    c1 = center;
                    size = center->neighbours.size();
                }
            }
        }
        c1->inTree = true;

        for(Center* c : root->neighbours){
            if(!c->inTree && runChecks(c,c1->neighbours)){
                c2 = c;
                break;
            }
        }
        if(c2 == nullptr){
            return false;
        }
        size = c2->neighbours.size();
        checkLists.push_back(c1->neighbours);

        // find child 2
        for(Center* center : root->neighbours){
            if(runChecks(center,checkLists)){
                if(depth == 1){
                    if(center->neighbours.size() == 3 && !center->inTree){
                        c2 = center;
                        break;
                    }
                }
                if(center->neighbours.size() > size && !center->inTree){
                    c2 = center;
                    size = center->neighbours.size();
                }
            }
        }
        c2->inTree = true;

        

        if(depth > 0){
            findChildren(c1,c2,depth -1);
            findChildren(c2,c1,depth -1);
        }
        closeBorders(root,c1,c2);
        return true;
    }

    bool  VoronoiDiagram::runChecks(Center* center, vector<vector<Center*>> checkLists){
        if(checkLists.size() == 0) return true;
        for(vector<Center*> list : checkLists){
            for(Center* c : list){
                if(center == c) return false;
            }
        }
        return true;
    }
    bool VoronoiDiagram::runChecks(Center* center, vector<Center*> checkList){
        if(checkList.size() == 0) return true;
        for(Center* c : checkList){
            if(center == c) return false;
        }
        return true;
    }
    void VoronoiDiagram::closeBorders(Center* root, Center* c1, Center* c2){
        for(Edge* edge : root->borders){
            if(edge->d0 == root && edge->d1 == c1 || edge->d1 == root && edge->d0 == c1 || 
                edge->d0 == root && edge->d1 == c2 || edge->d1 == root && edge->d0 == c2){
                    edge->isTraversable = true;
            }else{ 
                edge->isTraversable = false;
            }
        }
    }
    vector<Center*> VoronoiDiagram::findSharedNodes(Center* c1, Center* c2){
        vector<Center*> retval;
        for(Center* c1n : c1->neighbours){
            for(Center* c2n : c2->neighbours){
                if(c2n == c1n) retval.push_back(c2n);
            }
        }
        return retval;
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