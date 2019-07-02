add_library(cmd STATIC
        src/CoincidenceMessenger.cc
        src/DBMessenger.cc
        src/ESgenMessenger.cc
        src/FastNeutronMessenger.cc
        src/GLG4DebugMessenger.cc
        src/GLG4PrimaryGeneratorMessenger.cc
        src/GLG4VisMessenger.cc
        src/IsotopeMessenger.cc
        src/PhysicsListMessenger.cc
        src/ProcBlockManager.cc
        src/ReacIBDgenMessenger.cc
        src/SNgenMessenger.cc
        src/TrackingMessenger.cc)

target_include_directories(cmd PUBLIC ${RAT_INCDIRS})
