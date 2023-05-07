#pragma once
#include <string>
#include <memory>

class Person {
    public:
        explicit Person(std::string name);
        ~Person();

        void setName(std::string name);
        const std::string& getName() const;

    private:
        class Impl;
        std::unique_ptr<Impl> m_impl;
};