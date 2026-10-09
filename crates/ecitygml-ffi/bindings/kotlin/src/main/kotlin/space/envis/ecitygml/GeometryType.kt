package space.envis.ecitygml

import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface GeometryTypeLib: Library {
}
/** Type of a GML geometry.
*/
enum class GeometryType {
    Point,
    LineString,
    Curve,
    OrientableCurve,
    LinearRing,
    Ring,
    Polygon,
    Surface,
    OrientableSurface,
    PolyhedralSurface,
    TriangulatedSurface,
    Tin,
    Shell,
    Solid,
    MultiGeometry,
    MultiPoint,
    MultiCurve,
    MultiSurface,
    MultiSolid,
    GeometricComplex,
    CompositeCurve,
    CompositeSurface,
    CompositeSolid,
    Grid,
    RectifiedGrid;

    fun toNative(): Int {
        return this.ordinal
    }


    companion object {
        internal val libClass: Class<GeometryTypeLib> = GeometryTypeLib::class.java
        internal val lib: GeometryTypeLib = Native.load("ecitygml_ffi", libClass) 
        fun fromNative(native: Int): GeometryType {
            return GeometryType.entries[native]
        }

        fun default(): GeometryType {
            return Point
        }
    }
}
