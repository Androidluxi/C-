#include "my_pthread.h"

// 定义线程执行的函数
void* threadFunction(void* arg)
{
    int threadID = *(static_cast<int*>(arg));
    std::cout << "Thread ID " << threadID << " started." << std::endl;
    // 实现线程逻辑...
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Thread ID " << threadID << " finished." << std::endl;
    delete static_cast<int*>(arg);
    return nullptr; // pthread_create 需要返回一个 void* 类型的值，通常设为 nullptr
}

int thread_test(){
    constexpr int numThreads = 5; // 想要创建的线程数量
    pthread_t threads[numThreads]; // 用于存储线程标识符的数组

    // 创建新线程
    for (int i = 0; i < numThreads; ++i)
    {
        const auto threadID = new int(i); // 创建一个指向线程ID的指针，作为参数传递给线程函数

        if (pthread_create(&threads[i], nullptr, threadFunction, threadID) != 0)
        {
            std::cerr << "Error creating thread " << i + 1 << std::endl;
            delete threadID; // 如果线程创建失败，立即释放内存
            exit(1);
        }
    }

    // 等待所有线程完成（可选，取决于实际需求）
    for (int i = 0; i < numThreads; ++i)
    {
        //阻塞当前线程，直到目标线程结束
        pthread_join(threads[i], nullptr);
    }

    std::cout << "All threads finished." << std::endl;

    return 0;
}
