#include "CHttpUrl.h"

std::string toString(Protocol protocol) {
    static std::map<Protocol, std::string> protocolStrings = {
            {Protocol::HTTP, "http"},
            {Protocol::HTTPS, "https"}
    };
    return protocolStrings[protocol];
}

std::optional<Protocol> CHttpUrl::DefineProtocol(std::string &protocolStr)
{
    Protocol protocol;
    std::transform(protocolStr.begin(), protocolStr.end(), protocolStr.begin(), ::tolower);
    if (protocolStr == "http")
    {
        protocol = Protocol::HTTP;
    }
    else if (protocolStr == "https")
    {
        protocol = Protocol::HTTPS;
    }
    else
    {
        return std::nullopt;
    }
    return protocol;
}


std::optional<unsigned short> CHttpUrl::ParsePort(Protocol protocol, const std::string& portStr)
{
    unsigned short port = 0;
    if (portStr.empty())
    {
        switch (protocol)
        {
            case Protocol::HTTP:
                port = 80;
                break;
            case Protocol::HTTPS:
                port = 443;
                break;
        }
    }
    else
    {
        port = std::stoi(portStr);
    }
    if (port < 1 or port > MAX_PORT) return std::nullopt;
    return port;
}

std::string CHttpUrl::GetURL() const
{
    unsigned short defaultPort;
    if (m_protocol == Protocol::HTTP)
    {
        defaultPort = 80;
    }
    else
    {
        defaultPort = 443;
    }
    std::string url = toString(m_protocol) + "://" + m_domain;
    if (m_port != defaultPort)
    {
        url = url + ":" + std::to_string(m_port);
    }
    url += m_document;
    return url;
}

std::string CHttpUrl::GetDomain() const
{
    return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
    return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
    return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
    return m_port;
}

CHttpUrl::CHttpUrl(const std::string &url) noexcept(false)
{
    std::smatch urlMatch;
    if (!std::regex_match(url, urlMatch, URL_REGEX)) throw CUrlParsingError();
    std::string protocolString = urlMatch[1];
    std::optional<Protocol> protocolOpt = DefineProtocol(protocolString);
    if (!protocolOpt) throw CUrlProtocolParsingError();
    std::optional<unsigned short> portOpt = ParsePort(protocolOpt.value(), urlMatch[3]);
    if (!portOpt) throw CUrlPortParsingError();
    m_protocol = protocolOpt.value();
    m_port = portOpt.value();
    m_domain = urlMatch[2];
    m_document = urlMatch[4];

}

CHttpUrl::CHttpUrl(const std::string &domain, const std::string &document, Protocol protocol) noexcept(false)
{
    std::smatch domainMatch;
    if (!std::regex_match(domain, domainMatch, DOMAIN_REGEX)) throw CUrlDomainParsingError();
    m_domain = domainMatch[1];
    std::smatch documentMatch;
    if (!std::regex_match(document, documentMatch, DOCUMENT_REGEX)) throw CUrlDocumentParsingError();
    if (documentMatch[1].str()[0] != '/')
    {
        m_document = "/";
    }
    m_document += documentMatch[1];
    m_protocol = protocol;
    std::optional<unsigned short> portOpt = ParsePort(protocol);
    if (!portOpt) throw CUrlPortParsingError();
    m_port = portOpt.value();
}

CHttpUrl::CHttpUrl(const std::string &domain, const std::string &document, Protocol protocol, unsigned short port) noexcept(false)
{
    std::smatch domainMatch;
    if (!std::regex_match(domain, domainMatch, DOMAIN_REGEX)) throw CUrlDomainParsingError();
    m_domain = domainMatch[1];
    std::smatch documentMatch;
    if (!std::regex_match(document, documentMatch, DOCUMENT_REGEX)) throw CUrlDocumentParsingError();
    if (documentMatch[1].str()[0] != '/')
    {
        m_document = "/";
    }
    m_document += documentMatch[1];
    m_protocol = protocol;
    if (port < 1 or port > MAX_PORT) throw CUrlPortParsingError();
    m_port = port;
}
