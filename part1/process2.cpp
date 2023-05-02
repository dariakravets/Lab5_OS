#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    // Find the shared memory segment
    key_t key = ftok("counter", 'R');
    int shmid = shmget(key, sizeof(int), 0666);

    // Attach to the shared memory segment
    int* counter = (int*) shmat(shmid, NULL, 0);

    // Read the counter value in a loop
    while (true) {
        std::cout << "Counter value: " << *counter << std::endl;
        sleep(1);
    }

    // Detach from the shared memory segment
    shmdt(counter);

    return 0;
}
