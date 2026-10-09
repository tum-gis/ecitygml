package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractSpaceBoundaryPropertyLib: Library {
    fun ecitygml_AbstractSpaceBoundaryProperty_destroy(handle: Pointer)
    fun ecitygml_AbstractSpaceBoundaryProperty_object(handle: Pointer): Pointer?
    fun ecitygml_AbstractSpaceBoundaryProperty_href(handle: Pointer): Pointer?
}
/** A space boundary property (inline space boundary and/or `xlink:href`), borrowed from a city model.
*/
class AbstractSpaceBoundaryProperty internal constructor (
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

    private class AbstractSpaceBoundaryPropertyCleaner(val handle: Pointer, val lib: AbstractSpaceBoundaryPropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractSpaceBoundaryProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractSpaceBoundaryProperty.AbstractSpaceBoundaryPropertyCleaner(handle, AbstractSpaceBoundaryProperty.lib));
    }

    companion object {
        internal val libClass: Class<AbstractSpaceBoundaryPropertyLib> = AbstractSpaceBoundaryPropertyLib::class.java
        internal val lib: AbstractSpaceBoundaryPropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline space boundary; none if the property only references one via `href`.
    */
    fun object_(): AbstractSpaceBoundaryKind? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractSpaceBoundaryProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractSpaceBoundaryKind(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractSpaceBoundaryProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}