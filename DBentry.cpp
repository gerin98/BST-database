#include "DBentry.h"

#include <iostream>

    DBentry::DBentry()
    :name(""),IPaddress(0),active(false)
    {}

    DBentry::DBentry (string _name, unsigned int _IPaddress, bool _active)
    :IPaddress(_IPaddress),active(_active)
    {
        name = _name;
    }

    // the destructor
    DBentry::~DBentry()
    {}

    // sets the domain name, which we will use as a key.
    void DBentry::setName(string _name)
    {
        name = _name;
    }

    // sets the IPaddress data.
    void DBentry::setIPaddress(unsigned int _IPaddress)
    {
        IPaddress = _IPaddress;
    }

    // sets whether or not this entry is active.
    void DBentry::setActive (bool _active)
    {
        active = _active;
    }

    // returns the name.
    string DBentry::getName() const
    {
        return name;
    }

    // returns the IPaddress data.
    unsigned int DBentry::getIPaddress() const
    {
        return IPaddress;
    }

    // returns whether or not this entry is active.
    bool DBentry::getActive() const
    {
        return active;
    }

    ostream& operator<< (ostream& out, const DBentry& rhs)
    {
        //out << "hi";
        out << rhs.name << " : " << rhs.IPaddress << " : " << rhs.active << endl;
    }

