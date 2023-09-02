#include "../include/Database.h"
#include <math.h>
#include <algorithm>
#include <unordered_map>


char toLower(char chr)
{
    if (chr >= 'А' && chr <= 'Я')
        chr += 32;
    else
        chr = std::tolower(chr);
    return chr;
}

char toUpper(char chr)
{
    if (chr >= 'а' && chr <= 'я')
        chr -= 32;
    else
        chr = std::toupper(chr);
    return chr;
}

std::string& strToLower(std::string& str)
{
    for (auto& chr : str)
        chr = toLower(chr);
    return str;
}

std::string& strToUpper(std::string& str)
{
    for (auto& chr : str)
        chr = toUpper(chr);
    return str;
}

std::string& beautifyStr(std::string& str)
{
    strToLower(str);
    if (!str.empty()) 
        str[0] = toUpper(str[0]);
    return str;
}


std::ostream& operator<< (std::ostream& stream, const Object& obj)
{
    stream << obj._name << ' ' << obj._x << ' ' << obj._y << ' ' << obj._type << ' ' << obj._time;
    return stream;
}

std::istream& operator>> (std::istream& stream, Object& obj)
{
    stream >> obj._name >> obj._x >> obj._y >> obj._type >> obj._time;
    beautifyStr(obj._name);
    beautifyStr(obj._type);
    return stream;
}


bool Database::readAllObjectsFromFile()
{
    _isOpen = false;
    _list.clear();
    
    std::fstream file(_filename, std::ios::in);
    if (!file.is_open())
        return false;

    Object obj;
    while (file >> obj)
    {
        _list.emplace_back(obj);
    }

    file.close();
    _isOpen = true;
    
    return true;
}

Database::Database(const std::string& filename)
{
    open(filename);
}

bool Database::open(const std::string& filename)
{
    if (_isOpen)
        save();
    
    _isOpen = false;
    _list.clear();
    _filename = filename;

    std::fstream file(filename, std::ios::in);
    if (!file.is_open())
        file.open(filename, std::ios::out | std::ios::trunc);

    file.close();
    return readAllObjectsFromFile();
}

const ObjectList& Database::getObjectList() const
{
    return _list;
}

bool Database::addObject(const Object& obj)
{
    if (!_isOpen)
        return false;

    _list.emplace_back(obj);
    beautifyStr(_list.back()._name);
    beautifyStr(_list.back()._type);
    return true;
}

std::size_t Database::removeObjectByName(const std::string& name)
{
    std::size_t counter = 0;
    std::string nameTmp = name;
    beautifyStr(nameTmp);

    _list.remove_if( [&] (Object& obj) -> bool {
        if (obj._name == nameTmp)
        {
            counter++;
            return true;
        }
        return false;
    });

    return counter;
}

std::size_t Database::getObjCount() const
{
    return _list.size();
}

bool Database::isOpen() const
{
    return _isOpen;
}

bool Database::save()
{
    std::fstream file(_filename, std::ios::out | std::ios::trunc);
    if (!file.is_open())
        return false;

    for (auto& obj : _list)
    {
        file << obj << '\n';
    }

    file.close();
    return true;
}

void Database::close()
{
    _filename = "";
    _isOpen = false;
    _list.clear();
}

const ObjectDistanceGroup Database::groupByDistance(double d)
{
    auto cmp = [] (double dist1, double dist2) -> bool
    {
        return dist2 > dist1 ? true : false;
    };

    ObjectDistanceGroup sortedObjects(cmp);

    for (auto& obj : _list)
    {
        double dist = abs(obj._y - obj._x);
        if (dist < d)
            sortedObjects.insert({dist, &obj});
    }

    return sortedObjects;
}

const ObjectGroup Database::groupByName(const std::regex& regex)
{
    auto cmp = [] (const Object* obj1, const Object* obj2) -> bool
    {
        return obj1->_name < obj2->_name;
    };

    ObjectGroup sortedObjects(cmp);

    for (auto& obj : _list)
    {
        if (!obj._name.empty())
        {
            if (std::regex_search(obj._name, regex))
                sortedObjects.insert(&obj);
        }
    }

    return sortedObjects;
}

const ObjectGroup Database::groupByTime(const time_t t2, const time_t t1)
{
    auto cmp = [] (const Object* obj1, const Object* obj2) -> bool
    {
        return obj1->_time < obj2->_time;
    };

    ObjectGroup sortedObjects(cmp);

    for (auto& obj : _list)
    {
        if (obj._time >= time(0) - t2 && time(0) - t1 >= obj._time)
            sortedObjects.insert(&obj);
    }

    return sortedObjects;
}

static auto cmp = [] (const Object* obj1, const Object* obj2) -> bool
{
    return obj1->_name < obj2->_name;
};

const ObjectGroup Database::groupByType(const std::string& type)
{
    ObjectGroup sortedObjects(cmp);
    std::string typeTmp = type;
    beautifyStr(typeTmp);

    for (auto& obj : _list)
    {
        if (obj._type == typeTmp)
            sortedObjects.insert(&obj);
    }

    return sortedObjects;
}

const ObjectGroup Database::groupByTypeNotMoreN(size_t n)
{
    ObjectGroup sortedObjects(cmp);
    std::unordered_map<decltype(Object::_type), size_t> typeMap;

    for (auto& obj : _list)
    {
        ++typeMap[obj._type];
    }

    for (auto& obj : _list)
    {
        if (typeMap[obj._type] <= n)
            sortedObjects.insert(&obj);
    }

    return sortedObjects;
}

Database::~Database()
{
    save();
    close();
}
