using namespace std;

class Animal {
    public:
        Animal (string sound) : sound_(sound) {}
        string MakeSound() { return sound_; }
        virtual int GetPower() { return 0; }

    private:
        string sound_;

};