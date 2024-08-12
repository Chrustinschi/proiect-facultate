#include "curierat.h"
#include <algorithm>
#include <limits>
#include <iostream>
#include <string>


Pachet::Pachet(int id, const std::string& livrator, const std::string& adresalivrator, const std::string& destinatar,
               const std::string& adresadestinatar, const std::string& specificati)
    : id(id), livrator(livrator), adresalivrator(adresalivrator), destinatar(destinatar), adresadestinatar(adresadestinatar), specificati(specificati) {}

Depozit::Depozit(int id, const std::string& nume, const std::string& adresa)
    : id(id), nume(nume), adresa(adresa) {}

Transportator::Transportator(int id, const std::string& nume, const std::string& adresapreluare, const std::string& adresalivrare)
    : id(id), nume(nume), adresapreluare(adresapreluare), adresalivrare(adresalivrare) {}


//adăugam date în fișier fără să ștergem datel pe care le avem deja adugate.
void CurieratManager::salveazaPachetInFisier(const Pachet& pachet) const {
    try {
        std::ofstream file("pachete.txt", std::ios::app);
        if (!file.is_open()) {
            throw std::runtime_error("Eroare la deschiderea fisierului pentru scriere.");
        }

        file << "ID: " << pachet.getId() << "\nNumele si prenumele livratorului: " << pachet.getLivrator()
             << "\nAdresa livratorului: " << pachet.getAdresalivrator() << "\nNumele si prenumele destinatar: "
             << pachet.getDestinatar() << "\nAdresa destinatar: " << pachet.getAdresadestinatar()
             << "\nSpecificatii: " << pachet.getSpecificati() << "\n";

        file.close();
    } catch (const std::exception& e) {
        std::cerr << "Exceptie: " << e.what() << std::endl;
    }
}

void CurieratManager::salveazaDepozitInFisier(const Depozit& depozit) const {
    try {
        std::ofstream file("depozite.txt", std::ios::app);
        if (!file.is_open()) {
            throw std::runtime_error("Eroare la deschiderea fisierului pentru scriere.");
        }

        file << "ID: " << depozit.getId() << "\nNumele depozitului: " << depozit.getNume()
             << "\nAdresa depozitului: " << depozit.getAdresa() << "\n";

        file.close();
    } catch (const std::exception& e) {
        std::cerr << "Exceptie: " << e.what() << std::endl;
    }
}

void CurieratManager::salveazaTransportatorInFisier(const Transportator& transportator) const {
    try {
        std::ofstream file("transportatori.txt", std::ios::app);
        if (!file.is_open()) {
            throw std::runtime_error("Eroare la deschiderea fisierului pentru scriere.");
        }

        file << "ID: " << transportator.getId() << "\nNumele si prenumele transportatorului: " << transportator.getNume()
             << "\nAdresa preluare coletului: " << transportator.getAdresapreluare()
             << "\nAdresa livrarii pachetului: " << transportator.getAdresalivrare() << "\n";

        file.close();
    } catch (const std::exception& e) {
        std::cerr << "Exceptie: " << e.what() << std::endl;
    }
}

//rescrim complet fișierele după ștergere sau modificare.
void CurieratManager::salveazaToatePachetele() const {
    try {
        std::ofstream file("pachete.txt", std::ios::trunc);
        if (!file.is_open()) {
            throw std::runtime_error("Eroare la deschiderea fisierului pentru scriere.");
        }

        for (const auto& pachet : colete) {
            file << "ID: " << pachet.getId() << "\nNumele si prenumele livratorului: " << pachet.getLivrator()
                 << "\nAdresa livratorului: " << pachet.getAdresalivrator() << "\nNumele si prenumele destinatar: "
                 << pachet.getDestinatar() << "\nAdresa destinatar: " << pachet.getAdresadestinatar()
                 << "\nSpecificatii: " << pachet.getSpecificati() << "\n";
        }

        file.close();
    } catch (const std::exception& e) {
        std::cerr << "Exceptie: " << e.what() << std::endl;
    }
}

