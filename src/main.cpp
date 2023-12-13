#include "defs.h"

#include "QIconButton.h"
#include "AEDController.h"
#include "QScreenSettings.h"

#include <QApplication>
#include <QMainWindow>
#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>

int main(int argc, char *argv[])
{
    // Setup Mainwindow and layout
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Team 17 AED System");
    QGridLayout* mainLayout = new QGridLayout();
    // mainLayout->setSpacing(0);

    AEDController* controller = new AEDController();
    QAEDScreen* screen = controller->getScreen(); // Create a screen instance
    QScreenSettings* settings = new QScreenSettings(controller); // Create screen settings instance

    // Add screen to main window
    mainLayout->addWidget(screen, 0, 0, 1, 3);

    QLabel* powerLabel = new QLabel("POWER");
    QLabel* pediatricLabel = new QLabel("PEDIATRIC");

    // Add buttons to main window
    mainLayout->addWidget(controller->getPowerIndicator(), 2, 0, Qt::AlignRight);
    mainLayout->addWidget(controller->getPowerButton(), 2, 0);
    mainLayout->addWidget(powerLabel, 1, 0, 1, 1, Qt::AlignCenter | Qt::AlignTop);
    mainLayout->addWidget(controller->getPediatricIndicator(), 2, 2, Qt::AlignRight);
    mainLayout->addWidget(controller->getPediatricButton(), 2, 2);
    mainLayout->addWidget(pediatricLabel, 1, 2, 1, 1, Qt::AlignCenter | Qt::AlignTop);

    // Dock the settings to the right side of the screen.
    QDockWidget* settingsDock = new QDockWidget("Settings", &mainWindow);
    settingsDock->setWidget(settings);
    mainWindow.addDockWidget(Qt::RightDockWidgetArea, settingsDock);

    QString labelStyle = QString(
        "QLabel { "
        "    padding: 0px;"
        "    font-family: Frank;"
        "    color: #c9cbbc; "
        "}"
        "QLabel:disabled { "
        "    color: #464e55; "
        "}"
    );

    powerLabel->setStyleSheet(labelStyle);
    pediatricLabel->setStyleSheet(labelStyle);

    // Create an array of buttons to toggle betweent the stages, this is for testing only
    QWidget* stageSelector = new QWidget();
    QGridLayout* stageSelectorLayout = new QGridLayout();
    stageSelector->setLayout(stageSelectorLayout);
    
    // Add a button for each stage, do it by looping through all the stages
    for (int i = static_cast<int>(Stage::POWER); i <= static_cast<int>(Stage::POST_USE); i++) {
        QLabel* stageLabel = controller->getStageLabel(i);
        QIconButton* stageButton = controller->getStageButton(i);

        // Add the button and the label into the grid view
        if(stageLabel){
            stageSelectorLayout->addWidget(stageLabel, 0, i-1, 1, 1, Qt::AlignCenter | Qt::AlignVCenter);
        }
        if(stageButton){
            stageSelectorLayout->addWidget(stageButton, 1, i-1, 1, 1, Qt::AlignCenter);
        }
    }

    // QDockWidget* stagesDock = new QDockWidget("Stages", &mainWindow);
    // stagesDock->setWidget(stageSelector);
    // mainWindow.addDockWidget(Qt::TopDockWidgetArea, stagesDock);

    mainLayout->addWidget(stageSelector, 2, 1);

    // Create central widget
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    mainWindow.setCentralWidget(centralWidget);

    // Resize to fit everything
    mainWindow.resize(centralWidget->sizeHint());

    // Show window and run app
    mainWindow.show();
    return app.exec();
}
