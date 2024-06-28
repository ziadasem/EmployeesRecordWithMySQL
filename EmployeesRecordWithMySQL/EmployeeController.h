#pragma once
#include <iostream>
#include <vector>
#include "Employee.h"
#include "DBConector.h"


namespace Records {
    const int firsEmployeeNum {100};
    class EmployeeController {
        public:
            EmployeeController();
            Employee& addEmployee(const std::string firstName, const std::string lastName);
            Employee& getEmployee(const std::string& firstName, const std::string& lastName);
            Employee& getEmployee(int employeeNumber);
            void fireEmployee(int employeeNumber);
            void promotEmployee(int employeeNumber, int raiseAmount);
            Employee& getEmployeeFromDB(int employeeNumber);
            void displayAll() const;
            void displayCurrent() const;
            void displayPast() const;

        
        private:
            std::vector<Employee> m_employees ;
            int m_nextEmployeeNum; 
            DBConector dbConnector ;

            void fillEmployees();
            int getNextEmployeeNum();

    };
}