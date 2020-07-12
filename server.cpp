#include <iostream>
#include <zmq.h>
#include <cassert>
#include <unistd.h>

int main()
{
    std::cout << "ZMQ Reply Server using libzmq" << std::endl;

    void *ctx = zmq_ctx_new(); // create context
    void *rep = zmq_socket(ctx, ZMQ_REP); // create a socket that sends a reply
    int rc = zmq_bind(rep, "tcp://*:5555"); // binds the rep tcp socket to an address and to port 5555
    assert(rc == 0); // bind should return zero on success

    for(;;)
    {
        char buffer[10] = {0};
        zmq_recv(rep, buffer, 10, 0); // waits for someone to request to our rep socket
	    std::cout << "Received msg: " << buffer << std::endl;
        sleep(1); // simulate "doing some work"

        zmq_send(rep, "got ur msg", 10, 0); // reply to the requestor
    }

    return 0;
}
