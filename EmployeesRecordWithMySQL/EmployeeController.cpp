#include "EmployeeController.h"

namespace Records {

    EmployeeController::EmployeeController()
    :dbConnector { DBConector("tcp://localhost:3306", "root", "admin", "employeesDB", "employees",Employee::getSchema())}
    {
        fillEmployees();
        m_nextEmployeeNum =  getNextEmployeeNum();
    }

    void EmployeeController::fillEmployees() {
        sql::ResultSet* res =  dbConnector.getRecord({}, {}); //get all
       m_employees.clear();
       while (res->next()) {
           Employee e{ res };
           m_employees.push_back(e);

       }
    }

    int EmployeeController::getNextEmployeeNum() {
        int result{ firsEmployeeNum };
        sql::ResultSet* res = dbConnector.getRecordWithAggregateFunction("MAX", "employeeNumber");
        if (res->next()) {
            result = res->getInt("employeeNumber");
        }
            
        return result + 1;
    }
    
    Employee& EmployeeController::addEmployee(const std::string firstName, const std::string lastName){
        Employee e {firstName, lastName};
        e.setEmployeeNumber(m_nextEmployeeNum++);
        e.hire();
        m_employees.push_back(e);
        dbConnector.addRecord(&e);
        return m_employees.back(); 
    }

    Employee& EmployeeController::getEmployee(const std::string& firstName, const std::string& lastName) {

        for (auto& employee : m_employees){
            if (employee.getFirstName() == firstName && employee.getLastName() == lastName){
                return employee;
            }
        }
        Employee e( dbConnector.getRecord({"firstName", "lastName"}, { firstName , lastName }) );
        throw std::logic_error("Employee not found");
    }

    Employee& EmployeeController::getEmployee(int employeeNumber) {
        for (auto& employee : m_employees){
            if (employee.getEmployeeNumber() == employeeNumber){
                return employee;
            }
        }
        sql::ResultSet* res = dbConnector.getRecord({ "employeeNumber" }, { std::to_string(employeeNumber) });
        if (res->next()) {
            m_employees.push_back(Employee{ res });
            return m_employees.back();
        }
       
        
        throw std::logic_error("Employee not found");
    }

    void EmployeeController::promotEmployee(int employeeNumber, int raiseAmount) {
        Employee& employee = getEmployee(employeeNumber);
        employee.promote(raiseAmount);
        dbConnector.updateRecord({ "employeeNumber" }, { std::to_string(employee.getEmployeeNumber()) }, &employee);
    }

    void EmployeeController::fireEmployee(int employeeNumber) {
        Employee& employee = getEmployee(employeeNumber);
        employee.fire();
        dbConnector.updateRecord({ "employeeNumber" }, { std::to_string(employee.getEmployeeNumber()) }, &employee);
    }



    void EmployeeController::displayAll() const{
        for (auto& employee : m_employees){
            employee.display();
        }
    }

    void EmployeeController::displayCurrent() const{
        for (auto& employee : m_employees){
            if (employee.isHired()){
                employee.display();
            }
        }
    }

    void EmployeeController::displayPast() const{
        for (auto& employee : m_employees){
            if (!employee.isHired()){
                employee.display();
            }
        }
    }
        
       
}