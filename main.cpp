// Matas Pieczulis 3T
// Informatyka
// Zadanie: Należy napisać program konsolowy w C++, który sporządzi raport z symulacji oszczędzania na tzw. "procent składany'.

#include <iostream>
#include <fstream>

#include <sstream>
#include <algorithm>

using namespace std;

bool continuation = false;
struct Values{ // Struktura do wygodnego zwracania wartości
    int miesiac = 0; // Miesiac od ktorego zmiany maja byc wprowadzone
    int miesiac_total = 0; // Poprzedni miesiąc zczytany z pliku
    float result = 0; // Wynik
    float mies_wplata = 0; // Miesięczna wpłata
    float suma_wplata = 0; // Suma wpłat
    float suma_odsetek = 0; // Suma odsetek
    float procent = 0; // Oprocentowanie środków w skali rocznej
    int kapitalizacja = 0; // Częstotliwość kapitalizacji w miesiącach
};

void create_file(string name){ // Stwórz plik
    try
    {
        std::ofstream file(name);
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

void calculate(Values values){ // Właściwe obliczenia
    fstream output_file;

    if(continuation == true) {output_file.open("output.csv", std::ios_base::app | std::ios_base::in);} // Otwarcie pliku w trybie dopisywania
    else {output_file.open("output.csv", std::ofstream::out | std::ofstream::trunc);} // Otwarcie pliku w trybie nadpisywania

    if(!output_file) {create_file("output.csv");} // Sprawdzenie czy plik istnieje

    float wynik = 0;
    int miesiac = 0; // Miesiące oszczędzania
    float wplacone = 0; // Całkowita wpłata
    float suma_odsetek = 0;
    float suma_wplata = 0;

    float mies_wplata = values.mies_wplata;
    float odsetki = 0;
    float odsetki_nienaliczone = 0; 

    float procent = values.procent; // Oprocentowanie w skali rocznej
    float mies_proc = procent/12; // Miesięczne oprocentowanie
    int loop = values.kapitalizacja-1; // Miesiące do kapitalizacji
    int kapitalizacja = values.kapitalizacja;

    if(continuation){
        miesiac = values.miesiac; // Miesiące oszczędzania
        wynik = values.result; // Suma zaoszczędzonych pieniędzy
        suma_odsetek = values.suma_odsetek;
        wplacone = values.suma_wplata;
    }
    else{
        output_file << "<M-c>,<Kapitał>,<Miesięczna wpłata>,<Całkowita wpłacona kwota>,<Odsetki naliczone w miesiącu>,<Odsetki nie naliczone>,<Suma odsetek>,<Oprocentowanie w skali roku>,<Czas do kapitalizacji>\n";
    
        wynik = values.mies_wplata; // Suma zaoszczędzonych pieniędzy
        miesiac = values.miesiac; // Miesiące oszczędzania
    }

    for (int i = 0; i < miesiac; i++) {
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
        output_file << values.miesiac_total+i+1 << ",";
        output_file << wynik << ",";
        output_file << mies_wplata << ",";
        output_file << wplacone << ",";
        output_file << odsetki << ",";
        output_file << odsetki_nienaliczone << ",";
        output_file << suma_odsetek << ",";
        output_file << procent << ",";
        output_file << loop << "\n";

        wynik += mies_wplata; 
        loop--;
    }

    output_file.close(); 
    return;
}

void draw_help(){
    cout << "\n----Help----\n";
    cout << "usage: main <Miesiące> <Mies wplata> <Oprocen> <Kapita>\n";
    cout << "\n---Other args---\n";
    cout << "-c - kontynułuj kalkulacje z pliku" << "output.csv" << "\n";
    cout << "Więcej info: https://github.com/Sekyzio/Savings_calc/blob/master/REDME.md\n";
    exit(0);
    return;
}

Values str_to_struct(string str){ // Podziel string na struct Values
    int i = 0;

    string arr[9];
    stringstream ssin(str);

    while (ssin.good() && i < 9){
        ssin >> arr[i];
        ++i;
    }

    Values values;
    try
    {
        values.miesiac_total = stoi(arr[0]);
        values.result = stof(arr[1]);
        values.mies_wplata = stof(arr[2]);
        values.suma_wplata = stof(arr[3]);
        values.suma_odsetek = stof(arr[6]);
        values.procent = stof(arr[7]);
        values.kapitalizacja = stoi(arr[8]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Wprowadzono błędne dane\n";
        cout << "Nie można przeprowadzić kontynuacji na pustym pliku\n";
    }
    
    return values;
}

Values load_result(){ //Załaduj dane z pliku
    string line;
    ifstream output_file("output.csv"); // Otwarcie pliku
    if (!output_file){create_file("output.csv");}// Sprawdzenie czy plik istnieje

    while (output_file >> ws && getline(output_file, line)); // Zwróć ostatnią linię
    output_file.close();

    replace(line.begin(), line.end(), ',', ' '); // Podmień ',' na ", "(przecinek + spacja). str_to_struc rozdziela na podstaie spacji
    return str_to_struct(line);
}

Values get_args(int argc, char const *argv[]){
    Values values, continuation_values;
    cout << argc << endl;

    for(int i=0; i<argc; i++){ // Sprawdzanie argumentów
        string arg = argv[i];
        if(arg == "-help" || arg == "/?") {draw_help();}
        if(arg == "-c") {continuation = true;} 

        try
        {
            if(i==1) {values.miesiac = stoi(arg);}
            else if(i==2) {values.mies_wplata = stof(arg);}
            else if(i==3) {values.procent = stof(arg);}
            else if(i==4) {values.kapitalizacja = stoi(arg);}
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            cout << "Wprowadzono błędne argumenty\n";
        }
        
    }
    
    if(continuation){
        continuation_values = load_result();
        continuation_values.miesiac = values.miesiac;
        continuation_values.mies_wplata = values.mies_wplata;
        continuation_values.procent = values.procent;
        continuation_values.kapitalizacja = values.kapitalizacja;

        return continuation_values;
    }

    return values;
}

int main(int argc, char const *argv[])
{
    Values values;
    values = get_args(argc, argv);
    calculate(values); // Właściwe obliczenia

    return 0;
}
