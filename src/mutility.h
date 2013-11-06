#ifndef MUTILITY_H
#define MUTILITY_H

#include <QString>

class MUtility
{
public:
    static QString getImagesDir();
    static QString getStyleSheetDir();
    static QString getLanguageDir();
    static QString getMainDir();
    static QString getConfigDir();
    static QString getHelpDir();
    static QString getTempDir();
    static QString fetchStyleSheet(const QString &file_path);

    static bool checkIPString(const QString &ip);
    static QString trimmedAll(const QString &str);

private:
    MUtility();
    ~MUtility();
};

#endif // MUTILITY_H
