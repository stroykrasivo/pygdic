#include <stdio.h>

#include <string.h>
#include <iostream>
#include <curl/curl.h>
using namespace std;

string chunk;

static size_t WriteDataCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  cout << contents.c_str();
  cout << "\n" << size;
  cout << "\n" << nmemb;
  cout << "\n" << userp;

  return nmemb;
}
 
int main(void)
{
  CURL *curl;
  CURLcode res;


 
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://www.c-cpp.ru/books/yazyk-s");

	/* send all data to this function  */ 
  	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteDataCallback);

	/* we pass our 'chunk' struct to the callback function */ 
  	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
 
    /* Выполнение запроса, res будет содержать код возврата */ 
    res = curl_easy_perform(curl);
    /* Проверка на ошибки */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* Очистка */ 
    curl_easy_cleanup(curl);
	cout << "curl_easy_perform() return : ";
	cout << chunk.c_str();
	cout << "\n";

  }
  return 0;
}
