#include "DBConector.h"
#define _DEBUG 0

inline std::string expandConditionStatment(std::initializer_list<std::string> idLabels, std::initializer_list<std::string> idValues) {
	
	if (idLabels.size() == 0 || idValues.size() == 0) {
		return "";
	}

	std::string condition = "";
	for (int i = 0; i < idLabels.size() && i < idValues.size(); i++) {
		condition += "`" + idLabels.begin()[i] + "` = '" + idValues.begin()[i] + "' and";
	}
	if (condition.length() > 3) {
		condition = condition.substr(0, condition.length() - 3); //remove trailing and
	}
	return " Where "+ condition;
}

inline void printSQLQuery(std::string query) {
	#if _DEBUG == 1
	std::cout << query << std::endl;
	#endif
}


DBConector::DBConector(std::string _dbAddress,  std::string _username,
				std::string _password,  std::string _dbName, std::string _initalTableName,
				std::string _schema ):
		dbAddress {_dbAddress}, username{ _username }, password{ _password }, dbName{_dbName}, 
	currentTableName{ _initalTableName }, schema{ _schema }
	{
	try {
		connectToDBService();
		createDB();
		createTable(currentTableName);
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQL Error: " << e.what() << std::endl;
		throw e;
	}
}

//PRE: the program isnot connected to DB Service
//POST: the program is connected to the DB with the provided credentials
//Requires: MySQL Service is running
void DBConector::connectToDBService() {
	driver = sql::mysql::get_mysql_driver_instance() ;
	con = driver->connect(dbAddress, username, password);
	
}


//PRE: the required database isn't confirmed to be exists
//POST: the required database will exisits without duplicates or removing existing one
//Requires: MySQL Service is running
void DBConector::createDB() {

	std::unique_ptr<sql::Statement> stmt{ con->createStatement() };
	printSQLQuery("create database if not exists " + dbName);
	stmt->execute("create database if not exists " + dbName);
	con->setSchema(dbName); // set the default db to work against
	
}


//PRE: the required table isn't confirmed to be exists
//POST: the required table will exisits without duplicates or removing existing one
//Requires: the connection is set to an existing schema
void DBConector::createTable(std::string tableName) {
	sql::Statement* stmt;
	stmt = con->createStatement();

	// SQL query to create a table 
	std::string createTableSQL
		{ "CREATE TABLE IF NOT EXISTS " + tableName +  " (" 
		+ schema 
		+ ") "};
	printSQLQuery(createTableSQL);
	stmt->execute(createTableSQL);
	delete stmt;

}


DBConector::~DBConector() {
	delete con;
	delete driver;
}



void DBConector::addRecord(DBTable* record, std::string tableName ) {
	if (tableName.compare("") == 0 ) {
		tableName = this->currentTableName;
	}
	std::unique_ptr<sql::Statement> stmt { con->createStatement() };
	printSQLQuery("Insert into " + tableName + +" Values " + record->valuestoStringSchema());
	stmt->execute("Insert into " + tableName + +" Values " +  record->valuestoStringSchema());

}
sql::ResultSet* DBConector::getRecord(std::initializer_list<std::string> idLabel , std::initializer_list<std::string>  idValue, std::string tableName) {
	if (tableName == "") {
		tableName = currentTableName;
	}
	std::unique_ptr<sql::Statement> stmt{ con->createStatement()};
	printSQLQuery("select * from " + tableName + expandConditionStatment(idLabel, idValue));
	return
		stmt->executeQuery("select * from " + tableName + expandConditionStatment(idLabel, idValue));
}
void DBConector::updateRecord(std::initializer_list<std::string> idLabel, std::initializer_list<std::string> idValue,  DBTable* record, std::string tableName) {
	if (tableName.compare("") == 0) {
		tableName = this->currentTableName;
	}
	std::unique_ptr<sql::Statement> stmt{ con->createStatement() };
	printSQLQuery("Update  " + tableName + " SET " + record->keysValuestoStringSchema() + expandConditionStatment(idLabel, idValue));
	stmt->execute("Update  " + tableName + " SET " + record->keysValuestoStringSchema() + expandConditionStatment(idLabel, idValue));
}
void DBConector::deleteRecord(std::initializer_list<std::string> idLabel, std::initializer_list<std::string> idValue, std::string tableName) {
	if (tableName.compare("") == 0) {
		tableName = this->currentTableName;
	}
	std::unique_ptr<sql::Statement> stmt{ con->createStatement() };
	stmt->execute("delete from  " + tableName + expandConditionStatment(idLabel, idValue) ) ;
}
sql::ResultSet* DBConector::getRecordWithAggregateFunction( std::string aggregateFuncion, std::string columnName , std::string tableName) {
	if (tableName == "") {
		tableName = currentTableName;
	}
	std::unique_ptr<sql::Statement> stmt{ con->createStatement() };
	printSQLQuery("select " + aggregateFuncion + "(`" + columnName + "`) as `" + columnName + "` from " + tableName);
	return
		stmt->executeQuery("select " + aggregateFuncion + "(`" + columnName + "`) as `" + columnName +  "` from " + tableName);

}


