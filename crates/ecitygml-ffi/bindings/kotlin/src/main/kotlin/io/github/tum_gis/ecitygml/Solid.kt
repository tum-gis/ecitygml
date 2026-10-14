package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface SolidLib: Library {
    fun ecitygml_Solid_destroy(handle: Pointer)
    fun ecitygml_Solid_id(handle: Pointer): Pointer?
    fun ecitygml_Solid_names(handle: Pointer): Pointer
    fun ecitygml_Solid_triangulate(handle: Pointer): ResultPointerPointer
    fun ecitygml_Solid_try_from(geometry: Pointer): Pointer?
    fun ecitygml_Solid_exterior(handle: Pointer): Pointer?
    fun ecitygml_Solid_interior(handle: Pointer): Pointer
    fun ecitygml_Solid_volume_3d(handle: Pointer): ResultDoublePointer
    fun ecitygml_Solid_compute_envelope(handle: Pointer): Pointer?
    fun ecitygml_Solid_points(handle: Pointer): Pointer
}
/** A solid, borrowed from a city model.
*/
class Solid internal constructor (
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

    private class SolidCleaner(val handle: Pointer, val lib: SolidLib) : Runnable {
        override fun run() {
            lib.ecitygml_Solid_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Solid.SolidCleaner(handle, Solid.lib));
    }

    companion object {
        internal val libClass: Class<SolidLib> = SolidLib::class.java
        internal val lib: SolidLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The geometry as a `Solid`, or none if it is another type (Rust: nested
        *`AbstractGeometryKind` variants).
        */
        fun tryFrom(geometry: AbstractGeometryKind): Solid? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(geometry);
            
            val returnVal = lib.ecitygml_Solid_try_from(geometry.handle);
            val selfEdges: List<Any> = listOf(geometry)
            val handle = returnVal ?: return null
            val returnOpaque = Solid(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Solid_id(handle);
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
        
        val returnVal = lib.ecitygml_Solid_names(handle);
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
        
        val returnVal = lib.ecitygml_Solid_triangulate(handle);
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
    
    fun exterior(): Shell? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Solid_exterior(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Shell(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun interior(): ShellIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Solid_interior(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = ShellIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Volume of the exterior shell. Stricter than Rust, which skips shell members it can't
    *triangulate (and panics on some): fails with `UnresolvedReference` if a member is only an
    *`xlink:href`, and with `InvalidArgument` if a member can't be triangulated, so the volume is
    *never computed from an incomplete shell.
    */
    fun volume3d(): Result<Double> {
        
        val returnVal = lib.ecitygml_Solid_volume_3d(handle);
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
        
        val returnVal = lib.ecitygml_Solid_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }
    
    /** All positions of the exterior shell.
    */
    fun points(): DirectPositionIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Solid_points(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = DirectPositionIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }

}