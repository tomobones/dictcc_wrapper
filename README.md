# dict.cc terminal client

## Dependencies
- 'ncurses' for UI
- 'curl' for html requests
- 'regex' for pattern search in html data
- [minUnit](http://www.jera.com/techinfo/jtns/jtn002.html) for minimal unit testing

## Functionality
- Search for specific vocabulary on [dict.cc](https://dict.cc)
- Save chosen entries in one of your vocabulary lists

## Todo List - Requirements - Status 2021-05-13
- [x] Search for vocabulary
- [x] Parse vocabulary lists for a language
- [x] API to add vocabulary to list
- [x] Simple UI via ncurses
- [x] Choose vocabulary in UI
- [x] Choose vocabulary list in UI
- [x] Add chosen vocabulary to chosen list
- [x] Deal with arguments
- [x] Added unit testing
- [x] Get rid of unwanted characters in vocabulary
- [ ] Ability to scroll - display some scroll progress
- [ ] Deal with special characters like german Umlaute
- [ ] Info Window with key binding
- [ ] Arrow keys, Return key
- [ ] Exit, if opening session not successful
- [ ] Exit, if vocab lists has no entry

## Todo List - Tests - Status 2021-05-13
- [ ] Write unit tests
- [ ] Test special cases
- [ ] Problem with "wahrnehmen"
- [ ] Behavior, if no internet connection
