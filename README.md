# dict.cc terminal client

## Dependencies
- 'ncurses' for UI
- 'curl' for html requests
- 'regex' for pattern search in html data
- [minUnit](http://www.jera.com/techinfo/jtns/jtn002.html) for minimal unit testing

## Aimed Functionality
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
- [ ] Get rid of unwanted characters in vocabulary
- [ ] Ability to scroll - display some scroll progress
- [ ] Deal with special characters like german Umlaute
- [ ] Problem with "wahrnehmen"
- [ ] Write unit tests
- [ ] Test special cases
