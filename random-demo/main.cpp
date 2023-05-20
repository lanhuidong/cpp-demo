#include <iostream>
#include <random>
#include <ctime>
#include <functional>

const unsigned int Start{1};
const unsigned int End{999};
const unsigned int Iterations {1'000};

int main(int argc, char *argv[]){
    std::random_device rnd;
    std::cout<<"Entropy: "<<rnd.entropy()<<std::endl;
    std::cout<<"Min: "<<rnd.min()<<std::endl;
    std::cout<<"Max: "<<rnd.max()<<std::endl;

    std::random_device seeder;
    const auto seed {seeder.entropy() ? seeder():time(nullptr)};
    std::mt19937 engine{static_cast<std::mt19937::result_type>(seed)};
    std::uniform_int_distribution<int> distribution {Start, End};

    auto generator(std::bind(distribution, engine));
    for(unsigned int i{0}; i<Iterations; i++){
        std::cout<<generator()<<std::endl;
    }

    std::cout<<distribution(engine)<<std::endl;
    return 0;
}