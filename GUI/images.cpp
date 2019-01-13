#include "images.h"

Images::Images()
{
    m_names.push_back(":/new/prefix1/pic1");
    m_currentImageName = m_names[0];
}

Images::~Images() {}

QString Images::getCurrentImageName() {
    return m_currentImageName;
}

void Images::addMember(const QString &name) {
    m_names.push_back(name);
}

void Images::removeMember(const QString &name) {
    QString removeName = name;
    m_names.erase(std::remove(m_names.begin(), m_names.end(), removeName), m_names.end());
}

QString Images::names(unsigned int i) const
 {

    return m_names[i];
}

unsigned int Images::size() {
    return m_names.size();
}

void Images::importImages(int type, QLabel* label) {

    unsigned int n = size();
    QString first = m_names[0];
    QString last = m_names[n-1];

    // proverava se da li je ime trenutno prikazane slike
    // jednako imenu slike iz vektora i kad se poklope
    // slika se postavlja na narednu tj. prethodnu
    // i azurira se ime trenutno prikazane slike

    // ako je type 1, onda se ucitava naredna
    if(type == 1) {

        // ako je trenutna poslednja, naredna je prva
        if(!(m_currentImageName.compare(last))) {
                label->setPixmap(QPixmap(first));
                m_currentImageName = first;
         }

        else {
            for(unsigned i = 0; i < n-1; i++) {
                if(!(m_currentImageName.compare(m_names[i]))) {
                        unsigned j = i;
                        label->setPixmap(QPixmap(m_names[j+1]));
                        m_currentImageName = m_names[j+1];
                        break;
                 }
            }
        }

    }

    // ako je type 0 ucitava se prethodna slika
    else if(type == 0) {

        // ako je trenutna prva, prethodna je poslednja
        if(!(m_currentImageName.compare(first))) {
            label->setPixmap(QPixmap(last));
            m_currentImageName = last;
        }

        else {
            for(unsigned i = 1; i < n; i++) {
                if(!(m_currentImageName.compare(m_names[i]))) {
                        label->setPixmap(QPixmap(m_names[i-1]));
                        m_currentImageName = m_names[i-1];
                    }
            }
        }
    }

    else return;
}













