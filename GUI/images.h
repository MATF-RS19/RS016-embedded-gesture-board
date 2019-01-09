#ifndef IMAGES_H
#define IMAGES_H

#include <list>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <QPixmap>

class Images
{
public:
    Images(unsigned int num);
    virtual ~Images();
    void addMember(const QString &name);
    void removeMember(const QString &name);
    QString names(unsigned int i) const;
    unsigned int size();


private:
    unsigned int m_num;
    std::vector<QString> m_names;
};

#endif // IMAGES_H
