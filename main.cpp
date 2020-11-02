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

bool dynamic_values_bool = false;
//TODO del
int count_from = 0; // Miesiac od ktorego zmiany maja byc wprowadzone
float new_procent = 0;
int new_kapita = 0;
float new_wplata = 0;
//----

double output_wynik[1200];

double output_odsetki[1200];
double output_suma_odsetek[1200];
double output_odsetki_nienaliczone[1200];

double output_wplata[1200];
double output_wplacono[1200];

double output_procent[1200];
int output_kapita[1200];

struct Values{
    int count_from = 0; // Miesiac od ktorego zmiany maja byc wprowadzone
    float procent = 0; // Oprocentowanie środków w skali rocznej
    int kapitalizacja = 0; // Częstotliwość kapitalizacji w miesiącach
    float mies_wplata = 0; // Miesięczna wpłata
};

void create_file(string name){ // Stwórz plik
    try
    {
        std::ofstream outfile (name+".txt");
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
    string lines[4]; //TODO CHange this
    ifstream input_file("config.txt"); // Otwarcie pliku

    if (!input_file){create_file("config");}// Sprawdzenie czy plik istnieje

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

    if (!output_file){create_file("output");}// Sprawdzenie czy plik istnieje

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
    output_file << "\nWpłacone środki: " << wplacone << endl;
    output_file << "Odsetki: " << suma_odsetek << endl;
    output_file << "Suma oszczędności: " << wplacone+suma_odsetek << endl;

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

Values menu_dynamic_values(){ // Wybierz dynamiczne dane
    string dynamic;

    cout << "\nZmienne wartosci?\n";
    cout << "t - Tak \nn - Nie \n";
    cin >> dynamic; //TODO add podatek

    if(dynamic == "t"){
        string wyb;
        string month;
        string temp_procent;
        string temp_kapita;
        string temp_wplata; //TODO change variable names

        dynamic_values_bool = true;

        cout << "1. Oprocentowanie\n";
        cin >> temp_procent;

        cout << "2. Czestotliwosc kapitalizacji\n";
        cin >> temp_kapita;

        cout << "3. Miesieczna wplata\n";
        cin >> temp_wplata;

        cout << "Od ktorego miesiaca wartosci maja sie zmienic?\n";
        cin >> month;

        try // Sprawdzanie poprawności wprowadzonych danych
        {
            Values values;
            values.count_from = stoi(month);
            values.procent = stof(temp_procent); //TODO  fix conversion 
            values.kapitalizacja = stoi(temp_kapita);
            values.mies_wplata = stof(temp_wplata);

            return values;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << ", Błąd podczas konwersji\n";
            cout << "Wprowadzono błędne dane \n";
            menu_dynamic_values();
        }
    }

    Values empty_values;
    return empty_values;
}

void draw_data(Values dynamic_values){ // Wypisz wprowadzone dane
    cout << "\nIlość miesięcy oszczędzania: " << miesiace << "\n";
    cout << "Oprocentowanie środków (w skali rocznej): " << procent << "\n";
    cout << "Częstotliwość kapitalizacji (co ile miesięcy): " << kapita << "\n";
    cout << "Miesięczna wplata: " << wplata << "\n";

    if(dynamic_values_bool == true){
        cout << "\nZmienne wartości:\n";
        cout << "Zmienia sie od miesiąca: " << dynamic_values.count_from << endl;
        if(dynamic_values.procent != procent){
            cout << "Oprocentowanie: " << dynamic_values.procent << endl;
        }
        if(dynamic_values.kapitalizacja != kapita){
            cout << "Kapitalizacja: " << dynamic_values.kapitalizacja << endl;
        }
        if(dynamic_values.mies_wplata != wplata){
            cout << "Wplata: " << dynamic_values.mies_wplata << endl;
        }
    }
    return;
}

void calculate(Values dynamic_values){ // Właściwe obliczenia
    float odsetki_nienaliczone = 0;
    int loop = kapita-1;
    for (int i = 0; i < miesiace; i++) {

        if(dynamic_values_bool == true && count_from == i){ // Wprowadzenie dynamicznych danych
            procent = new_procent; // TODO fix if end of savings capitalise
            mies_proc = procent/12;
            kapita = new_kapita;
            wplata = new_wplata;
        }
        
        odsetki = wynik * mies_proc / 100;
        odsetki_nienaliczone += odsetki;

        wplacone += wplata;
        suma_odsetek += odsetki;

        if(loop == 0 && i==miesiace){ // Naliczanie odsetek
            wynik += odsetki_nienaliczone;
            odsetki_nienaliczone = 0;
            loop = kapita;
        }

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
    Values dynamic_values;
    cout << "\n--------------------\n";

    menu_load_mode();// Wybory dotyczące danych
    dynamic_values = menu_dynamic_values();

    draw_data(dynamic_values); // Wyświetl wprowadzone dane

    // calculate(); // Właściwe obliczenia
 
    // result(); // Wyświetl rezultat
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
