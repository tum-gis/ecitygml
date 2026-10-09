package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TriangulatedSurfaceLib: Library {
    fun ecitygml_TriangulatedSurface_destroy(handle: Pointer)
    fun ecitygml_TriangulatedSurface_id(handle: Pointer): Pointer?
    fun ecitygml_TriangulatedSurface_names(handle: Pointer): Pointer
    fun ecitygml_TriangulatedSurface_try_from(surface: Pointer): Pointer?
    fun ecitygml_TriangulatedSurface_triangles(handle: Pointer): Pointer
    fun ecitygml_TriangulatedSurface_surface(handle: Pointer): Pointer
    fun ecitygml_TriangulatedSurface_points(handle: Pointer): Pointer
    fun ecitygml_TriangulatedSurface_area_3d(handle: Pointer): ResultDoublePointer
    fun ecitygml_TriangulatedSurface_compute_envelope(handle: Pointer): Pointer?
}
/** A surface made of triangles, borrowed from a city model or a triangulation.
*/
class TriangulatedSurface internal constructor (
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

    private class TriangulatedSurfaceCleaner(val handle: Pointer, val lib: TriangulatedSurfaceLib) : Runnable {
        override fun run() {
            lib.ecitygml_TriangulatedSurface_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TriangulatedSurface.TriangulatedSurfaceCleaner(handle, TriangulatedSurface.lib));
    }

    companion object {
        internal val libClass: Class<TriangulatedSurfaceLib> = TriangulatedSurfaceLib::class.java
        internal val lib: TriangulatedSurfaceLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The surface as a triangulated surface, or none if it is another type (Rust: a
        *`TriangulatedSurface` in `AbstractSurfaceKind::SurfaceKind`).
        */
        fun tryFrom(surface: AbstractSurfaceKind): TriangulatedSurface? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(surface);
            
            val returnVal = lib.ecitygml_TriangulatedSurface_try_from(surface.handle);
            val selfEdges: List<Any> = listOf(surface)
            val handle = returnVal ?: return null
            val returnOpaque = TriangulatedSurface(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TriangulatedSurface_id(handle);
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
        
        val returnVal = lib.ecitygml_TriangulatedSurface_names(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CodeIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun triangles(): TriangleIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TriangulatedSurface_triangles(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = TriangleIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** The underlying surface, whose patches are the triangles.
    */
    fun surface(): Surface {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TriangulatedSurface_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Surface(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** All corners of the triangles.
    */
    fun points(): DirectPositionIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TriangulatedSurface_points(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = DirectPositionIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun area3d(): Result<Double> {
        
        val returnVal = lib.ecitygml_TriangulatedSurface_area_3d(handle);
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
    
    /** Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
    */
    fun computeEnvelope(): Envelope? {
        
        val returnVal = lib.ecitygml_TriangulatedSurface_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}