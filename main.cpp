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
double suma_odsetek = 0;
double wplacone = 0;

bool dynamic_values = false;
int count_from = 0; // Miesiac od ktorego zmiany maja byc wprowadzone
double new_procent = procent;
int new_kapita = kapita;
double new_wplata = wplata;

double output_wynik[1200];

double output_odsetki[1200];
double output_suma_odsetek[1200];
double output_odsetki_nienaliczone[1200];

double output_wplata[1200];
double output_wplacono[1200];

double output_procent[1200];
int output_kapita[1200];

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
    return;
}

void create_output(){ // Stworzenie pliku wyjściowego
    try
    {
        std::ofstream outfile ("output.txt");
        outfile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        cout << "Nie mozna utworzyć pliku\n";
        exit(0);
    }
    cout << "Poprawnie utworzono plik\n";
    return;
}

void load_config(){ // Wczytanie danych wejściowych z pliku
    int loop = 0;
    string line; 
    string lines[4];
    ifstream input_file("config.txt"); // Otwarcie pliku

    if (!input_file){create_config();}// Sprawdzenie czy plik istnieje

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

        new_procent = procent;
        new_kapita = kapita;
        new_wplata = wplata;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << ", Błąd podczas konwersji\n";
        cout << "Wprowadzono błędne dane \n";
        exit(0);
    }
    
    return;
}

void manual_config(){ // Ręcznie wprowadzanie danych
    string temp_procent;
    string temp_kapita;
    string temp_wplata;

    cout << "\nPodaj oprocentowanie: \n";
    cin >> temp_procent;

    cout << "Podaj częstotliwość kapitalizacji (w miesiącach): \n";
    cin >> temp_kapita;

    cout << "Podaj miesięczną wplatę: \n";
    cin >> temp_wplata;

    try // Sprawdzanie poprawności wprowadzonych danych
    {
        procent = stod(temp_procent);
        kapita = stoi(temp_kapita);
        wplata = stod(temp_wplata);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        cout << "Podano błędne wartości\n";
        manual_config();
    }
    return;
}

void save_data(){ // Zapisanie wyniku do pliku
    ofstream output_file("output.txt"); // Otwarcie pliku

    if (!output_file){create_output();}// Sprawdzenie czy plik istnieje

    output_file << "<M-c>  <Kapitał>  <Kwota wpłacona w miesiącu> <Całkowita wpłacona kwota> <Odsetki naliczone w miesiącu> <Odsetki nie naliczone> <Suma odsetek> <Oprocentowanie w skali roku> <Czas do pakitalizacji>\n"; 
    for(int i=0; i<miesiace; i++){
        output_file << i+1 << "   ";
        output_file << output_wynik[i] << " zł   ";
        output_file << output_wplata[i] << " zł   ";
        output_file << output_wplacono[i] << " zł   ";
        output_file << output_odsetki[i] << " zł   ";
        output_file << output_odsetki_nienaliczone[i] << " zł   ";
        output_file << output_suma_odsetek[i] << " zł   ";
        output_file << output_procent[i] << "%   ";
        output_file << output_kapita[i] << "   \n";

    }

    output_file.close();
    return;
}

void menu_load_mode(){ // Wybierz tryb ładowania danych
    string mode;
    cout << "Wybierz tryb wprowadzania danych: \n";
    cout << "1. Zaladuj z pliku\n";
    cout << "2. Wprowadz ręcznie\n";
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
        cout << "Podano błędne wartość\n";
        menu_load_mode();
    }
    return;
}

