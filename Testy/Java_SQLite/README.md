# Java_SQLite  
## Przykład jak użyć bazy danych SQLite z poziomu JAVY. Projekt w Eclipse. 

Jest to lekko przerobiona wersja przykładu z [tej](https://github.com/xerial/sqlite-jdbc#usage) strony.

W pliku [baza.db](baza.db) znajduje się baza danych z utworzoną tabelą. Polecenie do tworzenia tabeli było następujące:  
`CREATE TABLE Pracownicy (ID INTEGER PRIMARY KEY AUTOINCREMENT, Imie VARCHAR(255) NOT NULL, Nazwisko VARCHAR(255) NOT NULL);`  
Do bazy danych wprowadzono 10 pracowników.

Biblioteka do obsługi baz danych została pobrana [stąd](https://bitbucket.org/xerial/sqlite-jdbc/downloads/).

