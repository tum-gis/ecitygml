using Xunit;
using static Ecitygml.Tests.Conformance.ConformanceHelpers;
using static Ecitygml.Tests.Helpers;

namespace Ecitygml.Tests.Conformance;

/// <summary>The cases of crates/ecitygml/tests/conformance/asam-opendrive.md.</summary>
public class AsamOpendriveTests
{
    private static readonly string[] Spaces =
    [
        "UUID_ae81947d-a661-3678-a5ee-eed58b68694f",
        "UUID_6e4de408-1e54-3869-b7ce-1be3f2261421",
        "UUID_9582b02f-5cc7-38f8-b79c-a3a18b31856c",
        "UUID_c772e261-27f1-30b6-8a94-1ccf23e71a74",
        "UUID_656f23c9-92b6-3c98-a1bf-40b5f2625b13",
        "UUID_86f8df09-c972-332b-a279-636373ce4e0c",
        "UUID_144a6807-5844-32b2-bb34-8b2671b1afaa",
    ];

    private static Road FirstRoad(CityModel cityModel) =>
        Items(cityModel.IterFeatures().Next).Select(Road.TryFrom).OfType<Road>().First();

    /// <summary>The objects of inline properties; fails on a reference-only property.</summary>
    private static List<T> Objects<P, T>(Func<P?> next, Func<P, HRef?> href, Func<P, T?> obj)
        where P : class where T : class =>
        Items(next).Select(property =>
        {
            Assert.Null(href(property));
            return Assert.IsType<T>(obj(property), exactMatch: false);
        }).ToList();

    private static List<Section> Sections(Road road) => Objects(road.Sections().Next, p => p.Href(), p => p.Object());

    private static List<TrafficSpace> TrafficSpaces(TrafficSpacePropertyIterator spaces) =>
        Objects(spaces.Next, p => p.Href(), p => p.Object());

    private static List<string> Ids<T>(IEnumerable<T> features, Func<T, Id> featureId) =>
        features.Select(f => Str(featureId(f).AsStr())).ToList();

    private static void AssertPointClose((double, double, double) expected, DirectPosition position)
    {
        AssertClose(expected.Item1, position.X());
        AssertClose(expected.Item2, position.Y());
        AssertClose(expected.Item3, position.Z());
    }

    private static void AssertEnvelope(CityModel cityModel, (double, double, double) lower, (double, double, double) upper)
    {
        var envelope = cityModel.BoundedBy()!.Envelope()!;
        AssertPointClose(lower, envelope.LowerCorner());
        AssertPointClose(upper, envelope.UpperCorner());
    }

    /// <summary>The single boundary of a space, inline, as a feature.</summary>
    private static AbstractFeatureKindRef OnlyBoundary(AbstractSpaceBoundaryPropertyIterator boundaries)
    {
        var boundary = Assert.Single(Objects(boundaries.Next, p => p.Href(), p => p.Object()));
        return AbstractFeatureKindRef.FromSpaceBoundary(boundary);
    }

    /// <summary>The single curve member of an inline multi curve, as a line string: (point count, length).</summary>
    private static (int, double) LineStringOf(MultiCurve multiCurve)
    {
        var member = Assert.Single(Objects(multiCurve.CurveMember().Next, p => p.Href(), p => p.Object()));
        var curve = LineString.TryFrom(member)!;
        return (Items(curve.Points().Next).Count(), curve.Length3d());
    }

    /// <summary>The local ids of references. `HRef.LocalId` isn't bound in .NET, so they come from the written
    /// href (`#id`).</summary>
    private static List<string> LocalIds(TrafficSpaceReferenceIterator references) =>
        Items(references.Next).Select(r =>
        {
            var href = Reference.FromTrafficSpaceReference(r).Href()!;
            Assert.True(href.IsLocal());
            return href.ToString().TrimStart('#');
        }).ToList();

