#pragma once

#include <fstream>
#include <string>
#include <list>
#include <map>
#include <set>
#include <regex>
#include "Object.h"

using ObjectList = std::list<Object>;
using ObjectGroup = std::multiset<const Object*, bool (*)(const Object* obj1, const Object* obj2)>;
using ObjectDistanceGroup = std::multimap<double, const Object*, bool (*)(double, double)>;

std::ostream& operator<< (std::ostream& stream, const Object& obj);
std::istream& operator>> (std::istream& stream, Object& obj);


class Database
{
private:
    std::string _filename = "";
    ObjectList _list;
    bool _isOpen = false;

private:
    bool readAllObjectsFromFile();

public:
    Database() = default;
    Database(const std::string& filename);
    bool open(const std::string& filename);
    const ObjectList& getObjectList() const;
    bool addObject(const Object& obj);
    std::size_t removeObjectByName(const std::string& name);
    std::size_t getObjCount() const;
    bool isOpen() const;
    bool save();
    void close();
    const ObjectDistanceGroup groupByDistance(double d);
    const ObjectGroup groupByName(const std::regex& regex);
    const ObjectGroup groupByTime(const time_t t2, const time_t t1 = 0);
    const ObjectGroup groupByType(const std::string& type);
    const ObjectGroup groupByTypeNotMoreN(size_t n = 2);
    ~Database();
};

