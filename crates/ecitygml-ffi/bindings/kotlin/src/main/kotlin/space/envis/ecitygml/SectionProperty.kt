package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface SectionPropertyLib: Library {
    fun ecitygml_SectionProperty_destroy(handle: Pointer)
    fun ecitygml_SectionProperty_object(handle: Pointer): Pointer?
    fun ecitygml_SectionProperty_href(handle: Pointer): Pointer?
}
/** A section property (inline section and/or `xlink:href`), borrowed from a city model.
*/
class SectionProperty internal constructor (
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

    private class SectionPropertyCleaner(val handle: Pointer, val lib: SectionPropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_SectionProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, SectionProperty.SectionPropertyCleaner(handle, SectionProperty.lib));
    }

    companion object {
        internal val libClass: Class<SectionPropertyLib> = SectionPropertyLib::class.java
        internal val lib: SectionPropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline section; none if the property only references one via `href`.
    */
    fun object_(): Section? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SectionProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Section(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SectionProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}