#include "Header.hpp"
#include "Server.hpp"

class _Server : public SP::Server 
{
public:
    _Server(SP::context& ctx, SP::ushort port) :
        Server(ctx, port) {}

    void OnClientConnect(SP::Session* session) override
    {
        session->write(SP::format("Welcome! Your ID is: {}", session->getId()));
    }
    void OnClientDisconnect(SP::Session* session) override
    {

    }
    void OnClientMessage(SP::Message msg) override
    {
        std::cout << SP::format("Message received from {} :: {}", 
            msg.client->getId(), msg.message.to_string()) << std::endl;
    }
};


int main()
{
    try
    {
        SP::context io_context;
        _Server server(io_context, 8888);

        io_context.run();

        
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    

    return 0;
}