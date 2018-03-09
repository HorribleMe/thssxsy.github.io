/********************************************************************************
** Form generated from reading UI file 'pgraphwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PGRAPHWIDGET_H
#define UI_PGRAPHWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Pgraphwidget
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_13;
    QPushButton *pushButton_8;
    QLabel *label;
    QSlider *horizontalSlider;
    QLabel *label_2;
    QSlider *horizontalSlider_2;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QTextEdit *textEdit;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Pgraphwidget)
    {
        if (Pgraphwidget->objectName().isEmpty())
            Pgraphwidget->setObjectName(QStringLiteral("Pgraphwidget"));
        Pgraphwidget->resize(660, 596);
        gridLayout = new QGridLayout(Pgraphwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(Pgraphwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        verticalLayout->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(groupBox);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        verticalLayout->addWidget(pushButton_7);

        pushButton_13 = new QPushButton(groupBox);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));

        verticalLayout->addWidget(pushButton_13);

        pushButton_8 = new QPushButton(groupBox);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        verticalLayout->addWidget(pushButton_8);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label);

        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        sizePolicy.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
        horizontalSlider->setSizePolicy(sizePolicy);
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_2);

        horizontalSlider_2 = new QSlider(groupBox);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        sizePolicy.setHeightForWidth(horizontalSlider_2->sizePolicy().hasHeightForWidth());
        horizontalSlider_2->setSizePolicy(sizePolicy);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton_9 = new QPushButton(groupBox_3);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        gridLayout_2->addWidget(pushButton_9, 0, 0, 1, 2);

        pushButton_10 = new QPushButton(groupBox_3);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));

        gridLayout_2->addWidget(pushButton_10, 1, 0, 1, 1);

        pushButton_11 = new QPushButton(groupBox_3);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));

        gridLayout_2->addWidget(pushButton_11, 1, 1, 1, 1);

        pushButton_12 = new QPushButton(groupBox_3);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));

        gridLayout_2->addWidget(pushButton_12, 2, 0, 1, 2);


        verticalLayout->addWidget(groupBox_3);


        gridLayout->addWidget(groupBox, 0, 2, 3, 1);

        groupBox_2 = new QGroupBox(Pgraphwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_4 = new QPushButton(groupBox_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout->addWidget(pushButton_5);

        horizontalSpacer = new QSpacerItem(239, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addWidget(groupBox_2, 0, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(410, 296, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer_2, 1, 0, 2, 2);

        textEdit = new QTextEdit(Pgraphwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(textEdit, 4, 1, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 4, 0, 1, 1);

        groupBox->raise();
        groupBox_2->raise();
        textEdit->raise();

        retranslateUi(Pgraphwidget);
        QObject::connect(pushButton_8, SIGNAL(clicked()), Pgraphwidget, SLOT(close()));

        QMetaObject::connectSlotsByName(Pgraphwidget);
    } // setupUi

    void retranslateUi(QWidget *Pgraphwidget)
    {
        Pgraphwidget->setWindowTitle(QApplication::translate("Pgraphwidget", "Form", 0));
        groupBox->setTitle(QString());
        pushButton->setText(QApplication::translate("Pgraphwidget", "FMMMLayout", 0));
        pushButton_2->setText(QApplication::translate("Pgraphwidget", "CircularLayout", 0));
        pushButton_3->setText(QApplication::translate("Pgraphwidget", "BalloonLayout", 0));
        pushButton_6->setText(QApplication::translate("Pgraphwidget", "TutteLayout", 0));
        pushButton_7->setText(QApplication::translate("Pgraphwidget", "ModularMultilevelMixer", 0));
        pushButton_13->setText(QApplication::translate("Pgraphwidget", "save", 0));
        pushButton_8->setText(QApplication::translate("Pgraphwidget", "quit", 0));
        label->setText(QApplication::translate("Pgraphwidget", "Point", 0));
        label_2->setText(QApplication::translate("Pgraphwidget", "Edge", 0));
        groupBox_3->setTitle(QString());
        pushButton_9->setText(QApplication::translate("Pgraphwidget", "UP", 0));
        pushButton_10->setText(QApplication::translate("Pgraphwidget", "LEFT", 0));
        pushButton_11->setText(QApplication::translate("Pgraphwidget", "RIGHT", 0));
        pushButton_12->setText(QApplication::translate("Pgraphwidget", "DOWN", 0));
        groupBox_2->setTitle(QString());
        pushButton_4->setText(QApplication::translate("Pgraphwidget", "small", 0));
        pushButton_5->setText(QApplication::translate("Pgraphwidget", "big", 0));
    } // retranslateUi

};

namespace Ui {
    class Pgraphwidget: public Ui_Pgraphwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PGRAPHWIDGET_H
