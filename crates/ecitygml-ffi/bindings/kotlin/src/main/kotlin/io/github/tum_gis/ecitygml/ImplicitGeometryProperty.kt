package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface ImplicitGeometryPropertyLib: Library {
    fun ecitygml_ImplicitGeometryProperty_destroy(handle: Pointer)
    fun ecitygml_ImplicitGeometryProperty_object(handle: Pointer): Pointer?
    fun ecitygml_ImplicitGeometryProperty_href(handle: Pointer): Pointer?
}
/** An implicit geometry property (inline implicit geometry and/or `xlink:href`), borrowed from a city model.
*/
class ImplicitGeometryProperty internal constructor (
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

    private class ImplicitGeometryPropertyCleaner(val handle: Pointer, val lib: ImplicitGeometryPropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_ImplicitGeometryProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, ImplicitGeometryProperty.ImplicitGeometryPropertyCleaner(handle, ImplicitGeometryProperty.lib));
    }

    companion object {
        internal val libClass: Class<ImplicitGeometryPropertyLib> = ImplicitGeometryPropertyLib::class.java
        internal val lib: ImplicitGeometryPropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline implicit geometry; none if the property only references one via `href`.
    */
    fun object_(): ImplicitGeometry? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ImplicitGeometryProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = ImplicitGeometry(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ImplicitGeometryProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}