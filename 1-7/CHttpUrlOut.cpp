//
// Created by mrLogic on 5/16/2024.
//
#include <iostream>
#include "CHttpUrl.h"


int main()
{
    std::string url;
    while (std::getline(std::cin, url))
    {
        try
        {
            CHttpUrl httpUrl(url);
            std::cout << std::endl << url << std::endl;
            std::cout << "PROTOCOL: " << toString(httpUrl.GetProtocol()) << std::endl;
            std::cout << "DOMAIN: " << httpUrl.GetDomain() << std::endl;
            std::cout << "PORT: " << httpUrl.GetPort()  << std::endl;
            std::cout << "DOC: " << httpUrl.GetDocument()  << std::endl;
        }
        catch(const CUrlParsingError& e)
        {
            std::cerr << "Invalid input: invalid URL!\n";
        }
        catch(const CUrlProtocolParsingError& e)
        {
            std::cerr << "Invalid input: invalid protocol in URL!\n";
        }
        catch(const CUrlDomainParsingError& e)
        {
            std::cerr << "Invalid input: invalid domain in URL!\n";
        }
        catch(const CUrlPortParsingError& e)
        {
            std::cerr << "Invalid input: invalid port in URL!\n";
        }
        catch(const CUrlDocumentParsingError& e)
        {
            std::cerr << "Invalid input: invalid document in URL!\n";
        }
    }
    return 0;
}