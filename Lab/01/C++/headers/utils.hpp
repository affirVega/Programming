#pragma once
#include "../nlohmann/json.hpp"
using json = nlohmann::json;

// Makes request to openweathermap and returns json response or empty json
json get_json();

// Returns cache from `cache.json` or empty json.
json get_cache();

// Writes json to `cache.json`. Pass empty json to clear cache file.
void cache_json(json j);

// Gets forecast for this hour from hourly array. In case of error returns empty object.
json get_hour_forecast(const json &hourly);

// https://thispointer.com/find-and-replace-all-occurrences-of-a-sub-string-in-c/
void findAndReplaceAll(std::string &data, std::string toSearch, std::string replaceStr);