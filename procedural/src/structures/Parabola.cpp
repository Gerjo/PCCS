#include "Parabola.h"

namespace PGC{
    Parabola::Parabola():site(0),isLeaf(false),cEvent(0),edge(0),parent(0){

    }
    Parabola::Parabola(VPoint* p): cEvent(0),edge(0),parent(0){
        site = p;
        isLeaf = true;
    }
    void Parabola::setLeft(Parabola* p){
        _left = p;
        p->parent = this;
    }
    void Parabola::setRight(Parabola* p){
        _right = p;
        p->parent = this;
    }
    Parabola* Parabola::left(){
        return _left;
    }
    Parabola* Parabola::right(){
        return _right;
    }
    Parabola* Parabola::getLeft(Parabola* p){
        return(getLeftChild(getLeftParent(p)));
    }
    Parabola* Parabola::getRight(Parabola* p){
        return(getRightChild(getRightParent(p)));
    }
    Parabola* Parabola::getLeftParent(Parabola* p){
        Parabola* par = p->parent;
        Parabola* last = p;

        while(par->left() == last){
            if(!par->parent) return 0;
            last = par;
            par = par->parent;
        }
        return par;
    }
    Parabola* Parabola::getRightParent(Parabola* p){
        Parabola* par = p->parent;
        Parabola* last = p;

        while(par->right() == last){
            if(!par->parent) return 0;
            last = par;
            par = par->parent;
        }
        return par;
    }
    Parabola* Parabola::getLeftChild(Parabola* p){
        if(!p) return 0;
        Parabola* par = p->left();
        while(!par->isLeaf) par = par->right();
        return par;
    }
    Parabola* Parabola::getRightChild(Parabola* p){
        if(!p) return 0;
        Parabola* par = p->right();
        while(!par->isLeaf) par = par->left();
        return par;
    }

}