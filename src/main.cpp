#include "defs.h"

#include "QIconButton.h"
#include "AEDController.h"
#include "QScreenSettings.h"

#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>

int main(int argc, char *argv[])
{
    // Setup Mainwindow and layout
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Team 17 AED System");
    QGridLayout* mainLayout = new QGridLayout;

    AEDController* controller = new AEDController();
    QAEDScreen* screen = controller->getScreen(); // Create a screen instance
    QScreenSettings* settings = new QScreenSettings(controller); // Create screen settings instance

    // Create an array of buttons to toggle betweent the stages
    QList<QPushButton*> stageButtons;
    

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
        if(i == 4 || i == 6){
            stageButtons[i]->setEnabled(false);
        }

        // Create a label and set it to the current stage's name
        QString stageName = stageToString(currentStage);
        QLabel* stageLabel = new QLabel(stageName);
        stageLabel->setAlignment(Qt::AlignVCenter);

        // Add the button and the label into the grid view
        mainLayout->addWidget(stageLabel, 0, i-1);
        mainLayout->addWidget(stageButtons[i], 1, i-1);

        // Make the buttons update the screen when they're pressed
        // The button will change the stage on the screen
        // Also switch the screen settings tab to show settings for that stage
        QObject::connect(stageButtons[i], &QPushButton::clicked, [currentStage, controller, settings, i]() {
            controller->getStage(currentStage)->start();
            settings->setCurrentIndex(i-1);
        });
    }

    // Add screen and screen settings into the view
    mainLayout->addWidget(screen, 2, 0, 1, 12);
    mainLayout->addWidget(settings, 0, 12, 3, 6); // Add to left of screen
    // mainLayout->addWidget(settings, 3, 0, 1, 6); // Add under screen

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
