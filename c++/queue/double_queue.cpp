#ifndef COMMON_UTILITY_QUEUES_DOUBLE_QUEUE_H_
#define COMMON_UTILITY_QUEUES_DOUBLE_QUEUE_H_
#include <queue>
#ifndef __clang__
#include <bits/c++config.h>
#endif
#include "SmartPointerQueue.h"

namespace common {
namespace Utility {
template<typename T, typename BoundedQueue>
/**
 * @brief The DoubleQueue class
 */
class BasedDoubleQueue {
public:
    /**
     * @brief DoubleQueue
     * @param size
     */
    BasedDoubleQueue(std::size_t size) : max_size(size) {
        m_received_queue = &m_queue_a;
        m_trasmitted_queue = &m_queue_b;
    }

    /**
     * @brief dequeue
     * @return 
     */
    T dequeue() noexcept {
        T result{};
        dequeue(result);
        return result;
    }

    /**
     * @brief dequeue
     * @param element
     */
    void dequeue(T& element) noexcept {
        std::lock_guard<std::mutex> const lock{m_mutex_pop};
        if (m_trasmitted_queue->empty()) {
            {
                std::lock_guard<std::mutex> const lock{m_mutex_push};
                if (m_received_queue->empty())
                    return;
                swap();
            }
        }
        element = m_trasmitted_queue->front();
        m_trasmitted_queue->pop();
    }

    /**
     * @brief enqueue
     * @param element
     */
    void enqueue(const T& element) {
        // drop incomming data here
        std::lock_guard<std::mutex> const lock{m_mutex_push};
        if (m_received_queue->size() >= max_size) {
            m_received_queue->pop();
        }
        m_received_queue->push(element);
    }

    /**
     * @brief empty
     * @return 
     */
    bool empty() noexcept { return m_received_queue->empty() && m_trasmitted_queue->empty(); }

    /**
     * @brief clear
     * @return 
     */
    void clear() noexcept {
        std::lock_guard<std::mutex> const lock{m_mutex_pop};
        std::lock_guard<std::mutex> const lock{m_mutex_push};
        m_queue_a = {};
        m_queue_b = {};
    }

private:
    /**
     * @brief swap
     */
    void swap() {
        BoundedQueue* tmp = m_received_queue;
        m_received_queue = m_trasmitted_queue;
        m_trasmitted_queue = tmp;
    }

private:
    BoundedQueue m_queue_a;
    BoundedQueue m_queue_b;

    BoundedQueue* m_received_queue;
    BoundedQueue* m_trasmitted_queue;

    std::size_t max_size;

    static std::mutex m_mutex_push;
    static std::mutex m_mutex_pop;
};

template<typename T>
using DoubleQueue = BasedDoubleQueue<T, std::queue<T>>;

template<typename T>
using SharedPointerDoubleQueue = BasedDoubleQueue<T, SharedPointerQueue<T>>;
} // namespace Utility
} // namespace common

#endif