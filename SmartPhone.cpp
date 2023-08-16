//
//  SmartPhone.cpp
//  TeamProject
//
//  Created by Prasham Sheth on 6/9/22.
//

#include <string>
#include <iostream>
#include "SmartPhone.h"

SmartPhone::SmartPhone(string serialIn, string nameIn, string modelIn,
                       string dateIn, string issueIn, string costIn, string statusIn)
{
    serial = serialIn;
    name = nameIn;
    model = modelIn;
    date = dateIn;
    issue = issueIn;
    cost = costIn;
    status = statusIn;
}

SmartPhone::SmartPhone()
{
    serial = "";
    name = "";
    model = "";
    date = "";
    issue = "";
    status = "";
    cost = "";
}

std::ostream& operator<<(std::ostream& strm, const SmartPhone& obj) {
    strm << "\tSerial number: " << obj.serial << std::endl;
    strm << "\tName of owner: " << obj.name << std::endl;
    strm << "\tPhone model: " << obj.model << std::endl;
    strm << "\tDate received: " << obj.date << std::endl;
    strm << "\tIssue reported: " << obj.issue << std::endl;
    strm << "\tEstimated cost of repairs: $" << obj.cost << std::endl;
    strm << "\tRepair status: " << obj.status << std::endl;

    return strm;
}

