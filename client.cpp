#include <zmq.h>
#include <string>
#include <iostream>

int main()
{
    std::cout << "ZMQ Request Client using libzmq" << std::endl;
    void *ctx = zmq_ctx_new();
    void *req = zmq_socket(ctx, ZMQ_REQ);
    zmq_connect(req, "tcp://localhost:5555");

    for(;;)
    {
        char buffer[10];
        std::string input;
        std::cout << "Enter what to send [qqq to terminate]:";
        std::cin >> input;
        if (input == "qqq")
        {
            std::cout << "Terminating client" << std::endl;
            break;
        }
        std::cout << "Sending " << input << std::endl;
        zmq_send(req, input.c_str(), input.length(), 0);
        zmq_recv(req, buffer, 10, 0);
        std::cout << "Received from server: " << buffer << std::endl;
    }

    zmq_close(req);
    zmq_ctx_destroy(ctx);

    return 0;
}
