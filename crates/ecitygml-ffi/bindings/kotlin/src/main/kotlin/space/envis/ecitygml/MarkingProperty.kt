package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface MarkingPropertyLib: Library {
    fun ecitygml_MarkingProperty_destroy(handle: Pointer)
    fun ecitygml_MarkingProperty_object(handle: Pointer): Pointer?
    fun ecitygml_MarkingProperty_href(handle: Pointer): Pointer?
}
/** A marking property (inline marking and/or `xlink:href`), borrowed from a city model.
*/
class MarkingProperty internal constructor (
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

    private class MarkingPropertyCleaner(val handle: Pointer, val lib: MarkingPropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_MarkingProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, MarkingProperty.MarkingPropertyCleaner(handle, MarkingProperty.lib));
    }

    companion object {
        internal val libClass: Class<MarkingPropertyLib> = MarkingPropertyLib::class.java
        internal val lib: MarkingPropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline marking; none if the property only references one via `href`.
    */
    fun object_(): Marking? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_MarkingProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Marking(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_MarkingProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}