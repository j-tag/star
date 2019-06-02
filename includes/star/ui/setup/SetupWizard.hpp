#ifndef SETUPWIZARD_HPP
#define SETUPWIZARD_HPP

#include <QObject>

namespace star {

namespace ui {

namespace setup {

class SetupWizard : public QObject
{
    Q_OBJECT
public:
    SetupWizard();
    virtual ~SetupWizard();

signals:
    void initSetupWizard();
};

}

}

}

#endif // SETUPWIZARD_HPP
