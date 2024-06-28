#include "Employee.h"

namespace Records {
Employee::Employee(const std::string& firstName, const std::string& lastName) 
    : //initialize members 
    m_firstName {firstName}, m_lastName {lastName}
// implementation of constructor
{
   
}

Employee::Employee(sql::ResultSet* res)
    : //initialize members 
    m_firstName{ res->getString("firstName")}, m_lastName{ res->getString("lastName") }, m_employeeNumber{res->getInt("employeeNumber")},
    m_salary{ res->getInt("salary")  }, m_hired{res->getBoolean("hired")}
    // implementation of constructor
{ 

}




void Employee::promote(int raiseAmount){
    setSalary(getSalary() + raiseAmount);
}

void Employee::demote(int raiseAmount){
    int newSalary = getSalary() - raiseAmount ;
    setSalary(newSalary <= 0 ? 0 : getSalary() - raiseAmount);
}

void Employee::hire() { m_hired = true; }
void Employee::fire() { m_hired = false; }

void Employee::display() const {
    std::cout << m_firstName << " " << m_lastName << std::endl;
    std::cout<<getEmployeeNumber() << std::endl;
    std::cout << "Salary: " << getSalary() << std::endl;
    std::cout << "Hired: " << (m_hired? "Current Employee" : "Not a current Employee") << std::endl;
}

void Employee::setFirstName(const std::string& firstName) {
    m_firstName = firstName;
}

void Employee::setLastName(const std::string& lastName) {
    m_lastName = lastName;
}

void Employee::setEmployeeNumber(int number) {
    m_employeeNumber = number;
}

void Employee::setSalary(int salary) {
    m_salary = salary;
}

void Employee::setIsHired(bool _isHired) {
    m_hired = _isHired;
}

// Getters definitions
const std::string& Employee::getFirstName() const {
    return m_firstName;
}

const std::string& Employee::getLastName() const {
    return m_lastName;
}

int Employee::getEmployeeNumber() const {
    return m_employeeNumber;
}

int Employee::getSalary() const {
    return m_salary;
}

bool Employee::isHired() const {
    return m_hired;
}


std::string Employee::keystoStringSchema() {
    return "(firstName, lastName, employeeNumber, salary, hired)";

}

std::string Employee::valuestoStringSchema() {
    return "('" + m_firstName+ "', '"+ m_lastName + "' , '" + std::to_string(m_employeeNumber) + "', '" + std::to_string(m_salary) + "', '" + (m_hired ? "1" : "0") + "')";
}

std::string Employee::keysValuestoStringSchema() {
    return "firstName = '" + m_firstName + "', lastName =  '" + m_lastName + "', employeeNumber = " + std::to_string(m_employeeNumber) + ", salary= " + std::to_string(m_salary) + ", hired = " + (m_hired ? "1" : "0") ;
}


//static
std::string  Employee::getSchema() {
    return "firstName varchar(100), lastName varchar(100), employeeNumber int primary key, salary int, hired TINYINT";
}


};