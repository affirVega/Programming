#include <fstream>
#include "include/cpp-httplib/httplib.h"
#include "include/nlohmann/json.hpp"
using json = nlohmann::json;
using namespace httplib;

// TODO: Load from `config.json` file.
Client owm("http://api.openweathermap.org");
std::string latitude  = "45.0522222222";
std::string longitude = "33.9744444444";
std::string exclude   = "current,minutely,daily,alerts";
std::string lang      = "ru";
std::string units     = "metric";
std::string appid     = "4b4b143c5f50ea5d5810563a8346acc0";

Client time_srv("http://worldtimeapi.org");

json cache;

// https://thispointer.com/find-and-replace-all-occurrences-of-a-sub-string-in-c/
void findAndReplaceAll(std::string &data, std::string toSearch, std::string replaceStr) {
    size_t pos = data.find(toSearch);
    while (pos != std::string::npos) {
        data.replace(pos, toSearch.size(), replaceStr);
        pos = data.find(toSearch, pos + replaceStr.size());
    }
}

json get_json() {
    std::string request = "/data/2.5/onecall?lat=" + latitude + "&lon=" + longitude +
        "&exclude=" + exclude + "&appid=" + appid + "&units=" + units + "&lang=" + lang;
    
	auto result = owm.Get(request.c_str());
	
	if (!result) {
		return {"err", "Request to weather server wasn't successful"};
	}
	
	int status_code = result->status;

    if (status_code < 200 || status_code >= 300) {
		return {"err", "Got non-successful code " + std::to_string(status_code) + "."};
	}
	//findAndReplaceAll(result->body, "\\\"", "\"");
	
	return json::parse(result->body);
}

json get_cache() {
    if (!cache.empty())
    {
        return cache;
    }
	json cache;
	std::ifstream cache_file("cache.json");
    if (cache_file.is_open()) {
        std::string content;
        getline(cache_file, content, '\0');
		
        if (!content.empty()) {
            cache = json::parse(content);
		}
		cache_file.close();
    } else {
		return {"err", "Could not open `cache.json` to read cache."};
	}
	return cache;
}

bool cache_json(json j) {
    cache = j;
	std::ofstream cache_file("cache.json");
	if (cache_file.is_open()) {
		cache_file << j;
		cache_file.close();
	} else {
		return false;
	}
    return true;
}

json get_time() {
    std::string request = "/api/timezone/Europe/Simferopol";
    
	auto result = time_srv.Get(request.c_str());
	
	if (!result) {
		return {"err", "Request to time server wasn't successful"};
		
        return json::object();
	}
	
	int status_code = result->status;

    if (status_code < 200 || status_code >= 300) {
        return {"err", "Got non-successful code " + std::to_string(status_code) + "."};
	}
	//findAndReplaceAll(result->body, "\\\"", "\"");
	
	return json::parse(result->body);
}

json get_hour_forecast(const json &hourly) {
	json hour_forecast;
	
    int last = hourly.size() - 1;
    int current_time;
    json time_j = get_time();
    if (time_j["err"].is_null()) {
        current_time = time_j["unixtime"];
    } else {
        current_time = std::time(0); // in case of fail, use system time.
    }
	
    if (hourly[last]["dt"] < current_time) {
        return json::object();
    }
	
    for (int i = 0; i <= last; ++i) {
        if (hourly[i]["dt"] >= current_time) {
            hour_forecast = hourly[i];
            break;
        }
    }
    return hour_forecast;
}
