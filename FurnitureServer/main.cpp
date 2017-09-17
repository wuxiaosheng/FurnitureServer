#include <iostream>
#include "EventDispatcher.h"
#include "CCValue.h"
#include "ThreadManager.h"
#pragma comment(lib,"ws2_32.lib")
#include "ServerManager.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

unsigned int getLength(std::string &str)
{
	std::string sLength = str.substr(0, 4);
	str.erase(0, 4);

	for (int i = 0; i < sLength.size(); ++i)
	{
		sLength[i] ^= 0xff;
	}

	return *((unsigned int *)sLength.c_str());

}

void addLength(std::string &str, unsigned int length)
{
	std::string sLength = "";
	sLength.assign((char *)&length);

	for (int i = sLength.size(); i < sizeof(unsigned int); ++i)
	{
		sLength += '\0';
	}

	for (int i = 0; i < sLength.size(); ++i)
	{
		sLength[i] ^= 0xff;
	}
	str = sLength + str;
}

void encode(std::string &str, std::string key)
{
	for (int i = 0; i < str.size(); ++i)
	{
		str[i] ^= key[i%key.size()];
	}
}

void decode(std::string &str, std::string key)
{
	for (int i = 0; i < str.size(); ++i)
	{
		str[i] ^= key[i%key.size()];
	}
}

int main()
{
	/*int id = EventDispatcher::getInstance()->registerListener("test", [=](std::string key, int id, Value val)->void {

		std::cout << "key:" << key << " id:" << id << std::endl;
	});

	int id1 = EventDispatcher::getInstance()->registerListener("test", [=](std::string key, int id, Value val)->void {

		std::cout << "key1:" << key << " id1:" << id << std::endl;
	});

	EventDispatcher::getInstance()->dispatcher("test", id1, Value());

	std::string sContent = "content:sdfgfghhtytrgrefsfsdfesfefsfgfhfyjgyhgnhgdgfhgfdhtdrhtfhvbvcbncfgnbthtrsg";
	encode(sContent, "123456874wuxiaos");
	addLength(sContent, sContent.size());
	unsigned int len = getLength(sContent);
	decode(sContent, "1sfesgdgd");*/

	//ServerManager::getInstance()->start();

	Document doc;
	Document::AllocatorType &alloc = doc.GetAllocator();
	rapidjson::Value root(kObjectType);
	rapidjson::Value name(kStringType);
	name.SetString("wuxiaosheng", alloc);

	root.AddMember("name", name, alloc);

	rapidjson::Value sites(kArrayType);
	sites.PushBack("www.baidu.com", alloc).PushBack("www.google.com", alloc);
	root.AddMember("sites", sites, alloc);


	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	root.Accept(writer);
	std::string str = buffer.GetString();
	std::cout << str << std::endl;


	return 0;
}