void CurieratManager::salveazaToateDepozitele() const {
    try {
        std::ofstream file("depozite.txt", std::ios::trunc);
        if (!file.is_open()) {
            throw std::runtime_error("Eroare la deschiderea fisierului pentru scriere.");
        }

        for (const auto& depozit : depozite) {
            file << "ID: " << depozit.getId() << "\nNumele depozitului: " << depozit.getNume()
                 << "\nAdresa depozitului: " << depozit.getAdresa() << "\n";
        }

        file.close();
    } catch (const std::exception& e) {
        std::cerr << "Exceptie: " << e.what() << std::endl;
    }
}

void CurieratManager::salveazaToateTransportatorii() const {
    try {
        std::ofstream file("transportatori.txt", std::ios::trunc);
        if (!file.is_open()) {
            throw std::runtime_error("Eroare la deschiderea fisierului pentru scriere.");
        }

        for (const auto& transportator : transportatori) {
            file << "ID: " << transportator.getId() << "\nNumele si prenumele transportatorului: " << transportator.getNume()
                 << "\nAdresa preluare coletului: " << transportator.getAdresapreluare()
                 << "\nAdresa livrarii pachetului: " << transportator.getAdresalivrare() << "\n";
        }

        file.close();
    } catch (const std::exception& e) {
        std::cerr << "Exceptie: " << e.what() << std::endl;
    }
}

//asigurăm că datele sunt restabilite din fișiere
void CurieratManager::incarcaDateDinFisiere() {
    std::ifstream file;
    std::string line;

    // Încărcare pachete
    file.open("pachete.txt");
    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            int id;
            std::string livrator, adresalivrator, destinatar, adresadestinatar, specificati;

            if (line.find("ID: ") != std::string::npos) {
                id = std::stoi(line.substr(line.find(": ") + 2));
            }

            std::getline(file, line); if (line.find(": ") != std::string::npos) livrator = line.substr(line.find(": ") + 2);
            std::getline(file, line); if (line.find(": ") != std::string::npos) adresalivrator = line.substr(line.find(": ") + 2);
            std::getline(file, line); if (line.find(": ") != std::string::npos) destinatar = line.substr(line.find(": ") + 2);
            std::getline(file, line); if (line.find(": ") != std::string::npos) adresadestinatar = line.substr(line.find(": ") + 2);
            std::getline(file, line); if (line.find(": ") != std::string::npos) specificati = line.substr(line.find(": ") + 2);

            colete.emplace_back(id, livrator, adresalivrator, destinatar, adresadestinatar, specificati);
            if (id >= nextPachetId) nextPachetId = id + 1;
        }
        file.close();
    }

    // Încărcare depozite
    file.open("depozite.txt");
    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            int id;
            std::string nume, adresa;

            if (line.find("ID: ") != std::string::npos) {
                id = std::stoi(line.substr(line.find(": ") + 2));
            }

            std::getline(file, line); if (line.find(": ") != std::string::npos) nume = line.substr(line.find(": ") + 2);
            std::getline(file, line); if (line.find(": ") != std::string::npos) adresa = line.substr(line.find(": ") + 2);

            depozite.emplace_back(id, nume, adresa);
            if (id >= nextDepozitId) nextDepozitId = id + 1;
        }
        file.close();
    }

    // Încărcare transportatori
    file.open("transportatori.txt");
    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            int id;
            std::string nume, adresapreluare, adresalivrare;

            if (line.find("ID: ") != std::string::npos) {
                id = std::stoi(line.substr(line.find(": ") + 2));
            }

            std::getline(file, line); if (line.find(": ") != std::string::npos) nume = line.substr(line.find(": ") + 2);
            std::getline(file, line); if (line.find(": ") != std::string::npos) adresapreluare = line.substr(line.find(": ") + 2);
            std::getline(file, line); if (line.find(": ") != std::string::npos) adresalivrare = line.substr(line.find(": ") + 2);

            transportatori.emplace_back(id, nume, adresapreluare, adresalivrare);
            if (id >= nextTransportatorId) nextTransportatorId = id + 1;
        }
        file.close();
    }
}

