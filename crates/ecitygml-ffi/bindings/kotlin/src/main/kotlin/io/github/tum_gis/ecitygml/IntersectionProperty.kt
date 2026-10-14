package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface IntersectionPropertyLib: Library {
    fun ecitygml_IntersectionProperty_destroy(handle: Pointer)
    fun ecitygml_IntersectionProperty_object(handle: Pointer): Pointer?
    fun ecitygml_IntersectionProperty_href(handle: Pointer): Pointer?
}
/** A intersection property (inline intersection and/or `xlink:href`), borrowed from a city model.
*/
class IntersectionProperty internal constructor (
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

    private class IntersectionPropertyCleaner(val handle: Pointer, val lib: IntersectionPropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_IntersectionProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, IntersectionProperty.IntersectionPropertyCleaner(handle, IntersectionProperty.lib));
    }

    companion object {
        internal val libClass: Class<IntersectionPropertyLib> = IntersectionPropertyLib::class.java
        internal val lib: IntersectionPropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline intersection; none if the property only references one via `href`.
    */
    fun object_(): Intersection? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_IntersectionProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Intersection(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_IntersectionProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}