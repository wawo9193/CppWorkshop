#ifndef ELECTION_HPP
#define ELECTION_HPP

class Election {
private:
    std::unordered_map<Party, Candidate> candidates_;
    ElectoralMap electoral_map_
    std::map<Candidate, int> vote_count_
public:
    Election();
    void RegisterCandidate(std::string name, Party p);
    void DirectCampaigns();
    virtual void Vote();
    Candidate GetWinner();
};

class RepresentiveElection : public Election {
public:
    void Vote();
};

#endif
