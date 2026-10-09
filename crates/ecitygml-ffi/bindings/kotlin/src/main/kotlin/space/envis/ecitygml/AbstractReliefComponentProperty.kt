package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractReliefComponentPropertyLib: Library {
    fun ecitygml_AbstractReliefComponentProperty_destroy(handle: Pointer)
    fun ecitygml_AbstractReliefComponentProperty_object(handle: Pointer): Pointer?
    fun ecitygml_AbstractReliefComponentProperty_href(handle: Pointer): Pointer?
}
/** A relief component property (inline relief component and/or `xlink:href`), borrowed from a city model.
*/
class AbstractReliefComponentProperty internal constructor (
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

    private class AbstractReliefComponentPropertyCleaner(val handle: Pointer, val lib: AbstractReliefComponentPropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractReliefComponentProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractReliefComponentProperty.AbstractReliefComponentPropertyCleaner(handle, AbstractReliefComponentProperty.lib));
    }

    companion object {
        internal val libClass: Class<AbstractReliefComponentPropertyLib> = AbstractReliefComponentPropertyLib::class.java
        internal val lib: AbstractReliefComponentPropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline relief component; none if the property only references one via `href`.
    */
    fun object_(): AbstractReliefComponentKind? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractReliefComponentProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractReliefComponentKind(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractReliefComponentProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}