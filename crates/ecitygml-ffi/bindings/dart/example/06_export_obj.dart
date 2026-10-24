// Exports the building geometry of a CityGML file to a Wavefront OBJ file.
//
// Shows how to get triangles out of CityGML geometry for your own file format or renderer:
// `triangulate()` turns a multi surface or solid into a `Triangulation`, whose `surface()` is a
// triangulated surface; each `Triangle` has its corners `a()`, `b()` and `c()`. Every wall, roof and
// ground surface, door and window becomes a named OBJ group, using its highest level of detail;
// buildings without such surfaces fall back to their highest LoD solid.
//
// Usage: dart run example/06_export_obj.dart input.gml output.obj
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml:
//
//     Wrote 48 vertices, 16 triangles, 7 groups

import 'dart:io';

import 'package:ecitygml/ecitygml.dart';

import 'common.dart';

/// Collects OBJ groups as they come: `g` starts a group, `v` adds a vertex, `f` a triangle of the
/// last three vertices (OBJ indices are 1-based and count all vertices written so far).
class ObjWriter {
  final lines = StringBuffer();
  int vertices = 0;
  int triangles = 0;
  int groups = 0;

  void writeGroup(String name, Triangulation triangulation) {
    lines.writeln('g $name');
    groups++;
    for (final triangle in items(triangulation.surface().triangles())) {
      for (final corner in [triangle.a(), triangle.b(), triangle.c()]) {
        lines.writeln(
          'v ${corner.x().toStringAsFixed(6)} ${corner.y().toStringAsFixed(6)} ${corner.z().toStringAsFixed(6)}',
        );
      }
      lines.writeln('f ${vertices + 1} ${vertices + 2} ${vertices + 3}');
      vertices += 3;
      triangles++;
    }
  }

  /// Writes a surface's multi surface (if any); throws if triangulation fails.
  void writeSurface(String name, MultiSurface? multiSurface) {
    if (multiSurface != null) writeGroup(name, multiSurface.triangulate());
  }
}

/// Writes a wall, roof or ground surface (its LoD3 to LoD0 multi surfaces) and its doors and windows
/// (`featureType()` names their type).
void writeSurfaceWithFillings(
  ObjWriter obj,
  String prefix,
  String type,
  String id,
  List<MultiSurfaceProperty?> lods,
  AbstractFillingSurfacePropertyIterator fillingSurfaces,
) {
  obj.writeSurface('${prefix}_${type}_$id', highestLod(lods));
  for (final property in items(fillingSurfaces)) {
    final filling = property.object();
    if (filling != null) {
      obj.writeSurface(
        '${prefix}_${filling.featureType()}_${filling.featureId().asStr()}',
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

void exportBuilding(ObjWriter obj, Building building) {
  final prefix = building.featureId().asStr();
  var hasSurfaces = false;
  for (final property in items(building.boundaries())) {
    final boundary = property.object();
    if (boundary == null) continue;
    final feature = AbstractFeatureKindRef.fromSpaceBoundary(boundary);
    final wall = WallSurface.tryFrom(feature);
    final roof = RoofSurface.tryFrom(feature);
    final ground = GroundSurface.tryFrom(feature);
    if (wall != null) {
      writeSurfaceWithFillings(obj, prefix, 'WallSurface', wall.featureId().asStr(), [
        wall.lod3MultiSurface(),
        wall.lod2MultiSurface(),
        wall.lod1MultiSurface(),
        wall.lod0MultiSurface(),
      ], wall.fillingSurfaces());
    } else if (roof != null) {
      writeSurfaceWithFillings(obj, prefix, 'RoofSurface', roof.featureId().asStr(), [
        roof.lod3MultiSurface(),
        roof.lod2MultiSurface(),
        roof.lod1MultiSurface(),
        roof.lod0MultiSurface(),
      ], roof.fillingSurfaces());
    } else if (ground != null) {
      writeSurfaceWithFillings(obj, prefix, 'GroundSurface', ground.featureId().asStr(), [
        ground.lod3MultiSurface(),
        ground.lod2MultiSurface(),
        ground.lod1MultiSurface(),
        ground.lod0MultiSurface(),
      ], ground.fillingSurfaces());
    } else {
      continue;
    }
    hasSurfaces = true;
  }
  if (hasSurfaces) return;
  for (final (lod, property) in [(3, building.lod3Solid()), (2, building.lod2Solid()), (1, building.lod1Solid())]) {
    final solid = property?.object();
    if (solid != null) {
      obj.writeGroup('${prefix}_LoD${lod}Solid', solid.triangulate());
      return;
    }
  }
}

void main(List<String> args) {
  final [inputPath, outputPath] = pathArguments(args, '06_export_obj', 'input.gml output.obj');
  final cityModel = readCityModel(inputPath);
  final obj = ObjWriter();
  try {
    for (final feature in items(cityModel.iterFeatures())) {
      final building = Building.tryFrom(feature);
      if (building != null) exportBuilding(obj, building);
    }
  } on Error catch (error) {
    fail(error);
  }
  try {
    File(outputPath).writeAsStringSync(obj.lines.toString());
  } on FileSystemException catch (error) {
    stderr.writeln('error: ${error.message}: ${error.path}');
    exit(1);
  }
  print('Wrote ${obj.vertices} vertices, ${obj.triangles} triangles, ${obj.groups} groups');
}
