#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ============================================================
// Leistungsnachweis
// ============================================================
class Leistungsnachweis {
private:
    float note;
    string datum;
    float gewichtung;
public:
    Leistungsnachweis(float note, string datum, float gewichtung)
        : note(note), datum(datum), gewichtung(gewichtung) {}

    float getNote() const { return note; }
    void setNote(float n) { note = n; }
    string getDatum() const { return datum; }
    float getGewichtung() const { return gewichtung; }

    float getNotendurchschnitt() const { return note * gewichtung; }
};

// ============================================================
// Fach
// ============================================================
class Fach {
private:
    string bezeichnung;
    int fachId;
    vector<Leistungsnachweis> leistungsnachweise;
public:
    Fach(int fachId, string bezeichnung)
        : fachId(fachId), bezeichnung(bezeichnung) {}

    string getBezeichnung() const { return bezeichnung; }
    int getFachId() const { return fachId; }

    void addLeistungsnachweis(const Leistungsnachweis& ln) {
        leistungsnachweise.push_back(ln);
    }

    float getDurchschnitt() const {
        if (leistungsnachweise.empty()) return 0.0f;
        float summeGewichtet = 0.0f;
        float summeGewichtung = 0.0f;
        for (const auto& ln : leistungsnachweise) {
            summeGewichtet += ln.getNote() * ln.getGewichtung();
            summeGewichtung += ln.getGewichtung();
        }
        return (summeGewichtung > 0) ? summeGewichtet / summeGewichtung : 0.0f;
    }

    const vector<Leistungsnachweis>& getLeistungsnachweise() const {
        return leistungsnachweise;
    }
};

// ============================================================
// Person (abstrakt)
// ============================================================
class Person {
protected:
    int id;
    string name;
    string email;
public:
    Person(int id, string name, string email)
        : id(id), name(name), email(email) {}
    virtual ~Person() {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    void setEmail(string e) { email = e; }

    virtual string getInfo() const {
        return "Person[" + to_string(id) + "]: " + name + " (" + email + ")";
    }
};

// ============================================================
// Lehrperson
// ============================================================
class Lehrperson : public Person {
private:
    string fachbereich;
public:
    Lehrperson(int id, string name, string email, string fachbereich)
        : Person(id, name, email), fachbereich(fachbereich) {}

    string getFachbereich() const { return fachbereich; }
    void setFachbereich(string f) { fachbereich = f; }

    void noteEintragen(Fach& fach, float note, string datum, float gewichtung) {
        Leistungsnachweis ln(note, datum, gewichtung);
        fach.addLeistungsnachweis(ln);
        cout << "Note " << note << " eingetragen von " << name
             << " in Fach " << fach.getBezeichnung() << endl;
    }

    string getInfo() const override {
        return "Lehrperson[" + to_string(id) + "]: " + name
               + " | Fachbereich: " + fachbereich;
    }
};

// ============================================================
// Schüler
// ============================================================
class Schueler : public Person {
private:
    string klasse;
    vector<Fach> faecher;
public:
    Schueler(int id, string name, string email, string klasse)
        : Person(id, name, email), klasse(klasse) {}

    string getKlasse() const { return klasse; }
    void setKlasse(string k) { klasse = k; }

    void addFach(const Fach& f) { faecher.push_back(f); }
    vector<Fach>& getFaecher() { return faecher; }

    string getInfo() const override {
        return "Schueler[" + to_string(id) + "]: " + name
               + " | Klasse: " + klasse;
    }
};

// ============================================================
// main
// ============================================================
int main() {
    Lehrperson lp(1, "Herr Meier", "meier@schule.ch", "Mathematik");
    Schueler s(2, "Anna Mueller", "anna@schule.ch", "3A");

    Fach mathe(101, "Mathematik");
    Fach deutsch(102, "Deutsch");

    lp.noteEintragen(mathe, 5.5f, "2026-03-15", 1.0f);
    lp.noteEintragen(mathe, 4.0f, "2026-05-20", 2.0f);
    lp.noteEintragen(deutsch, 5.0f, "2026-04-10", 1.0f);

    s.addFach(mathe);
    s.addFach(deutsch);

    cout << lp.getInfo() << endl;
    cout << s.getInfo() << endl;

    for (auto& f : s.getFaecher()) {
        cout << "  Fach: " << f.getBezeichnung()
             << " -> Durchschnitt: " << f.getDurchschnitt() << endl;
    }

    return 0;
}