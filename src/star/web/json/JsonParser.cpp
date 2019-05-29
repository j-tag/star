#include "includes/star/Star.hpp"

star::web::json::JsonParser::JsonParser() {}

star::web::json::JsonParser::~JsonParser() {}

QString star::web::json::JsonParser::getSafeStringValue(const QJsonObject &json, const QString &strKey) const
{
    return json[strKey].toString();
}

int star::web::json::JsonParser::getSafeIntegerValue(const QJsonObject &json, const QString &strKey, int defaultValue)
{
    return json[strKey].toInt(defaultValue);
}
