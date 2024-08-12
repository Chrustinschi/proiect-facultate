#ifndef CURIERAT_H_INCLUDED
#define CURIERAT_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>


class Pachet {

private:
    int id;
    std::string livrator;
    std::string adresalivrator;
    std::string destinatar;
    std::string adresadestinatar;
    std::string specificati;

public:
    Pachet(int id, const std::string& livrator, const std::string& adresalivrator, const std::string& destinatar, const std::string& adresadestinatar, const std::string& specificati);

    int getId() const { return id; }
    std::string getLivrator() const { return livrator; }
    std::string getAdresalivrator() const { return adresalivrator; }
    std::string getDestinatar() const { return destinatar; }
    std::string getAdresadestinatar() const { return adresadestinatar; }
    std::string getSpecificati() const { return specificati; }
    void setLivrator(const std::string& newLivrator) { livrator = newLivrator; }
    void setAdresalivrator(const std::string& newAdresalivrator) { adresalivrator = newAdresalivrator; }
    void setDestinatar(const std::string& newDestinatar) { destinatar = newDestinatar; }
    void setAdresadestinatar(const std::string& newAdresadestinatar) { adresadestinatar = newAdresadestinatar; }
    void setSpecificati(const std::string& newSpecificati) { specificati = newSpecificati; }

};

class Depozit {

private:
    int id;
    std::string nume;
    std::string adresa;

public:
    Depozit(int id, const std::string& nume, const std::string& adresa);

    int getId() const { return id; }
    std::string getNume() const { return nume; }
    std::string getAdresa() const { return adresa; }
    void setNume(const std::string& nume) { this->nume = nume; }
    void setAdresa(const std::string& adresa) { this->adresa = adresa; }

};

class Transportator {

private:
    int id;
    std::string nume;
    std::string adresapreluare;
    std::string adresalivrare;

public:
    Transportator(int id, const std::string& nume, const std::string& adresapreluare, const std::string& adresalivrare);

    int getId() const { return id; }
    std::string getNume() const { return nume; }
    std::string getAdresapreluare() const { return adresapreluare; }
    std::string getAdresalivrare() const { return adresalivrare; }
    void setNume(const std::string& newNume) { nume = newNume; }
    void setAdresapreluare(const std::string& newAdresapreluare) { adresapreluare = newAdresapreluare; }
    void setAdresalivrare(const std::string& newAdresalivrare) { adresalivrare = newAdresalivrare; }

};

class CurieratManager {

private:
    std::vector<Depozit> depozite;
    std::vector<Pachet> colete;
    std::vector<Transportator> transportatori;
    int nextPachetId = 1;
    int nextDepozitId = 1;
    int nextTransportatorId = 1;

public:
    void menu();
    void salveazaPachetInFisier(const Pachet& pachet) const;
    void salveazaDepozitInFisier(const Depozit& depozit) const;
    void salveazaTransportatorInFisier(const Transportator& transportator) const;
    void salveazaToatePachetele() const;
    void salveazaToateDepozitele() const;
    void salveazaToateTransportatorii() const;
    void incarcaDateDinFisiere();
    void incarcaIduri();
    void salveazaIduri() const;
    void adaugaPachet();
    void stergePachet();
    void modificaPachet();
    void adaugaDepozit();
    void stergeDepozit();
    void modificaDepozit();
    void adaugaTransportator();
    void stergeTransportator();
    void modificaTransportator();


    friend std::ostream& operator<<(std::ostream& out, const CurieratManager& manager);
    friend std::istream& operator>>(std::istream& in, CurieratManager& manager);
};

#endif // CURIERAT_H_INCLUDED
