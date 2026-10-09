package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractGeometryKindLib: Library {
    fun ecitygml_AbstractGeometryKind_destroy(handle: Pointer)
    fun ecitygml_AbstractGeometryKind_id(handle: Pointer): Pointer?
    fun ecitygml_AbstractGeometryKind_names(handle: Pointer): Pointer
    fun ecitygml_AbstractGeometryKind_triangulate(handle: Pointer): ResultPointerPointer
    fun ecitygml_AbstractGeometryKind_geometry_type(handle: Pointer): Int
    fun ecitygml_AbstractGeometryKind_compute_envelope(handle: Pointer): Pointer?
}
/** A geometry of any type, borrowed from a city model; convert it with `MultiSurface::try_from`,
*`MultiCurve::try_from`, `Point::try_from`, `Solid::try_from`, `AbstractSurfaceKind::try_from`
*or `AbstractCurveKind::try_from`. Not bound yet: `MultiPoint`, `MultiGeometry`.
*/
class AbstractGeometryKind internal constructor (
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

    private class AbstractGeometryKindCleaner(val handle: Pointer, val lib: AbstractGeometryKindLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractGeometryKind_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractGeometryKind.AbstractGeometryKindCleaner(handle, AbstractGeometryKind.lib));
    }

    companion object {
        internal val libClass: Class<AbstractGeometryKindLib> = AbstractGeometryKindLib::class.java
        internal val lib: AbstractGeometryKindLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractGeometryKind_id(handle);
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
        
        val returnVal = lib.ecitygml_AbstractGeometryKind_names(handle);
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
        
        val returnVal = lib.ecitygml_AbstractGeometryKind_triangulate(handle);
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
        
        val returnVal = lib.ecitygml_AbstractGeometryKind_geometry_type(handle);
        return (GeometryType.fromNative(returnVal))
    }
    
    /** Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
    */
    fun computeEnvelope(): Envelope? {
        
        val returnVal = lib.ecitygml_AbstractGeometryKind_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}