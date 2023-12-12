#include <iostream>
#include <vector>

class Animal {
protected:
    std::string name;
    std::string species;

public:
    Animal(const std::string& name, const std::string& species) : name(name), species(species) {}

    virtual void display() const {
        std::cout << "Name: " << name << ", Species: " << species << std::endl;
    }
    const std::string& getName() {
        return name;
    }
    const std::string& getSpecies() {
        return species;
    }
    virtual void setNew(const std::string& newName, const std::string& newSpecies) {
        name = newName;
        species = newSpecies;
    }
};

class Bird : public Animal {
private:
    int wingspan;

public:
    Bird(const std::string& name, const std::string& species, int wingspan)
        : Animal(name, species), wingspan(wingspan) {}

    void display() const override {
        std::cout << "Name: " << name << ", Species: " << species << ", Wingspan: " << wingspan << "cm" << std::endl;
    }
    void setNew(const std::string& newName, const std::string& newSpecies) override {
        ElectronicDevice::setNew(newName, newSpecies);
        this->wingspan *= 2;
    }
};

class Mammal : public Animal {
private:
    std::string furType;

public:
    Mammal(const std::string& name, const std::string& species, const std::string& furType)
        : Animal(name, species), furType(furType) {}

    void display() const override {
        std::cout << "Name: " << name << ", Species: " << species << ", Fur Type: " << furType << std::endl;
    }
    void setNew(const std::string& newName, const std::string& newSpecies) override {
        ElectronicDevice::setNew(newName, newSpecies);
        this->furType = "Long";
    }
};

void modifyAnimal(Animals* animal) {
    animal->setNew(("Updated " + animal->getName(), animal->getSpecies());
}

int main() {
    std::vector<Animal*> animals;
    animals.push_back(new Bird("Eagle", "Bird of Prey", 200));
    animals.push_back(new Mammal("Tiger", "Big Cat", "Short"));

    for (const auto& animal : animals) {
        animal->display();
    }
    for (const auto& animal : animals) {
        animal->modifyAnimal();
    }
    for (const auto& animal : animals) {
        animal->display();
    }
    for (auto animal : animals) {
        delete animal;
        animal = nullptr;
    }

    return 0;
}