#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <json/json.h>

class http_request{
private:
    std::string _url;
public:
    http_request(std::string url);
    Json::Value GET();
    Json::Value POST(std::string postData);
    bool POST();
    void setUrl(std::string url);
};

#endif // HTTP_REQUEST_H
