#include <ecitygml/AbstractCityObjectKind.hpp>
#include <ecitygml/AbstractCityObjectKindRef.hpp>
#include <ecitygml/AbstractCityObjectProperty.hpp>
#include <ecitygml/AbstractCityObjectPropertyIterator.hpp>
#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/Building.hpp>
#include <ecitygml/CityModel.hpp>
#include <ecitygml/ElevationReferenceValue.hpp>
#include <ecitygml/Error.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/Height.hpp>
#include <ecitygml/HeightIterator.hpp>
#include <ecitygml/HeightStatusValue.hpp>
#include <ecitygml/Length.hpp>

#include <cstdio>

int main(int argc, char** argv) {
    const char* path = argc > 1 ? argv[1] : "model.gml";

    // Parse the CityGML document into the in-memory city model
    auto reader = ecitygml::GmlReader::from_path(path);
    if (!reader.is_ok()) return 1;
    auto city_model = std::move(reader).ok().value()->finish();
    if (!city_model.is_ok()) return 1;
    auto model = std::move(city_model).ok().value();

    // Sum up the measured heights of the top-level buildings; only heights
    // from the lowest ground point to the top of construction given in
    // meters are taken into account
    double total_height = 0.0;
    auto members = model->city_object_members();
    while (const auto* member = members->next()) {
        const auto* city_object = member->object();
        if (!city_object) continue;
        auto city_object_ref =
            ecitygml::AbstractCityObjectKindRef::from_city_object(*city_object);
        auto feature = ecitygml::AbstractFeatureKindRef::from_city_object(
            *city_object_ref);
        const auto* building = ecitygml::Building::try_from(*feature);
        if (!building) continue;
        auto heights = building->heights();
        while (const auto* height = heights->next()) {
            if (height->low_reference().value() == "lowestGroundPoint" &&
                height->high_reference().value() == "topOfConstruction" &&
                height->status() == ecitygml::HeightStatusValue::Measured &&
                height->length().uom() == "urn:adv:uom:m") {
                total_height += height->length().value();
            }
        }
    }

    std::printf("Total measured height of buildings: %.3f m\n", total_height);
}
