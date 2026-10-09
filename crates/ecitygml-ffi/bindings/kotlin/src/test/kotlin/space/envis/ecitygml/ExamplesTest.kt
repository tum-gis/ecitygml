package space.envis.ecitygml

import org.junit.jupiter.api.DynamicTest
import org.junit.jupiter.api.TestFactory
import space.envis.ecitygml.examples.runBuildingReport
import space.envis.ecitygml.examples.runConvert
import space.envis.ecitygml.examples.runExportObj
import space.envis.ecitygml.examples.runListFeatures
import space.envis.ecitygml.examples.runMeasureGeometry
import space.envis.ecitygml.examples.runReadCityModel
import space.envis.ecitygml.examples.runRoadNetwork
import java.io.ByteArrayOutputStream
import java.io.File
import java.io.PrintStream
import java.nio.file.Files
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertTrue

private val fixtures = System.getProperty("ecitygml.fixtures")
private val expected = File(System.getProperty("ecitygml.examples.expected"))

/** The examples by name, and the extension of the file they write (if any, their second argument). */
private val examples: Map<String, Pair<(Array<String>) -> Int, String?>> = mapOf(
    "01_read_city_model" to (::runReadCityModel to null),
    "02_list_features" to (::runListFeatures to null),
    "03_building_report" to (::runBuildingReport to null),
    "04_road_network" to (::runRoadNetwork to null),
    "05_measure_geometry" to (::runMeasureGeometry to null),
    "06_export_obj" to (::runExportObj to ".obj"),
    "07_convert" to (::runConvert to ".gml.gz"),
)

/**
 * Runs the examples in src/examples and compares their output with the expected output shared by all
 * languages: for every `crates/ecitygml-ffi/tests/examples/expected/<example>/<fixture>.txt`, the example runs on
 * `tests/fixtures/<fixture>.gml` and must print that text; if `<fixture><extension>` exists there too,
 * the written file must match it.
 */
class ExamplesTest {
    private fun captured(block: () -> Int): Triple<Int, String, String> {
        val out = ByteArrayOutputStream()
        val err = ByteArrayOutputStream()
        val (originalOut, originalErr) = System.out to System.err
        System.setOut(PrintStream(out, true))
        System.setErr(PrintStream(err, true))
        val exitCode = try {
            block()
        } finally {
            System.setOut(originalOut)
            System.setErr(originalErr)
        }
        return Triple(exitCode, out.toString(), err.toString())
    }

    @TestFactory
    fun expectedOutputs(): List<DynamicTest> =
        expected.listFiles()!!.sorted().flatMap { directory ->
            val (run, extension) = examples.getValue(directory.name)
            directory.listFiles { file -> file.extension == "txt" }!!.sorted().map { case ->
                DynamicTest.dynamicTest("${directory.name} ${case.nameWithoutExtension}") {
                    val output = extension?.let { Files.createTempFile("ecitygml-example", it).toFile() }
                    val arguments = listOfNotNull("$fixtures/${case.nameWithoutExtension}.gml", output?.path)
                    val (exitCode, out, err) = captured { run(arguments.toTypedArray()) }
                    assertEquals(0, exitCode, err)
                    assertEquals(case.readText(), out)
                    val expectedFile = File(directory, case.nameWithoutExtension + (extension ?: ""))
                    if (output != null && expectedFile.exists()) {
                        assertEquals(expectedFile.readText(), output.readText())
                    }
                    output?.delete()
                }
            }
        }

    @Test
    fun everyExampleHasExpectedOutput() {
        assertEquals(examples.keys.sorted(), expected.listFiles()!!.map { it.name }.sorted())
    }

    @Test
    fun missingFile() {
        val (exitCode, _, err) = captured { runReadCityModel(arrayOf("$fixtures/does-not-exist.gml")) }
        assertEquals(1, exitCode)
        assertTrue(err.contains("No such file"), err)
    }
}
