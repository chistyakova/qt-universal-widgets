#pragma once

#include <QObject>
#include <QLocale>
#include <QString>

namespace qthelpers {

class Converters {
 public:
  static QString BytesToHuman(const qlonglong& bytes) {
    QString number;

    if (bytes < 0x400)  // If less than 1 KB, report in B
    {
      number = QLocale::system().toString(bytes);
      number.append(QObject::tr("B"));
      return number;
    } else {
      if (bytes >= 0x400 &&
          bytes < 0x100000)  // If less than 1 MB, report in KB, unless rounded
                             // result is 1024 KB, then report in MB
      {
        qlonglong result = (bytes + (0x400 / 2)) / 0x400;

        if (result < 0x400) {
          number = QLocale::system().toString(result);
          number.append(QObject::tr("KB"));
          return number;
        } else {
          qlonglong result = (bytes + (0x100000 / 2)) / 0x100000;
          number = QLocale::system().toString(result);
          number.append(QObject::tr("MB"));
          return number;
        }
      } else {
        if (bytes >= 0x100000 &&
            bytes < 0x40000000)  // If less than 1 GB, report in MB, unless
                                 // rounded result is 1024 MB, then report in GB
        {
          qlonglong result = (bytes + (0x100000 / 2)) / 0x100000;

          if (result < 0x100000) {
            number = QLocale::system().toString(result);
            number.append(QObject::tr("MB"));
            return number;
          } else {
            qlonglong result = (bytes + (0x40000000 / 2)) / 0x40000000;
            number = QLocale::system().toString(result);
            number.append(QObject::tr("GB"));
            return number;
          }
        } else {
          if (bytes >= 0x40000000 &&
              bytes < 0x10000000000)  // If less than 1 TB, report in GB, unless
                                      // rounded result is 1024 GB, then report
                                      // in TB
          {
            qlonglong result = (bytes + (0x40000000 / 2)) / 0x40000000;

            if (result < 0x40000000) {
              number = QLocale::system().toString(result);
              number.append(QObject::tr("GB"));
              return number;
            } else {
              qlonglong result = (bytes + (0x10000000000 / 2)) / 0x10000000000;
              number = QLocale::system().toString(result);
              number.append(QObject::tr("TB"));
              return number;
            }
          } else {
            qlonglong result =
                (bytes + (0x10000000000 / 2)) /
                0x10000000000;  // If more than 1 TB, report in TB
            number = QLocale::system().toString(result);
            number.append(QObject::tr("TB"));
            return number;
          }
        }
      }
    }
  }
};

}  // namespace qthelpers
