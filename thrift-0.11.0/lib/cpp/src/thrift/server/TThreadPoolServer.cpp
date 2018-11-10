#include <thrift/server/TThreadPoolServer.h>

namespace apache {
namespace thrift {
namespace server {

using apache::thrift::concurrency::ThreadManager;
using apache::thrift::protocol::TProtocol;
using apache::thrift::protocol::TProtocolFactory;
using apache::thrift::transport::TServerTransport;
using apache::thrift::transport::TTransport;
using apache::thrift::transport::TTransportException;
using apache::thrift::transport::TTransportFactory;
using stdcxx::shared_ptr;
using std::string;

TThreadPoolServer::TThreadPoolServer(const shared_ptr<TProcessorFactory>& processorFactory,
                                     const shared_ptr<TServerTransport>& serverTransport,
                                     const shared_ptr<TTransportFactory>& transportFactory,
                                     const shared_ptr<TProtocolFactory>& protocolFactory,
                                     const shared_ptr<ThreadManager>& threadManager)
  : TServerFramework(processorFactory, serverTransport, transportFactory, protocolFactory),
    threadManager_(threadManager),
    timeout_(0),
    taskExpiration_(0) 
{

}

TThreadPoolServer::TThreadPoolServer(const shared_ptr<TProcessor>& processor,
                                     const shared_ptr<TServerTransport>& serverTransport,
                                     const shared_ptr<TTransportFactory>& transportFactory,
                                     const shared_ptr<TProtocolFactory>& protocolFactory,
                                     const shared_ptr<ThreadManager>& threadManager)
  : TServerFramework(processor, serverTransport, transportFactory, protocolFactory),
    threadManager_(threadManager),
    timeout_(0),
    taskExpiration_(0) 
{

}

TThreadPoolServer::TThreadPoolServer(const shared_ptr<TProcessorFactory>& processorFactory,
                                     const shared_ptr<TServerTransport>& serverTransport,
                                     const shared_ptr<TTransportFactory>& inputTransportFactory,
                                     const shared_ptr<TTransportFactory>& outputTransportFactory,
                                     const shared_ptr<TProtocolFactory>& inputProtocolFactory,
                                     const shared_ptr<TProtocolFactory>& outputProtocolFactory,
                                     const shared_ptr<ThreadManager>& threadManager)
  : TServerFramework(processorFactory,
                     serverTransport,
                     inputTransportFactory,
                     outputTransportFactory,
                     inputProtocolFactory,
                     outputProtocolFactory),
    threadManager_(threadManager),
    timeout_(0),
    taskExpiration_(0) {
}

TThreadPoolServer::TThreadPoolServer(const shared_ptr<TProcessor>& processor,
                                     const shared_ptr<TServerTransport>& serverTransport,
                                     const shared_ptr<TTransportFactory>& inputTransportFactory,
                                     const shared_ptr<TTransportFactory>& outputTransportFactory,
                                     const shared_ptr<TProtocolFactory>& inputProtocolFactory,
                                     const shared_ptr<TProtocolFactory>& outputProtocolFactory,
                                     const shared_ptr<ThreadManager>& threadManager)
  : TServerFramework(processor,
                     serverTransport,
                     inputTransportFactory,
                     outputTransportFactory,
                     inputProtocolFactory,
                     outputProtocolFactory),
    threadManager_(threadManager),
    timeout_(0),
    taskExpiration_(0) 
{

}

TThreadPoolServer::~TThreadPoolServer() 
{

}

void TThreadPoolServer::serve() 
{
    TServerFramework::serve();

    threadManager_->stop();
}

int64_t TThreadPoolServer::getTimeout() const 
{
    return timeout_;
}

void TThreadPoolServer::setTimeout(int64_t value) 
{
    timeout_ = value;
}

int64_t TThreadPoolServer::getTaskExpiration() const 
{
    return taskExpiration_;
}

void TThreadPoolServer::setTaskExpiration(int64_t value) 
{
    taskExpiration_ = value;
}

stdcxx::shared_ptr<apache::thrift::concurrency::ThreadManager>
TThreadPoolServer::getThreadManager() const 
{
    return threadManager_;
}

void TThreadPoolServer::onClientConnected(const shared_ptr<TConnectedClient>& pClient) 
{
    threadManager_->add(pClient, getTimeout(), getTaskExpiration());
}

void TThreadPoolServer::onClientDisconnected(TConnectedClient*) 
{

}

}
}
} // apache::thrift::server
