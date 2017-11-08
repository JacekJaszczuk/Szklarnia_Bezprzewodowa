#### Uruchomienie serwera
* instalacja npm: [npmjs](https://www.npmjs.com/get-npm)
* instalacja nodejs: [nodejs](https://nodejs.org/en/download/package-manager/)
* instalacja pakietów:
```
cd sys_wbud
npm install
```
* uruchomienie serwera:
```
npm start
```
Serwer nasłuchuje na porcie 3000. Slave'y mogą robić zapytania GET z parametrami:
- id - numer slave'a,
- value - wartość odczytana z czytnika.
np:
```
localhost:3000/data?id=1&value=3.1415
```

#### Baza:
W pliku `config.js` należy podać względną ścieżkę do pliku bazy sqlite3.
```
sqlite> CREATE TABLE slave (id integer primary key autoincrement, name_flower varchar(255));
sqlite> CREATE TABLE measurement (id integer primary key autoincrement, slave_id int, measurement decimal(2, 1), timestamp datetime, FOREIGN KEY (slave_id) REFERENCES slave(id) );
```
