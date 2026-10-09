#include "test_helpers.hpp"

#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/Bridge.hpp>
#include <ecitygml/BridgeClassValue.hpp>
#include <ecitygml/BridgePart.hpp>
#include <ecitygml/BridgePartProperty.hpp>
#include <ecitygml/BridgePartPropertyIterator.hpp>
#include <ecitygml/CitygmlFormat.hpp>
#include <ecitygml/Code.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/Tunnel.hpp>
#include <ecitygml/TunnelFunctionValue.hpp>
#include <ecitygml/TunnelPart.hpp>
#include <ecitygml/TunnelPartProperty.hpp>
#include <ecitygml/TunnelPartPropertyIterator.hpp>

#include <cstdint>
#include <fstream>
#include <optional>
#include <memory>
#include <sstream>
#include <string>
#include <utility>


TEST_CASE("Bridge and bridge part", "[bridge]") {
    auto city_model = read_member(R"(<cityObjectMember>
    <brid:Bridge gml:id="bridge_1">
      <brid:class codeSpace="https://example.org/bridge_class">1000</brid:class>
      <brid:isMovable>true</brid:isMovable>
      <brid:bridgePart><brid:BridgePart gml:id="bridge_part_1"><brid:isMovable>false</brid:isMovable></brid:BridgePart></brid:bridgePart>
    </brid:Bridge>
  </cityObjectMember>
</CityModel>
)");
    const auto* bridge = first<ecitygml::Bridge>(*city_model);
    REQUIRE(bridge != nullptr);
    REQUIRE(bridge->class_()->value() == "1000");
    REQUIRE(bridge->is_movable() == std::optional<bool>(true));
    auto parts = bridge->bridge_parts();
    const auto* part = parts->next()->object();
    REQUIRE(part->feature_id().as_str() == "bridge_part_1");
    REQUIRE(part->is_movable() == std::optional<bool>(false));
    REQUIRE(parts->next() == nullptr);
    REQUIRE(first<ecitygml::BridgePart>(*city_model) == part);
}

TEST_CASE("Tunnel and tunnel part", "[tunnel]") {
    auto city_model = read_member(R"(<cityObjectMember>
    <tun:Tunnel gml:id="tunnel_1">
      <tun:function>1010</tun:function>
      <tun:tunnelPart><tun:TunnelPart gml:id="tunnel_part_1"><tun:function>1030</tun:function></tun:TunnelPart></tun:tunnelPart>
    </tun:Tunnel>
  </cityObjectMember>
</CityModel>
)");
    const auto* tunnel = first<ecitygml::Tunnel>(*city_model);
    REQUIRE(tunnel != nullptr);
    REQUIRE(tunnel->functions()->next()->value() == "1010");
    auto parts = tunnel->tunnel_parts();
    REQUIRE(parts->next()->object()->functions()->next()->value() == "1030");
    REQUIRE(parts->next() == nullptr);
}
