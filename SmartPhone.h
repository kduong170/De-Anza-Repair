//
//  SmartPhone.h
//  TeamProject
//
//  Created by Prasham Sheth on 5/26/22.
//

#ifndef SmartPhone_h
#define SmartPhone_h

#include <iostream>
using std::string;

class SmartPhone
{
private:
    string serial;      // Device serial number.
    string name;       // Name of device owner.
    string model;       // Device model.
    string date;        // Date brought in.
    string issue;       // Device issue.
    string status;      // Estimated time to completion.
    string cost;           // Cost of repair.
    
    
public:
    SmartPhone();
    SmartPhone(string, string, string, string, string, string, string);
    
    /// Setters:
    void setSerial(string inSerial) { serial = inSerial; }
    void setName(string inName) { name = inName; }
    void setDate(string inDate) { date = inDate; }
    void setModel(string inModel) { model = inModel; }
    void setIssue(string inIssue) { issue = inIssue; }
    void setStatus(string inStatus) { status = inStatus; }
    void setCost(string inCost) { cost = inCost; }
    
    /// Getters:
    string getSerial() const { return serial; }
    string getName() const { return name; }
    string getModel() const  { return model; }
    string getDate() const { return date; }
    string getIssue() const { return issue; }
    string getStatus() const { return status; }
    string getCost() const { return cost; }
    
    /// Overloaded operators:
    friend std::ostream &operator << (std::ostream &strm, const SmartPhone &obj);
    bool operator ==(const SmartPhone &obj) { return serial == obj.serial;}
    bool operator < (const SmartPhone &obj) { return serial < obj.serial; }
    bool operator > (const SmartPhone &obj) { return serial > obj.serial; }
};
#endif /* SmartPhone_h */
