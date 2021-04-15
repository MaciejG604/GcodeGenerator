#define _CRT_SECURE_NO_WARNINGS

#include "dl_global.h"
#include "dl_creationadapter.h"

#include <string>
#include <vector>


using namespace std;

struct Entity {
    virtual void setData();
    virtual void add();
    vector <Entity*> path;

};

struct Line : Entity, DL_LineData{
    DL_LineData data;
    void setData(const DL_LineData& data) {
        this->data = data;
    }
    void add() {
        path.push_back(this);
    };
};


struct Arc : Entity {
    DL_ArcData data;
        void setData(const DL_ArcData &data) {
            this->data = data;
        }
    void add() {
        path.push_back(this);
    };
};

struct Circle : Entity {
    DL_ArcData data;
    void setData(const DL_ArcData& data) {
        this->data = data;
    }
    void add() {
        path.push_back(this);
    };
};