#include "mutility.h"

#include <QtCore>
#include <QRegExp>


QString MUtility::getImagesDir()
{
    QString dir = getMainDir();
    dir += "images/";
    return dir;
}

QString MUtility::getStyleSheetDir()
{
    QString dir = getMainDir();
    dir += "stylesheets/";
    return dir;
}

QString MUtility::getLanguageDir()
{
    QString dir = getMainDir();
    dir += "languages/";
    return dir;
}

QString MUtility::getMainDir()
{
    QString dir = QCoreApplication::applicationDirPath();
    dir += "/";
    return dir;
}

QString MUtility::getConfigDir()
{
    QString dir = getMainDir();
    dir += "config/";
    return dir;
}

QString MUtility::getHelpDir()
{
    QString dir = getMainDir();
    dir += "help/";
    return dir;
}

QString MUtility::getTempDir()
{
    QString dir = getMainDir();
    dir += "temp/";
    return dir;
}

QString MUtility::fetchStyleSheet(const QString &file_path)
{
    QString str;
    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly))
    {
        return str;
    }
    str.append(file.readAll());
    return str;
}

bool MUtility::checkIPString(const QString &ip)
{
    QRegExp reg("^([1]?\\d\\d?|2[0-4]\\d|25[0-5])\\.([1]?\\d\\d?|2[0-4]\\d|25[0-5])\\.([1]?\\d\\d?|2[0-4]\\d|25[0-5])\\.([1]?\\d\\d?|2[0-4]\\d|25[0-5])$");
    if (!reg.exactMatch(ip))
    {
        return false;
    }
    return true;
}

QString MUtility::trimmedAll(const QString &str)
{
    int index = str.indexOf(" ");
    if (index < 0)
    {
        return str;
    }
    return trimmedAll(str);
}

MUtility::MUtility()
{
}

MUtility::~MUtility()
{

}
