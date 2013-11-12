#ifndef XMLHELPER_H
#define XMLHELPER_H

#include <QDomDocument>
#include <QStringList>

class XmlHelper
{
public:
    static XmlHelper* GetInstance();

    bool LoadXmlFile(const QString& file_name);
    bool CreateXmlDocument(const QString& file_name, const QString& root_node);
    bool CreateXmlDocument(const QString& file_name,
                           const QString& ip, const QString& port);
//    bool AddXmlRootNode(const QString& root_node);
    bool AddXmlNode(QDomElement& parent, const QString& node_tag, const QString& text);
    bool AddXmlNode(const QString& parent_tag, const QString& node_tag, const QString& text = "");
    bool RemoveXmlNode(const QString& node_tag);
    bool ParseXmlDocument(const QString& file_name);

    QString ParseXmlNodeContent(const QString& node_tag);
    QStringList ParseXmlNodeList(const QString& node_tag);
    QString ParseXmlNodeContent(const QDomElement& elem);
    QString ParseXmlNodeContent(const QDomNode& special_node);

    QString ParseXmlNodeAttribute(const QString& node_tag, const QString& attr_key);
    QString ParseXmlNodeAttribute(const QDomElement& elem, const QString& attr_key);

    bool SetXmlNodeContent(const QDomElement& elem, const QString& text);
    bool SetXmlNodeContent(const QString& tag_name, const QString& text);

    bool SetXmlNodeAttribute(const QString& node_tag,
                             const QString& attr_key, const QString& attr_value);

    QDomElement GetXmlRootNode();
    QDomElement GetXmlNodeParent(const QString& node_tag);

    bool ClearXmlDocument();
    bool AddRootNode(const QString &root_node);

    void DestroyInstance();

private:
    XmlHelper() {}
    bool LoadXmlFile();

private:
    QDomDocument doc_;
    QString file_name_;

    static XmlHelper *helper_;
};

#endif // XMLHELPER_H
