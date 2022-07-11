/********************************************************************************
** Form generated from reading UI file 'searchw.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHW_H
#define UI_SEARCHW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchW
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QLineEdit *lineEdit;

    void setupUi(QWidget *SearchW)
    {
        if (SearchW->objectName().isEmpty())
            SearchW->setObjectName(QString::fromUtf8("SearchW"));
        SearchW->resize(863, 398);
        verticalLayout = new QVBoxLayout(SearchW);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(SearchW);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        lineEdit = new QLineEdit(SearchW);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);


        retranslateUi(SearchW);

        QMetaObject::connectSlotsByName(SearchW);
    } // setupUi

    void retranslateUi(QWidget *SearchW)
    {
        SearchW->setWindowTitle(QCoreApplication::translate("SearchW", "SearchW", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchW: public Ui_SearchW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHW_H
