package io.github.tum_gis.ecitygml

import org.junit.jupiter.api.DynamicTest
import org.junit.jupiter.api.TestFactory
import java.io.File
import java.nio.file.Files
import java.nio.file.Path
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertTrue

private val fixtures = System.getProperty("ecitygml.fixtures")
private val expected = File(System.getProperty("ecitygml.snippets.expected"))

/** The snippets by name, and the class of their file (each is a top-level `main` in the same package). */
private val snippets: Map<String, String> = mapOf(
    "compute_total_building_height" to "ComputeTotalBuildingHeightKt",
    "compute_traffic_space_volume" to "ComputeTrafficSpaceVolumeKt",
    "compute_wall_surface_area" to "ComputeWallSurfaceAreaKt",
    "translate_to_local_coordinates" to "TranslateToLocalCoordinatesKt",
)

/** Snippets that write a file, and its extension (the snippet's second argument). */
private val outputExtensions: Map<String, String> = mapOf("translate_to_local_coordinates" to ".gml")

/**
 * Runs a snippet's `main` in a JVM of its own, as the other languages run theirs in a process of their own: the
 * reader numbers the ids it generates for features without `gml:id` per process, so a written file depends on how
 * many models the process read before. Returns the exit code and standard output; standard error goes to the test log.
 */
private fun run(fileClass: String, args: List<String>): Pair<Int, String> {
    val java = Path.of(System.getProperty("java.home"), "bin", "java").toString()
    val command = listOf(
        java,
        "-cp", System.getProperty("java.class.path"),
        "-Djna.library.path=${System.getProperty("jna.library.path")}",
        "io.github.tum_gis.ecitygml.examples.snippets.$fileClass",
    ) + args
    val process = ProcessBuilder(command).redirectError(ProcessBuilder.Redirect.INHERIT).start()
    val out = process.inputStream.bufferedReader().readText()
    return process.waitFor() to out
}

/**
 * Runs the snippets in src/examples/…/snippets (short programs giving a first impression of the bindings) and
 * compares their output with the expected output shared by all languages: for every
 * `tests/expected/snippets/<snippet>/<dataset>/<fixture>.txt`, the snippet runs on `tests/fixtures/<dataset>/<fixture>.gml` and must print
 * that text; for snippets that write a file, it must match `<fixture><extension>` there if that exists.
 */
class SnippetsTest {
    @TestFactory
    fun expectedOutputs(): List<DynamicTest> =
        expected.listFiles()!!.sorted().flatMap { directory ->
            val fileClass = snippets.getValue(directory.name)
            // `<dataset>/<fixture>.txt`: the fixture is `<dataset>/<fixture>`, as below tests/fixtures.
            directory.walk().filter { it.isFile && it.extension == "txt" }.sorted().toList().map { case ->
                val fixture = "${case.parentFile.name}/${case.nameWithoutExtension}"
                DynamicTest.dynamicTest("${directory.name} $fixture") {
                    val extension = outputExtensions[directory.name]
                    val output = extension?.let { Files.createTempFile("ecitygml-snippet", it).toFile() }
                    val arguments = listOfNotNull("$fixtures/$fixture.gml", output?.path)
                    val (exitCode, out) = run(fileClass, arguments)
                    assertEquals(0, exitCode)
                    assertEquals(case.readText(), out)
                    val expectedFile = File(case.parentFile, case.nameWithoutExtension + (extension ?: ""))
                    if (output != null && expectedFile.exists()) {
                        assertTrue(expectedFile.readBytes().contentEquals(output.readBytes()), "$output differs from $expectedFile")
                    }
                    output?.delete()
                }
            }
        }

    @Test
    fun everySnippetHasExpectedOutput() {
        assertEquals(snippets.keys.sorted(), expected.listFiles()!!.map { it.name }.sorted())
    }
}
