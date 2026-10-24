// The cases of crates/ecitygml/tests/api/reader.md.
#include "api.hpp"

#include <ecitygml/WallSurface.hpp>

using ecitygml::CitygmlFormat;
using ecitygml::ErrorKind;
using ecitygml::GmlReader;

namespace {
const std::string FZK_LOD1 = "fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml";
const std::string FZK_LOD2 = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";
}  // namespace

TEST_CASE("Reader from bytes", "[api][reader]") {
    const auto data = read_bytes(fixture(FZK_LOD1));
    REQUIRE(read_data(data, CitygmlFormat::Gml)->city_objects_len() == 1);
}

TEST_CASE("Reader compressed", "[api][reader]") {
    for (const auto& [extension, format] : {std::pair{"gz", CitygmlFormat::GmlGz}, std::pair{"zst", CitygmlFormat::GmlZst}}) {
        const auto path = fixture(std::string("fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml.") + extension);
        CAPTURE(path);
        REQUIRE(read(path)->city_objects_len() == 1);
        const auto data = read_bytes(path);
        REQUIRE(read_data(data, format)->city_objects_len() == 1);
    }
}

TEST_CASE("Reader default rebuilds object bounds", "[api][reader]") {
    auto city_model = read(fixture(FZK_LOD2));
    std::vector<bool> bounded;
    auto features = city_model->iter_features();
    while (auto feature = features->next()) {
        if (const auto* wall = ecitygml::WallSurface::try_from(*feature)) {
            bounded.push_back(wall->bounded_by() != nullptr);
        }
    }
    REQUIRE(bounded == std::vector<bool>(4, true));
}

TEST_CASE("Reader finish once", "[api][reader]") {
    auto reader = std::move(GmlReader::from_path(fixture(FZK_LOD1)).ok().value());
    reader->with_rebuild_object_bounds(false);
    auto first = reader->finish();
    REQUIRE(first.is_ok());
    REQUIRE(std::move(first).ok().value()->city_objects_len() == 1);
    require_error(*error_of(reader->finish()), ErrorKind::InvalidArgument, "already finished");
}

TEST_CASE("Reader missing file", "[api][reader]") {
    require_error(*error_of(GmlReader::from_path(fixture("does-not-exist.gml"))), ErrorKind::Io, "No such file");
}

TEST_CASE("Reader unsupported extension", "[api][reader]") {
    require_error(*error_of(GmlReader::from_path(fixture("README.md"))), ErrorKind::InvalidArgument, "md");
}

TEST_CASE("Reader non utf8 path", "[api][reader]") {
    require_error(*error_of(GmlReader::from_path("\xff.gml")), ErrorKind::InvalidArgument, "`path`");
}

TEST_CASE("Reader invalid content", "[api][reader]") {
    auto reader = GmlReader::from_path(fixture("invalid/unclosed-tag.gml"));
    REQUIRE(reader.is_ok());
    require_error(*error_of(std::move(reader).ok().value()->finish()), ErrorKind::Parse, "tag not closed");
}
