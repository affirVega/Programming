#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "include/cpp-httplib/httplib.h"
using namespace httplib;

/* Функции для управления вебхуками через веб-интерфейс. */
void webhooks_get(const Request& req, Response& res);
void webhooks_post(const Request& req, Response& res);

/* Функция для вебхука Алисы. */
void yandex_hook(const Request& req, Response& res);

int main()
{
	// ---------------------------------------------------------
	// Update: к чёрту эту хрень, переводите терминалы на UTF-8.
	// https://stackoverflow.com/a/57134096
	// ---------------------------------------------------------

//#if defined(_WIN32) || defined(WIN32)
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
//#endif

	Server srv;

	// Для проверки пригодится https://webhook.site/
	srv.Get("/webhooks", webhooks_get);
	srv.Post("/webhooks", webhooks_post);

	// Яндекс будет посылать периодические запросы, а так же запросы при изменении состояния чатов.
	srv.Post("/yandex_hook", yandex_hook);

	std::cout << "Сервер успешно запустился!\n"
		<< "Сервер откыт по адресу localhost:1234\n\n"
		<< "Откройте http://localhost:1234/webhooks в веб-браузере, "
		<< "чтобы получить доступ к панели управления веб-хуками.\n"
		<< "Вебхук для яндекса http://localhost:1234/yandex_hook."
		<< std::endl;

	srv.listen("localhost", 1234);
}


