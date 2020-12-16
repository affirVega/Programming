/*
 * TODO: Make declaration of config in ONE place!
 *
 *
 * */

#include <iostream>
#include <string>
#include <ctime>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../include/cpp-httplib/httplib.h"
#include "../include/nlohmann/json.hpp"
#include "raii_file.hpp"
using namespace httplib;
using json = nlohmann::json;



// ---------------------------------------------------------------------------
// Global variables
// ---------------------------------------------------------------------------

const json default_config = {
	{"group_token", "Place your group token here!"},
	{"api_link", 	"https://api.vk.com"},
	{"api_version", "5.126"}
};

const std::string config_filename = "config.json";

struct Config
{
	std::string group_token;
	std::string	api_version;
	std::string api_link;
	Client		api;

	Result call_api(std::string method, std::string params)
	{
		auto res = api.Get(("/method/" + method + "?" + params
				           + "&access_token=" + group_token + "&v=" + api_version).c_str());
		return res;
	}

	Config(std::string group_token,
		   std::string api_version,
		   std::string api_link)
	 	 : api(api_link.c_str())
	{
		this->group_token = group_token;
		this->api_version = api_version;
		this->api_link    = api_link;
	}
};

struct LongPollConfig
{
	std::string key;
	std::string server;
	Client		lp;
	std::string ts;
	int 		wait;

	Result call_api(std::string act)
	{
		using std::to_string;
		// auto res = lp.Get(("/?act=" + act + "&key=" + key + "&ts=" + to_string(ts)
		// 		          + "&wait=" + to_string(wait)).c_str());
		auto res = lp.Get(("/?act=" + act + "&key=" + key + "&ts=" + ts
				          + "&wait=" + to_string(wait)).c_str());
		return res;
	}

	LongPollConfig(std::string key,
				   std::string server,
				   std::string ts = "1",
				   int wait = 25)
				 : lp(server.c_str())
	{
		this->key = key;
		this->server = server;
		this->ts = ts;
		this->wait = wait;
	}
};


									// {server}?act=a_check&key={key}&ts={ts}&wait=25 



// ---------------------------------------------------------------------------
// Creates config and exits from program
// ---------------------------------------------------------------------------
void create_config_and_exit()
{
	raii_file config_file(config_filename, std::fstream::out);
	if (!config_file)
	{
		std::cerr << "File '" << config_filename << "' cannot be created." << std::endl;
		exit(1);
	}

	config_file.get() << default_config.dump(4) << std::endl;
	
	std::cout << "Please check '" << config_filename << "' file and change token." << std::endl;
	exit(1);
}



// ---------------------------------------------------------------------------
// Reloads config from config file and returns Config object
// ---------------------------------------------------------------------------
json reload_config()
{
	raii_file config_file(config_filename, std::fstream::in);
	if (config_file)
	{

		json config_json = json::parse(config_file.get());

		if (   not config_json.contains("group_token")
		    or not config_json.contains("api_link")
			or not config_json.contains("api_version"))
		{
			std::cout << "Config file '" << config_filename << "' is invalid. "
				"Please rename it or delete." << std::endl;
			exit(1);
		}

		return {config_json["group_token"],
				config_json["api_version"],
				config_json["api_link"]};
	}
	else
	{
		create_config_and_exit();
	}
}



json get_longpoll(Config& cfg)
{
	std::string method 	 = "groups.getLongPollServer";
	std::string group_id = "201171455";

	auto res = cfg.call_api(method, "group_id="+group_id);

	if (!res)
	{
		std::cerr << res.error() << std::endl;
		exit(1);
	}

	if (res->status < 200 or res->status >= 300)
	{
		std::cerr << "Got status " << res->status << " from API server " << cfg.api_link << std::endl;
		exit(1);
	}

	std::cout << "longpoll: " << res->body << std::endl;
	json result_json = json::parse(res->body);
	if (result_json.contains("error"))
	{
		std::cerr << result_json["error"].dump(2) << std::endl;
		exit(1);
	}

	return {result_json["response"]["key"],
			result_json["response"]["server"],
			result_json["response"]["ts"]};
}



// ---------------------------------------------------------------------------
// Startup function
// ---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	json temp = reload_config();
	std::cout << "Read config: " << temp << std::endl;
	Config cfg(temp[0], temp[1], temp[2]);

	temp = get_longpoll(cfg);
	std::cout << "longpoll_got: " << temp << std::endl;
	LongPollConfig lpcfg(temp[0], temp[1], temp[2]);
}
