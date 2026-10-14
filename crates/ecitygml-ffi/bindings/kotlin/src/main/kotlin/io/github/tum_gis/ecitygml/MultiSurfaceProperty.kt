package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface MultiSurfacePropertyLib: Library {
    fun ecitygml_MultiSurfaceProperty_destroy(handle: Pointer)
    fun ecitygml_MultiSurfaceProperty_object(handle: Pointer): Pointer?
    fun ecitygml_MultiSurfaceProperty_href(handle: Pointer): Pointer?
}
/** A multi-surface property (inline multi surface and/or `xlink:href`), borrowed from a city model.
*/
class MultiSurfaceProperty internal constructor (
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

    private class MultiSurfacePropertyCleaner(val handle: Pointer, val lib: MultiSurfacePropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_MultiSurfaceProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, MultiSurfaceProperty.MultiSurfacePropertyCleaner(handle, MultiSurfaceProperty.lib));
    }

    companion object {
        internal val libClass: Class<MultiSurfacePropertyLib> = MultiSurfacePropertyLib::class.java
        internal val lib: MultiSurfacePropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline multi surface; none if the property only references one via `href`.
    */
    fun object_(): MultiSurface? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_MultiSurfaceProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiSurface(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_MultiSurfaceProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}