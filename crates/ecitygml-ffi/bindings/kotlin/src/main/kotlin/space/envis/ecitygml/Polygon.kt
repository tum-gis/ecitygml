package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface PolygonLib: Library {
    fun ecitygml_Polygon_destroy(handle: Pointer)
    fun ecitygml_Polygon_id(handle: Pointer): Pointer?
    fun ecitygml_Polygon_names(handle: Pointer): Pointer
    fun ecitygml_Polygon_triangulate(handle: Pointer): ResultPointerPointer
    fun ecitygml_Polygon_try_from(surface: Pointer): Pointer?
    fun ecitygml_Polygon_exterior(handle: Pointer): Pointer?
    fun ecitygml_Polygon_interior(handle: Pointer): Pointer
    fun ecitygml_Polygon_area_3d(handle: Pointer): ResultDoublePointer
    fun ecitygml_Polygon_points(handle: Pointer): Pointer
    fun ecitygml_Polygon_compute_envelope(handle: Pointer): Pointer?
}
/** A polygon, borrowed from a city model.
*/
class Polygon internal constructor (
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

    private class PolygonCleaner(val handle: Pointer, val lib: PolygonLib) : Runnable {
        override fun run() {
            lib.ecitygml_Polygon_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Polygon.PolygonCleaner(handle, Polygon.lib));
    }

    companion object {
        internal val libClass: Class<PolygonLib> = PolygonLib::class.java
        internal val lib: PolygonLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The surface as a polygon, or none if it is another type (Rust: `Polygon::try_from`,
        *which takes the surface by value).
        */
        fun tryFrom(surface: AbstractSurfaceKind): Polygon? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(surface);
            
            val returnVal = lib.ecitygml_Polygon_try_from(surface.handle);
            val selfEdges: List<Any> = listOf(surface)
            val handle = returnVal ?: return null
            val returnOpaque = Polygon(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Polygon_id(handle);
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
        
        val returnVal = lib.ecitygml_Polygon_names(handle);
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
        
        val returnVal = lib.ecitygml_Polygon_triangulate(handle);
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
    
    fun exterior(): AbstractRingKind? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Polygon_exterior(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractRingKind(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun interior(): AbstractRingKindIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Polygon_interior(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AbstractRingKindIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Exterior area minus the holes; fails if the polygon has no exterior ring.
    */
    fun area3d(): Result<Double> {
        
        val returnVal = lib.ecitygml_Polygon_area_3d(handle);
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
    
    /** All positions of the exterior and interior rings.
    */
    fun points(): DirectPositionIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Polygon_points(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = DirectPositionIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
    */
    fun computeEnvelope(): Envelope? {
        
        val returnVal = lib.ecitygml_Polygon_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}