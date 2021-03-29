//https://bisqwit.iki.fi/story/howto/openmp/
#include <iostream>
using namespace std;
int main()
{
    const int size = 100;
    // Example: Initializing a table in parallel (multiple threads)
    // This code divides the table initialization into multiple threads,
    //which are run simultaneously. Each thread initializes a portion of the table.
    std::cout << "Serial:" << std::endl;
    for (int i = 0; i < size; ++i)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "Parallel:" << std::endl;
#pragma omp parallel for
    for (int i = 0; i < size; ++i)
        printf("%d ", i);
    printf(".\n");
    //这里用printf而不用cout是因为cout之间用<<连接会导致输出操作不是原子性，
    //如输出cout<<i<<endl，在输出i和endl之间可能会有其他线程进行中断，导致i和endl没有连续输出

    std::cout << "Parallel: specified threads number" << std::endl;
#pragma omp parallel for num_threads(3)
    for (int i = 0; i < size; ++i)
        printf("%d ", i);
    printf(".\n");
    //specify the number of threads

    std::cout << "Parallel: static schedule" << std::endl;
#pragma omp for schedule(static)
    for (int n = 0; n < size; ++n)
        printf(" %d", n);
    printf(".\n");
    // static is the default schedule as shown above.
    // Upon entering the loop, each thread independently
    // decides which chunk of the loop they will process.

    std::cout << "Parallel: dynamic schedule" << std::endl;
#pragma omp for schedule(dynamic, 3)
    for (int n = 0; n < size; ++n)
        printf(" %d", n);
    printf(".\n");
    // In the dynamic schedule, there is no predictable order in which the loop items are assigned to different threads.
    // Each thread asks the OpenMP runtime library for an iteration number, then handles it, then asks for next, and so on.
    // This is most useful when used in conjunction with the ordered clause, or when the different iterations in the loop may take different time to execute.
    // The chunk size is specified as 3.
    // In this example, each thread asks for an iteration number, executes 3 iterations of the loop,
    // then asks for another, and so on. The last chunk may be smaller than 3, though.

    std::cout << "Parallel: collapse" << std::endl;
#pragma omp parallel for collapse(2)
    for (int y = 0; y < 10; ++y)
        for (int x = 0; x < 10; ++x)
        {
            printf("(%d %d) ", x, y);
        }
}