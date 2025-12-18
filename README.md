esp32/
├── README.md
├── common/
│   ├── pins.h
│   ├── config.h
│   ├── utils.h
│   └── utils.cpp
│
├── tests/
│   ├── spi_test/
│   │   └── spi_test.ino
│   │
│   ├── can_loopback/
│   │   └── can_loopback.ino
│   │
│   └── power_test/
│       └── power_test.ino
│
└── main/
    ├── main.ino
    ├── can_manager.h
    ├── can_manager.cpp
    ├── obd_parser.h
    ├── obd_parser.cpp
    ├── dtc_decoder.h
    ├── dtc_decoder.cpp
    ├── ble_manager.h
    ├── ble_manager.cpp
    └── README.md



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
