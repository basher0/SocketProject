#include "Socket.hpp"

using namespace SP;

class Client : public Socket 
{
public:
    Client(context& io, const char* ip, ushort port) :
        Socket(io, ip, port) {}

    void OnServerConnect() override 
    {
        std::cout << "Connected to server." << std::endl;

        this->write("Thanks!");
    }
    void OnServerMessage(BytesHandler bytes) override 
    {
        std::cout << bytes.to_string() << std::endl;
    }

    void OnServerDisconnect() override
    {

    }

    void CMD() 
    {
        while (true) 
        {
            std::string in;
            std::cout << "CMD: ";
            std::getline(std::cin, in);
            this->write(in);

            std::cout << std::endl;
        }
    }
};



int main()
{
    try
    {

        context io_context;
        std::unique_ptr<Client> client = std::make_unique<Client>(io_context, "127.0.0.1", 8888);

        std::cout << "CMD: ";
        std::thread t(&Client::CMD, client.get());
        t.detach();

        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}