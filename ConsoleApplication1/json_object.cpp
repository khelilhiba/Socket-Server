#include "json_object.h"


JsonObject::JsonObject()
{
}

JsonObject::JsonObject(string json)
{
	m_JsonBuff = json;
}


JsonObject::~JsonObject()
{
}

void JsonObject::setJsonAttribute(const string attribute,const int value)
{
	Poco::JSON::Parser loParser;
	std::ostringstream out;

	// Parse the JSON and get the Results
	//
	Poco::Dynamic::Var loParsedJson = loParser.parse(m_JsonBuff);
	Poco::Dynamic::Var loParsedJsonResult = loParser.result();

	// Get the JSON Object
	//
	Poco::JSON::Object::Ptr loJsonObject = loParsedJsonResult.extract<Poco::JSON::Object::Ptr>();
	loJsonObject->set(attribute, value);

	loJsonObject->stringify(out);

	m_JsonBuff = std::string(out.str());	
}

string JsonObject::change_attr_value(const string attribute)
{
	Poco::JSON::Parser loParser;
	std::ostringstream out;
	int value = rand() % 2;
	int value1 = rand() % 2;
	int value2 = rand() % 2;
	int value3 = rand() % 2;
	int value4 = rand() % 2;
	int value5 = rand() % 2;
	int value6 = rand() % 8;
	int value7 = rand() % 2;

	// Parse the JSON and get the Results
	//
	Poco::Dynamic::Var loParsedJson = loParser.parse(attribute);
	Poco::Dynamic::Var loParsedJsonResult = loParser.result();

	// Get the JSON Object
	//
	Poco::JSON::Object::Ptr loJsonObject = loParsedJsonResult.extract<Poco::JSON::Object::Ptr>();
	loJsonObject->set("h_acceleration", value);
	loJsonObject->set("h_deceleration", value1);
	loJsonObject->set("rh_cornening", value2);
	loJsonObject->set("lh_cornening", value3);
	loJsonObject->set("excess_speed", value4);
	loJsonObject->set("excess_idle", value5);
	loJsonObject->set("gauge", value6);
	loJsonObject->set("excess_rpm", value7);
	
	loJsonObject->stringify(out);

	m_JsonBuff = std::string(out.str());

	//std::cout << "m_JsonBuff " << m_JsonBuff << endl;
	return(m_JsonBuff);
}