    public class RoadShape
    {
        // The city model outlives every test: the features borrow from it.
        private static readonly CityModel Model = ReadFixture("asam-opendrive", "ASAM-UC_RoadShape.gml");

        private static Section TheSection() => Assert.Single(Sections(FirstRoad(Model)));

        private static List<TrafficSpace> Spaces() => TrafficSpaces(TheSection().TrafficSpaces());

        [Fact]
        public void RoadShapeCityModel()
        {
            Assert.Equal(1u, (uint)Model.CityObjectsLen());
            FeatureType[] types =
            [
                FeatureType.CityModel, FeatureType.Road, FeatureType.Section,
                FeatureType.TrafficSpace, FeatureType.TrafficArea, FeatureType.TrafficSpace, FeatureType.TrafficArea,
                FeatureType.AuxiliaryTrafficSpace, FeatureType.AuxiliaryTrafficArea,
                FeatureType.AuxiliaryTrafficSpace, FeatureType.AuxiliaryTrafficArea,
            ];
            Assert.Equal(types, Items(Model.IterFeatures().Next).Select(f => f.FeatureType()));
            Assert.Equal(types.Skip(1), Items(Model.IterCityObjects().Next).Select(o => o.FeatureType()));
            AssertEnvelope(
                Model,
                (-50.21567184593757, -2.4442507170297514, 0.0),
                (-13.007511850967884, 29.053746110395082, 4.95));
        }

        [Fact]
        public void RoadShapeRoad()
        {
            var road = FirstRoad(Model);
            Assert.Equal("UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f", Str(road.FeatureId().AsStr()));
            Assert.Null(road.Class());
            Assert.Null(road.TrafficDirection());
            Assert.Null(road.Functions().Next());
            Assert.Null(road.Usages().Next());
            Assert.Null(road.Intersections().Next());
            Assert.Null(road.Occupancies().Next());
            Assert.Null(road.TrafficSpaces().Next());
            Assert.Null(road.AuxiliaryTrafficSpaces().Next());
            Assert.Null(road.Markings().Next());
            Assert.Null(road.Holes().Next());
            Assert.Equal("UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29", Str(TheSection().FeatureId().AsStr()));
        }

        [Fact]
        public void RoadShapeSection()
        {
            var section = TheSection();
            Assert.Null(section.Class());
            Assert.Null(section.TrafficDirection());
            Assert.Null(section.Lod0MultiCurve());
            Assert.Null(section.Lod1Solid());
            Assert.Null(section.Markings().Next());
            Assert.Null(section.Holes().Next());
            Assert.Equal(
                ["UUID_ae81947d-a661-3678-a5ee-eed58b68694f", "UUID_6e4de408-1e54-3869-b7ce-1be3f2261421"],
                Ids(TrafficSpaces(section.TrafficSpaces()), s => s.FeatureId()));
            Assert.Equal(
                ["UUID_12298df9-4982-33a8-ab4a-9953410bbff7", "UUID_f8211bb5-0ce8-36e1-9b84-73d30114f578"],
                Ids(Objects(section.AuxiliaryTrafficSpaces().Next, p => p.Href(), p => p.Object()), s => s.FeatureId()));
        }

        [Fact]
        public void RoadShapeTrafficSpaces()
        {
            var spaces = Spaces();
            Assert.Equal(
                [TrafficDirectionValue.Backwards, TrafficDirectionValue.Forwards],
                spaces.Select(s => s.TrafficDirection()!.Value));
            foreach (var space in spaces)
            {
                Assert.Equal(GranularityValue.Lane, space.Granularity());
                Assert.Null(space.Class());
                Assert.Equal(["1"], Items(space.Functions().Next).Select(f => Str(f.Value())));
                Assert.Equal(["2"], Items(space.Usages().Next).Select(u => Str(u.Value())));
                Assert.Null(space.Occupancies().Next());
                Assert.Equal(SpaceType.Open, space.SpaceType());
                Assert.Null(space.RelativeToTerrain());
                Assert.Null(space.CreationDate());
                Assert.Null(space.Predecessors().Next());
                Assert.Null(space.Successors().Next());
                Assert.NotNull(TrafficArea.TryFrom(OnlyBoundary(space.Boundaries())));
            }
        }

