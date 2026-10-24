// The cases of crates/ecitygml/tests/conformance/kit-bruecke.md.
#include "conformance/conformance.hpp"

#include <ecitygml/AbstractCityObjectKindRef.hpp>
#include <ecitygml/AbstractCityObjectKindRefIterator.hpp>
#include <ecitygml/AbstractSurfacePropertyIterator.hpp>
#include <ecitygml/BoundingShape.hpp>
#include <ecitygml/Bridge.hpp>
#include <ecitygml/BridgeFunctionValueIterator.hpp>
#include <ecitygml/BridgePartPropertyIterator.hpp>
#include <ecitygml/BridgeUsageValueIterator.hpp>
#include <ecitygml/CitygmlFormat.hpp>
#include <ecitygml/DirectPosition.hpp>
#include <ecitygml/Envelope.hpp>
#include <ecitygml/ExternalReferenceIterator.hpp>
#include <ecitygml/FeatureType.hpp>
#include <ecitygml/GenericAttributeKindIterator.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/GmlWriter.hpp>
#include <ecitygml/HeightIterator.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/OccupancyIterator.hpp>
#include <ecitygml/TriangleIterator.hpp>
#include <ecitygml/TriangulatedSurface.hpp>
#include <ecitygml/Triangulation.hpp>

#include <array>
#include <string>
#include <utility>
#include <vector>

using conformance::close;
using conformance::features;
using ecitygml::FeatureType;

namespace {
const std::string DATASET = "kit-bruecke";
const std::string BRIDGE = "Modellbahnbruecke-LoD2-V03__v3.gml";
const std::string BRIDGE_ID = "_Modellbahnbruecke-LoD2-V03_BD.rx3tFkxPQkL5qDXML1W7";

/// The number of items of a Diplomat iterator.
template <typename Iterator>
int count(const std::unique_ptr<Iterator>& iterator) {
    int n = 0;
    while (iterator->next() != nullptr) {
        ++n;
    }
    return n;
}

/// The value of a successful result.
template <typename Result>
auto ok(Result result) {
    REQUIRE(result.is_ok());
    return std::move(result).ok().value();
}

void require_point_close(const ecitygml::DirectPosition& position, const std::array<double, 3>& expected) {
    REQUIRE_THAT(position.x(), close(expected[0]));
    REQUIRE_THAT(position.y(), close(expected[1]));
    REQUIRE_THAT(position.z(), close(expected[2]));
}

std::vector<FeatureType> feature_types(const ecitygml::CityModel& city_model) {
    std::vector<FeatureType> result;
    for (const auto& feature : features(city_model)) {
        result.push_back(feature->feature_type());
    }
    return result;
}

/// The city model's bridge; the model must outlive it.
const ecitygml::Bridge* bridge(const ecitygml::CityModel& city_model) {
    const auto* bridge = first<ecitygml::Bridge>(city_model);
    REQUIRE(bridge != nullptr);
    return bridge;
}
}  // namespace

TEST_CASE("Bridge city model", "[kit-bruecke]") {
    auto city_model = conformance::read(DATASET, BRIDGE);
    REQUIRE(city_model->city_objects_len() == 1);
    const auto* envelope = city_model->bounded_by()->envelope();
    require_point_close(envelope->lower_corner(), {457644.585, 5439126.455, 109.0});
    require_point_close(envelope->upper_corner(), {457708.084, 5439157.169, 124.3});
    std::vector<FeatureType> expected{FeatureType::CityModel, FeatureType::Bridge, FeatureType::Appearance};
    expected.insert(expected.end(), 3, FeatureType::ParameterizedTexture);
    expected.insert(expected.end(), 2, FeatureType::BridgeInstallation);
    expected.insert(expected.end(), 11, FeatureType::BridgeConstructiveElement);
    REQUIRE(feature_types(*city_model) == expected);
    REQUIRE(count(city_model->iter_city_objects()) == 14);
}

TEST_CASE("Bridge attributes", "[kit-bruecke]") {
    auto city_model = conformance::read(DATASET, BRIDGE);
    const auto* b = bridge(*city_model);
    REQUIRE(b->feature_id().as_str() == BRIDGE_ID);
    REQUIRE(b->names()->next() == nullptr);
    REQUIRE(b->class_() == nullptr);
    REQUIRE(b->functions()->next() == nullptr);
    REQUIRE(b->usages()->next() == nullptr);
    REQUIRE(b->bridge_parts()->next() == nullptr);
    REQUIRE(b->boundaries()->next() == nullptr);
    REQUIRE(b->date_of_construction() == nullptr);
    REQUIRE(b->creation_date() == nullptr);
    REQUIRE(b->heights()->next() == nullptr);
    REQUIRE(b->occupancies()->next() == nullptr);
    REQUIRE(b->generic_attributes()->next() == nullptr);
    REQUIRE(b->external_references()->next() == nullptr);
}

TEST_CASE("Bridge geometry", "[kit-bruecke]") {
    auto city_model = conformance::read(DATASET, BRIDGE);
    const auto* b = bridge(*city_model);
    const auto* envelope = b->bounded_by()->envelope();
    require_point_close(envelope->lower_corner(), {457645.136, 5439126.692, 115.3});
    require_point_close(envelope->upper_corner(), {457707.533, 5439156.931, 116.2});
    const auto* property = b->lod2_multi_surface();
    REQUIRE(property != nullptr);
    REQUIRE(property->href() == nullptr);
    const auto* multi_surface = property->object();
    REQUIRE(multi_surface != nullptr);
    REQUIRE(count(multi_surface->surface_member()) == 18);
    REQUIRE_THAT(ok(multi_surface->area_3d()), close(795.4201811265907));
    auto triangulation = ok(multi_surface->triangulate());
    REQUIRE(count(triangulation->surface().triangles()) == 60);
    REQUIRE_FALSE(triangulation->has_skipped());
    REQUIRE(b->lod1_solid() == nullptr);
    REQUIRE(b->lod2_solid() == nullptr);
    REQUIRE(b->lod3_multi_surface() == nullptr);
}

TEST_CASE("Bridge round trip", "[kit-bruecke]") {
    auto city_model = conformance::read(DATASET, BRIDGE);
    auto writer = ecitygml::GmlWriter::create(ecitygml::CitygmlFormat::Gml);
    REQUIRE(writer->finish(*city_model).is_ok());
    auto written = ok(ecitygml::GmlReader::create(writer->data(), ecitygml::CitygmlFormat::Gml)->finish());
    REQUIRE(feature_types(*written) == feature_types(*city_model));
    REQUIRE(bridge(*written)->feature_id().as_str() == BRIDGE_ID);
}
