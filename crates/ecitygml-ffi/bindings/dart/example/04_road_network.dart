// Walks the road network of a CityGML file and measures it: centre-line lengths, traffic-area
// areas and the volumes of the traffic spaces.
//
// CityGML's transportation model is a hierarchy: a road consists of sections and intersections, which
// (like the road itself) hold traffic spaces and auxiliary traffic spaces (e.g. lanes and sidewalks).
// Each space is bounded by traffic areas or auxiliary traffic areas, its ground surfaces. The spaces
// are reached through properties (`object()`), the areas through the space's `boundaries()`,
// converted with `tryFrom`. Geometry calculations (`length3d`, `area3d`, `volume3d`) can fail, e.g.
// for degenerate geometry, and then throw the ecitygml `Error`.
//
// Usage: dart run example/04_road_network.dart path/to/model.gml
//
// Output for ASAM-UC_RoadShape.gml (shortened):
//
//     Road UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f
//       Section UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29
//         TrafficSpace UUID_ae81947d-a661-3678-a5ee-eed58b686946
//           Centre line (LoD2): 40.000 m
//           Volume (LoD2 solid): 720.000 m^3
//           TrafficArea UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2: 160.798 m^2
//         ...
//
//     Total volume of traffic spaces (LoD2): 1260.000 m^3

import 'package:ecitygml/ecitygml.dart';

import 'common.dart';

/// Counts and sums over all spaces of one kind (traffic or auxiliary traffic spaces).
class Totals {
  int spaces = 0;
  double length = 0;
  double volume = 0;
  int areas = 0;
  double area = 0;
}

/// A measurement as text (e.g. "40.000 m"), passed to `add`; "-" without geometry, and a note if the
/// calculation fails.
String measured<G extends Object>(G? geometry, double Function(G) measure, String unit, void Function(double) add) {
  if (geometry == null) return '-';
  try {
    final value = measure(geometry);
    add(value);
    return '${fixed(value)} $unit';
  } on Error catch (error) {
    return 'not computable (${error.message()})';
  }
}

/// A traffic or auxiliary traffic space: Dart has no union types, so the getters the example needs are
/// passed in as values.
void printSpace(
  String type,
  String id,
  MultiCurve? centreLine,
  Solid? solid,
  AbstractSpaceBoundaryPropertyIterator boundaries,
  Totals totals,
  String indent,
) {
  final isTrafficSpace = type == 'TrafficSpace';
  print('$indent$type $id');
  final length = measured(centreLine, (curve) => curve.length3d(), 'm', (value) => totals.length += value);
  final volume = measured(solid, (solid) => solid.volume3d(), 'm^3', (value) => totals.volume += value);
  print('$indent  Centre line (LoD2): $length');
  print('$indent  Volume (LoD2 solid): $volume');
  totals.spaces++;

  // The areas are the space's boundaries of the matching type.
  for (final property in items(boundaries)) {
    final boundary = property.object();
    if (boundary == null) continue;
    final feature = AbstractFeatureKindRef.fromSpaceBoundary(boundary);
    final area = isTrafficSpace ? trafficArea(feature) : auxiliaryTrafficArea(feature);
    if (area == null) continue;
    final (areaType, areaId, surface) = area;
    final text = measured(surface?.object(), (surface) => surface.area3d(), 'm^2', (value) => totals.area += value);
    print('$indent  $areaType $areaId: $text');
    totals.areas++;
  }
}

/// Type, id and LoD2 multi surface of a traffic area; null for other features.
(String, String, MultiSurfaceProperty?)? trafficArea(AbstractFeatureKindRef feature) {
  final area = TrafficArea.tryFrom(feature);
  return area == null ? null : ('TrafficArea', area.featureId().asStr(), area.lod2MultiSurface());
}

/// Type, id and LoD2 multi surface of an auxiliary traffic area; null for other features.
(String, String, MultiSurfaceProperty?)? auxiliaryTrafficArea(AbstractFeatureKindRef feature) {
  final area = AuxiliaryTrafficArea.tryFrom(feature);
  return area == null ? null : ('AuxiliaryTrafficArea', area.featureId().asStr(), area.lod2MultiSurface());
}

/// The traffic and auxiliary traffic spaces of a road, section or intersection.
void printSpaces(
  TrafficSpacePropertyIterator spaces,
  AuxiliaryTrafficSpacePropertyIterator auxiliarySpaces,
  Totals traffic,
  Totals auxiliary,
  String indent,
) {
  for (final property in items(spaces)) {
    final space = property.object();
    if (space == null) continue;
    printSpace(
      'TrafficSpace',
      space.featureId().asStr(),
      space.lod2MultiCurve()?.object(),
      space.lod2Solid()?.object(),
      space.boundaries(),
      traffic,
      indent,
    );
  }
  for (final property in items(auxiliarySpaces)) {
    final space = property.object();
    if (space == null) continue;
    printSpace(
      'AuxiliaryTrafficSpace',
      space.featureId().asStr(),
      space.lod2MultiCurve()?.object(),
      space.lod2Solid()?.object(),
      space.boundaries(),
      auxiliary,
      indent,
    );
  }
}

void main(List<String> args) {
  final cityModel = readCityModel(pathArgument(args, '04_road_network'));
  final traffic = Totals();
  final auxiliary = Totals();
  final roads = items(cityModel.iterFeatures()).map(Road.tryFrom).nonNulls.toList();
  for (final road in roads) {
    print('Road ${road.featureId().asStr()}');
    // A road can hold spaces directly, too.
    printSpaces(road.trafficSpaces(), road.auxiliaryTrafficSpaces(), traffic, auxiliary, '  ');
    for (final property in items(road.sections())) {
      final section = property.object();
      if (section == null) continue;
      print('  Section ${section.featureId().asStr()}');
      printSpaces(section.trafficSpaces(), section.auxiliaryTrafficSpaces(), traffic, auxiliary, '    ');
    }
    for (final property in items(road.intersections())) {
      final intersection = property.object();
      if (intersection == null) continue;
      print('  Intersection ${intersection.featureId().asStr()}');
      printSpaces(intersection.trafficSpaces(), intersection.auxiliaryTrafficSpaces(), traffic, auxiliary, '    ');
    }
  }

  print('');
  print('Roads: ${roads.length}');
  for (final (label, totals) in [('Traffic spaces', traffic), ('Auxiliary traffic spaces', auxiliary)]) {
    print(
      '$label: ${totals.spaces}, centre lines ${fixed(totals.length)} m, ${totals.areas} areas '
      '${fixed(totals.area)} m^2, volume ${fixed(totals.volume)} m^3',
    );
  }
  print('Total volume of traffic spaces (LoD2): ${fixed(traffic.volume)} m^3');
}
