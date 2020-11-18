#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "yhirose/httplib.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace httplib;

json cache;
int	 unixtime = -1;


Client cli("http://api.openweathermap.org");
std::string latitude  = "45.0522222222";
std::string longitude = "33.9744444444";
std::string exclude   = "current,minutely,daily,alerts";
std::string lang      = "ru";
std::string units     = "metric";
std::string appid     = "4b4b9867687dg6sd876d87sa6d8a7s78";

// https://thispointer.com/find-and-replace-all-occurrences-of-a-sub-string-in-c/
void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
{
    size_t pos = data.find(toSearch);
    while( pos != std::string::npos)
    {
        data.replace(pos, toSearch.size(), replaceStr);
        pos =data.find(toSearch, pos + replaceStr.size());
    }
}

void gen_response_test(const Request& req, Response& res) {
  std::ofstream log("server.log", std::ofstream::app);
	log << "[log] Test successful!" << std::endl;
	res.set_content("Test successful!", "text/plain");
	log.close();
}

void gen_response(const Request& req, Response& res) {
  std::ofstream log("server.log", std::ofstream::app);
  log << "[log]" << ": gen_response began" << std::endl;
  std::string request = "/data/2.5/onecall?lat="+latitude+"&lon="+longitude+
    "&exclude="+exclude+"&appid="+appid+"&units="+units+"&lang="+lang;

  json body;
  bool b = true;
  int status_code = 200;
  if (::cache.empty()) {
	log << "[log]" << "Cache was empty" << std::endl;
	auto result = cli.Get(request.c_str());

	auto str = result->body;
	findAndReplaceAll(str, "\\\"", "\"");
	body = json::parse(str);

	status_code = result->status;
  } else {
	body = ::cache;
  }
  log << "[log]" << ": b, status_code = " << b << " " << status_code << " "<< std::endl;

  if (b) {
    if (status_code == 200) {
	  log << "[log]" << "Everything's okay, start processing json" << std::endl;
      ::cache = body;

	  std::ofstream cache_file("cache.json");
	  cache_file << ::cache;
	  cache_file.close();

	  log << "[log]" << "creating json hour_forecast" << std::endl;
      json hour_forecast;

	  log << "[log]" << "Getting hourly size" << std::endl;
      int size = body["hourly"].size();

	  log << "[log]" << "Getting current time" << std::endl;
      int current_time = std::time(0);
	  log << "[log]" << "After current time" << std::endl;

      if (body["hourly"][size - 1]["dt"] < current_time) {
	    log << "[log]" << "Cache is old, creating new request" << std::endl;
      	::cache = json::object();
      	gen_response(req, res);
      	return;
      }
      for (int i = 0; i < size-1; ++i) {
        if (body["hourly"][i]["dt"] >= current_time) {
          hour_forecast = body["hourly"][i];
		  break;
        }
      }
      if (hour_forecast.empty()) {
        log << "Time error! System time goes before returned forecasts." << std::endl;
        return;
      }

      std::string template_file_name = "template.html";
      std::ifstream template_file(template_file_name);
      std::string site; 
      if (template_file.is_open()) {
        getline(template_file, site, '\0');
      } else {
        std::cerr << "Error with opening template file: " << template_file_name << std::endl;
        return;
      }

	  log << "[log]" << "began working on site" << std::endl;

      // TODO: check if begin != std::npos
      findAndReplaceAll(site, "{hourly[i].weather[0].description}", hour_forecast["weather"][0]["description"]);

	  log << "[log]" << "second replace" << std::endl;
      findAndReplaceAll(site, "{hourly[i].weather[0].icon}", hour_forecast["weather"][0]["icon"]);

	  log << "[log]" << "third replace" << std::endl;
      findAndReplaceAll(site, "{hourly[i].temp}", std::to_string(int(std::round(hour_forecast["temp"].get<double>()))));

      res.set_content(site, "text/html");
    } else {

      res.set_content("Error happened. Got code != 200", "text/html");
    }
  } else {

    res.set_content("Error happened. b == false", "text/html");
  }
  log.close();
}


void gen_response_raw(const Request& req, Response& res) {
  std::ofstream log("server.log", std::ofstream::app);
  log << "[log]" << ": gen_response began" << std::endl;
  std::string request = "/data/2.5/onecall?lat="+latitude+"&lon="+longitude+
    "&exclude="+exclude+"&appid="+appid+"&units="+units+"&lang="+lang;

  json body;
  bool b = true;
  int status_code = 200;
  if (::cache.empty()) {
	log << "[log]" << "Cache was empty" << std::endl;
	auto result = cli.Get(request.c_str());

	auto str = result->body;
	findAndReplaceAll(str, "\\\"", "\"");
	body = json::parse(str);

	status_code = result->status;
  } else {
	body = ::cache;
  }
  log << "[log]" << ": b, status_code = " << b << " " << status_code << " "<< std::endl;

  if (b) {
    if (status_code == 200) {
	  log << "[log]" << "Everything's okay, start processing json" << std::endl;
      ::cache = body;

	  std::ofstream cache_file("cache.json");
	  cache_file << ::cache;
	  cache_file.close();


	  log << "[log]" << "creating json hour_forecast" << std::endl;
      json hour_forecast;

	  log << "[log]" << "Getting hourly size" << std::endl;
      int size = body["hourly"].size();

	  log << "[log]" << "Getting current time" << std::endl;
      int current_time = std::time(0);
	  log << "[log]" << "After current time" << std::endl;

      if (body["hourly"][size - 1]["dt"] < current_time) {
	    log << "[log]" << "Cache is old, creating new request" << std::endl;
      	::cache = json::object();
      	gen_response(req, res);
      	return;
      }
      for (int i = 0; i < size-1; ++i) {
        if (body["hourly"][i]["dt"] >= current_time) {
          hour_forecast = body["hourly"][i];
		  break;
        }
      }
      if (hour_forecast.empty()) {
        log << "Time error! System time goes before returned forecasts." << std::endl;
        return;
      }

	  json out;
	  out["temp"] = hour_forecast["temp"];
	  out["description"] = hour_forecast["weather"][0]["description"];

	  res.set_content(out.dump(), "text/json");
    } else {

      res.set_content("Error happened. Got code != 200", "text/html");
    }
  } else {

    res.set_content("Error happened. b == false", "text/html");
  }
  log.close();
  // TODO:
  // {
  //   temp:        hourly[i].temp
  //   description: hourly[i].weather[0].description
  // }
}

int main(){
  std::ofstream log("server.log");
  Server svr;
  svr.Get("/", gen_response);
  svr.Get("/raw", gen_response_raw);
  svr.Get("/test", gen_response_test);
  
  std::ifstream cache_file("cache.json");
  if (cache_file.is_open()) {
	  std::string content;
	  getline(cache_file, content, '\0');
	  if (!content.empty())
		::cache = json::parse(content);
  } else {
	  log << "error opening cache file." << std::endl;
  }
  cache_file.close();
  log.close();

  log << "Server starting..." << std::endl;
  svr.listen("localhost", 3000);
}
