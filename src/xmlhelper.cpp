#include "xmlhelper.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

XmlHelper* XmlHelper::helper_ = NULL;

XmlHelper *XmlHelper::GetInstance()
{
    if (helper_ == NULL)
    {
        helper_ = new XmlHelper;
    }

    return helper_;
}

bool XmlHelper::LoadXmlFile(const QString &file_name)
{
    if (!QFile::exists(file_name))
    {
        return false;
    }

    QFile file(file_name);
    file_name_ = file_name;

    doc_.clear();
    if (!file.open(QIODevice::ReadWrite))
    {
        file.close();
        return false;
    }

    if (!doc_.setContent(&file))
    {
        file.close();
        return false;
    }
    file.close();

    return true;
}

bool XmlHelper::CreateXmlDocument(const QString &file_name, const QString& root_node)
{
    qDebug() << file_name;
    QFile file(file_name);
    file_name_ = file_name;
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return false;
    }

    QDomProcessingInstruction instruction =
            doc_.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc_.appendChild(instruction);
    QDomElement root = doc_.createElement(root_node);
    doc_.appendChild(root);
    QTextStream out(&file);
    doc_.save(out,4);
    file.close();

    return true;
}

bool XmlHelper::CreateXmlDocument(const QString &file_name, const QString &ip, const QString &port)
{
    QFile file(file_name);
    file_name_ = file_name;
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return false;
    }

    QDomProcessingInstruction instruction =
            doc_.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc_.appendChild(instruction);

    QDomElement root = doc_.createElement("appSettings");
    doc_.appendChild(root);
    QDomElement ip_node = doc_.createElement("ip");
    QDomElement port_node = doc_.createElement("port");

    QDomText text = doc_.createTextNode(ip);
    ip_node.appendChild(text);
    text = doc_.createTextNode(port);
    port_node.appendChild(text);

    root.appendChild(ip_node);
    root.appendChild(port_node);
    QTextStream out(&file);
    doc_.save(out, 4);

    return true;
}

//bool XmlHelper::AddXmlRootNode(const QString &root_node)
//{
//    if (!LoadXmlFile())
//    {
//        return false;
//    }

//    QDomElement root = doc_.createElement(root_node);
//    doc_.appendChild(root);

//    QFile file(file_name_);
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
//    {
//        return false;
//    }
//    QTextStream out(&file);
//    doc_.save(out, 4);
//    file.close();
//    return true;
//}

bool XmlHelper::AddXmlNode(QDomElement& parent, const QString &node_tag, const QString &text)
{
    if (!LoadXmlFile())
    {
        return false;
    }

    QDomNodeList node_list = doc_.elementsByTagName(parent.tagName());
    if (node_list.count() > 0)
    {
        QDomElement elem = doc_.createElement(node_tag);
        QDomText elem_text = doc_.createTextNode(text);
        elem.appendChild(elem_text);
        parent.appendChild(elem);

        QFile file(file_name_);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            return false;
        }
        QTextStream out(&file);
        doc_.save(out, 4);
        file.close();
        return true;
    }

    return false;
}

bool XmlHelper::AddXmlNode(const QString &parent_tag, const QString &node_tag, const QString &text)
{
    if (!LoadXmlFile())
    {
        return false;
    }

    QDomNodeList node_list = doc_.elementsByTagName(parent_tag);
	int count = node_list.count();
    if (count > 0)
    {
        QDomElement elem = doc_.createElement(node_tag);
        QDomText elem_text = doc_.createTextNode(text);
        elem.appendChild(elem_text);
        node_list.at(count - 1).appendChild(elem);

        QFile file(file_name_);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return false;
        }
        QTextStream out(&file);
        doc_.save(out, 4);
        file.close();
        return true;
    }

    return false;
}

bool XmlHelper::RemoveXmlNode(const QString &node_tag)
{
    if (!LoadXmlFile())
    {
        return false;
    }

    QDomNodeList node_list = doc_.elementsByTagName(node_tag);
    if (node_list.count() > 0)
    {
        QDomNode parent(node_list.at(0).parentNode());
        parent.removeChild(node_list.at(0));
        QFile file(file_name_);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            return false;
        }
        QTextStream out(&file);
        doc_.save(out, 4);
        file.close();
        return true;
    }

    return false;
}

bool XmlHelper::ParseXmlDocument(const QString &file_name)
{
    file_name_ = file_name;

    if (!LoadXmlFile())
    {
        return false;
    }

    QDomElement doc_elem = doc_.documentElement();
    QDomNode node = doc_elem.firstChild();
    while (!node.isNull())
    {
        QDomElement elem = node.toElement();
        if (!elem.isNull())
        {
            qDebug() << elem.tagName() << ": " << elem.text()
                        << endl;
        }
        node = node.nextSibling();
    }
    doc_.clear();

    return true;
}

QString XmlHelper::ParseXmlNodeContent(const QString &node_tag)
{
    if (!LoadXmlFile())
    {
        return QString();
    }

    QDomNodeList node_list = doc_.elementsByTagName(node_tag);
    if (node_list.count() > 0)
    {
        if (!node_list.at(0).firstChild().isText())
        {
            return QString();
        }
        return node_list.at(0).toElement().text();
    }

    return QString();
}

QStringList XmlHelper::ParseXmlNodeList(const QString &node_tag)
{
    QStringList str_list;
    if (!LoadXmlFile())
    {
        return str_list;
    }

    QDomNodeList node_list = doc_.elementsByTagName(node_tag);
    for (int i = 0; i < node_list.count(); i++)
    {
        if (node_list.at(i).firstChild().isText())
        {
            str_list.append(node_list.at(i).toElement().text());
        }
        else
        {
            str_list.append(" ");
        }
    }

    return str_list;
}

