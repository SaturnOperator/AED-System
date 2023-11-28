#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>

#include "defs.h"

#include "QIconButton.h"
#include "QAEDScreen.h"

int main(int argc, char *argv[])
{
    // Setup Mainwindow and layout
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Team 17 AED System");
    QGridLayout* mainLayout = new QGridLayout;

    // Add content into layout
    QIconButton* test1 = new QIconButton("");
    QIconButton* test2 = new QIconButton("");
    mainLayout->addWidget(test1);
    mainLayout->addWidget(test2);

    QAEDScreen* screen = new QAEDScreen();
    mainLayout->addWidget(screen);

    // QObject::connect(test1, &QPushButton::clicked, [screen]() {
    //     screen->showElement("_1_helper_cpr", false);
    // });


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
