// The cases of crates/ecitygml/tests/api/writer.md.
#include "api.hpp"

#include <ecitygml/Formatting.hpp>
#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/AbstractRingKind.hpp>
#include <ecitygml/AbstractSurfaceKind.hpp>
#include <ecitygml/AbstractSurfaceProperty.hpp>
#include <ecitygml/AbstractSurfacePropertyIterator.hpp>
#include <ecitygml/DirectPosition.hpp>
#include <ecitygml/DirectPositionIterator.hpp>
#include <ecitygml/GmlWriter.hpp>
#include <ecitygml/LinearRing.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/Polygon.hpp>
#include <ecitygml/WallSurface.hpp>

#include <optional>
#include <tuple>
#include <vector>

using ecitygml::CitygmlFormat;
using ecitygml::ErrorKind;
using ecitygml::Formatting;
using ecitygml::GmlWriter;

namespace {
std::unique_ptr<ecitygml::CityModel> model() {
    return read(fixture("fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml"));
}

void require_reads_back(const std::string& path, const ecitygml::CityModel& model) {
    CAPTURE(path);
    REQUIRE(feature_types(*read(path)) == feature_types(model));
}

/// Writes the model with the writer of a successful result.
void write(diplomat::result<std::unique_ptr<GmlWriter>, std::unique_ptr<ecitygml::Error>> writer,
           const ecitygml::CityModel& model) {
    REQUIRE(writer.is_ok());
    REQUIRE(std::move(writer).ok().value()->finish(model).is_ok());
}

/// The model written as `Gml` text.
std::string text(const ecitygml::CityModel& model, std::unique_ptr<Formatting> formatting = nullptr) {
    auto writer = GmlWriter::create(CitygmlFormat::Gml);
    if (formatting) {
        writer->with_formatting(*formatting);
    }
    REQUIRE(writer->finish(model).is_ok());
    const auto data = writer->data();
    return {reinterpret_cast<const char*>(data.data()), data.size()};
}

std::vector<std::string> lines(const std::string& text) {
    std::vector<std::string> lines;
    std::istringstream stream(text);
    for (std::string line; std::getline(stream, line);) {
        lines.push_back(line);
    }
    return lines;
}

bool any_line_starts_with(const std::string& text, const std::string& prefix) {
    for (const auto& line : lines(text)) {
        if (line.rfind(prefix, 0) == 0) {
            return true;
        }
    }
    return false;
}
}  // namespace

TEST_CASE("Writer in memory", "[api][writer]") {
    auto city_model = model();
    for (const auto format : {CitygmlFormat::Gml, CitygmlFormat::GmlGz, CitygmlFormat::GmlZst}) {
        auto writer = GmlWriter::create(format);
        REQUIRE(writer->data().size() == 0);
        REQUIRE(writer->finish(*city_model).is_ok());
        REQUIRE(feature_types(*read_data(writer->data(), format)) == feature_types(*city_model));
    }
    REQUIRE_THAT(text(*city_model), Catch::Matchers::ContainsSubstring("<bldg:Building"));
}

TEST_CASE("Writer files", "[api][writer]") {
    auto city_model = model();
    const TempDir dir;
    for (const auto* name : {"out.gml", "out.gml.gz", "out.gml.zst"}) {
        write(GmlWriter::from_path(dir.path(name)), *city_model);
        require_reads_back(dir.path(name), *city_model);
    }
}

TEST_CASE("Writer overwrites file", "[api][writer]") {
    auto city_model = model();
    const TempDir dir;
    const auto path = dir.path("out.gml");
    std::ofstream(path) << std::string(100000, 'x');
    write(GmlWriter::from_path(path), *city_model);
    require_reads_back(path, *city_model);
}

TEST_CASE("Writer base path with format", "[api][writer]") {
    auto city_model = model();
    const TempDir dir;
    std::ofstream(dir.path("out.gml.gz")) << std::string(100000, 'x');
    write(GmlWriter::from_base_path_with_format(dir.path("out"), CitygmlFormat::GmlGz), *city_model);
    require_reads_back(dir.path("out.gml.gz"), *city_model);
}

