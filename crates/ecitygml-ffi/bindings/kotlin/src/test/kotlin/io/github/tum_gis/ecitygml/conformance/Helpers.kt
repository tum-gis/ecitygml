package io.github.tum_gis.ecitygml.conformance

import io.github.tum_gis.ecitygml.*
import kotlin.math.abs
import kotlin.test.assertNotNull
import kotlin.test.assertTrue

// Helpers of the conformance suite (crates/ecitygml/tests/conformance/README.md).

/** The tolerance of floating point comparisons in the case lists. */
private const val TOLERANCE = 1e-6

private val fixtures = System.getProperty("ecitygml.fixtures")

/** Reads `tests/fixtures/<dataset>/<file>`. */
internal fun read(dataset: String, file: String): CityModel =
    GmlReader.fromPath("$fixtures/$dataset/$file").mapCatching { it.finish().getOrThrow() }.getOrThrow()

internal fun assertClose(actual: Double, expected: Double) =
    assertTrue(abs(actual - expected) <= TOLERANCE, "$actual is not within $TOLERANCE of $expected")

/** The city model's first building. */
internal fun building(cityModel: CityModel): Building =
    assertNotNull(cityModel.iterFeatures().asSequence().firstNotNullOfOrNull { it?.let(Building::tryFrom) })

/** The building's boundaries, as features. */
internal fun boundaries(building: Building): List<AbstractFeatureKindRef> =
    building.boundaries().asSequence().map { AbstractFeatureKindRef.fromSpaceBoundary(assertNotNull(it?.object_())) }.toList()

/** The first of a feature's names (`names()`). */
internal fun firstName(names: Iterator<Code?>): String = assertNotNull(names.asSequence().first()).value()
