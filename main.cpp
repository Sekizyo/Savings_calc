// Matas Pieczulis 3T
// Informatyka
// Zadanie: Należy napisać program konsolowy w C++, który sporządzi raport z symulacji oszczędzania na tzw. "procent składany'.

#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

struct Values{ // Struktura do wygodnego zwracania wartości
    int miesiac = 0; // Miesiac od ktorego zmiany maja byc wprowadzone
    float result = 0; // Wynik
    float mies_wplata = 0; // Miesięczna wpłata
    double procent = 0; // Oprocentowanie środków w skali rocznej
    int kapitalizacja = 0; // Częstotliwość kapitalizacji w miesiącach
};

void draw_help(){
    cout << "\n----Help----\n";
    cout << "usage: calc <Months> <Mies wplata> <Oprocen> <Kapita>\n";
    cout << "\n---Other args---\n";
    cout << "-c - continue calculations from output_file.txt\n";
    exit(0);
    return;
}

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

void draw_data(Values values){ // Wypisz wprowadzone dane
    cout << "\nIlość miesięcy oszczędzania: " << values.miesiac;
    cout << "\nOprocentowanie środków (w skali rocznej): " << values.procent;
    cout << "\nCzęstotliwość kapitalizacji (co ile miesięcy): " << values.kapitalizacja;
    cout << "\nMiesięczna wplata: " << values.mies_wplata;
    return;
}

void calculate(Values values){ // Właściwe obliczenia

    ofstream output_file("output.csv"); // Otwarcie pliku
    if (!output_file){create_file("output.csv");}// Sprawdzenie czy plik istnieje
    output_file << "<M-c>,<Kapitał>,<Miesięczna wpłata>,<Całkowita wpłacona kwota>,<Odsetki naliczone w miesiącu>,<Odsetki nie naliczone>,<Suma odsetek>,<Oprocentowanie w skali roku>,<Czas do kapitalizacji>\n"; 

    int miesiac = values.miesiac; // Miesiące oszczędzania
    float wynik = values.mies_wplata; // Suma zaoszczędzonych pieniędzy
    float mies_wplata = values.mies_wplata;
    float wplacone = 0; // Całkowita wpłata
    float odsetki = 0;
    float odsetki_nienaliczone = 0; 
    float suma_odsetek = 0;
    float procent = values.procent; // Oprocentowanie w skali rocznej
    float mies_proc = procent/12;
    int loop = values.kapitalizacja-1; // Miesiące do kapitalizacji
    int kapitalizacja = values.kapitalizacja;

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
        output_file << i+1 << ",";
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

string load_result(){
    string line;
    ifstream output_file("output.csv"); // Otwarcie pliku
    if (!output_file){create_file("output.csv");}// Sprawdzenie czy plik istnieje

    while (output_file >> ws && getline(output_file, line)); // Zwróć ostatnią linię
    output_file.close();

    cout << line<< endl;

    // line.replace(',', ", "); TODO
    
    vector<int> vect;
    stringstream ss(line);

    for (int i; ss >> i;) {
        vect.push_back(i);    
        if (ss.peek() == ',')
            ss.ignore();
    }

    for (std::size_t i = 0; i < vect.size(); i++)
        std::cout << "geg" << vect[i] << std::endl;

    // ta funkcja działa tylko wtedy gdy wartości w LINIA są oddzielone spacją
    // spróbój podmienić ',' na ", " czyli ze spacją
    // następnie jeśli -c dopisz do pliku a nie nadpisuj
    // -c nadpisz wartości początkowe;

    return " ";
}

Values get_args(int argc, char const *argv[]){
    Values values;
    bool continuation = false;

    for(int i=0; i<argc; i++){ // Sprawdzanie argumentów
        string arg = argv[i];
        if(arg == "-help" || arg == "/?") {draw_help();}
        if(arg == "-c") {continuation = true;} 

        if(i==1) {values.miesiac = stoi(arg);}
        else if(i==2) {values.mies_wplata = stof(arg);}
        else if(i==3) {values.procent = stof(arg);}
        else if(i==4) {values.kapitalizacja = stoi(arg);}
    }
    
    if(continuation){
        load_result();
        // cout << values.result << endl;
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
