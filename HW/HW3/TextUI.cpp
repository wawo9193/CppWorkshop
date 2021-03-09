#include "TextUI.hpp"

void TextUI::UI() {
    for 
}



std::string TextUI::Register() {
    Election e;
    std::string election_type;
    std::cout << "What kind of election should we have (direct or representative, 0 to stop)?" << std::endl;
    cin >> election_type;

    if (election_type=="direct") {
        &e = new Election();
    } else if (election_type=="representative") {
        &e = new RepresentiveElection();
    } else {
        return "0";
    }

    std::map<std::string, Party> party_map = {
        {"1", Party::Democratic},
        {"2", Party::Republican},
        {"3", Party::Green},
        {"4", Party::Libertarian},
        {"5", Party::None}
    };

    for (auto p : party_map) {
        std::string input = "";

        while (input!="6") {
            std::cout << "Please enter your option for which party to register the candidate with" << std::endl;
            std::cout << "Enter \'1\' for Democratic" << std::endl;
            std::cout << "Enter \'2\' for Republican" << std::endl;
            std::cout << "Enter \'3\' for Green" << std::endl;
            std::cout << "Enter \'4\' for Libertarian" << std::endl;
            std::cout << "Enter \'5\' for Independent" << std::endl;
            std::cout << "Enter \'6\' or other key to exit" << std::endl;
            std::cin >> input;

            if (party_map.find(input)==party_map.end()) {
                std::cout << "Exiting..." << std::endl;
                input = "6";
            } else {
                std::string name;
                std::cout << "Please enter the name of the candidate" << std::endl;
                cin >> name;
                e->RegisterCandidate(name, party_map[input]);
            }
        }
    }
    // TODO 
    // 1: Spongebob [Party: one]
    // 2: Patrick [Party: two]
}

