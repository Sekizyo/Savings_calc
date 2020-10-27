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

void choices(){ // Wybieranie trybu wprowadzania danych
    // system("clear");
    string mode;
    string dynamic;

    cout << "\nWybierz tryb wprowadzania danych: \n";
    cout << "1. Zaladuj z pliku\n";
    cout << "2. Wprowadz recznie\n";
    cin >> mode;

    if(mode == "1"){
        load_config();
    }
    else if (mode == "2")
    {
        manual_config();
    }
    else
    {
        cout << "Wprowadz poprawną wartosc\n";
        choices();
    }

    cout << "\nZmienne wartosci?\n";
    cout << "t/n \n";
    cin >> dynamic;

    if(dynamic == "t"){
        string wyb;
        string month;

        dynamic_values = true;

        cout << "Ktora wartosc ma byc dynamiczna?\n";
        cout << "1. Oprocentowanie\n";
        cout << "2. Czestotliwosc kapitalizacji\n";
        cout << "3. Miesieczna wplata\n";
        cin >> wyb;

        cout << "Od ktorego miesiaca wartosc ma sie zmienic?\n";
        cin >> month;

    }
    else
    {
        return;
    }
}

void calculate(){ // Właściwe obliczenia
    int a = 0;
}

void draw_data(){ // Wypisz wprowadzone dane
    // system("clear");
    cout << "\nIlość miesięcy oszczędzania: " << miesiace << "\n";
    cout << "Oprocentowanie środków (w skali rocznej): " << procent << "\n";
    cout << "Częstotliwość kapitalizacji (co ile miesięcy): " << kapita << "\n";
    cout << "Miesięczna wplata: " << wplata << "\n";
    return;
}

void draw_menu(){
    choices();
    draw_data();
    calculate();
}

int main(int argc, char const *argv[])
{
    bool running = true;
    while(running == true){
        draw_menu();
    }
    return 0;
}
