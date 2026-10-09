package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TriangleLib: Library {
    fun ecitygml_Triangle_destroy(handle: Pointer)
    fun ecitygml_Triangle_triangulate(handle: Pointer): ResultPointerPointer
    fun ecitygml_Triangle_try_from(patch: Pointer): Pointer?
    fun ecitygml_Triangle_exterior(handle: Pointer): Pointer
    fun ecitygml_Triangle_a(handle: Pointer): Pointer
    fun ecitygml_Triangle_b(handle: Pointer): Pointer
    fun ecitygml_Triangle_c(handle: Pointer): Pointer
    fun ecitygml_Triangle_area(handle: Pointer): Double
    fun ecitygml_Triangle_points(handle: Pointer): Pointer
    fun ecitygml_Triangle_compute_envelope(handle: Pointer): Pointer?
}
/** A triangle, borrowed from a city model.
*/
class Triangle internal constructor (
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

    private class TriangleCleaner(val handle: Pointer, val lib: TriangleLib) : Runnable {
        override fun run() {
            lib.ecitygml_Triangle_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Triangle.TriangleCleaner(handle, Triangle.lib));
    }

    companion object {
        internal val libClass: Class<TriangleLib> = TriangleLib::class.java
        internal val lib: TriangleLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The patch as a triangle, or none if it is another type (Rust: `Triangle::try_from`, which
        *takes the patch by value).
        */
        fun tryFrom(patch: AbstractSurfacePatchKind): Triangle? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(patch);
            
            val returnVal = lib.ecitygml_Triangle_try_from(patch.handle);
            val selfEdges: List<Any> = listOf(patch)
            val handle = returnVal ?: return null
            val returnOpaque = Triangle(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to
    *triangulate are listed in `Triangulation::skipped`; as in egml, members that are only an
    *`xlink:href` are left out without such an entry.
    */
    fun triangulate(): Result<Triangulation> {
        
        val returnVal = lib.ecitygml_Triangle_triangulate(handle);
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
    
    fun exterior(): AbstractRingKind {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Triangle_exterior(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = AbstractRingKind(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun a(): DirectPosition {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Triangle_a(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = DirectPosition(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun b(): DirectPosition {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Triangle_b(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = DirectPosition(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun c(): DirectPosition {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Triangle_c(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = DirectPosition(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun area(): Double {
        
        val returnVal = lib.ecitygml_Triangle_area(handle);
        return (returnVal)
    }
    
    /** The three corners.
    */
    fun points(): DirectPositionIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Triangle_points(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = DirectPositionIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
    */
    fun computeEnvelope(): Envelope? {
        
        val returnVal = lib.ecitygml_Triangle_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}