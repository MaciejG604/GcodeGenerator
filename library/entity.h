#define _CRT_SECURE_NO_WARNINGS

#include "dl_global.h"
#include "dl_creationadapter.h"

#include <string>
#include <vector>


using namespace std;

struct Entity {
    virtual void setData() = 0;
    virtual ~Entity() = default;
};

struct Line : Entity{
    DL_LineData data;
    void setData(const DL_LineData& data) {
        this->data = data;
    }
};


struct Arc : Entity {
    DL_ArcData data;
    void setData(const DL_ArcData &data) {
         this->data = data;
    }
};

struct Circle : Entity {
    DL_CircleData data;
    void setData(const DL_CircleData& data) {
        this->data = data;
    }
};
