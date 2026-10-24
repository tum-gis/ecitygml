using System.Reflection;
using Ecitygml.Examples;
using Xunit;

namespace Ecitygml.Tests;

/// <summary>The examples redirect the console, which is global: their tests must not run in parallel with others.</summary>
[CollectionDefinition(nameof(ConsoleCollection), DisableParallelization = true)]
public class ConsoleCollection;

/// <summary>
/// Runs the examples and compares their output with the expected output shared by all languages: for every
/// `tests/expected/examples/&lt;example&gt;/&lt;dataset&gt;/&lt;fixture&gt;.txt`, the example runs on
/// `tests/fixtures/&lt;dataset&gt;/&lt;fixture&gt;.gml` and must print that text. Examples that write a file get a temporary output
/// path; if `&lt;fixture&gt;&lt;extension&gt;` exists next to the expected text, the file must match it.
/// </summary>
[Collection(nameof(ConsoleCollection))]
public class ExamplesTests
{
    private static readonly string Expected = typeof(ExamplesTests).Assembly
        .GetCustomAttributes<AssemblyMetadataAttribute>()
        .Single(attribute => attribute.Key == "ExamplesExpected").Value!;

    /// <summary>Examples with an output file, and its extension (the example's second argument).</summary>
    private static readonly Dictionary<string, string> OutputExtensions = new()
    {
        ["06_export_obj"] = ".obj",
        ["07_convert"] = ".gml.gz",
    };

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

    private static (int ExitCode, string Out, string Err) Captured(Func<int> run)
    {
        var (originalOut, originalError) = (Console.Out, Console.Error);
        var (output, error) = (new StringWriter { NewLine = "\n" }, new StringWriter { NewLine = "\n" });
        Console.SetOut(output);
        Console.SetError(error);
        try
        {
            return (run(), output.ToString(), error.ToString());
        }
        finally
        {
            Console.SetOut(originalOut);
            Console.SetError(originalError);
        }
    }

    [Theory]
    [MemberData(nameof(Cases))]
    public void ExpectedOutput(string example, string fixture)
    {
        var arguments = new List<string> { Helpers.Fixture($"{fixture}.gml") };
        var extension = OutputExtensions.GetValueOrDefault(example);
        if (extension != null)
        {
            arguments.Add(Path.Combine(Directory.CreateTempSubdirectory("ecitygml-example").FullName, $"output{extension}"));
        }
        var (exitCode, output, error) = Captured(() => Program.Examples[example](arguments.ToArray()));
        Assert.True(exitCode == 0, error);
        Assert.Equal(File.ReadAllText(Path.Combine(Expected, example, $"{fixture}.txt")), output);

        var expectedFile = Path.Combine(Expected, example, $"{fixture}{extension}");
        if (extension != null && File.Exists(expectedFile))
        {
            Assert.Equal(File.ReadAllText(expectedFile), File.ReadAllText(arguments[1]));
        }
    }

    [Fact]
    public void EveryExampleHasExpectedOutput()
    {
        Assert.Equal(Program.Examples.Keys.Order(), Directory.GetDirectories(Expected).Select(Path.GetFileName).Order());
    }

    [Fact]
    public void MissingFile()
    {
        var (exitCode, _, error) = Captured(() => ReadCityModel.Run([Helpers.Fixture("does-not-exist.gml")]));
        Assert.Equal(1, exitCode);
        Assert.Contains("No such file", error);
    }

    [Fact]
    public void Usage()
    {
        Assert.Equal(2, Captured(() => ReadCityModel.Run([])).ExitCode);
        Assert.Equal(2, Captured(() => Program.Main(["unknown"])).ExitCode);
    }
}
