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
    );

    powerLabel->setStyleSheet(labelStyle);
    pediatricLabel->setStyleSheet(labelStyle);

    // controller->getPowerIndicator()->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // controller->getPowerButton()->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // controller->getPediatricIndicator()->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // controller->getPediatricButton()->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // powerLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // pediatricLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);




    // Create an array of buttons to toggle betweent the stages, this is for testing only
    QWidget* stageSelector = new QWidget();
    QGridLayout* stageSelectorLayout = new QGridLayout();
    stageSelector->setLayout(stageSelectorLayout);
    QList<QIconButton*> stageButtons;
    
    // Add a button for each stage, do it by looping through all the stages
    for (int i = static_cast<int>(Stage::NONE); i <= static_cast<int>(Stage::POST_USE); i++) {
        Stage currentStage = static_cast<Stage>(i);

        // Create the button
        stageButtons.append(new QIconButton(QString::number(i)));
        
        // continue/ignore if it's the NONE stage
        if(currentStage == Stage::NONE){
            continue; 
        }

        // These stages aren't implemented yet, disable their buttons for now
        if(i == 6){
            stageButtons[i]->setEnabled(false);
        }

        // Create a label and set it to the current stage's name
        QString stageName = stageToString(currentStage);
        QLabel* stageLabel = new QLabel(stageName);
        stageLabel->setAlignment(Qt::AlignVCenter);

        // Add the button and the label into the grid view
        stageSelectorLayout->addWidget(stageLabel, 0, i-1);
        stageSelectorLayout->addWidget(stageButtons[i], 1, i-1);

        // Make the buttons update the screen when they're pressed
        // The button will change the stage on the screen
        // Also switch the screen settings tab to show settings for that stage
        QObject::connect(stageButtons[i], &QPushButton::clicked, [currentStage, controller, settings, i]() {
            controller->getStage(currentStage)->start();
            settings->setCurrentIndex(i-1);
        });
    }

    QDockWidget* stagesDock = new QDockWidget("Stages", &mainWindow);
    stagesDock->setWidget(stageSelector);
    mainWindow.addDockWidget(Qt::TopDockWidgetArea, stagesDock);

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
