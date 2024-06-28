#include "EmployeeController.h"

int displayMenu();
void doHire(Records::EmployeeController& db);
void doFire(Records::EmployeeController& db);
void doPromote(Records::EmployeeController& db);

int main()
{
    try {
        Records::EmployeeController employeeController;
        bool done{false};
        while (!done) {
            int selection { displayMenu() };
            switch (selection) {
            case 0://exit
                done = true;
                break;
            case 1:
                doHire(employeeController);
                break;
            case 2:
                doFire(employeeController);
                break;
            case 3:
                doPromote(employeeController);
                break;
            case 4:
                employeeController.displayAll();
                break;
            case 5:
                employeeController.displayCurrent();
                break;
            case 6:
                employeeController.displayPast();
                break;
            default:
                std::cerr<<"Unknown command.\n";
                break;
            }
        }

    }
    catch (sql::SQLException& e) {
        std::cerr << "Can't init DB Controller " << e.what() << std::endl;
        return -1;
    }
    
}


//print to the console the available options
//returns the selected option
int displayMenu()
{
    int selection;
    std::cout<<"Employee Database\n";
    std::cout<<"-----------------\n";
    std::cout<<("1) Hire a new employee\n");
    std::cout<<("2) Fire an employee\n");
    std::cout<<("3) Promote an employee\n");
    std::cout<<("4) List all employees\n");
    std::cout<<("5) List all current employees\n");
    std::cout<<("6) List all former employees\n");
    std::cout<<("0) Quit\n");
    std::cout<<("---> \n");
    std::cin >> selection;
    return selection;
}

//take from the user the first and last name of the employee
// add a new employee to the database
void doHire(Records::EmployeeController& db)
{
    try {
        std::string firstName;
        std::string lastName;
        std::cout << ("First name? ");
        std::cin >> firstName;
        std::cout << ("Last name? ");
        std::cin >> lastName;
        auto& employee{ db.addEmployee(firstName, lastName) };
        std::cout << "Hired employee " << firstName << " " << lastName << " with employee number " << employee.getEmployeeNumber() << ". \n";
    }
    catch (const sql::SQLException& exception) {
        std::cerr << "Unable to add employee: " << exception.what() << std::endl;
    }

}

//get from the user a employee number, assuming that the user will enter a number
//set isHired tp false to an employee in Database 
void doFire(Records::EmployeeController& db)
{
    int employeeNumber;
    std::cout<<("Employee number? \n");
    std::cin >> employeeNumber;
    try {
        db.fireEmployee(employeeNumber);
        std::cout<<"Employee "<<employeeNumber<<" terminated.\n";
    } catch (const std::logic_error& exception) {
      std::cerr<< "Unable to terminate employee: "<<exception.what()<<std::endl;
    }catch (const sql::SQLException& exception) {
        std::cerr << "Unable to terminate employee: " << exception.what() << std::endl;
    }
}
//takes an employee number and the required raise amount
//updates an employee salary in the database
void doPromote(Records::EmployeeController& db)
{
    int employeeNumber;
    std::cout<<"Employee number? \n";
    std::cin >> employeeNumber;
    int raiseAmount;
    std::cout<<"How much of a raise? \n";
    std::cin >> raiseAmount;
    try {
        db.promotEmployee(employeeNumber, raiseAmount);
    } catch (const std::logic_error& exception) {
        std::cerr<<"Unable to promote employee: "<< exception.what() << std::endl;
    }
    catch (const sql::SQLException& exception) {
        std::cerr << "Unable to promote employee: " << exception.what() << std::endl;
    }
}