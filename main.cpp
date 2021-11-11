#include "Client.h"
#include <future>
#include "File.h"

using namespace std;

int main(int argc, char** argv) {
    Client client("127.0.0.1", "4600");
    Socket *socket = client.getConnection();
    std::string requestType = argc >= 2 ? argv[1] : "GET";
    std::string requestFile = argc >= 3 ? argv[2] : "/folder/sadgesip.jpg";
    if(requestType == "GET")
    {
        socket->sendString(HTTP()
                                   .setRequestType(requestType)
                                   .setRequestFile(requestFile)
                                   .addHeader("Connection", "keep-alive")
                                   .build()
                                   .getString());
        int val = 0;
        HTTP response = socket->readRequest(&val);
        if(val == -1)
        {
            std::cout << ">>> Server closed the socket!" << std::endl;
            return 0;
        }
        std::cout << ">>> RESPONSE = \n" << response.build().getString() << std::endl;
        writeFile(requestFile, response.getBody());
    } else {
        if(!fileExists(requestFile))
        {
            std::cout << ">>> File " << requestFile << " Doesn't exist!" << std::endl;
            return 0;
        }
        std::string fileContent = getFileContent(requestFile);
        socket->sendString(HTTP()
                                   .setRequestType(requestType)
                                   .setRequestFile(requestFile)
                                   .setBody(fileContent)
                                   .addHeader("Connection", "keep-alive")
                                   .addHeader("Content-Length", std::to_string(fileContent.size()))
                                   .addHeader("Content-Type", "text/plain")
                                   .build()
                                   .getString());
        int val = 0;
        HTTP response = socket->readRequest(&val);
        if(val == -1)
        {
            std::cout << ">>> Server closed the socket!" << std::endl;
            return 0;
        }
        std::cout << ">>> RESPONSE = \n" << response.build().getString() << std::endl;
    }
    socket->destroy();
    Client::destroy();
    return 0;
}
