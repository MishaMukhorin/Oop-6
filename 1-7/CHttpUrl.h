#include <regex>
#include <optional>
#include "CUrlParsingError.h"

enum class Protocol
{
    HTTP,
    HTTPS
};

std::string toString(Protocol protocol);

class CHttpUrl
{
public:
    // выполняет парсинг строкового представления URL-а, в случае ошибки парсинга
    // выбрасывает исключение CUrlParsingError, содержащее текстовое описание ошибки
    explicit CHttpUrl(std::string const& url) noexcept(false);

    /* инициализирует URL на основе переданных параметров.
        При недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        Если имя документа не начинается с символа /, то добавляет / к имени документа
    */
    CHttpUrl(
            std::string const& domain,
            std::string const& document,
            Protocol protocol = Protocol::HTTP) noexcept(false);

    /* инициализирует URL на основе переданных параметров.
        При недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        Если имя документа не начинается с символа /, то добавляет / к имени документа
    */
    CHttpUrl(
            std::string const& domain,
            std::string const& document,
            Protocol protocol,
            unsigned short port) noexcept(false);


    // возвращает строковое представление URL-а. Порт, являющийся стандартным для
    // выбранного протокола (80 для http и 443 для https) в эту строку
    // не должен включаться
    [[nodiscard]] std::string GetURL() const;

    // возвращает доменное имя
    [[nodiscard]] std::string GetDomain()const;

    /*
        Возвращает имя документа. Примеры:
            /
            /index.html
            /images/photo.jpg
    */
    [[nodiscard]] std::string GetDocument()const;

    // возвращает тип протокола
    [[nodiscard]] Protocol GetProtocol()const;

    // возвращает номер порта
    [[nodiscard]] unsigned short GetPort()const;
private:
    Protocol m_protocol;
    unsigned short m_port;
    std::string m_domain;
    std::string m_document;

    const std::regex URL_REGEX = std::regex(R"(^(\w+):\/\/([^:\/\s]+)(?::(\d+))?(\/.*?)?$)");
    const std::regex DOMAIN_REGEX = std::regex(R"(^([^:\/\s]+)$)");
    const std::regex DOCUMENT_REGEX = std::regex(R"(^(\/?.*?)?$)");
    static const unsigned short MAX_PORT = 65535;

    static std::optional<Protocol> DefineProtocol(std::string &protocolStr);
    static std::optional<unsigned short> ParsePort(Protocol protocol, const std::string& portStr = "");


};




