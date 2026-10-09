"""Exports the building geometry of a CityGML file to a Wavefront OBJ file.

Shows how to get triangles out of CityGML geometry for your own file format or renderer:
`triangulate()` turns a multi surface or solid into a `Triangulation`, whose `surface()` is a
triangulated surface; each `Triangle` has its corners `a()`, `b()` and `c()`. Every wall, roof and
ground surface, door and window becomes a named OBJ group, using its highest level of detail;
buildings without such surfaces fall back to their highest LoD solid.

Usage: python examples/06_export_obj.py input.gml output.obj

Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml:

    Wrote 48 vertices, 16 triangles, 7 groups
"""

import sys
from typing import IO, Any

from ecitygml import AbstractFeatureKindRef, Building, GmlReader, GroundSurface, RoofSurface, WallSurface


class ObjWriter:
    """Writes OBJ groups as they come: `g` starts a group, `v` adds a vertex, `f` a triangle of the
    last three vertices (OBJ indices are 1-based and count all vertices written so far)."""

    def __init__(self, file: IO[str]) -> None:
        self.file = file
        self.vertices = 0
        self.triangles = 0
        self.groups = 0

    def write_group(self, name: str, geometry: Any) -> None:
        """Writes the triangles of anything with `triangulate()`, e.g. a multi surface or solid."""
        self.file.write(f"g {name}\n")
        self.groups += 1
        for triangle in geometry.triangulate().surface().triangles():
            for corner in (triangle.a(), triangle.b(), triangle.c()):
                self.file.write(f"v {corner.x():.6f} {corner.y():.6f} {corner.z():.6f}\n")
            self.file.write(f"f {self.vertices + 1} {self.vertices + 2} {self.vertices + 3}\n")
            self.vertices += 3
            self.triangles += 1


def highest_lod_multi_surface(surface: Any) -> Any:
    """The multi surface of the highest level of detail a thematic surface has, or None."""
    for prop in (surface.lod3_multi_surface(), surface.lod2_multi_surface(), surface.lod1_multi_surface(),
                 surface.lod0_multi_surface()):
        if prop is not None and prop.object() is not None:
            return prop.object()
    return None


def write_surface(obj: ObjWriter, prefix: str, surface: Any, type_name: str) -> None:
    if (multi_surface := highest_lod_multi_surface(surface)) is not None:
        obj.write_group(f"{prefix}_{type_name}_{surface.feature_id().as_str()}", multi_surface)


def export_building(obj: ObjWriter, building: Building) -> None:
    prefix = building.feature_id().as_str()
    has_surfaces = False
    for boundary_property in building.boundaries():
        boundary = boundary_property.object()
        if boundary is None:
            continue
        feature = AbstractFeatureKindRef.from_space_boundary(boundary)
        for type_name, cls in [("WallSurface", WallSurface), ("RoofSurface", RoofSurface), ("GroundSurface", GroundSurface)]:
            if (surface := cls.try_from(feature)) is None:
                continue
            has_surfaces = True
            write_surface(obj, prefix, surface, type_name)
            # Doors and windows: `feature_type()` names their type.
            for filling_property in surface.filling_surfaces():
                if (filling := filling_property.object()) is not None:
                    filling_type = repr(filling.feature_type()).removeprefix("FeatureType.")
                    write_surface(obj, prefix, filling, filling_type)
    if has_surfaces:
        return
    for lod, prop in [(3, building.lod3_solid()), (2, building.lod2_solid()), (1, building.lod1_solid())]:
        if prop is not None and prop.object() is not None:
            obj.write_group(f"{prefix}_LoD{lod}Solid", prop.object())
            return


def main() -> int:
    if len(sys.argv) != 3:
        print("usage: 06_export_obj input.gml output.obj", file=sys.stderr)
        return 2
    try:
        city_model = GmlReader.from_path(sys.argv[1]).finish()
        with open(sys.argv[2], "w", encoding="utf-8") as file:
            obj = ObjWriter(file)
            for feature in city_model.iter_features():
                if (building := Building.try_from(feature)) is not None:
                    export_building(obj, building)
    except Exception as error:  # the bindings raise Exception(Error); str() is its message
        print(f"error: {error}", file=sys.stderr)
        return 1
    print(f"Wrote {obj.vertices} vertices, {obj.triangles} triangles, {obj.groups} groups")
    return 0


if __name__ == "__main__":
    sys.exit(main())
