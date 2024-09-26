/*
 In this exercise we define a Person class that simply holds a person’s name and prints it when needed.
 We derive a Spy class from Person and add member function that can be used to set an alias for the spy.
 Use the following definition for Person class.

class Person {
public:
    Person(const char *name = "nobody");
    virtual ~Person() = default;
    virtual void identity() const;
    virtual void interrogate();
private:
    std::string name;
};

int main(int argc, char **argv) {
    Person agent("James Bond");
    Spy spy("Emilio Largo", "William Johnson", 3);
    Spy spy2("Ernst Blofield", "John Keats", 5);

    std::cout << std::endl << "Nice to meet you. ";
    agent.identity();

    for (int i = 0; i < 6; ++i) {
        std::cout << "Who are you?" << std::endl;
        spy.interrogate();
        spy.identity();
    }
    spy.set_identity("Bill Munny");
    spy.identity();

    std::cout << std::endl << "Nice to meet you. ";
    agent.identity();

    for (int i = 0; i < 6; ++i) {
        std::cout << "Who are you?" << std::endl;
        spy2.interrogate();
        spy2.identity();
    }

    return 0;
}

Example output:
Nice to meet you. My name is: James Bond
Who are you?
My name is: William Johnson
Who are you?
My name is: William Johnson
Who are you?
My name is: Emilio Largo
My alias is: William Johnson
Who are you?
My name is: Emilio Largo
My alias is: William Johnson
Who are you?
My name is: Emilio Largo
My alias is: William Johnson
Who are you?
My name is: Emilio Largo
My alias is: William Johnson
My name is: Emilio Largo
My alias is: Bill Munny
Nice to meet you. My name is: James Bond
Who are you?
My name is: John Keats
Who are you?
My name is: John Keats
Who are you?
My name is: John Keats
Who are you?
My name is: John Keats
Who are you?
My name is: Ernst Blofield
My alias is: John Keats
Who are you?
My name is: Ernst Blofield
My alias is: John Keats
 */

#include <iostream>
#include <string>

class Person {
public:
    explicit Person(const char *name = "nobody");
    virtual ~Person() = default;
    virtual void identity() const;
    virtual void interrogate();
protected:
    std::string name;
};

class Spy final : public Person {
public:
    Spy(const char *name, const char *alias, int lie_limit);
    void set_identity(const char *new_alias);
    void identity() const override;
    void interrogate() override;
private:
    std::string alias;
    int lie_limit;
    int interrogations;
};

int main(int argc, char **argv) {
    Person agent("James Bond");
    Spy spy("Emilio Largo", "William Johnson", 3);
    Spy spy2("Ernst Blofield", "John Keats", 5);

    std::cout << std::endl << "Nice to meet you. ";
    agent.identity();

    for (int i = 0; i < 6; ++i) {
        std::cout << "Who are you?" << std::endl;
        spy.interrogate();
        spy.identity();
    }
    spy.set_identity("Bill Munny");
    spy.identity();

    std::cout << std::endl << "Nice to meet you. ";
    agent.identity();

    for (int i = 0; i < 6; ++i) {
        std::cout << "Who are you?" << std::endl;
        spy2.interrogate();
        spy2.identity();
    }

    return 0;
}

Person::Person(const char *name) : name(name) {
}

void Person::identity() const {
    std::cout << "My name is: " << name << std::endl;
}

void Person::interrogate() {
}

Spy::Spy(const char *name, const char *alias, const int lie_limit) : Person(name), alias(alias), lie_limit(lie_limit), interrogations(0) {
}

void Spy::set_identity(const char *new_alias) {
    alias = new_alias;
}

void Spy::identity() const {
    // Check if the spy is still allowed to lie
    if (interrogations < lie_limit) {
        std::cout << "My name is: " << alias << std::endl;
    } else {
        std::cout << "My name is: " << name << std::endl;
        std::cout << "My alias is: " << alias << std::endl;
    }
}


void Spy::interrogate() {
    interrogations++;
}