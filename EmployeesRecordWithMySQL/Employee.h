#pragma once
#include <iostream>
#include <cppconn/statement.h>
#include"DBTable.h"

namespace Records {
    const int DefaultStartingSalary { 30'000 };
    const int DefaultRaiseAndDemeritAmount { 1'000 };

    class Employee : public DBTable {
        public:
            Employee(const std::string& firstName,const std::string& lastName);
            Employee(sql::ResultSet* res);
            void promote(int raiseAmount = DefaultRaiseAndDemeritAmount);
            void demote(int demeritAmount = DefaultRaiseAndDemeritAmount);
            void hire(); // Hires or rehires the employee
            void fire(); // Dismisses the employee
            void display() const; // Prints employee info to console
            // Getters and setters
            void setFirstName(const std::string& firstName);
            const std::string& getFirstName() const;
            void setLastName(const std::string& lastName);
            const std::string& getLastName() const;
            void setEmployeeNumber(int employeeNumber);
            int getEmployeeNumber() const;
            void setSalary(int newSalary);
            int getSalary() const;
            bool isHired() const;
            void setIsHired(bool);
            void setDbKeysWithValues();

            std::string keystoStringSchema();
            std::string valuestoStringSchema();
            std::string keysValuestoStringSchema();

            static std::string getSchema();
            
           
        private:
            std::string m_firstName;
            std::string m_lastName;
            int m_employeeNumber { -1 };
            int m_salary { DefaultStartingSalary };
            bool m_hired { false };

    };
};