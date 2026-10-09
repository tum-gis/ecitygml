package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AuxiliaryTrafficSpacePropertyLib: Library {
    fun ecitygml_AuxiliaryTrafficSpaceProperty_destroy(handle: Pointer)
    fun ecitygml_AuxiliaryTrafficSpaceProperty_object(handle: Pointer): Pointer?
    fun ecitygml_AuxiliaryTrafficSpaceProperty_href(handle: Pointer): Pointer?
}
/** A auxiliary traffic space property (inline auxiliary traffic space and/or `xlink:href`), borrowed from a city model.
*/
class AuxiliaryTrafficSpaceProperty internal constructor (
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

    private class AuxiliaryTrafficSpacePropertyCleaner(val handle: Pointer, val lib: AuxiliaryTrafficSpacePropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_AuxiliaryTrafficSpaceProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AuxiliaryTrafficSpaceProperty.AuxiliaryTrafficSpacePropertyCleaner(handle, AuxiliaryTrafficSpaceProperty.lib));
    }

    companion object {
        internal val libClass: Class<AuxiliaryTrafficSpacePropertyLib> = AuxiliaryTrafficSpacePropertyLib::class.java
        internal val lib: AuxiliaryTrafficSpacePropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline auxiliary traffic space; none if the property only references one via `href`.
    */
    fun object_(): AuxiliaryTrafficSpace? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficSpaceProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AuxiliaryTrafficSpace(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficSpaceProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}