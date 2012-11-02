#include "Crate.h"

Crate::Crate(){

}
void Crate::toData(Data& data){
    GameObject::toData(data);
    //data("content") = _content;
}

void Crate::fromData(Data& data){

}