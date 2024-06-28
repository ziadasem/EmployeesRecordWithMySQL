#pragma once
#include <cppconn/driver.h> 
#include <cppconn/exception.h> 
#include <cppconn/statement.h> 
#include <iostream> 
#include <mysql_connection.h> 
#include <mysql_driver.h> 
#include "DBTable.h"
#include "Employee.h"

class DBConector
{

	public:
		DBConector(std::string _dbAddress, std::string _username, std::string _password, std::string _dbName, std::string _tableName, std::string _schema);
		~DBConector();
		//CRUD
		void addRecord(DBTable* record, std::string tableName = "");
		sql::ResultSet* getRecord(std::initializer_list<std::string> idLabel, std::initializer_list<std::string> idValue, std::string tableName = "");
		void updateRecord(std::initializer_list<std::string> idLabel, std::initializer_list<std::string> idValue, DBTable* record, std::string tableName = "");
		void deleteRecord(std::initializer_list<std::string> idLabel, std::initializer_list<std::string> idValue, std::string tableName = "");
		sql::ResultSet* getRecordWithAggregateFunction(std::string aggregateFunction, std::string columnName, std::string tableName = "");

	private:
		const std::string dbAddress {"tcp://localhost:3306"};
		const std::string username{ "root" };
		const std::string password{ "admin" };

		const std::string dbName;
		const std::string schema;
		
		std::string currentTableName;


		sql::mysql::MySQL_Driver* driver;
		sql::Connection* con;


		void connectToDBService();
		void createDB();
		void createTable(std::string);
};