        [Fact]
        public void RoadShapeGenericAttributes()
        {
            var attributes = Items(Spaces()[0].GenericAttributes().Next).Select(a =>
            {
                var name = Str(a.Name());
                if (a.AsInt() is { } integer) return (name, "int", (object)integer.Value());
                if (a.AsDouble() is { } number) return (name, "double", number.Value());
                return (name, "string", Str(a.AsString()!.Value()));
            });
            Assert.Equal(
                [
                    ("identifier_laneId", "int", 1L),
                    ("identifier_laneSectionId", "int", 0L),
                    ("identifier_roadId", "string", "1"),
                    ("opendrive_road_length", "double", 40.0),
                    ("opendrive_road_rule", "string", "RIGHT_HAND_TRAFFIC"),
                    ("opendrive_laneSection_curvePositionStart", "double", 0.0),
                    ("opendrive_lane_type", "string", "DRIVING"),
                    ("opendrive_lane_level", "string", "false"),
                ],
                attributes);
        }

        [Fact]
        public void RoadShapeTrafficSpaceGeometry()
        {
            var spaces = Spaces();
            AssertClose(720.0, spaces[0].Lod2Solid()!.Object()!.Volume3d());
            AssertClose(540.0, spaces[1].Lod2Solid()!.Object()!.Volume3d());
            foreach (var space in spaces)
            {
                var property = space.Lod2MultiCurve()!;
                Assert.Null(property.Href());
                var multiCurve = property.Object()!;
                AssertClose(40.0, multiCurve.Length3d());
                var (points, length) = LineStringOf(multiCurve);
                Assert.Equal(2, points);
                AssertClose(40.0, length);
                Assert.Null(space.Lod0MultiCurve());
                Assert.Null(space.Lod3MultiCurve());
                Assert.Null(space.Lod1Solid());
                Assert.Null(space.Lod3Solid());
                Assert.Null(space.Lod2MultiSurface());
            }
        }

        [Fact]
        public void RoadShapeTrafficAreas()
        {
            var areas = Spaces().Select(s => TrafficArea.TryFrom(OnlyBoundary(s.Boundaries()))!).ToList();
            Assert.Equal(
                ["UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2", "UUID_dc110e80-dadc-3c87-b864-2854cc0cb39a"],
                Ids(areas, a => a.FeatureId()));
            foreach (var area in areas)
            {
                Assert.Equal("Lane", FirstName(area.Names()));
                Assert.Null(area.Class());
                Assert.Equal(["1"], Items(area.Functions().Next).Select(f => Str(f.Value())));
                Assert.Equal(["2"], Items(area.Usages().Next).Select(u => Str(u.Value())));
                Assert.Null(area.SurfaceMaterial());
                Assert.Null(area.Lod0MultiCurve());
                Assert.Null(area.Lod0MultiSurface());
                Assert.Null(area.Lod1MultiSurface());
                Assert.Null(area.Lod3MultiSurface());
                Assert.Null(area.RelativeToTerrain());
                Assert.Single(Items(area.Lod2MultiSurface()!.Object()!.SurfaceMember().Next));
            }
            AssertClose(160.79800993793438, areas[0].Lod2MultiSurface()!.Object()!.Area3d());
            AssertClose(121.34249049694012, areas[1].Lod2MultiSurface()!.Object()!.Area3d());
        }

