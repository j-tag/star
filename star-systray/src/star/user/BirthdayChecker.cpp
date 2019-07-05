#include "includes/star/Star.hpp"


star::user::BirthdayChecker::BirthdayChecker() {

    connect(s.getOAuth2(), &star::web::auth::OAuth2::loginResult, this, &BirthdayChecker::checkBirthday);
}

star::user::BirthdayChecker::~BirthdayChecker() {}

void star::user::BirthdayChecker::checkBirthday(bool result, QString )
{
    if(result == true) {

        if(s.getUserDetails()->getCelebrateBirthday() == true) {
            // User want to celebrate their birthday

            auto birthday = s.getUserDetails()->getBirthday().date();
            auto today = QDateTime::currentDateTime().date();

            if(birthday.month() == today.month() && birthday.day() == today.day()) {
                // Today is the user's birthday :)
                s.getTrayIconManager()->showMessage("تولدت مبارک!"
                                                    , "هوووررررررررررررررررررا! " + s.getUserDetails()->getName() + " تولدت رو تبریک میگیم! امیدواریم که همیشه شاد و سلامت باشی!");
            }

        }


    }
}

