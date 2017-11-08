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