        [Fact]
        public void RoadShapeAuxiliaryTraffic()
        {
            var spaces = Objects(TheSection().AuxiliaryTrafficSpaces().Next, p => p.Href(), p => p.Object());
            foreach (var space in spaces)
            {
                Assert.Equal(GranularityValue.Lane, space.Granularity());
                Assert.Null(space.Class());
                Assert.Null(space.Functions().Next());
                Assert.Null(space.Usages().Next());
                Assert.Equal(SpaceType.Open, space.SpaceType());
                AssertClose(100.0, space.Lod2Solid()!.Object()!.Volume3d());
                AssertClose(40.0, space.Lod2MultiCurve()!.Object()!.Length3d());
            }
            var areas = spaces.Select(s => AuxiliaryTrafficArea.TryFrom(OnlyBoundary(s.Boundaries()))!).ToList();
            Assert.Equal(
                ["UUID_4890681a-e9fa-365e-a676-f89afb453f9b", "UUID_d3c71d48-5222-355e-8037-9677aee30d7e"],
                Ids(areas, a => a.FeatureId()));
            foreach (var area in areas)
            {
                Assert.Equal("Lane", FirstName(area.Names()));
                Assert.Null(area.Class());
                Assert.Null(area.Functions().Next());
                Assert.Null(area.Usages().Next());
                Assert.Null(area.SurfaceMaterial());
                AssertClose(40.0, area.Lod2MultiSurface()!.Object()!.Area3d());
            }
        }
    }

    public class Junction
    {
        private static readonly CityModel Model =
            ReadFixture("asam-opendrive", "ASAM-Ex_Bidirectional_Junction.gml");

        private static List<TrafficSpace> JunctionSpaces() =>
            Items(Model.IterFeatures().Next).Select(TrafficSpace.TryFrom).OfType<TrafficSpace>().ToList();

        [Fact]
        public void JunctionCityModel()
        {
            Assert.Equal(1u, (uint)Model.CityObjectsLen());
            Assert.Equal(
                [
                    FeatureType.CityModel, FeatureType.Road, FeatureType.Section, FeatureType.TrafficSpace,
                    FeatureType.TrafficArea, FeatureType.TrafficSpace, FeatureType.TrafficArea, FeatureType.Marking,
                    FeatureType.Marking, FeatureType.Marking, FeatureType.Marking, FeatureType.Section,
                    FeatureType.TrafficSpace, FeatureType.TrafficArea, FeatureType.Section, FeatureType.TrafficSpace,
                    FeatureType.TrafficArea, FeatureType.Intersection, FeatureType.TrafficSpace, FeatureType.TrafficArea,
                    FeatureType.TrafficSpace, FeatureType.TrafficArea, FeatureType.TrafficSpace, FeatureType.TrafficArea,
                ],
                Items(Model.IterFeatures().Next).Select(f => f.FeatureType()));
            Assert.Equal(23, Items(Model.IterCityObjects().Next).Count());
            AssertEnvelope(
                Model,
                (-52.66282419815818, -37.4146115571896, 0.0),
                (34.10760429351533, 6.338805461729647, 0.0));
        }

        [Fact]
        public void JunctionRoad()
        {
            var road = FirstRoad(Model);
            Assert.Equal("UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f", Str(road.FeatureId().AsStr()));
            var sections = Sections(road);
            Assert.Equal(
                [
                    "UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29",
                    "UUID_ef20f165-2564-373a-a5f8-98fd15f1ae69",
                    "UUID_4799566b-daf4-3135-aa9d-ec1b34a9167d",
                ],
                Ids(sections, s => s.FeatureId()));
            Assert.Equal([2, 1, 1], sections.Select(s => Items(s.TrafficSpaces().Next).Count()));
            Assert.Equal([4, 0, 0], sections.Select(s => Items(s.Markings().Next).Count()));
            Assert.All(sections, s => Assert.Null(s.AuxiliaryTrafficSpaces().Next()));
            var intersection = Assert.Single(Objects(road.Intersections().Next, p => p.Href(), p => p.Object()));
            Assert.Equal("UUID_47b7678d-e8b1-36ca-90b6-5b86cc859571", Str(intersection.FeatureId().AsStr()));
            Assert.Null(intersection.Class());
            Assert.Equal(Spaces[4..], Ids(TrafficSpaces(intersection.TrafficSpaces()), s => s.FeatureId()));
        }

