#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>

#include "include/cpp-httplib/httplib.h"
#include "include/nlohmann/json.hpp"
#include "include/logger.hpp"
#include "include/utils.hpp"

using json = nlohmann::json;
using namespace httplib;

void gen_response_test(const Request &req, Response &res)
{
    res.set_content("Test successful!", "text/plain;charset=utf-8");
}

void gen_response(const Request &req, Response &res)
{
    json hour_forecast;
    json body;
    
    bool retry = false;
    do
    {
        body = get_cache();
        if (body.empty())
        {
            body = get_json();
            if (!body["err"].is_null())
            {
                res.set_content(body["err"], "text/plain;charset=utf-8");
                return;
            }
			cache_json(body);
        } 
        else if (!body["err"].is_null())
        {
            res.set_content(body, "text/json;charset=utf-8");
        }
        
        hour_forecast = get_hour_forecast(body["hourly"]);
        if (!hour_forecast["err"].is_null())
        {
            if (retry)
            {
                res.set_content(hour_forecast["err"], "text/plain;charset=utf-8");
                return;
            }
        }
    } while (retry);
    

    std::string template_file_name = "template.html";
    std::ifstream template_file(template_file_name);
    std::string site;
    
    if (template_file.is_open())
    {
        getline(template_file, site, '\0');
        template_file.close();
    } 
    else
    {
        res.set_content("Error! Could not open `template.html` file.", "text/plain;charset=utf-8");
        return;
    }

    findAndReplaceAll(site, "{hourly[i].weather[0].description}", 
			hour_forecast["weather"][0]["description"]);
    findAndReplaceAll(site, "{hourly[i].weather[0].icon}", 
			hour_forecast["weather"][0]["icon"]);
    findAndReplaceAll(site, "{hourly[i].temp}", 
			std::to_string(int(std::round(hour_forecast["temp"].get<double>()))));

    res.set_content(site, "text/html;charset=utf-8");
}

void gen_response_raw(const Request &req, Response &res) {
    json hour_forecast;
    json body;
    
    bool retry = false;
    do
    {
        body = get_cache();
        if (body.empty())
        {
            body = get_json();
            if (!body["err"].is_null())
            {
                res.set_content(body, "text/json;charset=utf-8");
                return;
            }
        }
        else if (!body["err"].is_null())
        {
            res.set_content(body, "text/json;charset=utf-8");
        }
        
        hour_forecast = get_hour_forecast(body["hourly"]);
        if (!hour_forecast["err"].is_null())
        {
            if (retry)
            {
                res.set_content(hour_forecast["err"], "text/plain;charset=utf-8");
                return;
            }
        }
    } while (retry);
    
    cache_json(body);

    std::string template_file_name = "template.html";
    std::ifstream template_file(template_file_name);
    std::string site;
    
    if (template_file.is_open())
    {
        getline(template_file, site, '\0');
        template_file.close();
    }
    else
    {
        res.set_content("{\"err\":\"Could not open `template.html` file\"}", "text/json;charset=utf-8");
        return;
    }

    json out;
    out["temp"] = hour_forecast["temp"];
    out["description"] = hour_forecast["weather"][0]["description"];

    res.set_content(out.dump(), "text/json;charset=utf-8");
}

int main() {
    Server svr;
    svr.Get("/", gen_response);
    svr.Get("/raw", gen_response_raw);
    svr.Get("/test", gen_response_test);

    svr.listen("localhost", 3000);
}
