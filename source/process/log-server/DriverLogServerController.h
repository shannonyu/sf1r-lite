#ifndef DRIVER_LOG_SERVER_CONTROLLER_H_
#define DRIVER_LOG_SERVER_CONTROLLER_H_

#include "DriverLogProcessor.h"
#include "LogServerStorage.h"

#include <iostream>
#include <set>

#include <util/driver/Controller.h>
#include <util/driver/writers/JsonWriter.h>

namespace sf1r
{

/**
 * @brief Controller \b log_server
 * Log server for updating cclog
 */
class DriverLogServerController : public izenelib::driver::Controller
{
public:
    void update_cclog();

    void setDriverCollections(const std::set<std::string>& collections)
    {
        driverCollections_ = collections;
    }

    void setDrum(LogServerStorage::DrumPtr& drum)
    {
        drum_ = drum;
    }

    void setDocidDB(LogServerStorage::KVDBPtr& docidDB)
    {
        docidDB_ = docidDB;
    }

private:
    bool skipProcess(const std::string& collection);

private:
    izenelib::driver::JsonWriter jsonWriter_;

    std::set<std::string> driverCollections_;

    LogServerStorage::DrumPtr drum_;
    LogServerStorage::KVDBPtr docidDB_;
};

}

#endif /* DRIVER_LOG_SERVER_CONTROLLER_H_ */
