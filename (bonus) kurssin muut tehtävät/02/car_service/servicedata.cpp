#include <iostream>
#include "servicedata.hh"

ServiceData::ServiceData(): services_({}) {}

ServiceData::~ServiceData() {}


bool ServiceData::makeService(const Service &service, int kilometres)
{
    if (services_.find(kilometres) != services_.end()){
        std::cout << "Error: already serviced with the same kilometres" << std::endl;
        return false;
    }
    services_[kilometres] = service;
    return true;
}

void ServiceData::print() const
{
    for(const auto &service_data: services_){
        std::cout << "* Kilometres driven " << service_data.first << " until " << service_data.second.date_ << std::endl;
        for(const auto &info: service_data.second.operations_){
            std::cout << "  --- " << info << std::endl;
        }
    }
}

const std::map<int, Service> &ServiceData::getServices() const
{
    return services_;
}
