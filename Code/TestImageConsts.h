#ifndef TESTIMAGECONSTS_H
#define TESTIMAGECONSTS_H

#include <QString>

#define DEFINE_CONSISTER(name, value) const QString name = QStringLiteral(value);

#define DEFINE_CONSISTINT(name, value) const int name = value;

typedef unsigned int uint;

#endif // TESTIMAGECONSTS_H