QString XmlHelper::ParseXmlNodeContent(const QDomElement &elem)
{
    if (!LoadXmlFile())
    {
        return QString();
    }

    QDomElement root = doc_.documentElement();
    QDomNode node = root.firstChild();
    while (!node.isNull())
    {
        if (node.toElement().tagName() == elem.tagName())
        {
            return elem.text();
        }
        node = node.nextSibling();
    }

    return QString("");
}

QString XmlHelper::ParseXmlNodeContent(const QDomNode &special_node)
{
    if (!LoadXmlFile())
    {
        return QString();
    }

    QDomElement root = doc_.documentElement();
    QDomNode node = root.firstChild();
    while (!node.isNull())
    {
        if (node.toElement().tagName() == special_node.toElement().tagName())
        {
            return special_node.toElement().text();
        }
        node = node.nextSibling();
    }

    return QString("");
}

QString XmlHelper::ParseXmlNodeAttribute(const QString &node_tag, const QString& attr_key)
{
    if (!LoadXmlFile())
    {
        return QString();
    }

    QString str;
    QDomNodeList node_list = doc_.elementsByTagName(node_tag);

    if (node_list.count() > 0)
    {
        QDomElement elem = node_list.at(0).toElement();
        str = elem.attributeNode(attr_key).toText().data();
    }

    return str;
}

QString XmlHelper::ParseXmlNodeAttribute(const QDomElement &elem, const QString& attr_key)
{
    if (!LoadXmlFile())
    {
        return QString();
    }

    QString str;
    QDomNodeList node_list = doc_.elementsByTagName(elem.tagName());
    if (node_list.count() > 0)
    {
        QDomElement elem = node_list.at(0).toElement();
        str = elem.attributeNode(attr_key).toText().data();
    }

    return str;
}

bool XmlHelper::SetXmlNodeContent(const QDomElement &elem, const QString&)
{
    if (!LoadXmlFile())
    {
        return false;
    }

    QDomElement root = doc_.documentElement();
    QDomNode node = root.firstChild();
    while (!node.isNull())
    {
        if (node.toElement().tagName() == elem.tagName())
        {
            doc_.replaceChild(elem, node);
            return true;
        }

        node = node.nextSibling();
    }

    return false;
}

bool XmlHelper::SetXmlNodeContent(const QString &tag_name, const QString &text)
{
    if (!LoadXmlFile())
    {
        return false;
    }

    QDomElement root = doc_.documentElement();
    QDomNodeList node_list = root.elementsByTagName(tag_name);
    if (node_list.count() > 0)
    {
        QDomElement elems = node_list.at(0).toElement();
        QDomNode old_node = elems.firstChild();
        if (elems.firstChild().isText())
        {
            elems.firstChild().setNodeValue(text);
            QDomNode new_node = elems.firstChild();
            elems.replaceChild(new_node, old_node);
        }
        else
        {
            elems.firstChild().setNodeValue(text);
            QDomText text_node;
            text_node.setNodeValue(text);
            QDomNode new_node = elems.firstChild();
            new_node.appendChild(text_node);
            elems.replaceChild(new_node, old_node);
        }
        QFile file(file_name_);
        if (!file.open(QIODevice::WriteOnly))
        {
            return false;
        }
        QTextStream out(&file);
        doc_.save(out, 4);
        file.close();
        return true;
    }

    return false;
}

bool XmlHelper::SetXmlNodeAttribute(const QString& node_tag, const QString &attr_key, const QString &attr_value)
{
    if (!LoadXmlFile())
    {
        return false;
    }

    QDomNodeList node_list = doc_.elementsByTagName(node_tag);
    if (node_list.count() > 0)
    {
        QDomElement elem = node_list.at(0).toElement();
        elem.setAttribute(attr_key, attr_value);

        QFile file(file_name_);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return false;
        }
        QTextStream out(&file);
        doc_.save(out, 4);
        file.close();
        return true;
    }

    return false;
}

QDomElement XmlHelper::GetXmlRootNode()
{
    if (!LoadXmlFile())
    {
        return QDomElement();
    }

    return doc_.firstChild().toElement();
}

QDomElement XmlHelper::GetXmlNodeParent(const QString &node_tag)
{
    if (!LoadXmlFile())
    {
        return QDomElement();
    }

    QDomNodeList node_list = doc_.elementsByTagName(node_tag);
    if (node_list.count() > 0)
    {
        return node_list.at(0).toElement();
    }

    return QDomElement();
}

bool XmlHelper::ClearXmlDocument()
{
    if (!LoadXmlFile())
    {
        return false;
    }

    QFile file(file_name_);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }
    QTextStream out(&file);
    doc_.clear();
    doc_.save(out, 4);
    return true;
}

bool XmlHelper::AddRootNode(const QString &root_node)
{
    QFile file(file_name_);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return true;
    }
    QDomProcessingInstruction instruction =
            doc_.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc_.appendChild(instruction);
    QDomElement root = doc_.createElement(root_node);
    doc_.appendChild(root);
    QTextStream out(&file);
    doc_.save(out, 4);
    file.close();

    return true;
}

void XmlHelper::DestroyInstance()
{
    if (helper_ != NULL)
    {
        delete helper_;
        helper_ = NULL;
    }
}

bool XmlHelper::LoadXmlFile()
{
    doc_.clear();
    QFile file(file_name_);
    if (!file.open(QIODevice::ReadWrite))
    {
        file.close();
        return false;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");
    QString xml_str(out.readAll().toUtf8());
    if (!doc_.setContent(xml_str))
    {
        file.close();
        return false;
    }
    file.close();

    return true;
}
