#include "defs.h"

#include "QIconButton.h"
#include "QAEDScreen.h"

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

    
    QAEDScreen* screen = new QAEDScreen(); // Create a screen instance
    QList<QPushButton*> stageButtons; // Create an array of buttons
    

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
        if( i == 1 || i == 4 || i == 6){
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
        QObject::connect(stageButtons[i], &QPushButton::clicked, [currentStage, screen]() {
            screen->setStage(currentStage);
        });
    }



    // Add screen 
    mainLayout->addWidget(screen, 2, 0, 1, 12);

    
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
