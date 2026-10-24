// Measures the geometry of every building in a CityGML file: areas and triangle counts of its wall,
// roof and ground surfaces, its doors and windows, and the volumes of its solids.
//
// Geometry calculations work on the geometry stored inline: `area3d()` of a multi surface,
// `volume3d()` of a solid, `triangulate()` (a `Triangulation`, whose `surface()` holds the triangles).
// They throw the ecitygml `Error` when they can't compute a result. A common case: a solid whose
// surfaces only reference the boundary polygons by `xlink:href` (the reader doesn't resolve such
// references, as in Rust), shown here as "not computable" with the error message.
//
// Usage: dart run example/05_measure_geometry.dart path/to/model.gml
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//
//     Building UUID_d281adfc-4901-0f52-540b-4cc1a9325f82
//       WallSurface: 4, area 188.629 m^2, 10 triangles
//       RoofSurface: 2, area 138.564 m^2, 4 triangles
//       GroundSurface: 1, area 120.000 m^2, 2 triangles
//       Doors and windows: 0, area 0.000 m^2
//       LoD2 solid: 7 surfaces, 7 of them xlink:href references
//         Volume: not computable (surface member references '#PolyID7350_878_759628_120742' via ...)

import 'package:ecitygml/ecitygml.dart';

import 'common.dart';

class Measurement {
  int count = 0;
  double area = 0;
  int triangles = 0;

  /// Adds a surface with its highest LoD multi surface; throws if a calculation fails.
  void add(MultiSurface? multiSurface) {
    count++;
    if (multiSurface == null) return;
    area += multiSurface.area3d();
    triangles += items(multiSurface.triangulate().surface().triangles()).length;
  }
}

/// Adds a wall, roof or ground surface (its LoD3 to LoD0 multi surfaces), and its doors and windows to `fillings`.
void addSurface(
  List<MultiSurfaceProperty?> lods,
  AbstractFillingSurfacePropertyIterator fillingSurfaces,
  Measurement measurement,
  Measurement fillings,
) {
  measurement.add(highestLod(lods));
  for (final property in items(fillingSurfaces)) {
    final filling = property.object();
    if (filling != null) {
      fillings.add(
        highestLod([
          filling.lod3MultiSurface(),
          filling.lod2MultiSurface(),
          filling.lod1MultiSurface(),
          filling.lod0MultiSurface(),
        ]),
      );
    }
  }
}

void printBoundaries(Building building) {
  final (walls, roofs, grounds, fillings) = (Measurement(), Measurement(), Measurement(), Measurement());
  for (final property in items(building.boundaries())) {
    final boundary = property.object();
    if (boundary == null) continue;
    final feature = AbstractFeatureKindRef.fromSpaceBoundary(boundary);
    // Dart has no union types: each surface type passes its own getters.
    final wall = WallSurface.tryFrom(feature);
    final roof = RoofSurface.tryFrom(feature);
    final ground = GroundSurface.tryFrom(feature);
    if (wall != null) {
      addSurface(
        [wall.lod3MultiSurface(), wall.lod2MultiSurface(), wall.lod1MultiSurface(), wall.lod0MultiSurface()],
        wall.fillingSurfaces(),
        walls,
        fillings,
      );
    } else if (roof != null) {
      addSurface(
        [roof.lod3MultiSurface(), roof.lod2MultiSurface(), roof.lod1MultiSurface(), roof.lod0MultiSurface()],
        roof.fillingSurfaces(),
        roofs,
        fillings,
      );
    } else if (ground != null) {
      addSurface(
        [ground.lod3MultiSurface(), ground.lod2MultiSurface(), ground.lod1MultiSurface(), ground.lod0MultiSurface()],
        ground.fillingSurfaces(),
        grounds,
        fillings,
      );
    }
  }
  for (final (label, measurement) in [('WallSurface', walls), ('RoofSurface', roofs), ('GroundSurface', grounds)]) {
    print('  $label: ${measurement.count}, area ${fixed(measurement.area)} m^2, ${measurement.triangles} triangles');
  }
  print('  Doors and windows: ${fillings.count}, area ${fixed(fillings.area)} m^2');
}

void printSolids(Building building) {
  for (final (lod, property) in [(1, building.lod1Solid()), (2, building.lod2Solid()), (3, building.lod3Solid())]) {
    final solid = property?.object();
    if (solid == null) continue;
    final shell = solid.exterior();
    final members = shell == null ? <AbstractSurfaceProperty>[] : items(shell.members()).toList();
    final references = members.where((member) => member.object() == null).length;
    print('  LoD$lod solid: ${members.length} surfaces, $references of them xlink:href references');
    String volume;
    try {
      volume = '${fixed(solid.volume3d())} m^3';
    } on Error catch (error) {
      volume = 'not computable (${error.message()})';
    }
    print('    Volume: $volume');
  }
}

void main(List<String> args) {
  final cityModel = readCityModel(pathArgument(args, '05_measure_geometry'));
  final buildings = items(cityModel.iterFeatures()).map(Building.tryFrom).nonNulls.toList();
  if (buildings.isEmpty) {
    print('No buildings.');
  }
  for (final (index, building) in buildings.indexed) {
    if (index > 0) print('');
    print('Building ${building.featureId().asStr()}');
    try {
      printBoundaries(building);
    } on Error catch (error) {
      // e.g. a surface that can't be triangulated
      print('  Boundaries: not computable (${error.message()})');
    }
    printSolids(building);
  }
}
