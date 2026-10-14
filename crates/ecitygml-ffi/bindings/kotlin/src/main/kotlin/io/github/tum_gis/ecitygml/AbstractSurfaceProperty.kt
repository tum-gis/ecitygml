package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractSurfacePropertyLib: Library {
    fun ecitygml_AbstractSurfaceProperty_destroy(handle: Pointer)
    fun ecitygml_AbstractSurfaceProperty_object(handle: Pointer): Pointer?
    fun ecitygml_AbstractSurfaceProperty_href(handle: Pointer): Pointer?
}
/** A surface property (inline surface and/or `xlink:href`), borrowed from a city model.
*/
class AbstractSurfaceProperty internal constructor (
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

    private class AbstractSurfacePropertyCleaner(val handle: Pointer, val lib: AbstractSurfacePropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractSurfaceProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractSurfaceProperty.AbstractSurfacePropertyCleaner(handle, AbstractSurfaceProperty.lib));
    }

    companion object {
        internal val libClass: Class<AbstractSurfacePropertyLib> = AbstractSurfacePropertyLib::class.java
        internal val lib: AbstractSurfacePropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline surface; none if the property only references one via `href`.
    */
    fun object_(): AbstractSurfaceKind? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractSurfaceProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractSurfaceKind(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractSurfaceProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}