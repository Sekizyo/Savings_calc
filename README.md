<p align="center">
  <h3 align="center">Kalkulator na procent składany</h3>
</p>


## Spis treści

* [O projekcie](#O-projekcie)
* [Uruchamianie](#Uruchamianie)
  * [Instalacja](#Instalacja)
* [Używanie](#Używanie)
  * [Przykłady](#Przykłady)
  * [Opcje](#Opcje)
* [Licencja](#Licencja)
* [Kontakt](#Kontakt)


<!-- ABOUT THE PROJECT -->
## O projekcie
Autor: Matas Pieczulis
Projekt został wykonany na lekcję Informatyki

Zadanie: Należy napisać program konsolowy w C++, który sporządzi raport z symulacji oszczędzania na tzw. "procent składany'.


<!-- GETTING STARTED -->
## Uruchamianie

### Instalacja

1. Klonowanie repozytorium
```sh
git clone https://github.com/Sekyzio/Savings_calc.git
```

2. Następnie należy skompilować plik main.cpp używająć kompilatora c++.

  ```sh
  gcc main.cpp
  ```
  Lub:
  ```sh
  g++ main.cpp
  ```

## Używanie

By użyć programu należy wprowadzić odpowiednie argumenty.
* Miesiące oszczędzania
* Miesięczna wpłata
* Oprocentowanie w skali rocznej
* Kapitalizacja

```sh
main.exe 12 500 2.5 1
```

Wynik obliczeń zapisuje do pliku "output.csv".


### Przykłady
Będzie kontynuować obliczenia z pliku "output.csv" z nowymi wartościami.
```sh
 main.exe 36 750 2.2 1 -c
```

### Opcje
 ```
/?, -help      Standardowa pomoc 
-c             Kontynuacja poprzednich obliczeń z nowymi wartościami
 ```


## Licencja

Distributed under the MIT License. See `LICENSE` for more information.

## Kontakt

Email: mateuszpieczulis123@gmail.com 

Github: [https://github.com/Sekyzio](https://github.com/Sekyzio)

