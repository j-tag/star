#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include <QObject>
#include <QJsonObject>

namespace star {

namespace web {

namespace json {

class JsonParser : public QObject
{
    Q_OBJECT
public:
    JsonParser();
    virtual ~JsonParser();

    QString getSafeStringValue(const QJsonObject &json, const QString &strKey) const;
    int getSafeIntegerValue(const QJsonObject &json, const QString &strKey, int defaultValue = -1);
    QJsonObject getSafeObjectValue(const QJsonObject &json, const QString &strKey) const;
};

}

}

}

#endif // JSONPARSER_HPP
