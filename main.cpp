// SysOp si Admin: User = admin, Parola = admin
// ClientVIP: Nume = admin, Prenume = admin, Parola = admin
// Clinet: nu conteaza numele si prenumele
// Am adaugat 3 destinatii, 3 hoteluri si 4 pachete promotionale


#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <list>
#include <set>
#include <map>

using namespace std;

ifstream in("baza_de_date.in");
ofstream out("bon.out");

class Destinatii
{
    private:
        int nrLocuri, nrDatePlecare, nrClase;
        int* scauneLibere;
        bool disponibil;
        float distanta;
        float* preturi;
        char moneda;
        char* plecareDin;
        string destinatie;
        string* datePlecare;
        const int zborID;

    public:
        static int nrCalatorii;

        // Constructori si destructor
        Destinatii():zborID(nrCalatorii++)
        {
            this->nrLocuri = 0;
            this->nrDatePlecare = 0;
            this->disponibil = false;
            this->distanta = 0;
            this->moneda = '0';
            this->nrClase = 0;
            this->destinatie = "Fara destinatie";
            this->scauneLibere = NULL;
            this->preturi = NULL;
            this->plecareDin = new char[31];
            strcpy(this->plecareDin, "Fara ruta de plecare");
            this->datePlecare = NULL;

        }
        Destinatii(int nrLocuri, int nrDatePlecare, int nrClase, int* scauneLibere, bool disponibil, float distanta, float* preturi, char moneda, char* plecareDin, string destinatie, string* datePlecare):zborID(nrCalatorii++)
        {
            this->nrLocuri = nrLocuri;
            this->nrDatePlecare = nrDatePlecare;
            this->nrClase = nrClase;
            this->disponibil = disponibil;
            this->distanta = distanta;
            this->moneda = moneda;
            this->destinatie = destinatie;
            this->scauneLibere = new int[nrLocuri];
            for(int i=0; i<nrLocuri; i++)
                this->scauneLibere[i] = scauneLibere[i];
            this->preturi = new float[nrClase];
            for(int i=0; i<nrClase; i++)
                this->preturi[i] = preturi[i];
            this->plecareDin = new char[strlen(plecareDin)+1];
            strcpy(this->plecareDin, plecareDin);
            this->datePlecare = new string [nrDatePlecare];
            for(int i=0; i<nrDatePlecare; i++)
                this->datePlecare[i] = datePlecare[i];
        }
        Destinatii(char* plecareDin, string destinatie, float distanta):zborID(nrCalatorii++)
        {
            this->plecareDin = new char[strlen(plecareDin)+1];
            strcpy(this->plecareDin, plecareDin);
            this->destinatie = destinatie;
            this->distanta = distanta;
            this->moneda = '0';
            this->nrLocuri = 0;
            this->nrDatePlecare = 0;
            this->disponibil = false;
            this->nrClase = 0;
            this->scauneLibere = NULL;
            this->preturi = NULL;
            this->datePlecare = NULL;
        }
        Destinatii(const Destinatii &dest):zborID(nrCalatorii++)
        {
            this->nrLocuri = dest.nrLocuri;
            this->nrDatePlecare = dest.nrDatePlecare;
            this->nrClase = dest.nrClase;
            this->disponibil = dest.disponibil;
            this->distanta = dest.distanta;
            this->moneda = dest.moneda;
            this->destinatie = dest.destinatie;
            this->scauneLibere = new int[dest.nrLocuri];
            for(int i=0; i<dest.nrLocuri; i++)
                this->scauneLibere[i] = dest.scauneLibere[i];
            this->preturi = new float[dest.nrClase];
            for(int i=0; i<dest.nrClase; i++)
                this->preturi[i] = dest.preturi[i];
            this->plecareDin = new char[strlen(dest.plecareDin)+1];
            strcpy(this->plecareDin, dest.plecareDin);
            this->datePlecare = new string [dest.nrDatePlecare];
            for(int i=0; i<dest.nrDatePlecare; i++)
                this->datePlecare[i] = dest.datePlecare[i];
        }
        ~Destinatii()
        {
            if(this->scauneLibere != NULL)
                delete[] this->scauneLibere;
            if(this->preturi != NULL)
                delete[] this->preturi;
            if(this->plecareDin != NULL)
                delete[] this->plecareDin;
            if(this->datePlecare != NULL)
                delete[] this->datePlecare;
        }


        //Operatorii
        Destinatii& operator=(const Destinatii& dest)
        {
            if(this != &dest)
            {
                if(this->scauneLibere != NULL)
                    delete[] this->scauneLibere;
                if(this->preturi != NULL)
                    delete[] this->preturi;
                if(this->plecareDin != NULL)
                    delete[] this->plecareDin;
                if(this->datePlecare != NULL)
                    delete[] this->datePlecare;

                this->nrLocuri = dest.nrLocuri;
                this->nrDatePlecare = dest.nrDatePlecare;
                this->nrClase = dest.nrClase;
                this->disponibil = dest.disponibil;
                this->distanta = dest.distanta;
                this->moneda = dest.moneda;
                this->destinatie = dest.destinatie;
                this->scauneLibere = new int[dest.nrLocuri];
                for(int i=0; i<dest.nrLocuri; i++)
                    this->scauneLibere[i] = dest.scauneLibere[i];
                this->preturi = new float[dest.nrClase];
                for(int i=0; i<dest.nrClase; i++)
                    this->preturi[i] = dest.preturi[i];
                this->plecareDin = new char[strlen(dest.plecareDin)+1];
                strcpy(this->plecareDin, dest.plecareDin);
                this->datePlecare = new string [dest.nrDatePlecare];
                for(int i=0; i<dest.nrDatePlecare; i++)
                    this->datePlecare[i] = dest.datePlecare[i];
            }
            *this;
        }
        friend istream& operator>>(istream& in, Destinatii& dest);
        friend ostream& operator<<(ostream& out, const Destinatii& dest);
        friend ifstream& operator>>(ifstream& in, Destinatii& dest);
        friend ofstream& operator<<(ofstream& out, const Destinatii& dest);
        bool operator==(const Destinatii& dest)
        {
            if(strcmp(dest.plecareDin, this->plecareDin)==0 && this->destinatie == dest.destinatie)
                return true;
            return false;
        }
        bool operator<(const Destinatii& dest)
        {
            if(this->distanta < dest.distanta)
                return true;
            return false;
        }
        bool operator>=(const Destinatii& dest)
        {
            if(this->distanta >= dest.distanta)
                return true;
            return false;
        }
        explicit operator int()
        {
            return (int)this->preturi[0];
        }
        const Destinatii& operator++()
        {
            for(int i=0; i<this->nrClase; i++)
                this->preturi[i]++;
            return *this;
        }
        const Destinatii operator++(int)
        {
            Destinatii aux(*this);
            for(int i=0; i<this->nrClase; i++)
                this->preturi[i]++;
            return aux;
        }
        const Destinatii& operator--()
        {
            for(int i=0; i<this->nrClase; i++)
                this->preturi[i]--;
            return *this;
        }
        const Destinatii operator--(int)
        {
            Destinatii aux(*this);
            for(int i=0; i<this->nrClase; i++)
                this->preturi[i]--;
            return aux;
        }
        Destinatii operator*(int x)
        {
            Destinatii aux(*this);
            for(int i=0; i<aux.nrClase; i++)
                aux.preturi[i] = aux.preturi[i] * x;
            return aux;
        }
        friend Destinatii operator*(int x, Destinatii dest)
        {
            for(int i=0; i<dest.nrClase; i++)
                dest.preturi[i] = x * dest.preturi[i];
            return dest;
        }
        Destinatii operator+(Destinatii dest)
        {
            Destinatii aux;
            aux.plecareDin = new char[strlen(dest.plecareDin)+strlen(this->plecareDin)+1];
            strcpy(aux.plecareDin, this->plecareDin);
            strcat(aux.plecareDin, ", ");
            strcat(aux.plecareDin, dest.plecareDin);
            aux.destinatie = this->destinatie+", "+dest.destinatie;
            return aux;
        }



