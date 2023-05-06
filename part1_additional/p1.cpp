#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

using namespace std;

int main()
{
    int* counterPtr;
    const char* sharedMemName = "/my_shared_mem";
    const int sharedMemSize = sizeof(int);

    // create shared memory
    int shm_fd = shm_open(sharedMemName, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sharedMemSize);

    // map shared memory
    counterPtr = (int*)mmap(0, sharedMemSize, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    *counterPtr = 0;

    while(true)
    {
        ++(*counterPtr);
        cout << "Counter value: " << *counterPtr << endl;
        sleep(1);
    }

    munmap(counterPtr, sharedMemSize);
    shm_unlink(sharedMemName);

    return 0;
}
