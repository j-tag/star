#include "includes/star/Star.hpp"


star::ui::general::Alerts::Alerts() {}

star::ui::general::Alerts::~Alerts() {}

void star::ui::general::Alerts::showErrorMessage(const QString &strMessage)
{
    emit this->showError(strMessage);
}
