#pragma once
#include <string>
#include <map>

class DBTable {

public :

	virtual std::string keystoStringSchema() = 0;
	virtual std::string valuestoStringSchema() = 0;
	virtual std::string keysValuestoStringSchema() = 0;

	
};