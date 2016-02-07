#ifndef UTIL_MSGQUEUE_HPP
#define UTIL_MSGQUEUE_HPP

#include <list>
#include "rtos/Semaphore.h"
#include "rtos/Mutex.h"

namespace sdc {
namespace util {

/** Classe de politique pour les queues de messages à unique écrivain */
struct SingleWriter {
    template <class T, class Ctr>
    void push(Ctr & ctr, T && t) { ctr.push_back(std::forward<T>(t)); }
};


/** Classe de politique pour les queues de messages à multiples écrivains */
class MultipleWriter {
    rtos::Mutex _mutex;

public:
    template <class T, class Ctr>
    void push(Ctr & ctr, T && t) {
        _mutex.lock();
        ctr.push_back(std::forward(t));
        _mutex.unlock();
    }
};


/** Classe de politique pour les queues de messages à unique lecteur */
struct SingleReader {
    template <class T, class Ctr>
    T & pop(Ctr & ctr) {
        T & t{ctr.front()};
        ctr.pop_front();
        return t;
    }
};


/** Classe de politique pour les queues de messages à multiples lecteurs */
class MultipleReader {
    rtos::Mutex _mutex;

public:
    template <class T, class Ctr>
    T & pop(Ctr & ctr) {
        _mutex.lock();
        T & t{ctr.front()};
        ctr.pop_front();
        _mutex.unlock();
        return t;
    }
};


/**
 * Cette classe est une file de message. Cela signifie qu'elle fonctionne comme
 * une FIFO mais la méthode pop() est bloquante si la file est vide.
 */
template <
    class T,
    class WriterPolitic = MultipleWriter,
    class ReaderPolitic = MultipleReader,
    template <class, class = std::allocator<T>> class Container = std::list
>
struct MsgQueue {
    using Queue = Container<T>;

private:
    WriterPolitic _writer;
    ReaderPolitic _reader;

    Queue           _queue;
    rtos::Semaphore _sem;

public:
    MsgQueue() : _sem{0} {}

    void push(T const & t) {
        _writer.push(_queue, t);
        _sem.release();
    }

    void push(T && t) {
        _writer.push(_queue, t);
        _sem.release();
    }

    T & pop() {
        _sem.wait();
        return _reader.template pop<T>(_queue);
    }
};

} // namespace util
} // sdc

#endif // UTIL_MSGQUEUE_HPP
