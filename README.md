# AED-System

Project Description

## Run Instructions

```bash
cd src/
make all
```


## Requirements

**Linux**: 

QtSvg library

```bash
sudo apt install libqt5svg5-dev
```

---

**macOS**: 

Qt5 framework

```bash
brew install qt@5
```

## Sequence Diagrams

### UC1
```mermaid
sequenceDiagram
actor User
participant PowerButton
participant MainWindow
participant ControlSystem
participant Screen
    User->>PowerButton: press()
    PowerButton->>MainWindow: selfTest()
    MainWindow->>ControlSystem: selfTest()
    ControlSystem->>MainWindow: testPassed()
    MainWindow->>Screen: displayUnitOk()

```

### UC2: Electrodes Placement
```mermaid
sequenceDiagram
actor User
participant MainWindow
participant ControlSystem
participant Light
participant Screen
    ControlSystem->>MainWindow: stage1()
    MainWindow->>Light: flashLight()
    MainWindow->>Screen: displayCheckResponse()
    User->>MainWindow: shakePatient()
    MainWindow->>ControlSystem: checkPatient()
    ControlSystem->>MainWindow: callHelp()
    MainWindow->>Light: flashLight()
    MainWindow->>Screen: displayCallForHelp()
    User->>MainWindow: callsHelp()
    MainWindow->>ControlSystem: stage2Required()
    ControlSystem->>MainWindow: stage2()
    MainWindow->>Light: flashLight()
    MainWindow->>Screen: displayPlaceElectrodes()
    User->>MainWindow: placesElectrode()
    MainWindow->>ControlSystem: checkPads()
    ControlSystem->>MainWindow: padsInfo()
    MainWindow->>Screen: displayPadsInfo()
```

### UC3: Heart Rythm Analysis
```mermaid
sequenceDiagram
actor User
participant MainWindow
participant ControlSystem
participant Light
participant Screen
    User->>MainWindow: selectMode()
    MainWindow->>ControlSystem: stage3Required()
    ControlSystem->>MainWindow: stage3()
    MainWindow->>Light: flashLight()
    MainWindow->>Screen: displayDoNotTouch()
    User->>MainWindow: backsAway()
    MainWindow->>ControlSystem: startAnalysisRequired()
    ControlSystem->>MainWindow: startAnalysis()
    ControlSystem->>MainWindow: analysisFinished()
    MainWindow->>Screen: displayAdvice()
```

### UC4: Shock Delivery
```mermaid
sequenceDiagram
actor User
participant MainWindow
participant ControlSystem
participant Screen
participant Light
    MainWindow->>ControlSystem: stage4Required()
    ControlSystem->>MainWindow: stage4()
    MainWindow->>Screen: displayStandClear()
    User->>MainWindow: pressShock()
    MainWindow->>ControlSystem: shockRequired()
    ControlSystem->>MainWindow: shock()
    MainWindow->>Light: flashLight()
    MainWindow->>Screen: displayShockDelivered()
```

### UC5: CPR
```mermaid
sequenceDiagram
actor User
participant MainWindow
participant ControlSystem
participant Light
participant Screen
    MainWindow->>ControlSystem: stage5Required()
    ControlSystem->>MainWindow: stage5()
    MainWindow->>Light: flashLight()
    MainWindow->>Screen: displayStartCPR()
    User->>MainWindow: performCPR()
    MainWindow->>ControlSystem: checkCPR()
    ControlSystem->>MainWindow: CPRFeedback()
    MainWindow->>Screen: displayFeedback()
    ControlSystem->>MainWindow: timeUp()
    MainWindow->>Screen: displayStopCPR()
```

### UC6: Battery Depletion
```mermaid
sequenceDiagram
actor User
```

### UC7: Detached Pads
```mermaid
sequenceDiagram
actor User
```