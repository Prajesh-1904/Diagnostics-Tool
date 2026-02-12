esp32/
├── README.md
├──include
|    ├──can_manager.h
|    ├──dtc_decoder.h
|    └──obd_parser.h
|    ├──src
|        ├──platform.ini
|        └──main.cpp
└──mockECU
    ├──src
        ├──platform.ini
        └──main.cpp




flutter/
├── README.md
├── pubspec.yaml
└── lib/
    ├── main.dart
    ├── screens/
    │   ├── home_screen.dart
    │   ├── live_data_screen.dart
    │   └── dtc_screen.dart
    │
    ├── services/
    │   ├── ble_service.dart
    │   └── parser.dart
    │
    └── models/
        ├── obd_data.dart
        └── dtc.dart



Hardware/
├── README.md
├── Schematic/
│   └── universal_2w_diagnostic.kicad_sch
│
├── PCB/
│   └── universal_2w_diagnostic.kicad_pcb
│
└── BOM/
    └── bom.xlsx




Docs/
├── README.md
├── bringup.md
├── power_and_safety.md
├── can_and_kline.md
└── circuit_diagram.pdf
