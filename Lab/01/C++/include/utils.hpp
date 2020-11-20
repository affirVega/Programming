#pragma once
#include "nlohmann/json.hpp"
using json = nlohmann::json;

// Makes request to openweathermap and returns json response or json {"err": message}.
json get_json();

// Returns cache from `cache.json` or or json {"err": message}.
json get_cache();

// Writes json to `cache.json`. Pass empty json to clear cache file.
bool cache_json(json j);

// Gets json of time from worldtimeapi.org
json get_time();

// Gets forecast for this hour from hourly array. In case of error returns empty object.
json get_hour_forecast(const json &hourly);

// https://thispointer.com/find-and-replace-all-occurrences-of-a-sub-string-in-c/
void findAndReplaceAll(std::string &data, std::string toSearch, std::string replaceStr);
