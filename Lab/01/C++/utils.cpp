#include <fstream>
#include "yhirose/httplib.h"
#include "nlohmann/json.hpp"
#include "headers/logger.hpp"
using json = nlohmann::json;
using namespace httplib;

// TODO: Load from `config.json` file.
Client cli("http://api.openweathermap.org");
std::string latitude = "45.0522222222";
std::string longitude = "33.9744444444";
std::string exclude = "current,minutely,daily,alerts";
std::string lang = "ru";
std::string units = "metric";
std::string appid = "4b4b143c5f50ea5d5810563a8346acc0";

// https://thispointer.com/find-and-replace-all-occurrences-of-a-sub-string-in-c/
void findAndReplaceAll(std::string &data, std::string toSearch, std::string replaceStr) {
    size_t pos = data.find(toSearch);
    while (pos != std::string::npos) {
        data.replace(pos, toSearch.size(), replaceStr);
        pos = data.find(toSearch, pos + replaceStr.size());
    }
}

json get_json() {
	log_append_line("[Info] Entered get_json");
    std::string request = "/data/2.5/onecall?lat=" + latitude + "&lon=" + longitude +
        "&exclude=" + exclude + "&appid=" + appid + "&units=" + units + "&lang=" + lang;
    
	auto result = cli.Get(request.c_str());
	
	if (!result) {
		log_append_line("[Err] Request wasn't successful");
		
        return json::object();
	}
	
	int status_code = result->status;

    if (status_code < 200 || status_code >= 300) {
		log_append_line("[Err] Got non-successful code " + std::to_string(status_code) + ".");
		
        return json::object();
	}
	findAndReplaceAll(result->body, "\\\"", "\"");
	
	log_append_line("[Info] Left get_json");
	return json::parse(result->body);
}

json get_cache() {
	log_append_line("[Info] Entered get_cache");
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
		log_append_line("[Error] Could not open `cache.json` to read cache.");
	}
	log_append_line("[Info] Left get_cache");
	return cache;
}

void cache_json(json j) {
	log_append_line("[Info] Entered cache_json");
	std::ofstream cache_file("cache.json");
	if (cache_file.is_open()) {
		cache_file << j;
		cache_file.close();
	} else {
		log_append_line("[Error] Could not open `cache.json` to write cache.");
	}
	log_append_line("[Info] Left cache_json");
}

json get_hour_forecast(const json &hourly) {
	log_append_line("[Info] Entered get_hour_forecast");
	json hour_forecast;
	
    int last = hourly.size() - 1;
    int current_time = std::time(0);
	
    if (hourly[last]["dt"] < current_time) {
		log_append_line("[Info] Cache got old.");
        return json::object();
    }
	
    for (int i = 0; i <= last; ++i) {
        if (hourly[i]["dt"] >= current_time) {
            hour_forecast = hourly[i];
            break;
        }
    }
	log_append_line("[Info] Left get_hour_forecast");
    return hour_forecast;
}