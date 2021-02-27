#ifndef EARTH_H
#define EARTH_H


class Earth {
public:
	std::string public_var_ = "Hello Earth";

	static Earth& GetInstance() {
		// gets instantiated the first time
		static Earth instance; // guaranteed to be destroyed

		return instance;
	}

    int get_population() { return population_; };

    void IncreasePopulation() { population_ += 1; };

	// Delete the methods we don't want
	Earth(Earth const&) = delete; // copy constructor
	void operator=(Earth const&) = delete; // assignment operator

 private:
 	Earth();  // private constructor

    int population_;
  
};  // class Earth

#endif  // EARTH_H

