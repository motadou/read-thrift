#include <thrift/thrift-config.h>

#include <thrift/concurrency/Mutex.h>
#include <thrift/concurrency/Util.h>
#include <thrift/Thrift.h>

#include <cassert>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace apache {
namespace thrift {
namespace concurrency {

/**
 * Implementation of Mutex class using boost::timed_mutex
 *
 * Methods throw boost::lock_error on error.
 *
 * @version $Id:$
 */
class Mutex::impl : public boost::timed_mutex {};

Mutex::Mutex(Initializer init) : impl_(new Mutex::impl()) 
{
    THRIFT_UNUSED_VARIABLE(init);
}

void* Mutex::getUnderlyingImpl() const 
{
    return impl_.get();
}

void Mutex::lock() const 
{
    impl_->lock();
}

bool Mutex::trylock() const 
{
    return impl_->try_lock();
}

bool Mutex::timedlock(int64_t ms) const 
{
    return impl_->timed_lock(boost::get_system_time() + boost::posix_time::milliseconds(ms));
}

void Mutex::unlock() const 
{
    impl_->unlock();
}

void Mutex::DEFAULT_INITIALIZER(void* arg) 
{
    THRIFT_UNUSED_VARIABLE(arg);
}

}
}
} // apache::thrift::concurrency
