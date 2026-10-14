package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractFillingSurfacePropertyLib: Library {
    fun ecitygml_AbstractFillingSurfaceProperty_destroy(handle: Pointer)
    fun ecitygml_AbstractFillingSurfaceProperty_object(handle: Pointer): Pointer?
    fun ecitygml_AbstractFillingSurfaceProperty_href(handle: Pointer): Pointer?
}
/** A filling surface property (inline filling surface and/or `xlink:href`), borrowed from a city model.
*/
class AbstractFillingSurfaceProperty internal constructor (
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

    private class AbstractFillingSurfacePropertyCleaner(val handle: Pointer, val lib: AbstractFillingSurfacePropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractFillingSurfaceProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractFillingSurfaceProperty.AbstractFillingSurfacePropertyCleaner(handle, AbstractFillingSurfaceProperty.lib));
    }

    companion object {
        internal val libClass: Class<AbstractFillingSurfacePropertyLib> = AbstractFillingSurfacePropertyLib::class.java
        internal val lib: AbstractFillingSurfacePropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline filling surface; none if the property only references one via `href`.
    */
    fun object_(): AbstractFillingSurfaceKind? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractFillingSurfaceProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractFillingSurfaceKind(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractFillingSurfaceProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}