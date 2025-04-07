#include <iostream>
#include "Empirical/include/emp/math/Random.hpp"

class Organism {
    public: 
        double behavior;
        
        Organism (double b) : behavior(b) {};

        Organism* reproduce() {
            return new Organism(this->behavior);
        }
    
};

int main() {
    emp:: vector<Organism> population;

    // initializing populaiton with 100 organisms with the same behavior
    for (int i = 0; i < 100; i++) {
        population.push_back(*new Organism(0.5));
        //std :: cout << "Behavior of Organism 9:" << population[9].behavior << std::endl;
    }

    // Organism* parent = &population[9];
    // Organism* child = parent->reproduce();

    // std::cout << "Parent address: " << parent << ", Behavior: " << parent->behavior << std::endl;
    // std::cout << "Child  address: " << child << ", Behavior: " << child->behavior << std::endl;

    // delete child;

    // return 0;

    //100 updates
    for (int update = 0; update < 100; update++ ){

        Organism* best_org = &population[0]; 
        for (Organism& org : population) {
            if(org.behavior > best_org->behavior){
                best_org = &org;
            }
        }

        Organism* new_org = best_org->reproduce();

        population[0] = *new_org; 

        delete new_org;
    }

    std :: cout << "population size after updates " << population.size() << std::endl;
    
}