//restabilirea ID-urile după repornire, pentru a nu folosi acelas id
void CurieratManager::incarcaIduri() {
    std::ifstream file("ids.txt");
    if (file.is_open()) {
        file >> nextPachetId >> nextDepozitId >> nextTransportatorId;
        file.close();
    }
}

//păstrăm ID-uril, dupa repornire
void CurieratManager::salveazaIduri() const {
    std::ofstream file("ids.txt", std::ios::trunc);
    if (file.is_open()) {
        file << nextPachetId << " " << nextDepozitId << " " << nextTransportatorId;
        file.close();
    }
}

void CurieratManager::adaugaPachet() {
    std::string livrator, adresalivrator, destinatar, adresadestinatar, specificati;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Introduceti numele si prenumele livrator: ";
    std::getline(std::cin, livrator);
    std::cout << "Introduceti adresa livrator: ";
    std::getline(std::cin, adresalivrator);
    std::cout << "Introduceti numele si prenumele destinatarului: ";
    std::getline(std::cin, destinatar);
    std::cout << "Introduceti adresa destinatarului: ";
    std::getline(std::cin, adresadestinatar);
    std::cout << "Introduceti specificatile coletului: ";
    std::getline(std::cin, specificati);

    colete.emplace_back(nextPachetId++, livrator, adresalivrator, destinatar, adresadestinatar, specificati);
    salveazaPachetInFisier(colete.back());
    salveazaIduri();

    std::cout << "Pachetul a fost adaugat cu succes.\n";
}

void CurieratManager::stergePachet() {
    if (colete.empty()) {
        std::cout << "Nu exista pachete de sters.\n";
        return;
    }

    int id;
    std::cout << "Introduceti ID-ul pachetului pe care doriti sa-l stergeti: ";
    std::cin >> id;

    auto it = std::find_if(colete.begin(), colete.end(), [id](const Pachet& pachet) {
        return pachet.getId() == id;
    });

    if (it != colete.end()) {
        colete.erase(it);
        salveazaToatePachetele();
        std::cout << "Pachetul a fost sters cu succes.\n";
    } else {
        std::cout << "Pachetul cu ID-ul " << id << " nu a fost gasit.\n";
    }
}

void CurieratManager::modificaPachet() {
    if (colete.empty()) {
        std::cout << "Nu exista pachete de modificat.\n";
        return;
    }

    int id;
    std::cout << "Introduceti ID-ul pachetului pe care doriti sa-l modificati: ";
    std::cin >> id;

    auto it = std::find_if(colete.begin(), colete.end(), [id](const Pachet& pachet) {
        return pachet.getId() == id;
    });

    if (it != colete.end()) {
        std::string livrator, adresalivrator, destinatar, adresadestinatar, specificati;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Introduceti noul nume si prenume al livratorului: ";
        std::getline(std::cin, livrator);
        std::cout << "Introduceti noua adresa a livratorului: ";
        std::getline(std::cin, adresalivrator);
        std::cout << "Introduceti noul nume si prenume al destinatarului: ";
        std::getline(std::cin, destinatar);
        std::cout << "Introduceti noua adresa a destinatarului: ";
        std::getline(std::cin, adresadestinatar);
        std::cout << "Introduceti specificatiile coletului: ";
        std::getline(std::cin, specificati);

        it->setLivrator(livrator);
        it->setAdresalivrator(adresalivrator);
        it->setDestinatar(destinatar);
        it->setAdresadestinatar(adresadestinatar);
        it->setSpecificati(specificati);

        salveazaToatePachetele();
        std::cout << "Pachetul a fost modificat cu succes.\n";
    } else {
        std::cout << "Pachetul cu ID-ul " << id << " nu a fost gasit.\n";
    }
}

void CurieratManager::adaugaDepozit() {
    std::string nume;
    std::string adresa;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Introduceti numele depozitului: ";
    std::getline(std::cin, nume);
    std::cout << "Introduceti adresa depozitului: ";
    std::getline(std::cin, adresa);

    depozite.emplace_back(nextDepozitId++, nume, adresa);
    salveazaDepozitInFisier(depozite.back());
    salveazaIduri();

    std::cout << "Depozitul a fost adaugat cu succes.\n";
}

