
#include <gtest/gtest.h>
#include "../CHttpUrl.h"

TEST(CHttpUrlTest, ValidURL) {
CHttpUrl url("http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
EXPECT_EQ(url.GetPort(), 80);
EXPECT_EQ(url.GetDomain(), "www.mysite.com");
EXPECT_EQ(url.GetDocument(), "/docs/document1.html?page=30&lang=en#title");
EXPECT_EQ(url.GetURL(), "http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
}

TEST(CHttpUrlTest, InvalidURL) {
EXPECT_THROW(CHttpUrl("invalid_url"), CUrlParsingError);
}

TEST(CHttpUrlTest, ValidURLCustomPort) {
CHttpUrl url("http://www.mysite.com:8080/docs/document1.html");
EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
EXPECT_EQ(url.GetPort(), 8080);
EXPECT_EQ(url.GetDomain(), "www.mysite.com");
EXPECT_EQ(url.GetDocument(), "/docs/document1.html");
EXPECT_EQ(url.GetURL(), "http://www.mysite.com:8080/docs/document1.html");
}

TEST(CHttpUrlTest, ValidURLUppercaseProtocol) {
CHttpUrl url("HTTPS://www.mysite.com/docs/document1.html");
EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
EXPECT_EQ(url.GetPort(), 443);
EXPECT_EQ(url.GetDomain(), "www.mysite.com");
EXPECT_EQ(url.GetDocument(), "/docs/document1.html");
EXPECT_EQ(url.GetURL(), "https://www.mysite.com/docs/document1.html");
}

TEST(CHttpUrlTest, ValidURLEmptyPort) {
CHttpUrl url("http://www.mysite.com/");
EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
EXPECT_EQ(url.GetPort(), 80);
EXPECT_EQ(url.GetDomain(), "www.mysite.com");
EXPECT_EQ(url.GetDocument(), "/");
EXPECT_EQ(url.GetURL(), "http://www.mysite.com/");
}

TEST(CHttpUrlTest, InvalidURLInvalidProtocol) {
EXPECT_THROW(CHttpUrl("fttp://www.mysite.com/docs/document1.html"), std::invalid_argument);
}

TEST(CHttpUrlTest, InvalidURLInvalidPort) {
EXPECT_THROW(CHttpUrl("http://www.mysite.com:0/docs/document1.html"), std::invalid_argument);
}

TEST(CHttpUrlTest, InvalidURLInvalidPort2) {
EXPECT_THROW(CHttpUrl("http://www.mysite.com:65536/docs/document1.html"), std::invalid_argument);
}

TEST(CHttpUrlTest, InvalidURLInvalidPort3) {
EXPECT_THROW(CHttpUrl("http://www.mysite.com:-1/docs/document1.html"), std::invalid_argument);
}

TEST(CHttpUrlTest, ValidURLValidMaxPort) {
CHttpUrl url("http://www.mysite.com:65535/docs/document1.html");
EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
EXPECT_EQ(url.GetPort(), 65535);
EXPECT_EQ(url.GetDomain(), "www.mysite.com");
EXPECT_EQ(url.GetDocument(), "/docs/document1.html");
EXPECT_EQ(url.GetURL(), "http://www.mysite.com:65535/docs/document1.html");
}

TEST(CHttpUrlTest, ValidURLValidMinPort) {
CHttpUrl url("http://www.mysite.com:1/docs/document1.html");
EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
EXPECT_EQ(url.GetPort(), 1);
EXPECT_EQ(url.GetDomain(), "www.mysite.com");
EXPECT_EQ(url.GetDocument(), "/docs/document1.html");
EXPECT_EQ(url.GetURL(), "http://www.mysite.com:1/docs/document1.html");
}

TEST(CHttpUrlTest, InvalidURLInvalidHost) {
EXPECT_THROW(CHttpUrl("http:///docs/document1.html"), std::invalid_argument);
}

TEST(CHttpUrlTest, InvalidURLMissingProtocol) {
EXPECT_THROW(CHttpUrl("www.mysite.com/docs/document1.html"), CUrlParsingError);
}

TEST(CHttpUrlTest, InvalidURLMissingHost) {
EXPECT_THROW(CHttpUrl("http://"), CUrlParsingError);
}

TEST(CHttpUrlTest, InvalidURLMissingDocument) {
EXPECT_THROW(CHttpUrl("http://www.mysite.com:"), CUrlParsingError);
}

TEST(CHttpUrlTest, InvalidURLMissingProtocolAndHost) {
EXPECT_THROW(CHttpUrl("/docs/document1.html"), CUrlParsingError);
}

TEST(CHttpUrlTest, EmptyURL) {
EXPECT_THROW(CHttpUrl(""), CUrlParsingError);
}

TEST(CHttpUrlTest, ConstructorWithParameters) {
CHttpUrl url("www.example.com", "/index.html", Protocol::HTTP, 8080);
EXPECT_EQ(url.GetDomain(), "www.example.com");
EXPECT_EQ(url.GetDocument(), "/index.html");
EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
EXPECT_EQ(url.GetPort(), 8080);
EXPECT_EQ(url.GetURL(), "http://www.example.com:8080/index.html");
}

TEST(CHttpUrlTest, ConstructorWithParametersButWithoutSlash) {
CHttpUrl url("www.example.com", "index.html", Protocol::HTTP);
EXPECT_EQ(url.GetDomain(), "www.example.com");
EXPECT_EQ(url.GetDocument(), "/index.html");
EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
EXPECT_EQ(url.GetPort(), 80);
EXPECT_EQ(url.GetURL(), "http://www.example.com/index.html");
}

TEST(CHttpUrlTest, ConstructorWithParametersDefaultProtocol) {
CHttpUrl url("www.example.com", "/index.html");
EXPECT_EQ(url.GetDomain(), "www.example.com");
EXPECT_EQ(url.GetDocument(), "/index.html");
EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
EXPECT_EQ(url.GetPort(), 80);
EXPECT_EQ(url.GetURL(), "http://www.example.com/index.html");
}

TEST(CHttpUrlTest, ConstructorWithParametersDefaultPort) {
CHttpUrl url("www.example.com", "/index.html", Protocol::HTTPS);
EXPECT_EQ(url.GetDomain(), "www.example.com");
EXPECT_EQ(url.GetDocument(), "/index.html");
EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
EXPECT_EQ(url.GetPort(), 443);
EXPECT_EQ(url.GetURL(), "https://www.example.com/index.html");
}

TEST(CHttpUrlTest, ConstructorWithParametersAddSlashToDocument) {
CHttpUrl url("www.example.com", "index.html");
EXPECT_EQ(url.GetDomain(), "www.example.com");
EXPECT_EQ(url.GetDocument(), "/index.html");
EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
EXPECT_EQ(url.GetPort(), 80);
EXPECT_EQ(url.GetURL(), "http://www.example.com/index.html");
}

TEST(CHttpUrlTest, ConstructorWithParametersInvalidDomain) {
EXPECT_THROW(CHttpUrl("", "/index.html"), std::invalid_argument);
}


TEST(CHttpUrlTest, ConstructorWithParametersInvalidPort) {
EXPECT_THROW(CHttpUrl("www.example.com", "/index.html", Protocol::HTTP, 0), std::invalid_argument);
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}