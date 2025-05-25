#ifndef JSONCROSSWORDLOADER_H
#define JSONCROSSWORDLOADER_H

#include "icrosswordloader.h"

class JsonCrosswordLoader : public ICrosswordLoader {
public:
    ICrossword* load(const QString& filePath) override;
};

#endif // JSONCROSSWORDLOADER_H