void CurieratManager::stergeDepozit() {
    int id;
    std::cout << "Introduceti ID-ul depozitului pe care doriti sa-l stergeti: ";
    std::cin >> id;

    auto it = std::find_if(depozite.begin(), depozite.end(), [id](const Depozit& depozit) {
        return depozit.getId() == id;
    });

    if (it != depozite.end()) {
        depozite.erase(it);
        salveazaToateDepozitele();
        std::cout << "Depozitul a fost sters cu succes.\n";
    } else {
        std::cout << "Depozitul cu ID-ul " << id << " nu a fost gasit.\n";
    }
}

void CurieratManager::modificaDepozit() {
    int id;
    std::cout << "Introduceti ID-ul depozitului pe care doriti sa-l modificati: ";
    std::cin >> id;

    auto it = std::find_if(depozite.begin(), depozite.end(), [id](const Depozit& depozit) {
        return depozit.getId() == id;
    });

    if (it != depozite.end()) {
        std::string numeNou, adresaNoua;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Introduceti noul nume al depozitului: ";
        std::getline(std::cin, numeNou);
        std::cout << "Introduceti noua adresa a depozitului: ";
        std::getline(std::cin, adresaNoua);

        it->setNume(numeNou);
        it->setAdresa(adresaNoua);

        salveazaToateDepozitele();
        std::cout << "Depozitul a fost modificat cu succes.\n";
    } else {
        std::cout << "Depozitul cu ID-ul " << id << " nu a fost gasit.\n";
    }
}

void CurieratManager::adaugaTransportator() {
    std::string nume, adresapreluare, adresalivrare;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Introduceti numele si prenumele transportatorului: ";
    std::getline(std::cin, nume);
    std::cout << "Introduceti adresa de preluare: ";
    std::getline(std::cin, adresapreluare);
    std::cout << "Introduceti adresa de livrare: ";
    std::getline(std::cin, adresalivrare);

    transportatori.emplace_back(nextTransportatorId++, nume, adresapreluare, adresalivrare);
    salveazaTransportatorInFisier(transportatori.back());
    salveazaIduri();

    std::cout << "Transportatorul a fost adaugat cu succes.\n";
}

void CurieratManager::stergeTransportator() {
    if (transportatori.empty()) {
        std::cout << "Nu exista transportatori de sters.\n";
        return;
    }

    int id;
    std::cout << "Introduceti ID-ul transportatorului pe care doriti sa-l stergeti: ";
    std::cin >> id;

    auto it = std::find_if(transportatori.begin(), transportatori.end(), [id](const Transportator& transportator) {
        return transportator.getId() == id;
    });

    if (it != transportatori.end()) {
        transportatori.erase(it);
        salveazaToateTransportatorii();
        std::cout << "Transportatorul a fost sters cu succes.\n";
    } else {
        std::cout << "Transportatorul cu ID-ul " << id << " nu a fost gasit.\n";
    }
}

void CurieratManager::modificaTransportator() {
    if (transportatori.empty()) {
        std::cout << "Nu exista transportatori de modificat.\n";
        return;
    }

    int id;
    std::cout << "Introduceti ID-ul transportatorului pe care doriti sa-l modificati: ";
    std::cin >> id;

    auto it = std::find_if(transportatori.begin(), transportatori.end(), [id](const Transportator& transportator) {
        return transportator.getId() == id;
    });

    if (it != transportatori.end()) {
        std::string numeNou, adresapreluareNoua, adresalivrareNoua;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Introduceti noul nume si prenume al transportatorului: ";
        std::getline(std::cin, numeNou);
        std::cout << "Introduceti noua adresa de preluare: ";
        std::getline(std::cin, adresapreluareNoua);
        std::cout << "Introduceti noua adresa de livrare: ";
        std::getline(std::cin, adresalivrareNoua);

        it->setNume(numeNou);
        it->setAdresapreluare(adresapreluareNoua);
        it->setAdresalivrare(adresalivrareNoua);

        salveazaToateTransportatorii();
        std::cout << "Transportatorul a fost modificat cu succes.\n";
    } else {
        std::cout << "Transportatorul cu ID-ul " << id << " nu a fost gasit.\n";
    }
}


