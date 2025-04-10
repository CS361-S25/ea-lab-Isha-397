#include <iostream>
#include "Empirical/include/emp/math/Random.hpp"

class Organism {
    public: 
        double behavior;
        
        Organism (double b = 0 ) : behavior(b) {};

        void mutate(emp::Random random) {
            behavior += random.GetRandNormal(0.0, 0.02);
            // random.GetRandNormal(0.0, 0.02);
        }

        Organism* reproduce(emp::Random random) {
            // return new Organism(this->behavior);
            Organism* offspring = new Organism(behavior);
            offspring->mutate(random);
            return offspring;
        }

        
};

int main() {
    emp:: vector<Organism> population;
    emp:: Random random = *new emp::Random(1);

    // initializing populaiton with 100 organisms with the same behavior
    for (int i = 0; i < 100; i++) {
        population.push_back(*new Organism(0.5));
        population[i].mutate(random);
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

        Organism& best_org = population[0]; 
        for (Organism org : population) {
            if(org.behavior > best_org.behavior){
                best_org = org;
            }
        }

        Organism* new_org = best_org.reproduce(random);

        population[0] = *new_org; 

        size_t overwrite = random.GetUInt(0,100);
        population[overwrite] = *new_org;
        // delete new_org;

    }

    // std :: cout << "population size after updates " << population.size() << std::endl;
    

    Organism* best = &population[0];
    for (Organism org : population) {
        if (org.behavior > best->behavior) {
            best = &org;
        }
    }

    std::cout << "Max behavior after evolution: " << best->behavior << std::endl;
    std::cout << "Final population size: " << population.size() << std::endl;

    return 0;
    

}