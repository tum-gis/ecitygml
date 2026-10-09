package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface SurfaceLib: Library {
    fun ecitygml_Surface_destroy(handle: Pointer)
    fun ecitygml_Surface_id(handle: Pointer): Pointer?
    fun ecitygml_Surface_names(handle: Pointer): Pointer
    fun ecitygml_Surface_triangulate(handle: Pointer): ResultPointerPointer
    fun ecitygml_Surface_try_from(surface: Pointer): Pointer?
    fun ecitygml_Surface_patches(handle: Pointer): Pointer
    fun ecitygml_Surface_area_3d(handle: Pointer): ResultDoublePointer
    fun ecitygml_Surface_points(handle: Pointer): Pointer
    fun ecitygml_Surface_compute_envelope(handle: Pointer): Pointer?
}
/** A surface made of patches, borrowed from a city model.
*/
class Surface internal constructor (
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

    private class SurfaceCleaner(val handle: Pointer, val lib: SurfaceLib) : Runnable {
        override fun run() {
            lib.ecitygml_Surface_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Surface.SurfaceCleaner(handle, Surface.lib));
    }

    companion object {
        internal val libClass: Class<SurfaceLib> = SurfaceLib::class.java
        internal val lib: SurfaceLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The surface as a `gml:Surface`, or none if it is another type (Rust: `Surface::try_from`,
        *which takes the surface by value).
        */
        fun tryFrom(surface: AbstractSurfaceKind): Surface? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(surface);
            
            val returnVal = lib.ecitygml_Surface_try_from(surface.handle);
            val selfEdges: List<Any> = listOf(surface)
            val handle = returnVal ?: return null
            val returnOpaque = Surface(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Surface_id(handle);
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
        
        val returnVal = lib.ecitygml_Surface_names(handle);
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
        
        val returnVal = lib.ecitygml_Surface_triangulate(handle);
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
    
    /** The patches (`gml:patches`).
    */
    fun patches(): AbstractSurfacePatchKindIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Surface_patches(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AbstractSurfacePatchKindIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun area3d(): Result<Double> {
        
        val returnVal = lib.ecitygml_Surface_area_3d(handle);
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
    
    /** All positions of the patches.
    */
    fun points(): DirectPositionIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Surface_points(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = DirectPositionIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
    */
    fun computeEnvelope(): Envelope? {
        
        val returnVal = lib.ecitygml_Surface_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}