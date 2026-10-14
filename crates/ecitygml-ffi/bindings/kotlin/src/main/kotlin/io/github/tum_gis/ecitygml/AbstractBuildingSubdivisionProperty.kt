package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractBuildingSubdivisionPropertyLib: Library {
    fun ecitygml_AbstractBuildingSubdivisionProperty_destroy(handle: Pointer)
    fun ecitygml_AbstractBuildingSubdivisionProperty_object(handle: Pointer): Pointer?
    fun ecitygml_AbstractBuildingSubdivisionProperty_href(handle: Pointer): Pointer?
}
/** A building subdivision property (inline building subdivision and/or `xlink:href`), borrowed from a city model.
*/
class AbstractBuildingSubdivisionProperty internal constructor (
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

    private class AbstractBuildingSubdivisionPropertyCleaner(val handle: Pointer, val lib: AbstractBuildingSubdivisionPropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractBuildingSubdivisionProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractBuildingSubdivisionProperty.AbstractBuildingSubdivisionPropertyCleaner(handle, AbstractBuildingSubdivisionProperty.lib));
    }

    companion object {
        internal val libClass: Class<AbstractBuildingSubdivisionPropertyLib> = AbstractBuildingSubdivisionPropertyLib::class.java
        internal val lib: AbstractBuildingSubdivisionPropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline building subdivision; none if the property only references one via `href`.
    */
    fun object_(): AbstractBuildingSubdivisionKind? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractBuildingSubdivisionProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractBuildingSubdivisionKind(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractBuildingSubdivisionProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}