        //Setteri
        void set_locuriLibere(int nrLocuri, int* scauneLibere)
        {
            this->nrLocuri = nrLocuri;
            if(this->scauneLibere != NULL)
                delete[] this->scauneLibere;
            this->scauneLibere = new int[this->nrLocuri];
            for(int i=0; i<this->nrLocuri; i++)
                this->scauneLibere[i] = scauneLibere[i];
        }
        void set_disponibil(bool disponibil)
        {
            this->disponibil = disponibil;
        }
        void set_distanta(float distanta)
        {
            this->distanta = distanta;
        }
        void set_preturi(float* preturi, char moneda, int nrClase)
        {
            this->moneda = moneda;
            this->nrClase = nrClase;
            if(this->preturi != NULL)
                delete[] this->preturi;
            this->preturi = new float[this->nrClase];
            for(int i=0; i<this->nrClase; i++)
                this->preturi[i] = preturi[i];
        }
        void set_locatii(char* plecareDin, string destinatie)
        {
            if(this->plecareDin != NULL)
                delete[] this->plecareDin;
            this->plecareDin = new char[strlen(plecareDin)+1];
            strcpy(this->plecareDin, plecareDin);

            this->destinatie = destinatie;
        }
        void set_date(int nrDatePlecare, string* datePlecare)
        {
            this->nrDatePlecare = nrDatePlecare;
            if(this->datePlecare != NULL)
                delete[] this->datePlecare;
            this->datePlecare = new string[nrDatePlecare];
            for(int i=0; i<this->nrDatePlecare; i++)
                this->datePlecare[i] = datePlecare[i];
        }



        //Getteri
        int get_nrLocuri()
        {
            return nrLocuri;
        }
        int get_nrClase()
        {
            return nrClase;
        }
        int get_nrDatePlecare()
        {
            return nrDatePlecare;
        }
        int* get_scauneLibere()
        {
            return this->scauneLibere;
        }
        bool get_disponibil()
        {
            return disponibil;
        }
        float get_distanta()
        {
            return distanta;
        }
        float* get_preturi()
        {
            return this->preturi;
        }
        char get_moneda()
        {
            return moneda;
        }
        char* get_plecareDin()
        {
            return this->plecareDin;
        }
        string get_destinatie()
        {
            return destinatie;
        }
        string* get_datePlecare()
        {
            return this->datePlecare;
        }


        //Functii membre
        void afisare()
        {
            cout << "\nId zbor: " << this->zborID;
            cout << "\nNr zboruri pana acum: " << this->nrCalatorii;
            cout << "\nPlecare din: " << this->plecareDin;
            cout << "\nCatre: " << this->destinatie;
            cout << "\nDistanta: " << this->distanta;
            cout << "\nDisponibil: " << this->disponibil;
            cout << "\nDate de plecare: ";
            if(datePlecare != NULL)
                for(int i=0; i<this->nrDatePlecare; i++)
                    cout << this->datePlecare[i] << " ";
            cout << "\nMoneda de cumparare: " << this->moneda;
            cout << "\nPreturi pe clase: ";
            if(preturi != NULL)
                for(int i=0; i<this->nrClase; i++)
                    cout << this->preturi[i] << " ";
            cout << "\nScaune libere: ";
            if(scauneLibere != NULL)
                for(int i=0; i<this->nrLocuri; i++)
                    cout << this->scauneLibere[i] << " ";
        }

};
istream& operator>>(istream& in, Destinatii& dest)
{
    cout << "\nDe unde plecati? ";
    char aux[101];
    in>>aux;
    if(dest.plecareDin != NULL)
        delete[] dest.plecareDin;
    dest.plecareDin = new char[strlen(aux)+1];
    strcpy(dest.plecareDin, aux);
    cout << "\nDestinatia: ";
    in >> dest.destinatie;
    cout << "\nEste zborul disponibil: (1=Da, 0=Nu) ";
    in >> dest.disponibil;
    cout << "\nIntroduceti distanta in km: ";
    in >> dest.distanta;
    cout << "\nIn cate zile va fi disponibil zborul? ";
    in >> dest.nrDatePlecare;
    cout << "\nIntroduceti datele in care va fi disponibil zborul: ";
    if(dest.datePlecare != NULL)
        delete[] dest.datePlecare;
    dest.datePlecare = new string[dest.nrDatePlecare];
    for(int i=0; i<dest.nrDatePlecare; i++)
        in >> dest.datePlecare[i];
    cout << "\nIntroduceti initiala monedei de cumparare a biletului: ";
    in >> dest.moneda;
    cout << "\nCate clase de zbor va avea avionul? ";
    in >> dest.nrClase;
    cout << "\nIntroduceti pretul la fiecare clasa: ";
    if(dest.preturi != NULL)
        delete[] dest.preturi;
    dest.preturi = new float[dest.nrClase];
    for(int i=0; i<dest.nrClase; i++)
        in >> dest.preturi[i];
    cout << "\nCate locuri libere are avionul? ";
    in >> dest.nrLocuri;
    cout << "\nIntroduceti locurile libere: ";
    if(dest.scauneLibere != NULL)
        delete[] dest.scauneLibere;
    dest.scauneLibere = new int[dest.nrLocuri];
    for(int i=0; i<dest.nrLocuri; i++)
        in >> dest.scauneLibere[i];
}
ostream& operator<<(ostream& out, const Destinatii& dest)
{
    out << "\nId zbor: " << dest.zborID;
    out << "\nNr zboruri pana acum: " << dest.nrCalatorii;
    out << "\nPlecare din: " << dest.plecareDin;
    out << "\nCatre: " << dest.destinatie;
    out << "\nDisponibil: ";
    if(dest.disponibil == true) out << "Da";
    else out << "Nu";
    out << "\nDistanta in km: " << dest.distanta;
    out << "\nDate de plecare: ";
    for(int i=0; i<dest.nrDatePlecare; i++)
        out << dest.datePlecare[i] << " ";
    out << "\nMoneda de cumparare: " << dest.moneda;
    out << "\nPreturi pe clase: ";
    for(int i=0; i<dest.nrClase; i++)
        out << dest.preturi[i] << " ";
    out << "\nScaune libere: ";
    for(int i=0; i<dest.nrLocuri; i++)
        out << dest.scauneLibere[i] << " ";
}
ifstream& operator>>(ifstream& in, Destinatii& dest)
{
    char aux[101];
    in>>aux;
    if(dest.plecareDin != NULL)
        delete[] dest.plecareDin;
    dest.plecareDin = new char[strlen(aux)+1];
    strcpy(dest.plecareDin, aux);
    in >> dest.destinatie;
    in >> dest.disponibil;
    in >> dest.distanta;
    in >> dest.nrDatePlecare;
    if(dest.datePlecare != NULL)
        delete[] dest.datePlecare;
    dest.datePlecare = new string[dest.nrDatePlecare];
    for(int i=0; i<dest.nrDatePlecare; i++)
        in >> dest.datePlecare[i];
    in >> dest.moneda;
    in >> dest.nrClase;
    if(dest.preturi != NULL)
        delete[] dest.preturi;
    dest.preturi = new float[dest.nrClase];
    for(int i=0; i<dest.nrClase; i++)
        in >> dest.preturi[i];
    in >> dest.nrLocuri;
    if(dest.scauneLibere != NULL)
        delete[] dest.scauneLibere;
    dest.scauneLibere = new int[dest.nrLocuri];
    for(int i=0; i<dest.nrLocuri; i++)
        in >> dest.scauneLibere[i];
}
ofstream& operator<<(ofstream& out, const Destinatii& dest)
{
    out << "\nPlecare din: " << dest.plecareDin;
    out << "\nCatre: " << dest.destinatie;
    out << "\nDisponibil: ";
    if(dest.disponibil == true) out << "Da";
    else out << "Nu";
    out << "\nDistanta in km: " << dest.distanta;
    out << "\nDate de plecare: ";
    for(int i=0; i<dest.nrDatePlecare; i++)
        out << dest.datePlecare[i] << " ";
    out << "\nMoneda de cumparare: " << dest.moneda;
    out << "\nPreturi pe clase: ";
    for(int i=0; i<dest.nrClase; i++)
        out << dest.preturi[i] << " ";
    out << "\nScaune libere: ";
    for(int i=0; i<dest.nrLocuri; i++)
        out << dest.scauneLibere[i] << " ";
}
int Destinatii::nrCalatorii = 0;

