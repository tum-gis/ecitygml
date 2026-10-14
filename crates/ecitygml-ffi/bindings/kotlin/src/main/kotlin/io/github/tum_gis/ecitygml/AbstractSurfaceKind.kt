package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractSurfaceKindLib: Library {
    fun ecitygml_AbstractSurfaceKind_destroy(handle: Pointer)
    fun ecitygml_AbstractSurfaceKind_id(handle: Pointer): Pointer?
    fun ecitygml_AbstractSurfaceKind_names(handle: Pointer): Pointer
    fun ecitygml_AbstractSurfaceKind_triangulate(handle: Pointer): ResultPointerPointer
    fun ecitygml_AbstractSurfaceKind_try_from(geometry: Pointer): Pointer?
    fun ecitygml_AbstractSurfaceKind_geometry_type(handle: Pointer): Int
    fun ecitygml_AbstractSurfaceKind_area_3d(handle: Pointer): ResultDoublePointer
    fun ecitygml_AbstractSurfaceKind_points(handle: Pointer): Pointer
    fun ecitygml_AbstractSurfaceKind_compute_envelope(handle: Pointer): Pointer?
}
/** A surface of any type, borrowed from a city model; convert it with `Polygon::try_from`,
*`CompositeSurface::try_from`, `Shell::try_from`, `Surface::try_from` or
*`TriangulatedSurface::try_from`.
*/
class AbstractSurfaceKind internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal var owned: Boolean,
)  {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AbstractSurfaceKindCleaner(val handle: Pointer, val lib: AbstractSurfaceKindLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractSurfaceKind_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractSurfaceKind.AbstractSurfaceKindCleaner(handle, AbstractSurfaceKind.lib));
    }

    companion object {
        internal val libClass: Class<AbstractSurfaceKindLib> = AbstractSurfaceKindLib::class.java
        internal val lib: AbstractSurfaceKindLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The geometry as an `AbstractSurfaceKind`, or none if it is another type (Rust: nested
        *`AbstractGeometryKind` variants).
        */
        fun tryFrom(geometry: AbstractGeometryKind): AbstractSurfaceKind? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(geometry);
            
            val returnVal = lib.ecitygml_AbstractSurfaceKind_try_from(geometry.handle);
            val selfEdges: List<Any> = listOf(geometry)
            val handle = returnVal ?: return null
            val returnOpaque = AbstractSurfaceKind(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractSurfaceKind_id(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Id(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** The object's `gml:name`s.
    */
    fun names(): CodeIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractSurfaceKind_names(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CodeIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to
    *triangulate are listed in `Triangulation::skipped`; as in egml, members that are only an
    *`xlink:href` are left out without such an entry.
    */
    fun triangulate(): Result<Triangulation> {
        
        val returnVal = lib.ecitygml_AbstractSurfaceKind_triangulate(handle);
        val nativeOkVal = returnVal.getNativeOk();
        if (nativeOkVal != null) {
            val selfEdges: List<Any> = listOf()
            val handle = nativeOkVal 
            val returnOpaque = Triangulation(handle, selfEdges, true)
            return returnOpaque.ok()
        } else {
            val selfEdges: List<Any> = listOf()
            val handle = returnVal.getNativeErr()!! 
            val returnOpaque = Error(handle, selfEdges, true)
            return returnOpaque.err()
        }
    }
    
    fun geometryType(): GeometryType {
        
        val returnVal = lib.ecitygml_AbstractSurfaceKind_geometry_type(handle);
        return (GeometryType.fromNative(returnVal))
    }
    
    fun area3d(): Result<Double> {
        
        val returnVal = lib.ecitygml_AbstractSurfaceKind_area_3d(handle);
        val nativeOkVal = returnVal.getNativeOk();
        if (nativeOkVal != null) {
            return (nativeOkVal).ok()
        } else {
            val selfEdges: List<Any> = listOf()
            val handle = returnVal.getNativeErr()!! 
            val returnOpaque = Error(handle, selfEdges, true)
            return returnOpaque.err()
        }
    }
    
    fun points(): DirectPositionIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractSurfaceKind_points(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = DirectPositionIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
    */
    fun computeEnvelope(): Envelope? {
        
        val returnVal = lib.ecitygml_AbstractSurfaceKind_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}