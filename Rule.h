# pragma once
# include "Predicate.h"

class Rule {
    private:
        vector<Predicate> rule_set;
        vector<Rule> rule_list;

    public:
        // void setRulePred(Predicate pred) {
        //     rulePred = pred;
        // }

        // Predicate getRulePred() {
        //     return rulePred;
        // }

        void addRule(Predicate pre) {
            rule_set.push_back(pre);
        }

        vector<Predicate>& getRuleSet() {
            return rule_set;
        }

        void addRuleVec(Rule r) {
            rule_list.push_back(r);
        }

        string ruleString() {
            stringstream ss;
            ss << "Rules" << "(" << rule_list.size() << ")" << ":\n";
            for(unsigned i = 0; i < rule_list.size(); i++) {
                ss << "  " << rule_list.at(i).rule_set.at(0).getID()  << "(" 
                << rule_list.at(i).rule_set.at(0).parameterString() << ") :- ";
                for (unsigned j = 1; j < rule_list.at(i).rule_set.size(); j++) {
                    ss << rule_list.at(i).rule_set.at(j).getID() << "(" 
                    << rule_list.at(i).rule_set.at(j).parameterString() << ")";
                    if(j != rule_list.at(i).rule_set.size() - 1) {
                    ss << ",";
                    }
                }
                ss << ".\n";
            }


            return ss.str();
        }

        
};