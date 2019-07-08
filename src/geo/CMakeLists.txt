###########################################################
# CMakeLists for geo module

add_library(geo STATIC
        src/BWVetGenericChamber.cc
        src/BWVetGenericChamberHit.cc
        src/ConeWaveguideConstruction.cc
        src/ConeWaveguideFactory.cc
        src/DetectorConstruction.cc
        src/DetectorFactory.cc
        src/GLG4BoxSD.cc
        src/GLG4PMTSD.cc
        src/GLG4TestSolid.cc
        src/GLG4TorusStack.cc
        src/GeoBoxFactory.cc
        src/GeoBubbleFactory.cc
        src/GeoBuilder.cc
        src/GeoConvexLensFactory.cc
        src/GeoCutTubeFactory.cc
        src/GeoFactory.cc
        src/GeoLensFactory.cc
        src/GeoPMTArrayFactory.cc
        src/GeoPMTCoverageFactory.cc
        src/GeoPMTFactoryBase.cc
        src/GeoPMTParser.cc
        src/GeoPerfBoxFactory.cc
        src/GeoPerfSphereFactory.cc
        src/GeoPerfTubeFactory.cc
        src/GeoPolygonFactory.cc
        src/GeoReflectorFactory.cc
        src/GeoReflectorWaveguideFactory.cc
        src/GeoRevArrayFactory.cc
        src/GeoRevolutionChimneyFactory.cc
        src/GeoRevolutionFactory.cc
        src/GeoSolidArrayFactoryBase.cc
        src/GeoSolidFactory.cc
        src/GeoSphereFactory.cc
        src/GeoSurfaceFactory.cc
        src/GeoTorusFactory.cc
        src/GeoTubeArrayFactory.cc
        src/GeoTubeFactory.cc
        src/GeoTubeIntersectionFactory.cc
        src/GeoWatchmanShieldFactory.cc
        src/GeoWaterBoxArrayFactory.cc
        src/Materials.cc
        src/PMTConcentrator.cc
        src/PMTConstruction.cc
        src/TheiaDetectorFactory.cc
        src/TubeFacetSolid.cc
        src/UnionSolidArray.cc
        src/WatchmanDetectorFactory.cc
        src/WaterBoxConstruction.cc)

# Set our include directories
target_include_directories(geo PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include)

# Link necessary dependencies
target_link_libraries(geo PUBLIC cmd core db ds physics stlplus util)

# Copy our headers when installing
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/RAT
        DESTINATION include)
