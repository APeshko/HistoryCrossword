#ifndef ICROSSWORDLOADER_H
#define ICROSSWORDLOADER_H

class ICrossword;

class ICrosswordLoader {
public:
    virtual ~ICrosswordLoader() = default;
    virtual ICrossword* load(const QString& source) = 0;
};

#endif // ICROSSWORDLOADER_H
