#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int miesiace = 12; // Ilość miesięcy oszczędzania
float procent = 5.5; // Oprocentowanie środków w skali rocznej
float mies_proc = procent/12;
int kapita = 1; // Częstotliwość kapitalizacji w miesiącach
double wplata = 500; // Miesięczna wpłata

double wynik = wplata; // Wynik z oblicze
double odsetki = 0;

bool dynamic_values = false;
int count_from = 0; // Miesiac od ktorego zmiany maja byc wprowadzone
double new_percent = procent;
int new_kapita = kapita;
double new_wplata = wplata;

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

        new_percent = procent;
        new_kapita = kapita;
        new_wplata = wplata;
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
    cin >> dynamic; //TODO add podatek

    if(dynamic == "t"){
        string wyb;
        string month;

        dynamic_values = true;

        cout << "Ktora wartosc ma byc dynamiczna?\n";
        cout << "1. Oprocentowanie\n";
        cout << "2. Czestotliwosc kapitalizacji\n";
        cout << "3. Miesieczna wplata\n";
        cin >> wyb;

        cout << "Podaj nowa wartosc\n";
        if(wyb == "1")
        {
            cin >> new_percent; // TODO variable conversion
        }
        else if (wyb == "2")
        {
            cin >> new_kapita;
        }
        else if (wyb == "3")    
        {
            cin >> new_wplata;
        }
        else 
        {
            cout << "Podaj poprawną wartość\n";
            choices(); // TODO fix
        }

        cout << "Od ktorego miesiaca wartosc ma sie zmienic?\n";
        cin >> month;
        count_from = stoi(month);
    }
    else
    {
        return;
    }
}

void calculate(){ // Właściwe obliczenia
    float odsetki_nienaliczone = 0;
    int loop = kapita-1;
    for (int i = 0; i < miesiace; i++) {

        if(dynamic_values == true || count_from == i){
            procent = new_percent;
            mies_proc = procent/12;
            kapita = new_kapita;
            wplata = new_wplata;
        }
        
        odsetki = wynik * mies_proc / 100;
        odsetki_nienaliczone += odsetki;

        if(loop == 0){
            wynik += odsetki_nienaliczone;
            odsetki_nienaliczone = 0;
            loop = kapita;
        }

        cout << "loop" << loop << endl;
        cout << "miesiac" << i << endl;
        cout << "odsetki: " << odsetki << endl;
        cout << "proc" << procent << endl;
        cout << "wynik: " << wynik << endl;
        cout << "\n";
        wynik += wplata;
        loop--;
    }

    return;
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

int main()
{
    // bool running = true;
    // while(running == true){
    //     draw_menu();
    // }
    draw_menu();
    // calculate();
    return 0;
}
