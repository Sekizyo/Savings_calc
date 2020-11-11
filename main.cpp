// Matas Pieczulis 3T
// Informatyka
// Zadanie: Należy napisać program konsolowy w C++, który sporządzi raport z symulacji oszczędzania na tzw. "procent składany'.

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

bool dynamic_values_bool = false; // Dynamiczna wartość //TODO rename
struct Values{ // Struktura do wygodnego zwracania wartości
    int miesiac = 0; // Miesiac od ktorego zmiany maja byc wprowadzone
    float procent = 0; // Oprocentowanie środków w skali rocznej
    int kapitalizacja = 0; // Częstotliwość kapitalizacji w miesiącach
    float mies_wplata = 0; // Miesięczna wpłata
};

struct Result{ // Struktura do wygodnego zwracania wyniku
    float miesiac = 0; // Miesiące oszczędziania
    float wplacone = 0; // Suma wpłaconych pieniędzy
    float odsetki = 0; // Suma odsetek
    float suma = 0;
};

void create_file(string name){ // Stwórz plik
    try
    {
        std::ofstream file(name+".txt");
        file.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what();
        cout << "\nNie mozna utworzyć pliku\n";
        exit(0);
    }
    cout << "Poprawnie utworzono plik\n";
    return;
}

Values load_config(){ // Wczytanie danych wejściowych z pliku
    Values values;

    string line; 
    string lines[4];

    ifstream input_file("config.txt"); // Otwarcie pliku
    if (!input_file){create_file("config");}// Sprawdzenie czy plik istnieje

    int loop = 0; // Numer wiersza
    while(getline (input_file, line)) { // Odczytanie wszytkich lini z pliku i zapisanie ich w array
        lines[loop] = line;
        loop++; 
    }
    input_file.close(); // Zamknięcie pliku

    try // Sprawdzanie poprawności wartości oraz konwersja to odpowiedniego typu
    {
        values.miesiac = stoi(lines[0]); 
        values.procent = stof(lines[1]);
        values.kapitalizacja = stoi(lines[2]);
        values.mies_wplata = stof(lines[3]);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << ", Błąd podczas konwersji\n";
        cout << "Wprowadzono błędne dane \n";
        exit(0);
    }
    return values;
}

Values manual_config(){ // Ręcznie wprowadzanie danych
    Values values;
    string miesiac, procent, kapitalizacja, mies_wplata;

    cout << "Podaj miesiącze oszczędziania: \n";
    cin >> miesiac;
    
    cout << "\nPodaj oprocentowanie: \n";
    cin >> procent;

    cout << "Podaj częstotliwość kapitalizacji (w miesiącach): \n";
    cin >> kapitalizacja;

    cout << "Podaj miesięczną wplatę: \n";
    cin >> mies_wplata;

    try // Sprawdzanie poprawności wprowadzonych danych
    {
        values.miesiac = stoi(miesiac);
        values.procent = stof(procent);
        values.kapitalizacja = stoi(kapitalizacja);
        values.mies_wplata = stof(mies_wplata);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what();
        cout << "\nPodano błędne wartości\n";
        manual_config();
    }
    return values;
}

Values menu_load_mode(){ // Wybierz tryb ładowania danych
    Values values;
    string mode;

    cout << "Wybierz tryb wprowadzania danych: \n";
    cout << "1. Zaladuj z pliku\n";
    cout << "2. Wprowadz ręcznie\n";
    cin >> mode;

    if(mode == "1") {values = load_config();}
    else if (mode == "2") {values = manual_config();}
    else {cout << "Podano błędne wartość\n"; menu_load_mode();}

    return values;
}

Values menu_dynamic_values(){ // Wybierz dynamiczne dane
    Values values;
    string wyb;

    cout << "\nZmienne wartosci?\nt - Tak \nn - Nie \n";
    cin >> wyb; //TODO add feature: podatek

    if(wyb == "t"){
        string miesiac, procent, kapita, wplata;

        cout << "Od ktorego miesiaca wartosci maja sie zmienic?\n";
        cin >> miesiac;

        cout << "1. Oprocentowanie\n";
        cin >> procent;

        cout << "2. Czestotliwosc kapitalizacji\n";
        cin >> kapita;

        cout << "3. Miesieczna wplata\n";
        cin >> wplata;

        try // Sprawdzanie poprawności wprowadzonych danych
        {
            dynamic_values_bool = true;

            values.miesiac = stoi(miesiac);
            values.procent = stof(procent); 
            values.kapitalizacja = stoi(kapita);
            values.mies_wplata = stof(wplata);

            return values;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << ", Błąd podczas konwersji\n";
            cout << "Wprowadzono błędne dane \n";
            menu_dynamic_values();
        }
    }

    dynamic_values_bool = false;
    return values;
}

