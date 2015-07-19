#include "utils.h"

#include <curl/curl.h>
#include <json.h>


#define url "http://api.openweathermap.org/data/2.5/group?id=6077243,3033123,934154&units=metric&lang=fr"





size_t parsemeteo(struct MemoryStruct *ptr)
{
	json_object *new_obj,*list;

	if (!(new_obj = json_tokener_parse(ptr->memory))) return 0;

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
		printf("%s",Supper(txt));

	}
	return 0;
}



size_t writedd(char *ptr, size_t size, size_t nmemb, void *userp)
{
	size_t realsize=size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;
	mem->memory = realloc(mem->memory,mem->size + realsize +1 );
	memcpy(&(mem->memory[mem->size]),ptr,realsize);
	mem->size +=realsize;
	mem->memory[mem->size]=0;
	return realsize;

}

int main(int argc,char **argv)
{

	CURL *curl = curl_easy_init();
	CURLcode res;
	struct MemoryStruct buf;

	 buf.memory = malloc(1);
	          buf.size = 0;


	curl_easy_setopt(curl, CURLOPT_URL,url);
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writedd );
	curl_easy_setopt(curl,CURLOPT_WRITEDATA, (void*)&buf);
	res = curl_easy_perform(curl);

	if (res==CURLE_OK)
	{
	parsemeteo(&buf);
	}
	
	curl_easy_cleanup(curl);

	return 1;
}

