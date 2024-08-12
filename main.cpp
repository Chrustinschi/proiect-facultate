#include <iostream>
#include "curierat.h"

void CurieratManager::menu() {
    int optiune;
    do {
        std::cout << "\n===== MENIU =====\n";
        std::cout << "1. Adauga pachet\n";
        std::cout << "2. Sterge pachet\n";
        std::cout << "3. Modifica pachet\n";
        std::cout << "4. Adauga depozit\n";
        std::cout << "5. Sterge depozit\n";
        std::cout << "6. Modifica depozit\n";;
        std::cout << "7. Adauga transportator\n";
        std::cout << "8. Sterge transportator\n";
        std::cout << "9. Modifica transportator\n";
        std::cout << "10. Afiseaza informatiile\n";
        std::cout << "0. Iesire\n";
        std::cout << "Introduceti optiunea dorita: ";
        std::cin >> optiune;

        switch (optiune) {
            case 1:
                adaugaPachet();
                break;
            case 2:
                stergePachet();
                break;
            case 3:
                modificaPachet();
                break;
            case 4:
                adaugaDepozit();;
                break;
            case 5:
                stergeDepozit();
                break;
            case 6:
                modificaDepozit();
                break;
            case 7:
                adaugaTransportator();
                break;
            case 8:
                stergeTransportator();
                break;
            case 9:
                modificaTransportator();
                break;
             case 10:
               std::cout << *this << std::endl; // Afisam informatiile despre manager
            break;
            case 0:
                std::cout << "Iesire din aplicatie.\n";
                break;
            default:
                std::cout << "Optiune invalida. Va rugam sa reintroduceti optiunea.\n";
                break;
        }
    } while (optiune != 0);
}

int main() {
    CurieratManager manager;
    manager.incarcaIduri(); // Încarcă ID-urile din fișier
    manager.incarcaDateDinFisiere(); // Încarcă datele din fișiere
    manager.menu(); // Afiseaza meniul principal

    return 0;
}
