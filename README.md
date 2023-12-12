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
    User->>PowerButton: press()
    PowerButton->>MainWindow: powerOn()
    MainWindow->>ControlSystem: stage1Required()
    ControlSystem->>Stage1: start()
    Stage1->>ControlSystem: checkSafetySystems()
    MainWindow->>Screen: displayUnitOk()
```

### UC2: Electrodes Placement
```mermaid
sequenceDiagram
actor User
    MainWindow->>Screen: displayStayCalm()
    MainWindow->>Light: flashLight()
    MainWindow->>Screen: displayCheckResponse()
    User->>MainWindow: checksPatientResponsiveness
    MainWindow->>Light: flashLight()
    MainWindow->>Screen: displayCallForHelp()
    User->>MainWindow: callsForHelp
    MainWindow->>Screen: displayOpenAirways()
    User->>MainWindow: opensPatientsAirways
    MainWindow->>Screen: displayCheckForBreathing()
    User->>MainWindow: checksForPatientBreathing
    ControlSystem->>Stage2: start()
    Stage2->>ControlSystem: checkSafetySystems()
    MainWindow->>Screen: displayExposeCheck()
    MainWindow->>Screen: displayAttachPads()
    alt Pediatric Patient
        User->>PediatricButton: press()
        MainWindow->>Screen: displayPediatricPads()
    else Adult Patient
        MainWindow->>Screen: displayAdultPads()
    end
    Note over User: Selects Appropriate Pads
```

### UC3: Heart Rythm Analysis
```mermaid
sequenceDiagram
actor User
    User->>MainWindow: selectMode()
    MainWindow->>ControlSystem: stage3Required()
    ControlSystem->>Stage3: start()
    MainWindow->>Light: flashLight()
    MainWindow->>Screen: displayDoNotTouch()
    User->>MainWindow: backsAway
    Stage3->>ControlSystem: startAnalysis()
    ControlSystem->>Pads: getHeartRhythm()
    MainWindow->>Screen: displayHeartRhythm()
    MainWindow->>Screen: displayAdvice()
```

### UC4: Shock Delivery
```mermaid
sequenceDiagram
actor User
    MainWindow->>ControlSystem: stage4Required()
    ControlSystem->>Stage4: start()
    MainWindow->>Screen: displayStandClear()
    User->>MainWindow: pressShock()
    MainWindow->>ControlSystem: shockRequired()
    MainWindow->>Light: flashLight()
    MainWindow->>Screen: displayShockDelivering()
    ControlSystem->>Pads: shock()
    MainWindow->>Screen: displayShockDelivered()
```

### UC5: CPR
```mermaid
sequenceDiagram
actor User
    MainWindow->>ControlSystem: stage5Required()
    ControlSystem->>Stage5: start()
    MainWindow->>Light: flashLight()
    MainWindow->>Screen: displayStartCPR()
    User->>MainWindow: performsCPR()
    loop For 2 Minutes
    Stage5->>ControlSystem: checkCompression()
    ControlSystem->>MainWindow: CPRFeedback()
    MainWindow->>Screen: displayFeedback()
    end
    MainWindow->>Screen: displayStopCPR()
```

### UC6: Battery Depletion
```mermaid
sequenceDiagram
actor User
    ControlSystem->>ControlSystem: isLowBattery()
    MainWindow->>Screen: displayChangeBatteries()
    User->>MainWindow: removesAllBatteries()
    User->>MainWindow: insertsNewBatteries()
    User->>PowerButton: press()
    MainWindow->>Screen: displayPressBattery()
    User->>BatteryButton: press()
    MainWindow->>ControlSystem: stage1Required()
    ControlSystem->>Stage1: start()
    Stage1->>ControlSystem: checkSafetySystems()
    MainWindow->>Screen: displayUnitOkay()
```

### UC7: Detached Pads
```mermaid
sequenceDiagram
actor User
    MainWindow->>Pads: isConnected()
    MainWindow->>Screen: displayCheckPads()
```