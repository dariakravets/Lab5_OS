#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    // Create a shared memory segment
    key_t key = ftok("counter", 'R');
    int shmid = shmget(key, sizeof(int), 0666|IPC_CREAT);

    // Attach to the shared memory segment
    int* counter = (int*) shmat(shmid, NULL, 0);

    *counter = 0;

    while (true) {
        (*counter)++;
        std::cout << "Counter value: " << *counter << std::endl;
        sleep(1);
    }

    // Detach from the shared memory segment
    shmdt(counter);

    // Delete the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
