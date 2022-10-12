#include "Network.h"
#include "vector"
#include <mutex>

//std::vector<ReplicationBase*> GlobalReplicationList; // 记录要同步的对象
//static std::mutex Mutex;

//ReplicationBase::ReplicationBase() {
//    Mutex.lock();
//    this->ReplicateID = GlobalReplicationList.size();
//    GlobalReplicationList.push_back(this);
//    Mutex.unlock();
//}