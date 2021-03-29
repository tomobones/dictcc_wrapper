#ifndef _WEB_CLIENT_H_
#define _WEB_CLIENT_H_

void scrape_vocabs_for_search(char* lang, char* search_string);
void login_user(char* user, char* pass);
void scrape_vocablists_for_lang(char* lang);
void add_vocab_to_vocablist(int vocab_id, int list_id);
void web_client_clean_up(void);

void print_url(void);

#endif
