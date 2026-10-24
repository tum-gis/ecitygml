using System.Diagnostics;
using System.Reflection;
using Xunit;

namespace Ecitygml.Tests;

/// <summary>
/// Runs the snippets in examples/snippets/ (short programs giving a first impression of the bindings, file-based apps run with
/// <c>dotnet run --file</c>) and compares their output with the expected output shared by all languages: for every
/// `tests/expected/snippets/&lt;snippet&gt;/&lt;dataset&gt;/&lt;fixture&gt;.txt`, the snippet runs on
/// `tests/fixtures/&lt;dataset&gt;/&lt;fixture&gt;.gml` and must print that text.
/// </summary>
public class SnippetsTests
{
    private static readonly string Snippets = Metadata("Snippets");
    private static readonly string Expected = Metadata("SnippetsExpected");

    /// <summary>The snippets by name, and their file in examples/snippets/.</summary>
    private static readonly Dictionary<string, string> Files = new()
    {
        ["compute_total_building_height"] = "ComputeTotalBuildingHeight.cs",
        ["compute_traffic_space_volume"] = "ComputeTrafficSpaceVolume.cs",
        ["compute_wall_surface_area"] = "ComputeWallSurfaceArea.cs",
        ["translate_to_local_coordinates"] = "TranslateToLocalCoordinates.cs",
    };

    /// <summary>Snippets that write a file, and its extension (the snippet's second argument).</summary>
    private static readonly Dictionary<string, string> OutputExtensions = new()
    {
        ["translate_to_local_coordinates"] = ".gml",
    };

    private static string Metadata(string key) => typeof(SnippetsTests).Assembly
        .GetCustomAttributes<AssemblyMetadataAttribute>()
        .Single(attribute => attribute.Key == key).Value!;

    public static TheoryData<string, string> Cases()
    {
        var cases = new TheoryData<string, string>();
        foreach (var directory in Directory.GetDirectories(Expected).Order())
        {
            // `<dataset>/<fixture>.txt`: the fixture is `<dataset>/<fixture>`, as below tests/fixtures.
            foreach (var file in Directory.GetFiles(directory, "*.txt", SearchOption.AllDirectories).Order())
            {
                cases.Add(
                    Path.GetFileName(directory),
                    $"{Path.GetFileName(Path.GetDirectoryName(file))}/{Path.GetFileNameWithoutExtension(file)}");
            }
        }
        return cases;
    }

    [Theory]
    [MemberData(nameof(Cases))]
    public void ExpectedOutput(string snippet, string fixture)
    {
        // The dotnet CLI running the tests sets DOTNET_HOST_PATH to itself.
        var dotnet = Environment.GetEnvironmentVariable("DOTNET_HOST_PATH") ?? "dotnet";
        var start = new ProcessStartInfo(dotnet)
        {
            ArgumentList = { "run", "--file", Path.Combine(Snippets, Files[snippet]), "--", Helpers.Fixture($"{fixture}.gml") },
            RedirectStandardOutput = true,
            RedirectStandardError = true,
        };
        var extension = OutputExtensions.GetValueOrDefault(snippet);
        var outputFile = extension == null
            ? null
            : Path.Combine(Directory.CreateTempSubdirectory("ecitygml-snippet").FullName, $"output{extension}");
        if (outputFile != null) start.ArgumentList.Add(outputFile);
        using var process = Process.Start(start)!;
        var error = process.StandardError.ReadToEndAsync();
        var output = process.StandardOutput.ReadToEnd();
        process.WaitForExit();
        Assert.True(process.ExitCode == 0, error.Result + output);
        Assert.Equal(File.ReadAllText(Path.Combine(Expected, snippet, $"{fixture}.txt")), output);

        var expectedFile = Path.Combine(Expected, snippet, $"{fixture}{extension}");
        if (outputFile != null && File.Exists(expectedFile))
        {
            Assert.Equal(File.ReadAllBytes(expectedFile), File.ReadAllBytes(outputFile));
        }
    }

    [Fact]
    public void EverySnippetHasExpectedOutput()
    {
        Assert.Equal(Files.Keys.Order(), Directory.GetDirectories(Expected).Select(Path.GetFileName).Order());
        Assert.Equal(Files.Values.Order(), Directory.GetFiles(Snippets, "*.cs").Select(Path.GetFileName).Order());
    }
}
