#pragma once

#include "Relation.h"
#include <map>


using namespace std;

class Database : public map<string, Relation> {

public:
    Database() {}
    
};