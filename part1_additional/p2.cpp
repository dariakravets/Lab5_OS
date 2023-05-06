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

    // open existing shared memory
    int shm_fd = shm_open(sharedMemName, O_RDONLY, 0666);
    ftruncate(shm_fd, sharedMemSize);

    // map shared memory
    counterPtr = (int*)mmap(0, sharedMemSize, PROT_READ, MAP_SHARED, shm_fd, 0);

    while(true)
    {
        cout << "Counter value: " << *counterPtr << endl;
        sleep(1);
    }

    munmap(counterPtr, sharedMemSize);
    shm_unlink(sharedMemName);

    return 0;
}