TEST_CASE("Writer formatting", "[api][writer]") {
    auto city_model = model();
    const auto default_text = text(*city_model);
    REQUIRE(lines(default_text).size() > 1);
    REQUIRE_FALSE(any_line_starts_with(default_text, " "));
    REQUIRE_FALSE(any_line_starts_with(default_text, "\t"));
    REQUIRE(text(*city_model, Formatting::new_line()) == default_text);
    REQUIRE(text(*city_model, Formatting::indent(' ', 0)) == default_text);

    REQUIRE(lines(text(*city_model, Formatting::compact())).size() < lines(default_text).size());

    const auto spaces = text(*city_model, Formatting::indent(' ', 2));
    REQUIRE(any_line_starts_with(spaces, "  <"));
    REQUIRE_FALSE(any_line_starts_with(spaces, "\t"));

    const auto tabs = text(*city_model, Formatting::indent('\t', 1));
    REQUIRE(any_line_starts_with(tabs, "\t<"));
    const diplomat::span<const uint8_t> data(reinterpret_cast<const uint8_t*>(tabs.data()), tabs.size());
    REQUIRE(feature_types(*read_data(data, CitygmlFormat::Gml)) == feature_types(*city_model));
}

TEST_CASE("Writer finish once", "[api][writer]") {
    auto city_model = model();
    auto writer = GmlWriter::create(CitygmlFormat::Gml);
    REQUIRE(writer->finish(*city_model).is_ok());
    require_error(*error_of(writer->finish(*city_model)), ErrorKind::InvalidArgument, "already finished");
}

TEST_CASE("Writer unsupported extension", "[api][writer]") {
    const TempDir dir;
    require_error(*error_of(GmlWriter::from_path(dir.path("out.txt"))), ErrorKind::InvalidArgument, "txt");
}

TEST_CASE("Writer missing directory", "[api][writer]") {
    const TempDir dir;
    require_error(*error_of(GmlWriter::from_path(dir.path("missing/out.gml"))), ErrorKind::Io, "");
}

namespace {
const std::string FZK_LOD2 = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";

size_t occurrences(const std::string& text, const std::string& part) {
    size_t n = 0;
    for (size_t at = text.find(part); at != std::string::npos; at = text.find(part, at + part.size())) {
        ++n;
    }
    return n;
}

/// The exterior ring positions of every polygon of the wall surfaces' LoD2 multi surfaces, in document order.
std::vector<std::tuple<double, double, double>> wall_coordinates(const ecitygml::CityModel& city_model) {
    std::vector<std::tuple<double, double, double>> result;
    auto features = city_model.iter_features();
    while (auto feature = features->next()) {
        const auto* wall = ecitygml::WallSurface::try_from(*feature);
        if (wall == nullptr || wall->lod2_multi_surface() == nullptr) {
            continue;
        }
        auto members = wall->lod2_multi_surface()->object()->surface_member();
        while (const auto* member = members->next()) {
            const auto* polygon = ecitygml::Polygon::try_from(*member->object());
            if (polygon == nullptr) {
                continue;
            }
            auto points = ecitygml::LinearRing::try_from(*polygon->exterior())->points();
            while (const auto* p = points->next()) {
                result.emplace_back(p->x(), p->y(), p->z());
            }
        }
    }
    return result;
}
}  // namespace

TEST_CASE("Writer keeps references", "[api][writer]") {
    auto city_model = read(fixture(FZK_LOD2));
    const auto written = text(*city_model);
    REQUIRE(occurrences(written, "xlink:href=\"#PolyID7350_878_759628_120742\"") == 1);
    REQUIRE(occurrences(written, "gml:id=\"PolyID7350_878_759628_120742\"") == 1);
}

TEST_CASE("Writer preserves coordinates", "[api][writer]") {
    auto city_model = read(fixture(FZK_LOD2));
    const auto written_text = text(*city_model);
    const std::vector<uint8_t> data(written_text.begin(), written_text.end());
    auto written = read_data(data, ecitygml::CitygmlFormat::Gml);
    const auto coordinates = wall_coordinates(*city_model);
    REQUIRE_FALSE(coordinates.empty());
    REQUIRE(wall_coordinates(*written) == coordinates);
}