// Permite afișarea informațiilor unui obiect
std::ostream& operator<<(std::ostream& out, const CurieratManager& manager) {
    out << "\nPachete:\n";
    for (const auto& pachet : manager.colete) {
        out << "ID: " << pachet.getId() << "\nNumele si prenumele livratorului: " << pachet.getLivrator()
             << "\nAdresa livratorului: " << pachet.getAdresalivrator() << "\nNumele si prenumele destinatarului: "
             << pachet.getDestinatar() << "\nAdresa destinatarului: " << pachet.getAdresadestinatar()
             << "\nSpecificatii: " << pachet.getSpecificati() << "\n";
    }

    out << "\nDepozite:\n";
    for (const auto& depozit : manager.depozite) {
        out << "ID: " << depozit.getId() << "\nNumele depozitului: " << depozit.getNume()
             << "\nAdresa depozitului: " << depozit.getAdresa() << "\n";
    }

    out << "\nTransportatori:\n";
    for (const auto& transportator : manager.transportatori) {
        out << "ID: " << transportator.getId() << "\nNumele si prenumele transportatorului: " << transportator.getNume()
             << "\nAdresa preluare coletului: " << transportator.getAdresapreluare()
             << "\nAdresa livrarii pachetului: " << transportator.getAdresalivrare() << "\n";
    }

    return out;
}


//Permite citirea informațiilor într-un obiect
std::istream& operator>>(std::istream& in, CurieratManager& manager) {
    // Citirea informațiilor despre pachete
    manager.colete.clear();
    int numarPachete;
    std::cout << "Introduceti numarul de pachete: ";
    in >> numarPachete;
    for (int i = 0; i < numarPachete; ++i) {
        int id;
        std::string livrator, adresalivrator, destinatar, adresadestinatar, specificati;
        std::cout << "Pachet " << i + 1 << ":\n";
        std::cout << "Introduceti numele si prenumele livratorului: ";
        std::getline(in, livrator);
        std::cout << "Introduceti adresa livratorului: ";
        std::getline(in, adresalivrator);
        std::cout << "Introduceti numele si prenumele destinatarului: ";
        std::getline(in, destinatar);
        std::cout << "Introduceti adresa destinatarului: ";
        std::getline(in, adresadestinatar);
        std::cout << "Introduceti specificatiile coletului: ";
        std::getline(in, specificati);
        manager.colete.emplace_back(id, livrator, adresalivrator, destinatar, adresadestinatar, specificati);
    }

    // Citirea informațiilor despre depozite
    manager.depozite.clear();
    int numarDepozite;
    std::cout << "Introduceti numarul de depozite: ";
    in >> numarDepozite;
    for (int i = 0; i < numarDepozite; ++i) {
        int id;
        std::string nume, adresa;
        std::cout << "Depozit " << i + 1 << ":\n";
        std::cout << "Introduceti numele depozitului: ";
        std::getline(in, nume);
        std::cout << "Introduceti adresa depozitului: ";
        std::getline(in, adresa);
        manager.depozite.emplace_back(id, nume, adresa);
    }

    // Citirea informațiilor despre transportatori
    manager.transportatori.clear();
    int numarTransportatori;
    std::cout << "Introduceti numarul de transportatori: ";
    in >> numarTransportatori;
    for (int i = 0; i < numarTransportatori; ++i) {
        int id;
        std::string nume, adresapreluare, adresalivrare;
        std::cout << "Transportator " << i + 1 << ":\n";
        std::cout << "Introduceti numele si prenumele: ";
        std::getline(in, nume);
        std::cout << "Introduceti adresa de preluare: ";
        std::getline(in, adresapreluare);
        std::cout << "Introduceti adresa de livrare: ";
        std::getline(in, adresalivrare);
        manager.transportatori.emplace_back(id, nume, adresapreluare, adresalivrare);
    }

    return in;
}
