#include <fcntl.h> /* O_ constants */
#include <unistd.h> /* ftruncate */
#include <sys/mman.h> /* mmap */

int main() {
    int fd;
    int *map;
    int size = sizeof(int);
    char *name = "/a";

    shm_unlink(name);
    fd = shm_open(name, O_RDWR | O_CREAT, (mode_t)0600);
    /* THIS is the cause of the problem. */
    /*ftruncate(fd, size);*/
    map = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    /* This is what generates the SIGBUS. */
    *map = 0;
}

