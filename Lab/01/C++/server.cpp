#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>

#include "yhirose/httplib.h"
#include "nlohmann/json.hpp"
#include "headers/logger.hpp"
#include "headers/utils.hpp"

using json = nlohmann::json;
using namespace httplib;


void gen_response_test(const Request &req, Response &res) {
    res.set_content("Test successful!", "text/plain");
    log_append_line("[Info] Test request processed successfully.");
}

void gen_response(const Request &req, Response &res) {
    json hour_forecast;
    json body;
    
    bool retry = false;
    do {
        body = get_cache();
        if (body.empty()) {
            body = get_json();
            if (body.empty()) {
                res.set_content("Error! Could not get data from api.openweathermap.com", "text/plain");
                return;
            }
        }
        
        //log_append_line(body.dump(2));
        
        hour_forecast = get_hour_forecast(body["hourly"]);
        if (hour_forecast.empty()) {
            if (retry) {
                res.set_content("Error! Could not get data from api.openweathermap.com", "text/plain");
                return;
            }
        }
    } while (retry);
    
    cache_json(body);

    log_append_line("[Info] Starting to work with template.");
    std::string template_file_name = "template.html";
    std::ifstream template_file(template_file_name);
    std::string site;
    
    if (template_file.is_open()) {
        getline(template_file, site, '\0');
        template_file.close();
    } else {
        log_append_line("[Err] Could not open `template.html` file.");
        res.set_content("Error! Could not open `template.html` file.", "text/plain");
        return;
    }

    findAndReplaceAll(site, "{hourly[i].weather[0].description}", hour_forecast["weather"][0]["description"]);
    findAndReplaceAll(site, "{hourly[i].weather[0].icon}", hour_forecast["weather"][0]["icon"]);
    findAndReplaceAll(site, "{hourly[i].temp}", std::to_string(int(std::round(hour_forecast["temp"].get<double>()))));

    res.set_content(site, "text/html");
}

void gen_response_raw(const Request &req, Response &res) {
    json hour_forecast;
    json body;
    
    bool retry = false;
    do {
        json body = get_cache();
        if (body.empty()) {
            body = get_json();
            if (body.empty()) {
                res.set_content("{\"error\":\"Couldn't get data from api.openweathermap.com\"}", "text/json");
                return;
            }
        }

        hour_forecast = get_hour_forecast(body["hourly"]);
        if (hour_forecast.empty()) {
            if (retry) {
                res.set_content("{\"error\":\"Couldn't get data from api.openweathermap.com\"}", "text/json");
                return;
            }
        }
    } while (retry);
    
    cache_json(body);

    std::string template_file_name = "template.html";
    std::ifstream template_file(template_file_name);
    std::string site;
    
    if (template_file.is_open()) {
        getline(template_file, site, '\0');
        template_file.close();
    } else {
        log_append_line("[Err] Could not open `template.html` file.");
        res.set_content("{\"error\":\"Could not open `template.html` file\"}", "text/json");
        return;
    }

    json out;
    out["temp"] = hour_forecast["temp"];
    out["description"] = hour_forecast["weather"][0]["description"];

    res.set_content(out.dump(), "text/json");
}

int main() {
    Server svr;
    svr.Get("/", gen_response);
    svr.Get("/raw", gen_response_raw);
    svr.Get("/test", gen_response_test);

    log_append_line("[Info] Server starting...");
    svr.listen("localhost", 3000);
}