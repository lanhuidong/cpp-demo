#include "person.h"

class Person::Impl {
    public:
        Impl(std::string name);
        ~Impl() = default;
        void setName(std::string name);
        const std::string& getName() const;

    private:
        std::string m_name;

};

Person::Impl::Impl(std::string name) : m_name{name} {
}

void Person::Impl::setName(std::string name) {
    m_name = name;
}

const std::string& Person::Impl::getName() const{
    return m_name;
}

Person::Person(std::string name) {
    m_impl = std::make_unique<Impl>(name);
}

Person::~Person() = default;

void Person::setName(std::string name){
    m_impl->setName(name);
}

const std::string& Person::getName() const {
    return m_impl->getName();
}