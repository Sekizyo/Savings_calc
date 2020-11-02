#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

bool dynamic_values_bool = false;

// double output_wynik[1200];
double odsetki;
double wynik;
double wplacone;
double suma_odsetek;
double wplata;
// double output_odsetki[1200];
// double output_suma_odsetek[1200];
// double output_odsetki_nienaliczone[1200];

// double output_wplata[1200];
// double output_wplacono[1200];

// double output_procent[1200];
// int output_kapita[1200];

struct Values{
    int miesiac = 0; // Miesiac od ktorego zmiany maja byc wprowadzone
    float procent = 0; // Oprocentowanie środków w skali rocznej
    int kapitalizacja = 0; // Częstotliwość kapitalizacji w miesiącach
    float mies_wplata = 0; // Miesięczna wpłata
};

struct Result{
    float miesiac = 0; // Miesiące oszczędziania
    float wplacono = 0; 
    float odsetki = 0;
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
        std::cerr << "Error: " << e.what() << "\n";
        cout << "Nie mozna utworzyć pliku\n";
        exit(0);
    }
    cout << "Poprawnie utworzono plik\n";
    return;
}

Values load_config(){ // Wczytanie danych wejściowych z pliku
    Values input;

    string line; 
    string lines[4]; //TODO CHange this

    ifstream input_file("config.txt"); // Otwarcie pliku
    if (!input_file){create_file("config");}// Sprawdzenie czy plik istnieje

    int loop = 0;
    while(getline (input_file, line)) { // Odczytanie wszytkich lini z pliku i zapisanie ich w liście
        lines[loop] = line;
        loop++;//TODO change loading 
    }
    input_file.close(); // Zamknięcie pliku
    
    try // Sprawdzanie poprawności wartości oraz konwersja to odpowiedniego typu
    {
        input.miesiac = stoi(lines[0]); 
        input.procent = stod(lines[1]);
        input.kapitalizacja = stoi(lines[2]);
        input.mies_wplata = stod(lines[3]);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << ", Błąd podczas konwersji\n";
        cout << "Wprowadzono błędne dane \n";
        exit(0);
    }
    return input;
}

Values manual_config(){ // Ręcznie wprowadzanie danych
    Values values;
    string procent, kapitalizacja, mies_wplata;

    cout << "\nPodaj oprocentowanie: \n";
    cin >> procent;

    cout << "Podaj częstotliwość kapitalizacji (w miesiącach): \n";
    cin >> kapitalizacja;

    cout << "Podaj miesięczną wplatę: \n";
    cin >> mies_wplata;

    try // Sprawdzanie poprawności wprowadzonych danych
    {
        values.procent = stof(procent);
        values.kapitalizacja = stoi(kapitalizacja);
        values.mies_wplata = stof(mies_wplata);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        cout << "Podano błędne wartości\n";
        manual_config();
    }
    return values;
}

void save_data(Result result){ // Zapisanie wyniku do pliku
    ofstream output_file("output.txt"); // Otwarcie pliku

    if (!output_file){create_file("output");}// Sprawdzenie czy plik istnieje

    // output_file << "<M-c>  <Kapitał>  <Kwota wpłacona w miesiącu> <Całkowita wpłacona kwota> <Odsetki naliczone w miesiącu> <Odsetki nie naliczone> <Suma odsetek> <Oprocentowanie w skali roku> <Czas do pakitalizacji>\n"; 
    // for(int i=0; i<miesiace; i++){
    //     output_file << i+1 << "   ";
    //     output_file << output_wynik[i] << " zł   ";
    //     output_file << output_wplata[i] << " zł   ";
    //     output_file << output_wplacono[i] << " zł   ";
    //     output_file << output_odsetki[i] << " zł   ";
    //     output_file << output_odsetki_nienaliczone[i] << " zł   ";
    //     output_file << output_suma_odsetek[i] << " zł   ";
    //     output_file << output_procent[i] << "%   ";
    //     output_file << output_kapita[i] << "   \n";

    // }
    // output_file << "\nWpłacone środki: " << wplacone << endl;
    // output_file << "Odsetki: " << suma_odsetek << endl;
    // output_file << "Suma oszczędności: " << wplacone+suma_odsetek << endl;

    // output_file.close();
    return;
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
    string wyb;

    cout << "\nZmienne wartosci?\nt - Tak \nn - Nie \n";
    cin >> wyb; //TODO add podatek

    if(wyb == "t"){
        dynamic_values_bool = true;
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
            Values values;

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

    Values empty_values;
    return empty_values;
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
    Result result;
    float odsetki_nienaliczone = 0;
    int loop = values.kapitalizacja-1;
    float mies_proc = values.procent/12;
    for (int i = 0; i < values.miesiac; i++) {

        if(dynamic_values_bool == true && dynamic_values.miesiac == i){ // Wprowadzenie dynamicznych danych
            values.procent = dynamic_values.procent; // TODO fix if end of savings capitalise
            mies_proc = dynamic_values.procent/12;
            values.kapitalizacja = dynamic_values.kapitalizacja;
            values.mies_wplata = dynamic_values.mies_wplata;
        }
        
        odsetki = wynik * mies_proc / 100;
        odsetki_nienaliczone += odsetki;

        wplacone += values.mies_wplata;
        suma_odsetek += odsetki;

        if(loop == 0 && i==values.miesiac){ // Naliczanie odsetek
            wynik += odsetki_nienaliczone;
            odsetki_nienaliczone = 0;
            loop = values.kapitalizacja;
        }

        // Zapis do pliku
        // output_wynik[i] = wynik;

        // output_odsetki[i] = odsetki;
        // output_suma_odsetek[i] = suma_odsetek;
        // output_odsetki_nienaliczone[i] = odsetki_nienaliczone;

        // output_wplata[i] = wplata;
        // output_wplacono[i] = wplacone;

        // output_procent[i] = procent;
        // output_kapita[i] = loop;

        wynik += wplata; // TODO add save to file
        loop--;
    }
    // save_data(output);
    return result;
}

void result(Result values){ // Wyświetl rezultat
    cout << "\n\nWpłacone środki: " << values.wplacono;
    cout << "\nOdsetki: " << values.odsetki;
    cout << "\nSuma oszczędności: " << values.suma;
    return;
}

void draw_menu(){ // Główne menu
    Values values;
    Values dynamic_values;
    Result wynik;
    cout << "\n--------------------\n\n";

    values = menu_load_mode();// Wybory dotyczące danych
    dynamic_values = menu_dynamic_values();

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