vector <Destinatii> d;

class Hotel
{
    private:
        int nrStele, nrCamereLibere, nrDate;
        bool disponibil;
        float review, pret;
        string oras, nume;
        string* checkIn;

    public:
        Hotel()
        {
            this->nrStele = 0;
            this->nrCamereLibere = 0;
            this->nrDate = 0;
            this->disponibil = false;
            this->review = 0;
            this->pret = 0;
            this->oras = "Fara locatie";
            this->nume = "Fara nume";
            this->checkIn = NULL;
        }
        Hotel(int nrStele, int nrCamereLibere, int nrDate, bool disponibil, float review, float pret, string oras, string nume, string* checkIn)
        {
            this->nrStele = nrStele;
            this->nrCamereLibere = nrCamereLibere;
            this->nrDate = nrDate;
            this->disponibil = disponibil;
            this->review = review;
            this->pret = pret;
            this->oras = oras;
            this->nume = nume;
            this->checkIn = new string[this->nrDate];
            for(int i=0; i<this->nrDate; i++)
                this->checkIn[i] = checkIn[i];
        }
        Hotel(string oras, string nume, float pret, int nrStele)
        {
            this->oras = oras;
            this->nume = nume;
            this->pret = pret;
            this->nrStele = nrStele;
            this->nrDate = 0;
            this->nrCamereLibere = 0;
            this->disponibil = false;
            this->review = 0;
            this->checkIn = NULL;
        }
        Hotel(const Hotel &hot)
        {
            this->nrStele = hot.nrStele;
            this->nrCamereLibere = hot.nrCamereLibere;
            this->nrDate = hot.nrDate;
            this->disponibil = hot.disponibil;
            this->review = hot.review;
            this->pret = hot.pret;
            this->oras = hot.oras;
            this->nume = hot.nume;
            this->checkIn = new string[this->nrDate];
            for(int i=0; i<this->nrDate; i++)
                this->checkIn[i] = hot.checkIn[i];
        }
        ~Hotel()
        {
            if(this->checkIn != NULL)
                delete[] this->checkIn;
        }



        Hotel& operator=(const Hotel& hot)
        {
            if(this != &hot)
            {
                if(this->checkIn != NULL)
                    delete[] this->checkIn;

            this->nrStele = hot.nrStele;
            this->nrCamereLibere = hot.nrCamereLibere;
            this->nrDate = hot.nrDate;
            this->disponibil = hot.disponibil;
            this->review = hot.review;
            this->pret = hot.pret;
            this->oras = hot.oras;
            this->nume = hot.nume;
            this->checkIn = new string[this->nrDate];
            for(int i=0; i<this->nrDate; i++)
                this->checkIn[i] = hot.checkIn[i];
            }
            *this;
        }
        friend istream& operator>>(istream& in, Hotel& hot);
        friend ostream& operator<<(ostream& out, const Hotel& hot);
        friend ifstream& operator>>(ifstream& in, Hotel& hot);
        friend ofstream& operator<<(ofstream& out, const Hotel& hot);



        void set_nrStele(int nrStele)
        {
            this->nrStele = nrStele;
        }
        void set_nrCamereLibere(int nrCamereLibere)
        {
            this->nrCamereLibere = nrCamereLibere;
        }
        void set_disponibil(bool disponibil)
        {
            this->disponibil = disponibil;
        }
        void set_review(float review)
        {
            this->review = review;
        }
        void set_pret(float pret)
        {
            this->pret = pret;
        }
        void set_oras(string oras)
        {
            this->oras = oras;
        }
        void set_nume(string nume)
        {
            this->nume = nume;
        }
        void set_date(int nrDate, string* checkIn)
        {
            this->nrDate = nrDate;
            if(this->checkIn != NULL)
                delete[] this->checkIn;
            this->checkIn = new string[this->nrDate];
            for(int i=0; i<this->nrDate; i++)
                this->checkIn[i] = checkIn[i];
        }



        int get_nrStele()
        {
            return this->nrStele;
        }
        int get_nrCamereLibere()
        {
            return this->nrCamereLibere;
        }
        int get_nrDate()
        {
            return this->nrDate;
        }
        bool get_disponibil()
        {
            return this->disponibil;
        }
        float get_review()
        {
            return this->review;
        }
        float get_pret()
        {
            return this->pret;
        }
        string get_oras()
        {
            return this->oras;
        }
        string get_nume()
        {
            return this->nume;
        }
        string* get_checkIn()
        {
            return this->checkIn;
        }
};
istream& operator>>(istream& in, Hotel& hot)
{
    cout << "\nCum se numeste hotelul? ";
    in >> hot.nume;
    cout << "\nIn ce oras este? ";
    in >> hot.oras;
    cout << "\nCate stele are? ";
    in >> hot.nrStele;
    cout << "\nCat costa? ";
    in >> hot.pret;
    cout << "\nEste disponibil? (1-Da, 0-Nu) ";
    in >> hot.disponibil;
    cout << "\nCate camere libere are? ";
    in >> hot.nrCamereLibere;
    cout << "\nIn cate zile este disponibil? ";
    in >> hot.nrDate;
    cout << "\nIntroduceti datele in care se poate face check-in: ";
    if(hot.checkIn != NULL)
        delete[] hot.checkIn;
    hot.checkIn = new string[hot.nrDate];
    for(int i=0; i<hot.nrDate; i++)
        in >> hot.checkIn[i];
    cout << "\nCe nota are hotelul? ";
    in >> hot.review;
}
ostream& operator<<(ostream& out, const Hotel& hot)
{
    out << "\nNume hotel: " << hot.nume;
    out << "\nOras: " << hot.oras;
    out << "\nNumar de stele: " << hot.nrStele;
    out << "\nPret: " << hot.pret;
    out << "\nDisponibil: ";
    if(hot.disponibil == true) out << "da";
    else out << "nu";
    out << "\nNumar camere libere: " << hot.nrCamereLibere;
    out << "\nDate in care se poate face check-in: ";
    for(int i=0; i<hot.nrDate; i++)
        out << hot.checkIn[i] << " ";
    out << "\nNota: " << hot.review;
}
ifstream& operator>>(ifstream& in, Hotel& hot)
{
    in >> hot.nume;
    in >> hot.oras;
    in >> hot.nrStele;
    in >> hot.pret;
    in >> hot.disponibil;
    in >> hot.nrCamereLibere;
    in >> hot.nrDate;
    if(hot.checkIn != NULL)
        delete[] hot.checkIn;
    hot.checkIn = new string[hot.nrDate];
    for(int i=0; i<hot.nrDate; i++)
        in >> hot.checkIn[i];
    in >> hot.review;
}
ofstream& operator<<(ofstream& out, const Hotel& hot)
{
    out << "\nNume hotel: " << hot.nume;
    out << "\nOras: " << hot.oras;
    out << "\nNumar de stele: " << hot.nrStele;
    out << "\nPret: " << hot.pret;
    out << "\nDisponibil: ";
    if(hot.disponibil == true) out << "da";
    else out << "nu";
    out << "\nNumar camere libere: " << hot.nrCamereLibere;
    out << "\nDate in care se poate face check-in: ";
    for(int i=0; i<hot.nrDate; i++)
        out << hot.checkIn[i] << " ";
    out << "\nNota: " << hot.review;
}

vector <Hotel> h;

class Reduceri{
public:
    virtual void calculeazaReducerea()=0;
};

