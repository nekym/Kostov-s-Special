#pragma once
#ifndef BASE_H
#define BASE_H

#include <string>

class Printable {
public:
	virtual std::string GetString() const = 0;
};

class Named : virtual public Printable {
public:
	Named(std::string name) : m_name(name) {}
	virtual std::string GetString() const { return m_name; }
protected:
	std::string m_name;
};

#endif