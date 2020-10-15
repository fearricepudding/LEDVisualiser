#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "http_request.h"
#include <json/json.h>
#include <curl/curl.h>

http_request::http_request(std::string setUrl){
    _url = setUrl;
};

std::size_t callback(const char* in, std::size_t size, std::size_t num, std::string* out){
    const std::size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}

Json::Value http_request::GET(){
        CURL* curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, _url.c_str());
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        long httpCode(0);
        std::unique_ptr<std::string> httpData(new std::string());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
        // Perform curl
        curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);
        if(httpCode == 200){
            Json::Value jsonData;
            Json::Reader jsonReader;
            if(jsonReader.parse(*httpData.get(), jsonData)){
                return jsonData;
            }else{
                std::cout << "Could not parse HTTP data as JSON" << std::endl;
    //	        std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
            }
        };
        return "";
};

Json::Value http_request::POST(std::string postData){
   // std::cout << postData << std::endl;
    CURL *curl;
    CURLcode res;
    long httpCode(0);
    std::unique_ptr<std::string>httpData(new std::string());
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl){
        const std::string url(_url);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            std::cout << "Failed to CURL: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return "";
        };
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        if(httpCode != 200){
            std::cout << "Failed to get webpage, HTTP code: " << httpCode << std::endl;
        }
        curl_easy_cleanup(curl);
    };
    curl_global_cleanup();
    return "";
};

bool http_request::POST(){
    CURL *curl;
    CURLcode res;
    long httpCode(0);
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl){
        const std::string url(_url);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");
        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            std::cout << "Failed to curl: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        };
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        if(httpCode != 200){
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }
        curl_easy_cleanup(curl);
    };
    curl_global_cleanup();
    return true;
}