class Pachete:public Reduceri{
protected:
    string nume;
    float pret;

public:
    Pachete()
    {
        this -> nume = "Nimic inca";
        this -> pret = 0;
    }
    Pachete(string nume, float pret)
    {
        this ->nume = nume;
        this -> pret = pret;
    }
    Pachete(const Pachete& p)
    {
        this -> nume = p.nume;
        this -> pret = p.pret;
    }
    Pachete& operator=(const Pachete& p)
    {
        if(this!=&p)
        {
            this -> nume = p.nume;
            this -> pret = p.pret;

        }
        return *this;
    }
    ~Pachete()
    {

    }
    friend istream& operator>>(istream& in, Pachete& p)
    {
        cout<<"\nIntroduceti numele pachetului: ";
        in>>p.nume;
        cout<<"\nIntroduceti pretul pachetului: ";
        in>>p.pret;
        return in;
    }
    friend ifstream& operator>>(ifstream& in, Pachete& p)
    {
        in>>p.nume;
        in>>p.pret;
        return in;
    }
    friend ostream& operator<<(ostream& out,const Pachete& p)
    {
        out<<"\nNume pachet: "<<p.nume;
        out<<"\nPret pachet: "<<p.pret;
        return out;
    }

    string get_nume()
    {
        return this->nume;
    }
    float get_pret()
    {
        return this->pret;
    }
    void set_nume(string nume)
    {
        this->nume = nume;
    }
    void set_pret(float pret)
    {
        this->pret = pret;
    }

    virtual float aplicaReducerea()=0;
};

class PacheteLimitedEdition:public Pachete{
private:
    string dataExp;
    Destinatii d;
    Hotel h;

public:
    PacheteLimitedEdition():Pachete()
    {
        this -> dataExp = "\0";
    }
    PacheteLimitedEdition(string nume,float pret,string dataExp, Destinatii d, Hotel h):Pachete(nume,pret)
    {
        this -> dataExp = dataExp;
        this -> d = d;
        this -> h = h;
    }
    PacheteLimitedEdition(const PacheteLimitedEdition& p):Pachete(p)
    {
        this -> dataExp = p.dataExp;
        this -> d = p.d;
        this -> h = p.h;
    }
    ~PacheteLimitedEdition()
    {

    }
    PacheteLimitedEdition& operator=(const PacheteLimitedEdition& p)
    {
        if(this != &p)
        {
            Pachete::operator=(p);
            this -> dataExp = p.dataExp;
            this -> d = p.d;
            this -> h = p.h;
        }
        return *this;
    }
    friend istream& operator>>(istream& in,PacheteLimitedEdition& p)
    {
        in>>(Pachete&) p;
        cout<<"\nIntroduceti data de expirare a pachetului promotional: ";
        in>>p.dataExp;
        in>>p.d;
        in>>p.h;
        return in;
    }
    friend ifstream& operator>>(ifstream& in,PacheteLimitedEdition& p)
    {
        in>>(Pachete&) p;
        in>>p.dataExp;
        in>>p.d;
        in>>p.h;
        return in;
    }
    friend ostream& operator<<(ostream& out,const PacheteLimitedEdition& p)
    {
        out<<(Pachete&) p;
        out<<"\nData expirare: "<<p.dataExp;
        out<<p.d;
        out<<p.h;
        return out;
    }
    void set_data(string data)
    {
        this->dataExp = data;
    }

    float aplicaReducerea()
    {
        return this->pret-this->pret*25/100;
    }
    void calculeazaReducerea()
    {
        cout<<"\nSe aplica o reducere de 25% pentru pachetele Limited Edition egala cu "<< this->pret*25/100 << " euro";
    }
};

class PacheteAllTime:public Pachete{
private:
    int aniValabilitate;
public:
    PacheteAllTime():Pachete()
    {
        this -> aniValabilitate = 0;
    }
    PacheteAllTime(string nume,float pret,int aniValabilitate):Pachete(nume,pret)
    {
        this -> aniValabilitate = aniValabilitate;
    }
    PacheteAllTime(const PacheteAllTime& p):Pachete(p)
    {
        this -> aniValabilitate = p.aniValabilitate;
    }
    ~PacheteAllTime()
    {

    }
    PacheteAllTime& operator=(const PacheteAllTime& p)
    {
        if(this != &p)
        {
            Pachete::operator=(p);
            this -> aniValabilitate = p.aniValabilitate;
        }
        return *this;
    }
    friend istream& operator>>(istream& in,PacheteAllTime& p)
    {
        in>>(Pachete&) p;
        cout<<"\nIntroduceti perioada de valabilitate a pachetului promotional: ";
        in>>p.aniValabilitate;
        return in;
    }
    friend ifstream& operator>>(ifstream& in,PacheteAllTime& p)
    {
        in>>(Pachete&) p;
        in>>p.aniValabilitate;
        return in;
    }
    friend ostream& operator<<(ostream& out,const PacheteAllTime& p)
    {
        out<<(Pachete&) p;
        out<<"\nAni de valabilitate: "<<p.aniValabilitate;
        return out;
    }
    void set_valabilitate(int ani)
    {
        this->aniValabilitate = ani;
    }

    float aplicaReducerea()
    {
        return this->pret-this->pret*10/100;
    }
    void calculeazaReducerea()
    {
        cout<<"\nSe aplica o reducere de 10% pentru pachetele All-Time egala cu "<< this->pret*10/100 << " euro";
    }
};

list <PacheteLimitedEdition> p1;
list <PacheteAllTime> p2;

class Administrator
{
private:
    char* user;
    string parola;

public:
    Administrator()
    {
        this->user = new char[strlen("Admin")+1];
        strcpy(this->user, "Admin");
        this->parola = "\0";
    }
    Administrator(char* user, string parola)
    {
        this->user = new char[strlen(user)+1];
        strcpy(this->user, user);
        this->parola = parola;
    }
    Administrator(char* user)
    {
        this->user = new char[strlen(user)+1];
        strcpy(this->user, user);
        this->parola = "\0";
    }
    Administrator(const Administrator &ad)
    {
        this->user = new char[strlen(ad.user)+1];
        strcpy(this->user, ad.user);
        this->parola = ad.parola;
    }
    ~Administrator()
    {
        if(this->user != NULL)
            delete[] this->user;
    }



    Administrator& operator=(const Administrator& ad)
    {
        if(this != &ad)
        {
            if(this->user != NULL)
                delete[] this->user;
            this->user = new char[strlen(ad.user)+1];
            strcpy(this->user, ad.user);
            this->parola = ad.parola;
        }
        *this;
    }
    friend istream& operator>>(istream& in, Administrator& ad);
    friend ostream& operator<<(ostream& out, const Administrator& ad);
    friend ifstream& operator>>(ifstream& in, Administrator& ad);
    bool operator==(const Administrator& ad)
    {
        if(strcmp(ad.user, this->user)==0 && this->parola == ad.parola)
            return true;
        return false;
    }



    void set_nume(char* user)
    {
        if(this->user != NULL)
            delete[] this->user;
        this->user = new char[strlen(user)+1];
        strcpy(this->user, user);
    }
    void set_parola(string parola)
    {
        this->parola = parola;
    }



    char* get_user()
    {
        return this->user;
    }
    string get_parola()
    {
        return this->parola;
    }



