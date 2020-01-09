#include "Scene.h"
#include "Camera.h"
#include "tmp/Triangle.h"

Scene::Scene() {
    // TODO (@pochka15): Think about when and how to delete this object
    Camera *camera = new Camera(); 
    Triangle *triangle = new Triangle();
}