#include "test_helpers.hpp"

#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <ecitygml/AbstractCityObjectKindRef.hpp>
#include <ecitygml/AbstractCityObjectKindRefIterator.hpp>
#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/BoundingShape.hpp>
#include <ecitygml/DateTime.hpp>
#include <ecitygml/Envelope.hpp>
#include <ecitygml/FeatureType.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/Road.hpp>
#include <ecitygml/Scale3.hpp>
#include <ecitygml/Vector3.hpp>
#include <ecitygml/WallSurface.hpp>

#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

using Catch::Matchers::StartsWith;
using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

TEST_CASE("CityModel bounded_by", "[city_model]") {
    auto city_model = read(fixture("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"));
    const auto* bounding_shape = city_model->bounded_by();
    REQUIRE(bounding_shape != nullptr);
    const auto* envelope = bounding_shape->envelope();
    REQUIRE(envelope != nullptr);
    REQUIRE(envelope->size_x() == 12.0);
    REQUIRE(envelope->size_y() == 10.0);
    REQUIRE_THAT(envelope->size_z(), WithinAbs(6.517669, 1e-9));
}

TEST_CASE("CityModel feature_id", "[city_model]") {
    // Without gml:id, the reader generates one.
    auto generated = read(fixture("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"));
    REQUIRE_THAT(std::string(generated->feature_id().as_str()), StartsWith("ecitygml-gen-feature-"));

    auto explicit_id = read_modified("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml", "<CityModel ", "<CityModel gml:id=\"CM_1\" ");
    REQUIRE(explicit_id->feature_id().as_str() == "CM_1");
}

TEST_CASE("CityModel gml id and names", "[city_model]") {
    auto city_model = read(fixture("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"));
    auto names = city_model->names();
    const auto* name = names->next();
    REQUIRE(name != nullptr);
    REQUIRE(name->value() == "AC14-FZK-Haus");
    REQUIRE_FALSE(name->code_space().has_value());
    REQUIRE(names->next() == nullptr);

    auto with_id = read_modified("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml", "<CityModel ", "<CityModel gml:id=\"CM_gml\" ");
    REQUIRE(with_id->id() != nullptr);
    REQUIRE(with_id->id()->as_str() == "CM_gml");
}

TEST_CASE("CityModel lifespan", "[city_model]") {
    auto city_model = read_modified("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml", "</gml:boundedBy>",
                                    "</gml:boundedBy>\n  <creationDate>2017-01-23T00:00:00+01:00</creationDate>");
    const auto* creation_date = city_model->creation_date();
    REQUIRE(creation_date != nullptr);
    REQUIRE(creation_date->to_rfc3339() == "2017-01-23T00:00:00+01:00");
    REQUIRE(creation_date->timestamp() == 1485126000);
    REQUIRE(creation_date->offset_seconds() == 3600);
    REQUIRE(city_model->valid_to() == nullptr);
}

TEST_CASE("CityModel iter_features", "[city_model]") {
    auto city_model = read(fixture("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"));
    std::vector<ecitygml::FeatureType> types;
    auto features = city_model->iter_features();
    while (auto feature = features->next()) {
        types.push_back(feature->feature_type());
    }
    REQUIRE(std::find(types.begin(), types.end(), ecitygml::FeatureType::Building) != types.end());
}

