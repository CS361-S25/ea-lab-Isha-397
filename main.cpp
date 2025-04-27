#include <iostream>
#include "Empirical/include/emp/math/Random.hpp"

class Creature {
public:
    double behavior_value;

    Creature(double b = 0.0) : behavior_value(b) {}

    void Mutate(emp::Random& rng) {
        behavior_value += rng.GetRandNormal(0.0, 0.02);
    }

    Creature* MakeOffspring(emp::Random& rng) {
        Creature* offspring = new Creature(behavior_value);
        offspring->Mutate(rng);
        return offspring;
    }
};

int main() {
    emp::vector<Creature> creatures;
    emp::Random rng(1);

    // Fill the population
    for (size_t idx = 0; idx < 100; ++idx) {
        Creature temp(0.5);
        temp.Mutate(rng);
        creatures.push_back(temp);
    }

    // Evolution over 100 updates
    for (size_t gen = 0; gen < 100; ++gen) {
        Creature* top_creature = &creatures[0];
        for (Creature& c : creatures) {
            if (c.behavior_value > top_creature->behavior_value) {
                top_creature = &c;
            }
        }

        Creature* offspring = top_creature->MakeOffspring(rng);
        creatures[0] = *offspring;

        size_t idx_to_replace = rng.GetUInt(creatures.size());
        creatures[idx_to_replace] = *offspring;

        delete offspring; // Avoid memory leak
    }

    // Find the final best creature
    Creature* best = &creatures[0];
    for (Creature& c : creatures) {
        if (c.behavior_value > best->behavior_value) {
            best = &c;
        }
    }

    std::cout << "Highest behavior: " << best->behavior_value << std::endl;
    std::cout << "Population size: " << creatures.size() << std::endl;

    return 0;
}
