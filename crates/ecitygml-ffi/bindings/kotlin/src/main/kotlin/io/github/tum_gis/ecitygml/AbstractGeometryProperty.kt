package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractGeometryPropertyLib: Library {
    fun ecitygml_AbstractGeometryProperty_destroy(handle: Pointer)
    fun ecitygml_AbstractGeometryProperty_object(handle: Pointer): Pointer?
    fun ecitygml_AbstractGeometryProperty_href(handle: Pointer): Pointer?
}
/** A geometry property (inline geometry and/or `xlink:href`), borrowed from a city model.
*/
class AbstractGeometryProperty internal constructor (
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

    private class AbstractGeometryPropertyCleaner(val handle: Pointer, val lib: AbstractGeometryPropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractGeometryProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractGeometryProperty.AbstractGeometryPropertyCleaner(handle, AbstractGeometryProperty.lib));
    }

    companion object {
        internal val libClass: Class<AbstractGeometryPropertyLib> = AbstractGeometryPropertyLib::class.java
        internal val lib: AbstractGeometryPropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline geometry; none if the property only references one via `href`.
    */
    fun object_(): AbstractGeometryKind? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractGeometryProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractGeometryKind(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractGeometryProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}