TEST_CASE("CityModel iter_city_objects", "[city_model]") {
    auto city_model = read(fixture("FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml"));
    std::vector<ecitygml::FeatureType> types;
    auto city_objects = city_model->iter_city_objects();
    while (auto city_object = city_objects->next()) {
        types.push_back(city_object->feature_type());
    }
    REQUIRE(std::count(types.begin(), types.end(), ecitygml::FeatureType::CityModel) == 0);
    REQUIRE(std::count(types.begin(), types.end(), ecitygml::FeatureType::Building) == 1);
    REQUIRE(std::count(types.begin(), types.end(), ecitygml::FeatureType::WallSurface) == 4);

    // FZK LoD2: the building, 4 walls, 2 roofs and the ground.
    auto lod2 = read(fixture("FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml"));
    std::size_t lod2_count = 0;
    auto lod2_city_objects = lod2->iter_city_objects();
    while (lod2_city_objects->next()) {
        ++lod2_count;
    }
    REQUIRE(lod2_count == 8);

    auto junction = read(fixture("ASAM-Ex_Bidirectional_Junction.gml"));
    auto first = junction->iter_city_objects()->next();
    auto feature = ecitygml::AbstractFeatureKindRef::from_city_object(*first);
    REQUIRE(ecitygml::Road::try_from(*feature)->feature_id().as_str() == "UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f");
}

TEST_CASE("Wall surface found by id and its bounded_by", "[city_model]") {
    const std::string wall_id = "GML_5856d7ad-5e34-498a-817b-9544bfbb1475";
    auto city_model = read(fixture("FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml"));
    const auto find_wall = [&](const std::string& id) -> const ecitygml::WallSurface* {
        auto features = city_model->iter_features();
        while (auto feature = features->next()) {
            const auto* wall = ecitygml::WallSurface::try_from(*feature);
            if (wall != nullptr && wall->feature_id().as_str() == id) {
                return wall;
            }
        }
        return nullptr;
    };

    const auto* wall = find_wall(wall_id);
    REQUIRE(wall != nullptr);
    const auto* envelope = wall->bounded_by()->envelope();
    REQUIRE(envelope != nullptr);
    REQUIRE_THAT(envelope->size_x(), WithinAbs(0.0, 0.001));
    REQUIRE_THAT(envelope->size_y(), WithinRel(10.0, 0.001));
    REQUIRE_THAT(envelope->size_z(), WithinRel(6.51769, 0.001));

    REQUIRE(find_wall("missing") == nullptr);
}

TEST_CASE("CityModel recompute_child_bounding_shapes", "[city_model]") {
    auto reader = std::move(ecitygml::GmlReader::from_path(fixture("FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml")).ok().value());
    reader->with_rebuild_object_bounds(false);
    auto city_model = std::move(reader->finish().ok().value());
    const auto wall_bounded = [&] {
        auto features = city_model->iter_features();
        while (auto feature = features->next()) {
            if (const auto* wall = ecitygml::WallSurface::try_from(*feature)) {
                return wall->bounded_by() != nullptr;
            }
        }
        return false;
    };
    REQUIRE(!wall_bounded());
    city_model->recompute_child_bounding_shapes();
    REQUIRE(wall_bounded());
}

TEST_CASE("CityModel apply_translation and apply_scale", "[city_model]") {
    auto city_model = read(fixture("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"));
    const auto* envelope = city_model->bounded_by()->envelope();
    const double x = envelope->lower_corner().x();
    const double y = envelope->lower_corner().y();
    const double z = envelope->lower_corner().z();

    city_model->apply_translation(ecitygml::Vector3{-100.0, 200.0, 10.0});
    envelope = city_model->bounded_by()->envelope();
    REQUIRE_THAT(envelope->lower_corner().x(), Catch::Matchers::WithinAbs(x - 100.0, 1e-6));
    REQUIRE_THAT(envelope->lower_corner().y(), Catch::Matchers::WithinAbs(y + 200.0, 1e-6));
    REQUIRE_THAT(envelope->lower_corner().z(), Catch::Matchers::WithinAbs(z + 10.0, 1e-6));

    city_model->apply_scale(ecitygml::Scale3{2.0, 3.0, 0.5});
    envelope = city_model->bounded_by()->envelope();
    REQUIRE_THAT(envelope->size_x(), Catch::Matchers::WithinAbs(24.0, 1e-6));
    REQUIRE_THAT(envelope->size_y(), Catch::Matchers::WithinAbs(30.0, 1e-6));
    REQUIRE_THAT(envelope->size_z(), Catch::Matchers::WithinAbs(6.517669 / 2.0, 1e-6));
}