    void list_dest()
    {
        for(int i=0; i<d.size(); i++)
            {cout << d[i];
            cout << "\n";}
    }
    void list_hotel()
    {
        for(int i=0; i<h.size(); i++)
            {cout << h[i];
            cout << "\n";}
    }
    void list_pachete()
    {
        for(auto it=p1.begin(); it!=p1.end(); it++)
        {
            (*it).calculeazaReducerea();
            PacheteLimitedEdition p = (*it);
            p.set_pret(p.aplicaReducerea());
            cout << p;
            cout << "\n";
        }
        for(auto it=p2.begin(); it!=p2.end(); it++)
        {
            (*it).calculeazaReducerea();
            PacheteAllTime p = (*it);
            p.set_pret(p.aplicaReducerea());
            cout << p;
            cout << "\n";
        }
    }
    void mod_dest(int x)
    {
        int y;
        cout << "Alegeti ce doriti sa modificati: 1-Locurile, 2-Disponibilitatea, 3-Distanta, 4-Pretul, 5-Locatiile, 6-Datele\n";
        cin >> y;
        if(y==1)
        {
            int nrLocuri;
            int* scauneLibere;
            cout << "Cate locuri va avea? \n";
            cin >> nrLocuri;
            scauneLibere = new int[nrLocuri];
            cout << "Care sunt acestea? \n";
            for(int i=0; i<nrLocuri; i++)
                cin >> scauneLibere[i];
            d[x].set_locuriLibere(nrLocuri, scauneLibere);
            delete[] scauneLibere;
        }
        else if(y==2)
        {
            bool disponibil;
            cout << "Este zborul disponibil? (1-Da, 0-Nu)\n";
            cin >> disponibil;
            d[x].set_disponibil(disponibil);
        }
        else if(y==3)
        {
            float distanta;
            cout << "Introduceti distanta: \n";
            cin >> distanta;
            d[x].set_distanta(distanta);
        }
        else if(y==4)
        {
            int nrClase;
            char moneda;
            float* preturi;
            cout << "Cate clase va avea zborul? \n";
            cin >> nrClase;
            cout << "Introduceti initiala monedei de cumparare:\n";
            cin >> moneda;
            cout << "Care sunt preturile la fiecare clasa?\n";
            preturi = new float[nrClase];
            for(int i=0; i<nrClase; i++)
                cin >> preturi[i];
            d[x].set_preturi(preturi, moneda, nrClase);
            delete[] preturi;
        }
        else if(y==5)
        {
            char* plecareDin = new char[101];
            string destinatie;
            cout << "De unde se pleaca?\n";
            cin >> plecareDin;
            cout << "Care este destinatia?\n";
            cin >> destinatie;
            d[x].set_locatii(plecareDin, destinatie);
            delete[] plecareDin;
        }
        else if(y==6)
        {
            int nrDate;
            string* date;
            cout << "In cate zile este disponibil zborul?\n";
            cin >> nrDate;
            date = new string[nrDate];
            cout << "Introduceti datele:\n";
            for(int i=0; i<nrDate; i++)
                cin >> date[i];
            d[x].set_date(nrDate, date);
            delete[] date;
        }
        else cout <<"Nu ati selectat nimic\n";
    }
    void mod_hotel(int x)
    {
        int y;
        cout << "Alegeti ce doriti sa modificati: 1-Numele, 2-Disponibilitatea, 3-Numarul de stele, 4-Pretul, 5-Orasul, 6-Datele, 7-nota, 8-Numarul de camere libere\n";
        cin >> y;
        if(y==1)
        {
            string nume;
            cout << "Cum se numeste hotelul?\n";
            cin >> nume;
            h[x].set_nume(nume);
        }
        else if(y==2)
        {
            bool dis;
            cout << "Este disponibil hotelul? (1-Da, 0-Nu)\n";
            cin >> dis;
            h[x].set_disponibil(dis);
        }
        else if(y==3)
        {
            int nr;
            cout << "Numarul de stele:\n";
            cin >> nr;
            h[x].set_nrStele(nr);
        }
        else if(y==4)
        {
            float pret;
            cout << "Cat costa?\n";
            cin >> pret;
            h[x].set_pret(pret);
        }
        else if(y==5)
        {
            string oras;
            cout << "In ce oras se afla hotelul\n";
            cin >> oras;
            h[x].set_oras(oras);
        }
        else if(y==6)
        {
            int nr;
            string* checkIn;
            cout << "In cate zile se poate face check-in?\n";
            cin >> nr;
            checkIn = new string[nr];
            cout << "Introduceti zilele:\n";
            for(int i=0; i<nr; i++)
                cin >> checkIn[i];
            h[x].set_date(nr,checkIn);
        }
        else if(y==7)
        {
            float nota;
            cout << "Ce nota are hotelul?\n";
            cin >> nota;
            h[x].set_review(nota);
        }
        else if(y==8)
        {
            int nr;
            cout << "Cate camere are disponibile hotelul?\n";
            cin >> nr;
            h[x].set_nrCamereLibere(nr);
        }
        else cout << "Nu ati selectat nimic\n";
    }
};
istream& operator>>(istream& in, Administrator& ad)
{
    char aux[101];
    cout << "\nIntroduceti userul: ";
    in >> aux;
    if(ad.user != NULL)
        delete[] ad.user;
    ad.user = new char[strlen(aux)+1];
        strcpy(ad.user, aux);
    cout << "\nIntroduceti parola: ";
    in >> ad.parola;
}
ifstream& operator>>(ifstream& in, Administrator& ad)
{
    char aux[101];
    in >> aux;
    if(ad.user != NULL)
        delete[] ad.user;
    ad.user = new char[strlen(aux)+1];
        strcpy(ad.user, aux);
    in >> ad.parola;
}
ostream& operator<<(ostream& out, const Administrator& ad)
{
    out << "\nUser: " << ad.user;
}

class SysOp:public Administrator
{
public:
    SysOp():Administrator()
    {

    }
    SysOp(char* nume, string parola):Administrator(nume,parola)
    {

    }
    SysOp(const SysOp &so):Administrator(so)
    {

    }
    ~SysOp()
    {

    }
    SysOp& operator=(const SysOp& so)
    {
        if(this != &so)
        {
            Administrator:operator=(so);
        }
        *this;
    }
    friend istream& operator>>(istream& in, SysOp& so)
    {
        in >> (Administrator&)so;
        return in;
    }
    friend ifstream& operator>>(ifstream& in, SysOp& so)
    {
        in >> (Administrator&)so;
        return in;
    }
    friend ostream& operator<<(ostream& out, const SysOp& so)
    {
        out << (Administrator&)so;
        return out;
    }
    void add_dest()
    {
        Destinatii aux;
        cin >> aux;
        d.push_back(aux);
    }
    void add_hotel()
    {
        Hotel aux;
        cin >> aux;
        h.push_back(aux);
    }
    void del_dest(int x)
    {
        d.erase(d.begin()+x);
    }
    void del_hotel(int x)
    {
        h.erase(h.begin()+x);
    }
};

map <string, float> rute;
set <pair <string, string>> cereri;

class Client
{
private:
    char* nume;
    string prenume;
    float buget;

public:
    Client()
    {
        this->nume = new char[strlen("Anonim")+1];
        strcpy(this->nume, "Anonim");
        this->prenume = "\0";
        this->buget = 0;
    }
    Client(char* nume, string prenume, float buget)
    {
        this->nume = new char[strlen(nume)+1];
        strcpy(this->nume, nume);
        this->prenume = prenume;
        this->buget = buget;
    }
    Client(char* nume)
    {
        this->nume = new char[strlen(nume)+1];
        strcpy(this->nume, nume);
        this->prenume = "\0";
        this->buget = 0;
    }
    Client(const Client &cl)
    {
        this->nume = new char[strlen(cl.nume)+1];
        strcpy(this->nume, cl.nume);
        this->prenume = cl.prenume;
        this->buget = cl.buget;
    }
    ~Client()
    {
        if(this->nume != NULL)
            delete[] this->nume;
    }



    Client& operator=(const Client& cl)
    {
        if(this != &cl)
        {
            if(this->nume != NULL)
                delete[] this->nume;
            this->nume = new char[strlen(cl.nume)+1];
            strcpy(this->nume, cl.nume);
            this->prenume = cl.prenume;
            this->buget = cl.buget;
        }
        *this;
    }
    friend istream& operator>>(istream& in, Client& cl);
    friend ostream& operator<<(ostream& out, const Client& cl);
    friend ifstream& operator>>(ifstream& in, Client& cl);



    void set_nume(char* nume)
    {
        if(this->nume != NULL)
            delete[] this->nume;
        this->nume = new char[strlen(nume)+1];
        strcpy(this->nume, nume);
    }
    void set_prenume(string prenume)
    {
        this->prenume = prenume;
    }
    void set_buget(float buget)
    {
        this->buget = buget;
    }



    char* get_nume()
    {
        return this->nume;
    }
    string get_prenume()
    {
        return this->prenume;
    }
    float get_buget()
    {
        return this->buget;
    }



