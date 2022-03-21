#pragma once


#include "Datalog.h"
#include "Database.h"

using namespace std;

class Interpreter {

private:
    Datalog datalog;
    vector<Predicate> schemeVec;
    vector<Predicate> factVec;
    // vector<Rule> ruleVec; Project 4
    vector<Predicate> queryVec; 
    Database database;

public:
    Interpreter();

    Interpreter(Datalog data) {
        datalog = data;
        schemeVec = data.getSchemeSet();
        factVec = data.getFactSet();
        // ruleVec: Project4
        queryVec = data.getQuerySet();
        
        for(int i = 0; i < (int)schemeVec.size(); ++i){
            string schemeName = schemeVec.at(i).getID();
            vector<Parameter> schemeParams = schemeVec.at(i).getParameter();
            Scheme scheme;
            for(int j = 0; j < (int)schemeParams.size(); ++j){
                string value = schemeParams.at(j).getParaVal();
                scheme.push_back(value);
            }
            Relation newRelation(schemeName, scheme);
            database.insert(pair<string, Relation>(schemeName, newRelation));
        }
        
        for(int i = 0; i < (int)factVec.size(); ++i){
            string factName = factVec.at(i).getID();
            vector<Parameter> factParams = factVec.at(i).getParameter();
            Tuple tuple;
            for(int j = 0; j < (int)factParams.size(); ++j){
                string value = factParams.at(j).getParaVal();
                tuple.push_back(value);
            }
            (database.at(factName)).addTuple(tuple);
        }
    };


    Relation evalQuery(Predicate myQuery) {
        string queryName = myQuery.getID();
        Relation myRelation = database.at(queryName);
        vector<Parameter> queryParams = myQuery.getParameter();
        vector<int> positions;
        vector<string> variableNames;
        map<string, int> variables;
        for(int i = 0; i < (int)queryParams.size(); i++) {
            if(queryParams.at(i).getParaVal().at(0) == '\'') {
                myRelation = myRelation.select(queryParams.at(i).getParaVal(), i, myRelation);
            }
            else {
                map<string, int> :: iterator duplicate = variables.find(queryParams.at(i).getParaVal());
                if(duplicate == variables.end()) {
                    positions.push_back(i);
                    variableNames.push_back(queryParams.at(i).getParaVal());
                    variables.insert(pair<string, int>(queryParams.at(i).getParaVal(), i));
                }
                else {
                    myRelation = myRelation.select(duplicate->second, i, myRelation);
                }
            }
            
        }
        myRelation = myRelation.project(positions, myRelation);
        myRelation = myRelation.rename(variableNames, myRelation);
        
        variables.clear();
        return myRelation;
    };


    void evalQueries() {
        for(int i = 0; i < (int)queryVec.size(); ++i) {
            Relation newRelation = evalQuery(queryVec.at(i));
            cout << queryVec.at(i).getID() << "(" << queryVec.at(i).parameterString() << ")" << "? " << newRelation.toString();
            if(i != (int)queryVec.size()-1) {
                cout << endl;
            }
        }
        cout << endl;
    };
    
};

