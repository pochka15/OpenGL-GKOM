#pragma once
#include <string>

class Object {
private:
    std::string name_;
public:
    Object(std::string name);

    virtual void render() = 0;
};
