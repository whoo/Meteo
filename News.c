#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


#define URL "http://www.france24.com/fr/actualites/rss/"

struct MemoryStruct { char *memory; size_t size; };
static void
print_element_names(xmlNode * a_node)
{
	xmlNode *cur_node = NULL,*cur;
	char *key;
	char *name;

	for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE) {
			//			printf("node type: Element, name: %s\n", cur_node->name);
			if (!xmlStrcmp(cur_node->name,"item"))
			{
				cur=cur_node;
				for (cur=cur_node->children;cur;cur=cur->next)
				{
					if (!xmlStrcmp(cur->name,"category")&&cur->children)
						printf("[%s]",cur->children->content);
					if (!xmlStrcmp(cur->name,"title")&&cur->children)
						printf(" %s\n",cur->children->content);
				}


			}
		}

		print_element_names(cur_node->children);
	}
}


void parsxml(struct MemoryStruct *document)
{
	xmlDocPtr doc;
	xmlNodePtr cur;
	char *key;

	doc=xmlParseMemory(document->memory,document->size);
	cur=xmlDocGetRootElement(doc);
	//cur=cur->xmlChildrenNode;
	//
	print_element_names(cur->children);
	//


	xmlMemoryDump();


	xmlFreeDoc(doc);
	xmlCleanupParser();



}

size_t write_data(void *ptr, size_t size, size_t nmemb, void *userp) 
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
	FILE *fp;
	struct MemoryStruct chunk;

	chunk.memory = malloc(1);
	chunk.size = 0;



	curl_global_init(CURL_GLOBAL_ALL);
	curl_easy_setopt(curl, CURLOPT_URL,URL);
	//	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, parsxml);//
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
	res = curl_easy_perform(curl);

	if (res == CURLE_OK)
		{
		parsxml(&chunk);
		}

	curl_easy_cleanup(curl);



}