        [Fact]
        public void JunctionTrafficSpaces()
        {
            var spaces = JunctionSpaces();
            Assert.Equal(Spaces, Ids(spaces, s => s.FeatureId()));
            Assert.Equal(
                new[] { TrafficDirectionValue.Backwards }.Concat(Enumerable.Repeat(TrafficDirectionValue.Forwards, 6)),
                spaces.Select(s => s.TrafficDirection()!.Value));
            Assert.All(spaces, s => Assert.Null(s.Lod2Solid()));
            var curves = spaces.Select(s => LineStringOf(s.Lod2MultiCurve()!.Object()!)).ToList();
            Assert.Equal([9, 9, 5, 6, 7, 8, 7], curves.Select(c => c.Item1));
            double[] lengths =
            [
                36.74683751297985, 36.74683751297985, 20.0, 21.746217945006258, 26.761532846607814,
                30.210435770102656, 30.0,
            ];
            foreach (var (expected, curve) in lengths.Zip(curves))
            {
                AssertClose(expected, curve.Item2);
            }
        }

        [Fact]
        public void JunctionTrafficAreas()
        {
            var surfaces = Items(Model.IterFeatures().Next).Select(TrafficArea.TryFrom).OfType<TrafficArea>()
                .Select(a => a.Lod2MultiSurface()!.Object()!).ToList();
            Assert.Equal([8, 8, 4, 5, 6, 7, 6], surfaces.Select(s => Items(s.SurfaceMember().Next).Count()));
            double[] areas =
            [
                112.81279116484816, 112.81279116484816, 61.4, 66.76088909116919, 81.22157625123039,
                92.69041581703632, 92.1,
            ];
            foreach (var (expected, surface) in areas.Zip(surfaces))
            {
                AssertClose(expected, surface.Area3d());
            }
        }

        [Fact]
        public void JunctionTrafficSpaceLinks()
        {
            var (s0, s1, s2, s3, s4, s5, s6) = (Spaces[0], Spaces[1], Spaces[2], Spaces[3], Spaces[4], Spaces[5], Spaces[6]);
            List<(string[], string[])> expected =
            [
                ([], []),
                ([], [s6]),
                ([s4, s5], []),
                ([], [s4]),
                ([s3], [s2]),
                (["UUID_d7d4aa5a-88c9-328d-9151-a6c043e57d7f"], [s0]),
                ([s1], [s2]),
            ];
            var links = JunctionSpaces().Select(s => (LocalIds(s.Predecessors()), LocalIds(s.Successors()))).ToList();
            Assert.Equal(expected.Count, links.Count);
            foreach (var ((predecessors, successors), (actualPredecessors, actualSuccessors)) in expected.Zip(links))
            {
                Assert.Equal(predecessors, actualPredecessors);
                Assert.Equal(successors, actualSuccessors);
            }
        }

        [Fact]
        public void JunctionMarkings()
        {
            var section = Sections(FirstRoad(Model))[0];
            var markings = Objects(section.Markings().Next, p => p.Href(), p => p.Object());
            foreach (var marking in markings)
            {
                Assert.Equal("RoadMarking", FirstName(marking.Names()));
                Assert.Null(marking.Class());
                Assert.Null(marking.Lod0MultiSurface());
                Assert.Null(marking.Lod3MultiSurface());
                Assert.Single(Items(marking.Lod2MultiSurface()!.Object()!.SurfaceMember().Next));
            }
            double[] areas = [0.48, 0.48, 0.48, 0.08962050155758661];
            Assert.Equal(areas.Length, markings.Count);
            foreach (var (expected, marking) in areas.Zip(markings))
            {
                AssertClose(expected, marking.Lod2MultiSurface()!.Object()!.Area3d());
            }
        }
    }
}