void draw_data(Values values, Values dynamic){ // Wypisz wprowadzone dane
    cout << "\nIlość miesięcy oszczędzania: " << values.miesiac;
    cout << "\nOprocentowanie środków (w skali rocznej): " << values.procent;
    cout << "\nCzęstotliwość kapitalizacji (co ile miesięcy): " << values.kapitalizacja;
    cout << "\nMiesięczna wplata: " << values.mies_wplata;

    if(dynamic_values_bool == true){
        cout << "\n\nZmienne wartości:";
        cout << "\n  Zmienia sie od miesiąca: " << dynamic.miesiac;
        if(dynamic.procent != values.procent) {cout << "\n  Oprocentowanie: " << dynamic.procent;}
        if(dynamic.kapitalizacja != values.kapitalizacja) {cout << "\n  Kapitalizacja: " << dynamic.kapitalizacja;}
        if(dynamic.mies_wplata != values.mies_wplata) {cout << "\n  Wplata: " << dynamic.mies_wplata;}
    }
    return;
}

Result calculate(Values values, Values dynamic_values){ // Właściwe obliczenia

    ofstream output_file("output.txt"); // Otwarcie pliku
    if (!output_file){create_file("output");}// Sprawdzenie czy plik istnieje
    output_file << "<M-c>  <Kapitał>  <Miesięczna wpłata> <Całkowita wpłacona kwota> <Odsetki naliczone w miesiącu> <Odsetki nie naliczone> <Suma odsetek> <Oprocentowanie w skali roku> <Czas do kapitalizacji>\n"; 

    int miesiac = values.miesiac; // Miesiące oszczędzania
    float wynik = values.mies_wplata; // Suma zaoszczędzonych pieniędzy
    float mies_wplata = values.mies_wplata;
    float wplacone = 0; // Całkowita wpłata
    float odsetki = 0;
    float odsetki_nienaliczone = 0; 
    float suma_odsetek = 0;
    float procent = values.procent; // Oprocentowanie w skali rocznej
    float mies_proc = procent/12;
    int loop = values.kapitalizacja; // Miesiące do kapitalizacji
    int kapitalizacja = values.kapitalizacja;

    for (int i = 0; i < miesiac+1; i++) {

        if(dynamic_values_bool == true && dynamic_values.miesiac == i){ // Wprowadzenie dynamicznych danych
            if(procent != dynamic_values.procent) {procent = dynamic_values.procent;};
            if(mies_proc != dynamic_values.procent/12) {mies_proc = dynamic_values.procent/12;};
            if(kapitalizacja != dynamic_values.kapitalizacja) {kapitalizacja = dynamic_values.kapitalizacja;};
            if(mies_wplata != dynamic_values.mies_wplata) {mies_wplata = dynamic_values.mies_wplata;};
        }

        odsetki = wynik * mies_proc / 100; //Obliczanie odsetek
        odsetki_nienaliczone += odsetki;

        wplacone += values.mies_wplata;
        suma_odsetek += odsetki;

        if(loop == 0 || i==miesiac){ // Naliczanie odsetek
            wynik += odsetki_nienaliczone;
            odsetki_nienaliczone = 0;
            loop = kapitalizacja;
        }

        // Zapis do pliku
        output_file << i+1 << "   ";
        output_file << wynik << " zł   ";
        output_file << mies_wplata << " zł   ";
        output_file << wplacone << " zł   ";
        output_file << odsetki << " zł   ";
        output_file << odsetki_nienaliczone << " zł   ";
        output_file << suma_odsetek << " zł   ";
        output_file << procent << "%   ";
        output_file << loop << "   \n";

        wynik += mies_wplata; 
        loop--;
    }
    output_file.close(); 
    
    Result result;
    result.miesiac = values.miesiac;
    result.wplacone = wplacone;
    result.odsetki = suma_odsetek;
    result.suma = wplacone + suma_odsetek;

    return result;
}

void result(Result result){ // Wyświetl wynik
    cout << "\n\nMiesiące oszczędzania: " << result.miesiac;
    cout << "\nWpłacone środki: " << result.wplacone;
    cout << "\nOdsetki: " << result.odsetki;
    cout << "\nSuma oszczędności: " << result.suma;
    return;
}

void draw_menu(){ // Główne menu
    cout << "\n--------------------\n\n";
    Values values;
    Values dynamic_values;
    Result wynik;

    values = menu_load_mode(); // Wybory dotyczące wprowadzania danych
    dynamic_values = menu_dynamic_values(); // Wybory dotyczące dynamicznych danych

    draw_data(values, dynamic_values); // Wyświetl wprowadzone dane

    wynik = calculate(values, dynamic_values); // Właściwe obliczenia
 
    result(wynik); // Wyświetl rezultat
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
