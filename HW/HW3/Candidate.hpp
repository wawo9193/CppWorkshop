#ifndef CANDIDATE_HPP
#define CANDIDATE_HPP

class Candidate {
private:
    std::string name_ 
    Party affiliation_
    int id_ 
    static int count_

public:
    Candidate();

    std::string get_name() { return name_; }
    Party get_party() { return affiliation_; }
    int get_id() { return id; }
    
}

#endif
