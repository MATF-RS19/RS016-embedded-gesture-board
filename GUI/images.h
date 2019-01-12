#ifndef IMAGES_H
#define IMAGES_H

#include <list>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <QPixmap>
#include <QLabel>
class Images
{
public:
    Images();
    virtual ~Images();
    void addMember(const QString &name);
    void removeMember(const QString &name);
    QString names(unsigned int i) const;
    unsigned int size();


    void importImages(int type, QLabel* label);
    QString getCurrentImageName();

private:

    std::vector<QString> m_names;
    QString m_currentImageName;
};

#endif // IMAGES_H