    void list_dest()
    {
        for(int i=0; i<d.size(); i++)
            {cout << d[i];
            cout << "\n";}
    }
    void list_hotel()
    {
        for(int i=0; i<h.size(); i++)
            {cout << h[i];
            cout << "\n";}
    }
    void list_pachete()
    {
        for(auto it=p1.begin(); it!=p1.end(); it++)
        {
            (*it).calculeazaReducerea();
            PacheteLimitedEdition p = (*it);
            p.set_pret(p.aplicaReducerea());
            cout << p;
            cout << "\n";
        }
        for(auto it=p2.begin(); it!=p2.end(); it++)
        {
            (*it).calculeazaReducerea();
            PacheteAllTime p = (*it);
            p.set_pret(p.aplicaReducerea());
            cout << p;
            cout << "\n";
        }
    }
};
istream& operator>>(istream& in, Client& cl)
{
    char aux[101];
    cout << "\nIntroduceti numele: ";
    in >> aux;
    if(cl.nume != NULL)
        delete[] cl.nume;
    cl.nume = new char[strlen(aux)+1];
        strcpy(cl.nume, aux);
    cout << "\nIntroduceti prenumele: ";
    in >> cl.prenume;
    cout << "\nIntroduceti bugetul: ";
    in >> cl.buget;

}
ifstream& operator>>(ifstream& in, Client& cl)
{
    char aux[101];
    in >> aux;
    if(cl.nume != NULL)
        delete[] cl.nume;
    cl.nume = new char[strlen(aux)+1];
        strcpy(cl.nume, aux);
    in >> cl.prenume;
    in >> cl.buget;

}
ostream& operator<<(ostream& out, const Client& cl)
{
    out << "\nNume: " << cl.nume;
    out << "\nPrenume: " << cl.prenume;
    out << "\nBuget: " << cl.buget;
}

class ClientVIP:public Client
{
private:
    string parola;
    float credit;

public:
    ClientVIP():Client()
    {
        this->parola = "\0";
        this->credit = 10000;
    }
    ClientVIP(char* nume, string prenume, float buget, string parola, float credit):Client(nume,prenume,buget)
    {
        this->parola = parola;
        this->credit = credit;
    }
    ClientVIP(const ClientVIP &cl):Client(cl)
    {
        this->parola = cl.parola;
        this->credit = cl.credit;
    }
    ~ClientVIP()
    {

    }
    ClientVIP& operator=(const ClientVIP& cl)
    {
        if(this != &cl)
        {
            Client:operator=(cl);
            this->parola = cl.parola;
            this->credit = cl.credit;
        }
        *this;
    }
    friend istream& operator>>(istream& in, ClientVIP& cl)
    {
        in >> (Client&)cl;
        cout << "\nIntroduceti parola: ";
        in >> cl.parola;
        return in;
    }
    friend ifstream& operator>>(ifstream& in, ClientVIP& cl)
    {
        in >> (Client&)cl;
        in >> cl.parola;
        return in;
    }
    friend ostream& operator<<(ostream& out, const ClientVIP& cl)
    {
        out << (Client&)cl;
        out << "\nCreditul dvs. este: " << cl.credit;
        return out;
    }
    string get_parola()
    {
        return this->parola;
    }
    float get_credit()
    {
        return this->credit;
    }
    void set_parola(string parola)
    {
        this->parola = parola;
    }
    void set_credit(float credit)
    {
        this->credit = credit;
    }

    void private_jet()
    {
        string plecare, sosire, data, ora;
        cout << "\nDe unde doriti sa plecati?";
        cin >> plecare;
        cout << "\nUnde doriti sa ajungeti?";
        cin >> sosire;
        cout << "\nIn ce data doriti sa programati zborul?";
        cin >> data;
        cout << "\nLa ce ora?";
        cin >> ora;

        auto pos = rute.find(plecare+"-"+sosire);
        if(pos != rute.end())
        {
            cereri.insert(make_pair(plecare+"-"+sosire, data+"-"+ora));
            cout << "\nCererea a fost inregistrata. Pretul mediu pe ruta selectata: ";
            cout << pos->second;
            cout << "\n";
        }
        else
            cout << "\nRuta dorita nu exista\n";
    }
    void list_cereri()
    {
        for(auto it=cereri.begin(); it!=cereri.end(); it++)
            cout << "\n" << it->first << " " << it->second;
        cout << "\n";
    }
};

