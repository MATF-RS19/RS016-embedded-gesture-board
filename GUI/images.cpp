#include "images.h"


Images::Images(unsigned int num) : m_num(std::move(num))
{

}

Images::~Images() {}


void Images::addMember(const QString &name) {
    m_names.push_back(name);
}

void Images::removeMember(const QString &name) {
    QString removeName = name;
    m_names.erase(std::remove(m_names.begin(), m_names.end(), removeName), m_names.end());
}

QString Images::names(unsigned int i) const
 {
   //std::cout << m_names[i] << std::endl;
    return m_names[i];
}




