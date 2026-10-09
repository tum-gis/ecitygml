#ifndef FeatureType_D_H
#define FeatureType_D_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "diplomat_runtime.h"





typedef enum FeatureType {
  FeatureType_Appearance = 0,
  FeatureType_AuxiliaryTrafficArea = 1,
  FeatureType_AuxiliaryTrafficSpace = 2,
  FeatureType_Bridge = 3,
  FeatureType_BridgeConstructiveElement = 4,
  FeatureType_BridgeFurniture = 5,
  FeatureType_BridgeInstallation = 6,
  FeatureType_BridgePart = 7,
  FeatureType_BridgeRoom = 8,
  FeatureType_Building = 9,
  FeatureType_BuildingConstructiveElement = 10,
  FeatureType_BuildingFurniture = 11,
  FeatureType_BuildingInstallation = 12,
  FeatureType_BuildingPart = 13,
  FeatureType_BuildingRoom = 14,
  FeatureType_BuildingUnit = 15,
  FeatureType_CeilingSurface = 16,
  FeatureType_CityFurniture = 17,
  FeatureType_CityModel = 18,
  FeatureType_CityObjectGroup = 19,
  FeatureType_ClearanceSpace = 20,
  FeatureType_ClosureSurface = 21,
  FeatureType_Door = 22,
  FeatureType_DoorSurface = 23,
  FeatureType_FloorSurface = 24,
  FeatureType_GenericLogicalSpace = 25,
  FeatureType_GenericOccupiedSpace = 26,
  FeatureType_GenericThematicSurface = 27,
  FeatureType_GenericUnoccupiedSpace = 28,
  FeatureType_GeoreferencedTexture = 29,
  FeatureType_GroundSurface = 30,
  FeatureType_Hole = 31,
  FeatureType_HoleSurface = 32,
  FeatureType_HollowSpace = 33,
  FeatureType_InteriorWallSurface = 34,
  FeatureType_Intersection = 35,
  FeatureType_LandUse = 36,
  FeatureType_Marking = 37,
  FeatureType_OtherConstruction = 38,
  FeatureType_OuterCeilingSurface = 39,
  FeatureType_OuterFloorSurface = 40,
  FeatureType_ParameterizedTexture = 41,
  FeatureType_PlantCover = 42,
  FeatureType_PointCloud = 43,
  FeatureType_Railway = 44,
  FeatureType_ReliefFeature = 45,
  FeatureType_Road = 46,
  FeatureType_RoofSurface = 47,
  FeatureType_Section = 48,
  FeatureType_SolitaryVegetationObject = 49,
  FeatureType_Square = 50,
  FeatureType_Storey = 51,
  FeatureType_TinRelief = 52,
  FeatureType_Track = 53,
  FeatureType_TrafficArea = 54,
  FeatureType_TrafficSpace = 55,
  FeatureType_Tunnel = 56,
  FeatureType_TunnelConstructiveElement = 57,
  FeatureType_TunnelFurniture = 58,
  FeatureType_TunnelInstallation = 59,
  FeatureType_TunnelPart = 60,
  FeatureType_WallSurface = 61,
  FeatureType_WaterBody = 62,
  FeatureType_WaterGroundSurface = 63,
  FeatureType_WaterSurface = 64,
  FeatureType_Waterway = 65,
  FeatureType_Window = 66,
  FeatureType_WindowSurface = 67,
  FeatureType_X3DMaterial = 68,
} FeatureType;

typedef struct FeatureType_option {union { FeatureType ok; }; bool is_ok; } FeatureType_option;



#endif // FeatureType_D_H
