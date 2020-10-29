#pragma once

#include <QLocale>
#include <QMap>
#include <QObject>
#include <QSet>
#include <QString>
#include <QtGlobal>
namespace qthelpers {

class Converters {
 public:
  static QString BytesToHuman(const qlonglong& bytes) {
    // Чтобы код оставался header-only делаем перевод не через QTranslator!
    // В самом деле, единицы измерения имеют однозначный перевод что в русском,
    // что в английском языках, поэтому харкодим перевод прямо здесь один раз и
    // навсегда. Язык определяем так же стандартным способом - переменной
    // окружения LANG.
    QMap<QString, QString> translations_en = {
        {"B", " B"}, {"KB", " KB"}, {"MB", " MB"}, {"GB", " GB"}, {"TB", " TB"},
    };
    QMap<QString, QString> translations_ru = {
        {"B", " Б"}, {"KB", " КБ"}, {"MB", " МБ"}, {"GB", " ГБ"}, {"TB", " ТБ"},
    };
    QMap<QString, QString>* t = &translations_en;
    if (qgetenv("LANG").toLower().contains("ru"))
      t = &translations_ru;

    QString number;
    if (bytes < 0x400)  // If less than 1 KB, report in B
    {
      number = QString::number(bytes);
      number.append(t->value("B"));
      return number;
    } else {
      if (bytes >= 0x400 &&
          bytes < 0x100000)  // If less than 1 MB, report in KB, unless rounded
                             // result is 1024 KB, then report in MB
      {
        qlonglong result = (bytes + (0x400 / 2)) / 0x400;

        if (result < 0x400) {
          number = QString::number(result);
          number.append(t->value("KB"));
          return number;
        } else {
          qlonglong result = (bytes + (0x100000 / 2)) / 0x100000;
          number = QString::number(result);
          number.append(t->value("MB"));
          return number;
        }
      } else {
        if (bytes >= 0x100000 &&
            bytes < 0x40000000)  // If less than 1 GB, report in MB, unless
                                 // rounded result is 1024 MB, then report in GB
        {
          qlonglong result = (bytes + (0x100000 / 2)) / 0x100000;

          if (result < 0x100000) {
            number = QString::number(result);
            number.append(t->value("MB"));
            return number;
          } else {
            qlonglong result = (bytes + (0x40000000 / 2)) / 0x40000000;
            number = QString::number(result);
            number.append(t->value("GB"));
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
              number = QString::number(result);
              number.append(t->value("GB"));
              return number;
            } else {
              qlonglong result = (bytes + (0x10000000000 / 2)) / 0x10000000000;
              number = QString::number(result);
              number.append(t->value("TB"));
              return number;
            }
          } else {
            qlonglong result =
                (bytes + (0x10000000000 / 2)) /
                0x10000000000;  // If more than 1 TB, report in TB
            number = QString::number(result);
            number.append(t->value("TB"));
            return number;
          }
        }
      }
    }
  }
};

}  // namespace qthelpers
