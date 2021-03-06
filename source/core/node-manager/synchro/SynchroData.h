/**
 * @file SynchroData.h
 * @author Zhongxia Li
 * @date Dec 7, 2011
 * @brief 
 */
#ifndef SYNCHRO_DATA_H_
#define SYNCHRO_DATA_H_

#include <util/kv2string.h>

namespace sf1r{

class SynchroData : public izenelib::util::kv2string
{
public:
    static const char* KEY_HOST;
    static const char* KEY_DATA_PORT;
    static const char* KEY_DATA_TYPE;
    static const char* DATA_TYPE_SCD_INDEX;
    static const char* TOTAL_COMMENT_SCD;
    static const char* COMMENT_TYPE_FLAG;
    static const char* KEY_DATA_PATH;
    static const char* KEY_COLLECTION;
    static const char* KEY_RETURN;
    static const char* KEY_ERROR;

    static const char* KEY_CONSUMER_STATUS;
    static const char* CONSUMER_STATUS_READY;
    static const char* CONSUMER_STATUS_RECEIVE_SUCCESS;
    static const char* CONSUMER_STATUS_RECEIVE_FAILURE;
};


/**
 * ZooKeeper namespace for Synchro Producer and Consumer(s).
 *
 * SynchroNode
 *  |--- Producer
 *  |--- Consumer00000000
 *  |--- Consumer00000001
 *  |--- ...
 */
class SynchroZkNode
{
public:
    static const char* PRODUCER;
    static const char* CONSUMER;
};

}

#endif /* SYNCHRO_DATA_H_ */
