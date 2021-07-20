#pragma once
struct Vertex{
    int value;
    int weight;
    Vertex *next;
    Vertex(int value, int weight,Vertex *next=nullptr):value(value),weight(weight),next(next){}
};
