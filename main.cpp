#include <iostream>
#include <fstream>
using namespace std;

int miesiace = 0; // Ilość miesięcy oszczędzania
double procent = 0; // Oprocentowanie środków w skali rocznej
int kapita = 0; // Częstotliwość kapitalizacji w miesiącach
double wplata = 0; // Miesięczna wpłata
bool dynamic_values = false;

void create_config(){ // Stworzenie pliku wejściowego
    try
    {
        std::ofstream outfile ("config.txt");
        outfile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        cout << "Nie mozna utworzyć pliku\n";
        exit(0);
    }
    cout << "Poprawnie utworzono plik\n";
    exit(0);
}

void load_config(){ // Wczytanie danych wejściowych z pliku
    int loop = 0;
    string line; 
    string lines[4];
    ifstream input_file("config.txt"); // Otwarcie pliku

    if (!input_file){create_config();} // Sprawdzenie czy plik istnieje

    while(getline (input_file, line)) { // Odczytanie wszytkich lini z pliku i zapisanie ich w liście
        lines[loop] = line;
        loop++;
    }
    input_file.close(); // Zamknięcie pliku
    
    try // Sprawdzanie poprawności wartości oraz konwersja to odpowiedniego typu
    {
        miesiace = stoi(lines[0]); 
        procent = stod(lines[1]);
        kapita = stoi(lines[2]);
        wplata = stod(lines[3]);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << ", Błąd podczas konwersji\n";
        cout << "Wprowadzono błędne dane \n";
    }
    
    return;
}

void manual_config(){ // Ręcznie wprowadzanie danych
    int a = 0;
}

void save_data(){ // Zapisanie wyniku do pliku
    int a = 0;
}


int main(int argc, char const *argv[])
{
    return 0;
}