void menu_dynamic_values(){ // Wybierz dynamiczne dane
    string dynamic;

    cout << "\nZmienne wartosci?\n";
    cout << "t - Tak \nn - Nie \n";
    cin >> dynamic; //TODO add podatek

    if(dynamic == "t"){
        string wyb;
        string month;
        string temp_procent;
        string temp_kapita;
        string temp_wplata;

        dynamic_values = true;

        cout << "Ktora wartosc ma byc dynamiczna?\n";
        cout << "1. Oprocentowanie\n";
        cout << "2. Czestotliwosc kapitalizacji\n";
        cout << "3. Miesieczna wplata\n";
        cin >> wyb;

        cout << "Podaj nowa wartosc\n";
        if(wyb == "1")
        {
            cin >> temp_procent;
        }
        else if (wyb == "2")
        {
            cin >> temp_kapita;
        }
        else if (wyb == "3")    
        {
            cin >> temp_wplata;
        }
        else 
        {
            cout << "Podano błędne wartość\n";
            menu_dynamic_values();
        }

        cout << "Od ktorego miesiaca wartosc ma sie zmienic?\n";
        cin >> month;

        try // Sprawdzanie poprawności wprowadzonych danych
        {
            count_from = stoi(month);
            new_procent = stod(temp_procent); //TODO  fix conversion 
            new_kapita = stoi(temp_kapita);
            new_wplata = stod(temp_wplata);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << ", Błąd podczas konwersji\n";
            cout << "Wprowadzono błędne dane \n";
            menu_dynamic_values();
        }
        
    }
    return;

}

void draw_data(){ // Wypisz wprowadzone dane
    cout << "\nIlość miesięcy oszczędzania: " << miesiace << "\n";
    cout << "Oprocentowanie środków (w skali rocznej): " << procent << "\n";
    cout << "Częstotliwość kapitalizacji (co ile miesięcy): " << kapita << "\n";
    cout << "Miesięczna wplata: " << wplata << "\n";

    if(dynamic_values == true){
        cout << "\nZmienne wartości:\n";
        cout << "Zmienia sie od miesiąca: " << count_from << endl;
        if(new_procent != procent){
            cout << "Oprocentowanie: " << new_procent << endl;
        }
        if(new_kapita != kapita){
            cout << "Kapitalizacja: " << new_kapita << endl;
        }
        if(new_wplata != wplata){
            cout << "Wplata: " << new_wplata << endl;
        }
    }
    return;
}

void calculate(){ // Właściwe obliczenia
    float odsetki_nienaliczone = 0;
    int loop = kapita-1;
    for (int i = 0; i < miesiace; i++) {

        if(dynamic_values == true && count_from == i){ // Wprowadzenie dynamicznych danych
            procent = new_procent; // TODO fix if end of savings capitalise
            mies_proc = procent/12;
            kapita = new_kapita;
            wplata = new_wplata;
        }
        
        odsetki = wynik * mies_proc / 100;
        odsetki_nienaliczone += odsetki;

        wplacone += wplata;
        suma_odsetek += odsetki;

        if(loop == 0 || i == miesiace){ // Naliczanie odsetek
            wynik += odsetki_nienaliczone;
            odsetki_nienaliczone = 0;
            loop = kapita;
        }

        // cout << "loop" << loop << endl;
        // cout << "miesiac" << i << endl;
        // cout << "odsetki: " << odsetki << endl;
        // cout << "proc" << procent << endl;
        // cout << "wynik: " << wynik << endl;
        // cout << "\n";

        // Zapis do pliku
        output_wynik[i] = wynik;

        output_odsetki[i] = odsetki;
        output_suma_odsetek[i] = suma_odsetek;
        output_odsetki_nienaliczone[i] = odsetki_nienaliczone;

        output_wplata[i] = wplata;
        output_wplacono[i] = wplacone;

        output_procent[i] = procent;
        output_kapita[i] = loop;

        wynik += wplata; // TODO add save to file
        loop--;
    }
    save_data();
    return;
}

void result(){ // Wyświetl rezultat
    cout << "\nWpłacone środki: " << wplacone << endl;
    cout << "Odsetki: " << suma_odsetek << endl;
    cout << "Suma oszczędności: " << wplacone+suma_odsetek << endl;
    return;
}

void draw_menu(){ // Główne menu
    cout << "\n--------------------\n";

    menu_load_mode();// Wybory dotyczące danych
    menu_dynamic_values();

    draw_data(); // Wyświetl wprowadzone dane

    calculate(); // Właściwe obliczenia
 
    result(); // Wyświetl rezultat
    return;
}

int main()
{
    bool running = true;
    while(running == true){
        draw_menu();
    }
    return 0;
}
