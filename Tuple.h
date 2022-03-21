#pragma once


#include "Scheme.h"

using namespace std;

class Tuple : public vector<string> {

 public:

  Tuple(vector<string> values) : vector<string>(values) { }
  Tuple() {}

};