void meniu(int nr_admini, Administrator a[10], int nr_sysop, SysOp s[10], int nr_VIP, ClientVIP c[10])
{
    int login;
    char command[20];
    cout << "Alegeti cum doriti sa va logati:\n(Introduceti cifra corespunzatoare optiunii)\n1-Administrator 2-SystemOperator 3-Client 4-ClientVIP\n";
    cin >> login;
    while(login!=1 && login!=2 && login!=3 && login!=4)
    {
        cout << "Comanda invalida, va rugam introduceti una valida\n";
        cin >> login;
    }
    if(login == 1)
    {
        cout << "Va rugam sa introduceti userul si parola:\n";
        int ok = 0;
        Administrator a1;
        cin >> a1;
        for(int i=0; i<nr_admini; i++)
            if(a1 == a[i])
                {ok = 1; break;}
        if(ok == 0)
            cout << "Nu sunteti admin";
        else
        {
            cout << "Sunteti administrator\n";
            cout << "==========Lista comenzilor disponibile:==========\n";
            cout << "List_Dest - listeaza toate destinatiile\n";
            cout << "List_Hotel - listeaza toate hotelurile disponibile\n";
            cout << "List_Pachete - listeaza toate pachetele\n";
            cout << "Mod_Dest - modifica date despre destinatii\n";
            cout << "Mod_Hotel - modifica date despre hoteluri\n";
            cout << "Stop - opreste programul\n";
            cout << "==================================================\n";
            cin >> command;
            while(stricmp(command,"stop")!=0)
            {
                if(stricmp(command,"list_dest")==0)
                    a1.list_dest();
                else if(stricmp(command,"list_hotel")==0)
                    a1.list_hotel();
                else if(stricmp(command,"mod_dest")==0)
                {
                    int x;
                    cout << "Ce destinatie doriti sa modificati? (Introduceti cifra corespunzatoare):\n";
                    cin >> x;
                    a1.mod_dest(x);
                }
                else if(stricmp(command,"mod_hotel")==0)
                {
                    int x;
                    cout << "Ce hotel doriti sa modificati? (Introduceti cifra corespunzatoare):\n";
                    cin >> x;
                    a1.mod_hotel(x);
                }
                else if(stricmp(command,"list_pachete")==0)
                    a1.list_pachete();
                else
                    cout << "Comanda invalida\n";

                cout << "==========Lista comenzilor disponibile:==========\n";
                cout << "List_Dest - listeaza toate destinatiile\n";
                cout << "List_Hotel - listeaza toate hotelurile disponibile\n";
                cout << "List_Pachete - listeaza toate pachetele\n";
                cout << "Mod_Dest - modifica date despre destinatii\n";
                cout << "Mod_Hotel - modifica date despre hoteluri\n";
                cout << "Stop - opreste programul\n";
                cout << "==================================================\n";
                cin >> command;
            }
        }
    }
    else if(login == 2)
    {
        cout << "Va rugam sa introduceti userul si parola:\n";
        int ok = 0;
        SysOp s1;
        cin >> s1;
        for(int i=0; i<nr_sysop; i++)
            if(strcmp(s1.get_user(),s[i].get_user())==0 && s1.get_parola() == s[i].get_parola())
                {ok = 1; break;}
        if(ok == 0)
            cout << "Nu sunteti SysOp";
        else
        {
            cout << "Sunteti System Operator\n";
            cout << "==========Lista comenzilor disponibile:==========\n";
            cout << "List_Dest - listeaza toate destinatiile\n";
            cout << "List_Hotel - listeaza toate hotelurile disponibile\n";
            cout << "List_pachete - listeaza toate pachetele\n";
            cout << "Mod_Dest - modifica date despre destinatii\n";
            cout << "Mod_Hotel - modifica date despre hoteluri\n";
            cout << "Del_Dest - sterge destinatii\n";
            cout << "Del_Hotel - sterge hoteluri\n";
            cout << "Add_Dest - adauga destinatii\n";
            cout << "Add_Hotel - adauga hoteluri\n";
            cout << "Stop - opreste programul\n";
            cout << "==================================================\n";
            cin >> command;
            while(stricmp(command,"stop")!=0)
            {
                if(stricmp(command,"list_dest")==0)
                    s1.list_dest();
                else if(stricmp(command,"list_hotel")==0)
                    s1.list_hotel();
                else if(stricmp(command,"mod_dest")==0)
                {
                    int x;
                    cout << "Ce destinatie doriti sa modificati? (Introduceti cifra corespunzatoare):\n";
                    cin >> x;
                    s1.mod_dest(x);
                }
                else if(stricmp(command,"mod_hotel")==0)
                {
                    int x;
                    cout << "Ce hotel doriti sa modificati? (Introduceti cifra corespunzatoare):\n";
                    cin >> x;
                    s1.mod_hotel(x);
                }
                else if(stricmp(command,"del_dest")==0)
                    {
                        int x;
                        cout << "Ce zbor doriti sa stergeti? (Introduceti cifra corespunzatoare):\n";
                        cin >> x;
                        s1.del_dest(x);
                    }
                else if(stricmp(command,"del_hotel")==0)
                    {
                        int x;
                        cout << "Ce hotel doriti sa stergeti? (Introduceti cifra corespunzatoare):\n";
                        cin >> x;
                        s1.del_hotel(x);
                    }
                else if(stricmp(command,"add_dest")==0)
                    s1.add_dest();
                else if(stricmp(command,"add_hotel")==0)
                    s1.add_hotel();
                else if(stricmp(command,"list_pachete")==0)
                    s1.list_pachete();
                else
                    cout << "Comanda invalida\n";

                cout << "==========Lista comenzilor disponibile:==========\n";
                cout << "List_Dest - listeaza toate destinatiile\n";
                cout << "List_Hotel - listeaza toate hotelurile disponibile\n";
                cout << "List_Pachete - listeaza toate pachetele\n";
                cout << "Mod_Dest - modifica date despre destinatii\n";
                cout << "Mod_Hotel - modifica date despre hoteluri\n";
                cout << "Del_Dest - sterge destinatii\n";
                cout << "Del_Hotel - sterge hoteluri\n";
                cout << "Add_Dest - adauga destinatii\n";
                cout << "Add_Hotel - adauga hoteluri\n";
                cout << "Stop - opreste programul\n";
                cout << "==================================================\n";
                cin >> command;
            }
        }
    }
    else if(login == 3)
    {
        Client c1;
        cout << "Va rugam sa introduceti numele, prenumele si bugetul:\n";
        cin >> c1;
        cout << "Sunteti client\n";
        cout << "==========Lista comenzilor disponibile:==========\n";
        cout << "Buget - afiseaza bugetul\n";
        cout << "Add_buget - adauga bani in cont\n";
        cout << "Del_buget - sterge bani din cont\n";
        cout << "List_Dest - listeaza toate destinatiile\n";
        cout << "List_Hotel - listeaza toate hotelurile disponibile\n";
        cout << "List_Pachete - listeaza toate pachetele\n";
        cout << "Cumpar_Bilet - cumpara bilet la una din destinatii\n";
        cout << "Rezerv_Hotel - rezerva camera la unul dintre hoteluri\n";
        cout << "Stop - Opreste programul\n";
        cout << "==================================================\n";
        cin >> command;
        while(stricmp(command,"stop")!=0)
        {
            if(stricmp(command,"Add_buget")==0)
            {
                cout << "Aveti " << c1.get_buget() << " euro\n";
                cout << "Cat doriti sa mai adaugati?\n";
                float x;
                cin >> x;
                if(x>0)
                    c1.set_buget(x+c1.get_buget());
                else
                    cout << "Suma invalida\n";
            }
            else if(stricmp(command,"Del_buget")==0)
            {
                cout << "Aveti " << c1.get_buget() << " euro\n";
                cout << "Cat doriti sa stergeti?\n";
                float x;
                cin >> x;
                if(x>0 && c1.get_buget()-x >= 0)
                    c1.set_buget(c1.get_buget()-x);
                else
                    cout << "Suma invalida\n";
            }
            else if(stricmp(command,"Buget")==0)
                cout << "Aveti " << c1.get_buget() << " euro\n";
            else if(stricmp(command,"list_dest")==0)
                c1.list_dest();
            else if(stricmp(command,"list_hotel")==0)
                c1.list_hotel();
            else if(stricmp(command,"cumpar_bilet")==0)
            {
                int x,y;
                cout << "La ce zbor doriti bilet?\nLista zborurilor disponibile\n";
                c1.list_dest();
                cout << "(Tastati numarul corespunzator zborului)\n";
                cin >> x;
                cout << "Selectati un pret din cele disponibile zborului vostru (Introduceti cifra de ordine a sa)\n";
                cin >> y;
                if(c1.get_buget() >= d[x].get_preturi()[y])
                {
                    c1.set_buget(c1.get_buget() - d[x].get_preturi()[y]);
                    cout << "Ati cumparat bilet catre destinatia cu numarul " << x << "! Zbor placut!\n";
                    cout << "Buget ramas: " << c1.get_buget() << "\n";
                    cout << "Detaliile despre zbor vor aparea pe bon\n";
                    out << "Detalii despre bilet:\n";
                    out << d[x];
                    out << "\n\n";
                }
                else
                    cout << "Nu aveti buget\n";
            }
            else if(stricmp(command,"rezerv_hotel")==0)
            {
                int x;
                cout << "La ce hotel doriti camera?\nLista hotelurilor disponibile\n";
                c1.list_hotel();
                cout << "(Tastati numarul corespunzator hotelului)\n";
                cin >> x;
                if(c1.get_buget() >= h[x].get_pret())
                {
                    c1.set_buget(c1.get_buget() - h[x].get_pret());
                    cout << "Ati rezervat camera la hotelul cu numarul " << x << "! Sedere placuta!\n";
                    cout << "Buget ramas: " << c1.get_buget() << "\n";
                    cout << "Detaliile despre hotel vor aparea pe bon\n";
                    out << "Detalii despre rezervare:\n";
                    out << h[x];
                    out << "\n\n";
                }
                else
                    cout << "Nu aveti buget\n";
            }
            else if(stricmp(command,"list_pachete")==0)
                c1.list_pachete();
            else
                cout << "Comanda invalida\n";

            cout << "==========Lista comenzilor disponibile:==========\n";
            cout << "Buget - afiseaza bugetul\n";
            cout << "Add_buget - adauga bani in cont\n";
            cout << "Del_buget - sterge bani din cont\n";
            cout << "List_Dest - listeaza toate destinatiile\n";
            cout << "List_Hotel - listeaza toate hotelurile disponibile\n";
            cout << "List_Pachete - listeaza toate pachetele\n";
            cout << "Cumpar_Bilet - cumpara bilet la una din destinatii\n";
            cout << "Rezerv_Hotel - rezerva camera la unul dintre hoteluri\n";
            cout << "Stop - opreste programul\n";
            cout << "==================================================\n";
            cin >> command;
        }
    }
    else if(login == 4)
    {
        cout << "Va rugam sa introduceti numele, prenumele, bugetul si parola:\n";
        int ok = 0;
        ClientVIP c1;
        cin >> c1;
        for(int i=0; i<nr_VIP; i++)
            if(strcmp(c1.get_nume(), c[i].get_nume()) == 0 && c1.get_prenume() == c[i].get_prenume() && c1.get_parola() == c[i].get_parola())
                {ok = 1; break;}
        if(ok == 0)
            cout << "Nu sunteti client VIP";
        else
        {
            cout << "Sunteti client VIP\n";
            cout << "==========Lista comenzilor disponibile:==========\n";
            cout << "Buget - afiseaza bugetul\n";
            cout << "Add_buget - adauga bani in cont\n";
            cout << "Del_buget - sterge bani din cont\n";
            cout << "Credit - afiseaza creditul\n";
            cout << "List_Dest - listeaza toate destinatiile\n";
            cout << "List_Hotel - listeaza toate hotelurile disponibile\n";
            cout << "List_Pachete - listeaza toate pachetele\n";
            cout << "Cumpar_Bilet - cumpara bilet la una din destinatii\n";
            cout << "Rezerv_Hotel - rezerva camera la unul dintre hoteluri\n";
            cout << "Bilet_VIP - cumpara bilet cu CREDIT la una din destinatii\n";
            cout << "Rezervare_VIP - rezerva o camera de hotel cu CREDIT\n";
            cout << "Private_jet - cere un zbor privat\n";
            cout << "List_cereri - listeaza toate cererile pentru zboruri private\n";
            cout << "Stop - Opreste programul\n";
            cout << "==================================================\n";
            cin >> command;
            while(stricmp(command,"stop")!=0)
            {
                if(stricmp(command,"Add_buget")==0)
                {
                    cout << "Aveti " << c1.get_buget() << " euro\n";
                    cout << "Cat doriti sa mai adaugati?\n";
                    float x;
                    cin >> x;
                    if(x>0)
                        c1.set_buget(x+c1.get_buget());
                    else
                        cout << "Suma invalida\n";
                }
                else if(stricmp(command,"Del_buget")==0)
                {
                    cout << "Aveti " << c1.get_buget() << " euro\n";
                    cout << "Cat doriti sa stergeti?\n";
                    float x;
                    cin >> x;
                    if(x>0 && c1.get_buget()-x >= 0)
                        c1.set_buget(c1.get_buget()-x);
                    else
                        cout << "Suma invalida\n";
                }
                else if(stricmp(command,"Buget")==0)
                    cout << "Aveti " << c1.get_buget() << " euro\n";
                else if(stricmp(command,"Credit")==0)
                    cout << "Aveti " << c1.get_credit() << " euro CREDIT\n";
                else if(stricmp(command,"list_dest")==0)
                    c1.list_dest();
                else if(stricmp(command,"list_hotel")==0)
                    c1.list_hotel();
                else if(stricmp(command,"list_pachete")==0)
                    c1.list_pachete();
                else if(stricmp(command,"cumpar_bilet")==0)
                {
                    int x,y;
                    cout << "La ce zbor doriti bilet?\nLista zborurilor disponibile\n";
                    c1.list_dest();
                    cout << "(Tastati numarul corespunzator zborului)\n";
                    cin >> x;
                    cout << "Selectati un pret din cele disponibile zborului vostru (Introduceti cifra de ordine a sa)\n";
                    cin >> y;
                    if(c1.get_buget() >= d[x].get_preturi()[y])
                    {
                        c1.set_buget(c1.get_buget() - d[x].get_preturi()[y]);
                        cout << "Ati cumparat bilet catre destinatia cu numarul " << x << "! Zbor placut!\n";
                        cout << "Buget ramas: " << c1.get_buget() << "\n";
                        cout << "Detaliile despre zbor vor aparea pe bon\n";
                        out << "Detalii despre bilet:\n";
                        out << d[x];
                        out << "\n\n";
                    }
                    else
                        cout << "Nu aveti buget\n";
                }
                else if(stricmp(command,"rezerv_hotel")==0)
                {
                    int x;
                    cout << "La ce hotel doriti camera?\nLista hotelurilor disponibile\n";
                    c1.list_hotel();
                    cout << "(Tastati numarul corespunzator hotelului)\n";
                    cin >> x;
                    if(c1.get_buget() >= h[x].get_pret())
                    {
                        c1.set_buget(c1.get_buget() - h[x].get_pret());
                        cout << "Ati rezervat camera la hotelul cu numarul " << x << "! Sedere placuta!\n";
                        cout << "Buget ramas: " << c1.get_buget() << "\n";
                        cout << "Detaliile despre hotel vor aparea pe bon\n";
                        out << "Detalii despre rezervare:\n";
                        out << h[x];
                        out << "\n\n";
                    }
                    else
                        cout << "Nu aveti buget\n";
                }
                else if(stricmp(command,"bilet_vip")==0)
                {
                    int x,y;
                    cout << "La ce zbor doriti bilet?\nLista zborurilor disponibile\n";
                    c1.list_dest();
                    cout << "(Tastati numarul corespunzator zborului)\n";
                    cin >> x;
                    cout << "Selectati un pret din cele disponibile zborului vostru (Introduceti cifra de ordine a sa)\n";
                    cin >> y;
                    if(c1.get_credit() >= d[x].get_preturi()[y])
                    {
                        c1.set_credit(c1.get_credit() - d[x].get_preturi()[y]);
                        cout << "Ati cumparat bilet cu CREDIT catre destinatia cu numarul " << x << "! Zbor placut!\n";
                        cout << "Credit ramas: " << c1.get_credit() << "\n";
                        cout << "Detaliile despre zbor vor aparea pe bon\n";
                        out << "Detalii despre bilet:\n";
                        out << d[x];
                        out << "\n\n";
                    }
                    else
                        cout << "Nu aveti credit\n";
                }
                else if(stricmp(command,"rezervare_vip")==0)
                {
                    int x;
                    cout << "La ce hotel doriti camera?\nLista hotelurilor disponibile\n";
                    c1.list_hotel();
                    cout << "(Tastati numarul corespunzator hotelului)\n";
                    cin >> x;
                    if(c1.get_credit() >= h[x].get_pret())
                    {
                        c1.set_credit(c1.get_credit() - h[x].get_pret());
                        cout << "Ati rezervat camera cu CREDIT la hotelul cu numarul " << x << "! Sedere placuta!\n";
                        cout << "Credit ramas: " << c1.get_credit() << "\n";
                        cout << "Detaliile despre hotel vor aparea pe bon\n";
                        out << "Detalii despre rezervare:\n";
                        out << h[x];
                        out << "\n\n";
                    }
                    else
                        cout << "Nu aveti credit\n";
                }
                else if(stricmp(command,"private_jet")==0)
                    c1.private_jet();
                else if(stricmp(command,"list_cereri")==0)
                    c1.list_cereri();
                else
                    cout << "Comanda invalida\n";

                cout << "==========Lista comenzilor disponibile:==========\n";
                cout << "Buget - afiseaza bugetul\n";
                cout << "Add_buget - adauga bani in cont\n";
                cout << "Del_buget - sterge bani din cont\n";
                cout << "Credit - afiseaza creditul\n";
                cout << "List_Dest - listeaza toate destinatiile\n";
                cout << "List_Hotel - listeaza toate hotelurile disponibile\n";
                cout << "List_Pachete - listeaza toate pachetele\n";
                cout << "Cumpar_Bilet - cumpara bilet la una din destinatii\n";
                cout << "Rezerv_Hotel - rezerva camera la unul dintre hoteluri\n";
                cout << "Bilet_VIP - cumpara bilet la una din destinatii fara sa platesti in aplicatie\n";
                cout << "Rezervare_VIP - rezerva o camera de hotel fara sa platesti in aplicatie\n";
                cout << "Private_jet - cere un zbor privat\n";
                cout << "List_cereri - listeaza toate cererile pentru zboruri private\n";
                cout << "Stop - opreste programul\n";
                cout << "==================================================\n";
                cin >> command;
            }
        }
    }
}

int main()
{
    int nr_admini = 2;
    int nr_sysop = 2;
    int nr_VIP = 2;

    Administrator a[10];
    SysOp s[10];
    ClientVIP c[10];

    for(int i=0; i<nr_admini; i++)
        in >> a[i];
    for(int i=0; i<nr_sysop; i++)
        in >> s[i];
    for(int i=0; i<nr_VIP; i++)
        in >> c[i];
    for(int i=0; i<3; i++)
    {
        Destinatii aux;
        in >> aux;
        d.push_back(aux);
    }
    for(int i=0; i<3; i++)
    {
        Hotel aux;
        in >> aux;
        h.push_back(aux);
    }
    for(int i=0; i<2; i++)
    {
        PacheteLimitedEdition aux;
        in >> aux;
        p1.push_back(aux);
    }
    for(int i=0; i<2; i++)
    {
        PacheteAllTime aux;
        in >> aux;
        p2.push_back(aux);
    }
    for(int i=0; i<15; i++)
    {
        string ruta;
        float pret;
        in >> ruta >> pret;
        rute.insert(pair<string, float>(ruta,pret));
    }
    meniu(nr_admini,a,nr_sysop,s,nr_VIP,c);
    return 0;
}


