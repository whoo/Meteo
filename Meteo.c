#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <json-c/json.h>


#define url "http://api.openweathermap.org/data/2.5/group?id=6077243,3033123,934154&units=metric&lang=fr"


char *strupr(char *s) { 
	unsigned c; 
	unsigned char *p = (unsigned char *)s; 
	while (c = *p) *p++ =(unsigned char)((int)c>130)?'E':toupper(c); 
	return s;
} 

size_t writedd(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	json_object *new_obj,*list;

	if (!(new_obj = json_tokener_parse(ptr))) return 0;

	list=json_object_object_get(new_obj,"list");

	for (int a=0;a<json_object_array_length(list);a++)
	{
		json_object *w,*m,*c1;

		c1=json_object_array_get_idx(list,a);

		// LIST[0]->name
		// LIST[0]->weather[0]->description
		// LIST[0]->main['temp']

		w=	json_object_array_get_idx(json_object_object_get(c1,"weather"),0);
		m= 	json_object_object_get(c1,"main");
	char *txt=malloc(100);
	sprintf(txt,"%s - %s : Temp %dC (min %d/max %d) %d %%\n",
				json_object_get_string(json_object_object_get(c1,"name")),
				json_object_get_string(json_object_object_get(w,"description")),
				json_object_get_int(json_object_object_get(m,"temp")),
				json_object_get_int(json_object_object_get(m,"temp_min")),
				json_object_get_int(json_object_object_get(m,"temp_max")),
				json_object_get_int(json_object_object_get(m,"humidity"))
		      );

//	printf("%s",strupr(txt));
	printf("%s",txt);

	}

	return 0;
}

int main(int argc,char **argv)
{

	CURL *curl = curl_easy_init();
	CURLcode res;

	curl_easy_setopt(curl, CURLOPT_URL,url);
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, writedd);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	return 1;
}

