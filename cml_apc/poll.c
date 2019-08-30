    #include <stropts.h>
    #include <poll.h>
    
    struct pollfd fds[2];
    int timeout_msecs = 500;
    int ret;
        int i;


    /* Open STREAMS device. */
    fds[0].fd = open("/dev/dev0", ...);
    fds[1].fd = open("/dev/dev1", ...);
    fds[0].events = POLLOUT | POLLWRBAND;
    fds[1].events = POLLOUT | POLLWRBAND;


    ret = poll(fds, 2, timeout_msecs);


    if (ret > 0) {
        /* An event on one of the fds has occurred. */
        for (i=0; i<2; i++) {
            if (fds[i].revents & POLLWRBAND) {
            /* Priority data may be written on device number i. */
    
            }
            if (fds[i].revents & POLLOUT) {
            /* Data may be written on device number i. */
    
            }
            if (fds[i].revents & POLLHUP) {
            /* A hangup has occurred on device number i. */
    
            }
        }
    }


