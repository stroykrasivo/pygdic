#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_BUF	65536

char wr_buf[MAX_BUF+1];
int wr_index;

/*
 * Write data callback function (called within the context of * curl_easy_perform.
 */

size_t write_data( void *buffer, size_t size, size_t nmemb, void *userp )
{
 int segsize = size * nmemb;

 /* Check to see if this data exceeds the size of our buffer. If so, 
 * set the user-defined context value and return 0 to indicate a
 * problem to curl.
 */
 if ( wr_index + segsize > MAX_BUF ) {
 *(int *)userp = 1;
 return 0;
 }

 /* Copy the data from the curl buffer into our buffer */
 memcpy( (void *)&wr_buf[wr_index], buffer, (size_t)segsize );

 /* Update the write index */
 wr_index += segsize;

 /* Null terminate the buffer */
 wr_buf[wr_index] = 0;

 /* Return the number of bytes received, indicating to curl that all is okay */
 return segsize;
}
/*
 * Simple curl application to read the index.html file from a Web site.
 */
int main( void )
{
 CURL *curl;
 CURLcode ret;
 int wr_error;

 wr_error = 0;
 wr_index = 0;

 /* First step, init curl */
 curl = curl_easy_init();
 if (!curl) {
 printf("couldn't init curl\n");
 return 0;
 }

curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

/* only allow redirects to HTTP and HTTPS URLs */
  curl_easy_setopt(curl, CURLOPT_REDIR_PROTOCOLS,
                   CURLPROTO_HTTP | CURLPROTO_HTTPS);

 /* Tell curl the URL of the file we're going to retrieve */
 curl_easy_setopt( curl, CURLOPT_URL, "https://translate.google.com/?hl=ru&langpair=auto|ru&text=retrieve" );

 /* Tell curl that we'll receive data to the function write_data, and
 * also provide it with a context pointer for our error return.
 */
 curl_easy_setopt( curl, CURLOPT_WRITEDATA, (void *)&wr_error );
 curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, write_data );

 /* Allow curl to perform the action */
 ret = curl_easy_perform( curl );

 printf( "ret = %d (write_error = %d)\n", ret, wr_error );

 /* Emit the page if curl indicates that no errors occurred */
 if ( ret == 0 ) printf( "%s\n", wr_buf );

 curl_easy_cleanup( curl );

 return 0;
}
