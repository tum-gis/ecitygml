"""Measures the geometry of every building in a CityGML file: areas and triangle counts of its wall,
roof and ground surfaces, its doors and windows, and the volumes of its solids.

Geometry calculations work on the geometry stored inline: `area_3d()` of a multi surface,
`volume_3d()` of a solid, `triangulate()` (a `Triangulation`, whose `surface()` holds the
triangles). They raise when they can't compute a result. A common case: a solid whose surfaces only
reference the boundary polygons by `xlink:href` (the reader doesn't resolve such references, as in
Rust), shown here as "not computable" with the error message.

Usage: python examples/05_measure_geometry.py path/to/model.gml

Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml (shortened):

    Building UUID_d281adfc-4901-0f52-540b-4cc1a9325f82
      WallSurface: 4, area 188.629 m^2, 10 triangles
      RoofSurface: 2, area 138.564 m^2, 4 triangles
      GroundSurface: 1, area 120.000 m^2, 2 triangles
      Doors and windows: 0, area 0.000 m^2
      LoD2 solid: 7 surfaces, 7 of them xlink:href references
        Volume: not computable (surface member references '#PolyID7350_878_759628_120742' via ...)
"""

import sys
from typing import Any

from ecitygml import AbstractFeatureKindRef, Building, GmlReader, GroundSurface, RoofSurface, WallSurface


def highest_lod_multi_surface(surface: Any) -> Any:
    """The multi surface of the highest level of detail a thematic surface has, or None."""
    for prop in (surface.lod3_multi_surface(), surface.lod2_multi_surface(), surface.lod1_multi_surface(),
                 surface.lod0_multi_surface()):
        if prop is not None and prop.object() is not None:
            return prop.object()
    return None


def area_and_triangles(surface: Any) -> tuple[float, int]:
    """The area and triangle count of a surface's highest LoD multi surface (0 if it has none)."""
    multi_surface = highest_lod_multi_surface(surface)
    if multi_surface is None:
        return 0.0, 0
    triangles = sum(1 for _ in multi_surface.triangulate().surface().triangles())
    return multi_surface.area_3d(), triangles


def print_boundaries(building: Building) -> None:
    for label, cls in [("WallSurface", WallSurface), ("RoofSurface", RoofSurface), ("GroundSurface", GroundSurface)]:
        count, area, triangles = 0, 0.0, 0
        for boundary_property in building.boundaries():
            boundary = boundary_property.object()
            surface = None if boundary is None else cls.try_from(AbstractFeatureKindRef.from_space_boundary(boundary))
            if surface is None:
                continue
            surface_area, surface_triangles = area_and_triangles(surface)
            count, area, triangles = count + 1, area + surface_area, triangles + surface_triangles
        print(f"  {label}: {count}, area {area:.3f} m^2, {triangles} triangles")

    # Doors and windows are the filling surfaces of wall, roof and ground surfaces.
    fillings, filling_area = 0, 0.0
    for boundary_property in building.boundaries():
        boundary = boundary_property.object()
        if boundary is None:
            continue
        feature = AbstractFeatureKindRef.from_space_boundary(boundary)
        surface = WallSurface.try_from(feature) or RoofSurface.try_from(feature) or GroundSurface.try_from(feature)
        if surface is None:
            continue
        for filling_property in surface.filling_surfaces():
            if (filling := filling_property.object()) is not None:
                fillings += 1
                filling_area += area_and_triangles(filling)[0]
    print(f"  Doors and windows: {fillings}, area {filling_area:.3f} m^2")


def print_solids(building: Building) -> None:
    for lod, prop in [(1, building.lod1_solid()), (2, building.lod2_solid()), (3, building.lod3_solid())]:
        solid = None if prop is None else prop.object()
        if solid is None:
            continue
        shell = solid.exterior()
        members = [] if shell is None else list(shell.members())
        references = sum(1 for member in members if member.object() is None)
        print(f"  LoD{lod} solid: {len(members)} surfaces, {references} of them xlink:href references")
        try:
            print(f"    Volume: {solid.volume_3d():.3f} m^3")
        except Exception as error:  # the bindings raise Exception(Error); str() is its message
            print(f"    Volume: not computable ({error})")


def main() -> int:
    if len(sys.argv) != 2:
        print("usage: 05_measure_geometry path/to/model.gml", file=sys.stderr)
        return 2
    try:
        city_model = GmlReader.from_path(sys.argv[1]).finish()
    except Exception as error:  # the bindings raise Exception(Error); str() is its message
        print(f"error: {error}", file=sys.stderr)
        return 1

    buildings = [b for f in city_model.iter_features() if (b := Building.try_from(f)) is not None]
    if not buildings:
        print("No buildings.")
    for index, building in enumerate(buildings):
        if index > 0:
            print()
        print(f"Building {building.feature_id().as_str()}")
        try:
            print_boundaries(building)
        except Exception as error:  # e.g. a surface that can't be triangulated
            print(f"  Boundaries: not computable ({error})")
        print_solids(building)
    return 0


if __name__ == "__main__":
    sys.exit(main())
