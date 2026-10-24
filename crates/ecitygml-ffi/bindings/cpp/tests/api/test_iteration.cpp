// The cases of crates/ecitygml/tests/api/iteration.md.
#include "api.hpp"

#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>

#include <string>
#include <vector>

using ecitygml::FeatureType;

namespace {
const std::string FZK_LOD3 = "fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml";
const std::string ASAM_ROAD_SHAPE = "asam-opendrive/ASAM-UC_RoadShape.gml";
}  // namespace

TEST_CASE("Iterator exhausted", "[api][iteration]") {
    auto city_model = read(fixture(FZK_LOD3));
    auto iterator = city_model->iter_features();
    size_t count = 0;
    while (iterator->next() != nullptr) {
        ++count;
    }
    REQUIRE(count == 22);
    REQUIRE(iterator->next() == nullptr);
}

TEST_CASE("Iterator stopped early", "[api][iteration]") {
    auto city_model = read(fixture(ASAM_ROAD_SHAPE));
    {
        auto iterator = city_model->iter_features();
        auto first = iterator->next();
        REQUIRE(first != nullptr);
        REQUIRE(first->feature_type() == FeatureType::CityModel);
    }  // the feature and the iterator are destroyed here
    REQUIRE(feature_types(*city_model).size() == 11);
    REQUIRE(city_model->city_objects_len() == 1);
}

TEST_CASE("Iterators independent", "[api][iteration]") {
    auto city_model = read(fixture(FZK_LOD3));
    auto first = city_model->iter_features();
    auto second = city_model->iter_features();
    std::vector<FeatureType> a;
    std::vector<FeatureType> b;
    while (true) {
        auto x = first->next();
        auto y = second->next();
        REQUIRE((x == nullptr) == (y == nullptr));
        if (x == nullptr || y == nullptr) {
            break;
        }
        a.push_back(x->feature_type());
        b.push_back(y->feature_type());
    }
    REQUIRE(a.size() == 22);
    REQUIRE(a == b);
    REQUIRE(a == feature_types(*city_model));
}
