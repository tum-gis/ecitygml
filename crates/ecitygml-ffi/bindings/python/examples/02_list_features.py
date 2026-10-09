"""Lists the feature types of a CityGML file with their counts, and the ids of its buildings.

A city model is a tree of features: the city model, buildings, their wall surfaces, the doors in
those walls, and so on. `iter_features()` visits all of them, depth first in document order, as
`AbstractFeatureKindRef`s. Each tells its `feature_type()`; to use the getters of its concrete
type, convert it with that type's `try_from`, which returns `None` for other types.

Usage: python examples/02_list_features.py path/to/model.gml

Output for FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml (shortened):

    Feature type              Count
    CityModel                     1
    Building                      1
    WallSurface                   4
    ...
    Total                        22

    Buildings:
      UUID_d281adfc-4901-0f52-540b-4cc1a9325f82
"""

import sys

from ecitygml import Building, GmlReader


def main() -> int:
    if len(sys.argv) != 2:
        print("usage: 02_list_features path/to/model.gml", file=sys.stderr)
        return 2
    try:
        city_model = GmlReader.from_path(sys.argv[1]).finish()
    except Exception as error:  # the bindings raise Exception(Error); str() is its message
        print(f"error: {error}", file=sys.stderr)
        return 1

    # Count the features per type, in the order the types first appear. Diplomat's Python enums
    # have no methods, so the type's name comes from its repr ("FeatureType.Building").
    counts: dict[str, int] = {}
    for feature in city_model.iter_features():
        name = repr(feature.feature_type()).removeprefix("FeatureType.")
        counts[name] = counts.get(name, 0) + 1

    print(f"{'Feature type':<24} {'Count':>6}")
    for name, count in counts.items():
        print(f"{name:<24} {count:>6}")
    print(f"{'Total':<24} {sum(counts.values()):>6}")

    # `Building.try_from` turns a feature into a `Building` (or None). The building borrows from
    # the city model: keep `city_model` referenced while using it.
    print()
    print("Buildings:")
    for feature in city_model.iter_features():
        if (building := Building.try_from(feature)) is not None:
            print(f"  {building.feature_id().as_str()}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
